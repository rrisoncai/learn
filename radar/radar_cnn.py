from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential, load_model
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D, Conv2D
from keras.optimizers import SGD, RMSprop
from keras.utils import np_utils, generic_utils
from keras.callbacks import TensorBoard
from keras import backend as K


import tensorflow as tf
import os
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.pyplot as pyplot

import numpy as np
import scipy.io
from PIL import Image
from sklearn.cross_validation import train_test_split
from sklearn import cross_validation
from sklearn import preprocessing
from IPython import display
from datetime import datetime
import time
import random

img_rows, img_cols, img_depth = 128, 128, 3

root_dir = 'dataset/train/'
listing = os.listdir(root_dir)
listing = sorted(listing)

classes = {'none':0, 'left':1, 'right':2, 'click':3, 'wrist':4}
gs_class = {'left', 'right', 'click', 'wrist'}
num_classes = len(classes)

def set_groundtruth(filename):
    gs_class = {'left', 'right', 'click', 'wrist'}
    gt = 'none'
    for i in gs_class:
        idx = filename.find(i)
        if idx != -1:
            gt = i
            return gt

def generate_data_from_folder(root_dir):
    X = []
    y = []

    listing = os.listdir(root_dir)
    listing = sorted(listing)
    width = 128 # input image shape = [width, width, 3]
    delta = 12 # 12*0.625cm = 7.5cm
    esp = 1e-6

    for file in listing:

        # set ground truth
        gt = set_groundtruth(file)

        file = root_dir + file
        data = scipy.io.loadmat(file)

        raw = data['raw']
        label = data['label']
        speed = data['speed']
        phase = data['phase']
        mask = data['mask']

        label_mask = (label != 0)
        label_sum = np.sum(label_mask) # total frames of labels

        gs_mask = mask[label_mask[:,0], :]
        gs_window = np.sum(gs_mask, 0) / label_sum
        maxval = np.max(gs_window[width:])
        maxidx = np.argmax(gs_window[width:])

        if maxval < 0.3:
            continue

        gesture_index, b = np.nonzero(label)

        # set gesture region, [r_min:r_max, c_min:c_max]
        r_min, r_max = gesture_index[0], gesture_index[-1]
        r_min = max(r_min - delta, 0)
        r_max = max(r_min + width + delta, r_max)
        r_max = min(r_max, len(label))

        body_pos = maxidx + width
        c_max = body_pos
        c_min = max(c_max - width -delta, 0)


        if (r_max - r_min < width) or (c_max - c_min < width):
            print(str(c_max-c_min) + ',' + str(r_max-r_min))
            continue

        raw_rdm = raw[r_min:r_max, c_min:c_max]
        maxval = np.max(np.abs(raw_rdm)) + esp
        raw_rdm = raw_rdm / maxval

        speed_rdm = speed[r_min:r_max, c_min:c_max]
        maxval = np.max(np.abs(speed_rdm)) + esp
        speed_rdm = speed_rdm / maxval

        phase_rdm = phase[r_min:r_max, c_min:c_max]
        maxval = np.max(np.abs(phase_rdm)) + esp
        phase_rdm = phase_rdm / maxval

        raw_input = np.zeros((r_max-r_min, c_max-c_min, 3))
        raw_input[:,:,0] = raw_rdm
        raw_input[:,:,1] = speed_rdm
        raw_input[:,:,2] = phase_rdm
        X.append(raw_input)
        y.append(classes[gt])

        # generate negtive samples
        if random.random() > 0.25:
            continue
        gt = 'none'
        r_min = int((gesture_index[0] + gesture_index[-1]) / 2)
        r_max = len(label)

        body_pos = maxidx + width
        c_max = body_pos
        c_min = max(c_max - width -delta, 0)

        if (r_max - r_min < width) or (c_max - c_min < width):
            print(str(c_max-c_min) + ',' + str(r_max-r_min))
            continue

        raw_rdm = raw[r_min:r_max, c_min:c_max]
        maxval = np.max(np.abs(raw_rdm)) + esp
        raw_rdm = raw_rdm / maxval

        speed_rdm = speed[r_min:r_max, c_min:c_max]
        maxval = np.max(np.abs(speed_rdm)) + esp
        speed_rdm = speed_rdm / maxval

        phase_rdm = phase[r_min:r_max, c_min:c_max]
        maxval = np.max(np.abs(phase_rdm)) + esp
        phase_rdm = phase_rdm / maxval

        raw_input = np.zeros((r_max-r_min, c_max-c_min, 3))
        raw_input[:,:,0] = raw_rdm
        raw_input[:,:,1] = speed_rdm
        raw_input[:,:,2] = phase_rdm

        X.append(raw_input)
        y.append(classes[gt])
    return np.array(X), np.array(y)

X_train, y_train = generate_data_from_folder('dataset/train/')
X_val, y_val = generate_data_from_folder('dataset/test/')

labels = np.zeros((5))
for i in range(0, 5):
    labels[i] = np.sum(y_train == i)

print('y_train label:')
for i in range(5):
    print(labels[i])

y_train = np_utils.to_categorical(y_train, num_classes)
y_val = np_utils.to_categorical(y_val, num_classes)

num_filters = [32, 32]
num_pool = [2, 4]
num_conv = [5, 3]

# X = X.astype('float32')

batch_size = 32
num_classes = 5
num_epoch = 50
train_size = len(X_train)
val_size = len(X_val)


K.clear_session()
model = Sequential()

model.add(Conv2D(8,
                 (3, 3),
                 input_shape=(128, 128, 3),
                 activation='relu',
                 padding='SAME'))
model.add(Conv2D(8,
                 (3, 3),
                 activation='relu',
                 padding='SAME'))
model.add(MaxPooling2D(pool_size=2))
model.add(Dropout(0.5))

model.add(Conv2D(16,
                 (3, 3),
                 activation='relu',
                 padding='SAME'))
model.add(Conv2D(16,
                 (3, 3),
                 activation='relu',
                 padding='SAME'))
model.add(MaxPooling2D(pool_size=2))
model.add(Dropout(0.5))

model.add(Conv2D(32,
                 (3, 3),
                 activation='relu',
                 padding='same'))
model.add(Conv2D(32,
                 (3, 3),
                 activation='relu',
                 padding='same'))
model.add(MaxPooling2D(pool_size=2))
model.add(Dropout(0.5))

model.add(Conv2D(32,
                 (3, 3),
                 activation='relu',
                 padding='same'))
model.add(Conv2D(32,
                 (3, 3),
                 activation='relu',
                 padding='same'))
model.add(MaxPooling2D(pool_size=2))
model.add(Dropout(0.5))

model.add(Conv2D(32,
                 (3, 3),
                 activation='relu',
                 padding='same'))
model.add(Conv2D(32,
                 (3, 3),
                 activation='relu',
                 padding='same'))
model.add(MaxPooling2D(pool_size=2))
model.add(Dropout(0.5))

model.add(Flatten())
model.add(Dense(40, kernel_initializer='normal', activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(num_classes, kernel_initializer='normal'))
model.add(Activation('softmax'))
model.compile(loss='categorical_crossentropy', optimizer='RMSprop', metrics=['mse', 'accuracy'])

model.summary()


def generate_val_data(x, y):
    list_x = []
    list_y = []
    count = 0
    index = np.arange(len(x))
    np.random.shuffle(index)
    x = x[index]
    y = y[index]

    for i in range(len(x)):
        raw = x[i]
        sz = raw.shape

        label = np.argmax(y[i,:])
        num = 50

        for j in range(num):
            r = random.randint(0, sz[0]-128)
            c = random.randint(0, sz[1]-128)
            list_x.append(raw[r:r+128,c:c+128,:])
            list_y.append(y[i])
    return np.array(list_x), np.array(list_y)

X_val_aug, y_val_aug = generate_val_data(X_val, y_val)

gt = np.zeros((5))
for i in range(len(y_val_aug)):
    label = np.argmax(y_val_aug[i,:])
    gt[label] += 1
gt


aug_num = 10

def generate_data(x, y, batch_size):
    list_x = []
    list_y = []
    count = 0
    index = np.arange(len(x))
    np.random.shuffle(index)
    x = x[index]
    y = y[index]

    while True:
        num = aug_num
        for j in range(num):
            for i in range(len(x)):
                raw = x[i]
                sz = raw.shape

                label = np.argmax(y[i,:])
                r = random.randint(0, sz[0]-128)
                c = random.randint(0, sz[1]-128)
                list_x.append(raw[r:r+128,c:c+128,:])
                list_y.append(y[i])
                count += 1
                if count >= batch_size:
                    yield (np.array(list_x), np.array(list_y))
                    count = 0
                    list_x = []
                    list_y = []

generator = generate_data(X_train, y_train, batch_size)

now = datetime.utcnow().strftime("%Y%m%d%H%M%S")
root_logdir = "tf_logs"
logdir = "{}/run-{}/".format(root_logdir, now)

hist = model.fit_generator(generator=generator,
                    validation_data=(X_val_aug, y_val_aug),
                    epochs=num_epoch,
                    steps_per_epoch=(train_size*aug_num)//batch_size,
#                     validation_steps=val_size//batch_size,
                    callbacks=[TensorBoard(log_dir=logdir)]
                   )


train_loss = hist.history['loss']
val_loss = hist.history['val_loss']
train_acc = hist.history['acc']
val_acc = hist.history['val_acc']

plt.plot(train_loss); plt.title('train loss')
plt.plot(val_loss); plt.title('val loss')
plt.legend(['train loss', 'val_loss'])

plt.plot(train_acc); plt.title('train acc')
plt.plot(val_acc); plt.title('val acc')
plt.legend(['train acc', 'val acc'])
plt.grid(True)
plt.ylim(0,1)

# save model
model_fn = 'keras_' + now + '.h5'
model.save(model_fn)


# inference
from keras.models import load_model
model_saved = load_model(model_fn)
pred = model_saved.predict(X_val_aug)
pred = np.argmax(pred, axis=1)
gt = np.argmax(y_val_aug, axis=1)

from sklearn.metrics import confusion_matrix
conf_mat = confusion_matrix(a, gt)
test_acc = np.sum(np.diag(conf_mat)) / np.sum(conf_mat)
print('test accuracy:', test_acc)
print(conf_mat)

diag = np.diag(conf_mat)
sum_axis0 = np.sum(conf_mat, axis=0)
sum_axis1 = np.sum(conf_mat, axis=1)

prec = diag / sum_axis0
recall = diag / sum_axis1

print(prec)
print(recall)
