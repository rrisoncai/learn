import tensorflow as tf
import numpy as np


chirp_size = 256
frame_size = 180
channel_size = 3
#state_size = 4
#time_steps = 115*4
#time_pool_size = 4
#RNN_train_steps = 115

inner_class_size_1=20
inner_class_size_2=10
class_size=5

#lstm_size = 12



def CNN_cell(CNN_inputs, reuse = tf.AUTO_REUSE):
    
    with tf.variable_scope("CNN", reuse = reuse):
        with tf.variable_scope("conv_1"):
            conv2d_1_1 = tf.layers.conv2d(inputs=CNN_inputs, filters=8, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            conv2d_1_2 = tf.layers.conv2d(inputs=conv2d_1_1, filters=8, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            conv2d_1_3 = tf.layers.conv2d(inputs=conv2d_1_2, filters=8, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            pool2d_1 = tf.layers.max_pooling2d(conv2d_1_3, pool_size=[3, 3], strides=[2, 2], padding='same')
        with tf.variable_scope("conv_2"):
            conv2d_2_1 = tf.layers.conv2d(inputs=pool2d_1, filters=16, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            conv2d_2_2 = tf.layers.conv2d(inputs=conv2d_2_1, filters=16, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            conv2d_2_3 = tf.layers.conv2d(inputs=conv2d_2_2, filters=16, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            pool2d_2 = tf.layers.max_pooling2d(conv2d_2_3, pool_size=[3, 3], strides=[2, 2], padding='same')
        with tf.variable_scope("conv_3"):
            conv2d_3_1 = tf.layers.conv2d(inputs=pool2d_2, filters=16, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            conv2d_3_2 = tf.layers.conv2d(inputs=conv2d_3_1, filters=16, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            conv2d_3_3 = tf.layers.conv2d(inputs=conv2d_3_2, filters=16, kernel_size=[5, 5], padding="same", activation=tf.nn.relu)
            pool2d_3 = tf.layers.max_pooling2d(conv2d_3_3, pool_size=[3, 3], strides=[2, 2], padding='same')
        with tf.variable_scope("FC"):
            CNN_Flatten = tf.reshape(pool2d_3, [-1, pool2d_3.shape[1] * pool2d_3.shape[2] * pool2d_3.shape[3]])
            CNN_Dense_1 = tf.layers.dense(inputs = CNN_Flatten, units = inner_class_size_1, activation = tf.nn.relu)
            CNN_Dense_2 = tf.layers.dense(inputs = CNN_Dense_1, units = inner_class_size_2, activation = tf.nn.relu)
            CNN_logits = tf.layers.dense(inputs = CNN_Dense_2, units = class_size, activation = tf.nn.relu)
    return CNN_logits


