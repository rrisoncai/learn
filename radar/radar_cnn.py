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
        c_min = max(c_max - width - delta, 0)
    
        print(str(c_max-c_min) + ',' + str(r_max-r_min))
        if (r_max - r_min < width) or (c_max - c_min < width):
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
        c_min = max(c_max - width - delta, 0)
    
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

y_train = np_utils.to_categorical(y_train, num_classes)
y_val = np_utils.to_categorical(y_val, num_classes)

# index = np.arange(len(X_train))
# np.random.shuffle(index)
# X_train = X_train[index]
# y_train = y_train[index]

for i in range(len(X_train)):
    img = X_train[i]
    plt.imshow(img[:,:,0])
    plt.title(str(np.argmax(y_train[i])))
    plt.pause(1)
