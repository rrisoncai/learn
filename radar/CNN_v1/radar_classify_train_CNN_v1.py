import tensorflow as tf
import numpy as np
from tensorflow.python.ops import variables
from tensorflow.contrib import rnn

import scipy.io

import win_unicode_console
win_unicode_console.enable()

import os
import time
PROCESS = time.strftime("%Y%m%d_%H%M%S")

from radar_classify_network_CNN_v1 import *

ROOTDIR = 'D:\\radar\\'

DATADIR =  ROOTDIR + "data\\CNN_input\\output\\"
SAVEDIR = ROOTDIR + 'save\\'
WRITERDIR = ROOTDIR + 'writer\\'

SAVEPATH = SAVEDIR + PROCESS + '\\'
WRITERPATH = WRITERDIR + PROCESS + '\\'

train_tfrecord = DATADIR + "train.tfrecord"

if not os.path.exists( SAVEPATH ):
    os.makedirs( SAVEPATH )

if not os.path.exists( WRITERPATH ):
    os.makedirs( WRITERPATH )


BATCH_SIZE = 300
BATCH_CAPACITY = 2000
MIN_AFTER_DEQU = 1000


def read_and_decode(filename):
    filename_queue = tf.train.string_input_producer([filename])
    reader = tf.TFRecordReader()
    _, serialized_example = reader.read(filename_queue)
    features = tf.parse_single_example(serialized_example,
                                       features={
                                           'label': tf.FixedLenFeature([], tf.string),
                                           'radar_data': tf.FixedLenFeature([], tf.string),
                                       })
    radar_train_data = tf.decode_raw(features['radar_data'], tf.float32 )
    radar_train_data = tf.reshape(radar_train_data, [frame_size, chirp_size, channel_size])
    radar_train_data = tf.cast(radar_train_data, tf.float32)
    
    label = tf.decode_raw(features['label'], tf.int32)
    label = tf.reshape(label, [1])
    return radar_train_data, label


if __name__ == '__main__':

    # graph
    
    # train
    tf.reset_default_graph()
    
    with tf.name_scope('input_train'):
    
        radar_train_data, radar_train_label = read_and_decode(train_tfrecord)
        radar_train_batch_data, radar_train_batch_label = tf.train.shuffle_batch([radar_train_data, radar_train_label],batch_size=BATCH_SIZE, capacity=BATCH_CAPACITY, min_after_dequeue=MIN_AFTER_DEQU)
        #radar_train_batch_label_oh = tf.one_hot(radar_train_batch_label, class_size)
        #radar_train_batch_label_list = tf.unstack(radar_train_batch_label, num = RNN_train_steps, axis=1)
        #radar_train_batch_data_reshape = tf.reshape(radar_train_batch_data, [BATCH_SIZE, frame_size, chirp_size, channel_size])
        radar_train_batch_label = tf.reshape(radar_train_batch_label,[BATCH_SIZE])
    
    with tf.name_scope('CNN_train'):
        CNN_logits_train = CNN_cell(radar_train_batch_data)
    
    
    with tf.name_scope('loss_train'):
        train_loss = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=radar_train_batch_label, logits=CNN_logits_train)
        total_train_loss = tf.reduce_mean(train_loss)
    
    with tf.name_scope("train"):
        train_step = tf.train.AdamOptimizer(0.001).minimize(total_train_loss)
    
    
    # sess
    
    init = tf.global_variables_initializer()
    saver = tf.train.Saver(max_to_keep=0)
    graph = tf.get_default_graph()
    
    with tf.Session() as sess:
    
        sess.run(init)
        
        writer = tf.summary.FileWriter( WRITERPATH )
        writer.add_graph(sess.graph)
        
        coord = tf.train.Coordinator()
        threads = tf.train.start_queue_runners(sess=sess, coord=coord)
        try:
            while not coord.should_stop():
                loss=0.
                for i in range(50000):
                    _, loss_result = sess.run([train_step, total_train_loss])
                    loss += loss_result
                    if (i+1)%20==0:
                        print('step:',i+1)
                        print('loss:', loss/10)
                        loss=0.
                        
                    if i % 100 == 0 and i >0:
                        save_path = saver.save(sess, SAVEPATH + "step" + '_' + str(i) + ".ckpt")
            
        except tf.errors.OutOfRangeError:
            print('finished')
        finally:
            coord.request_stop()
        coord.join(threads)
        sess.close()







'''
    # test
    
    CNN_outputs_test = CNN_cell(radar_train_data_reshape, True)
    
    with tf.name_scope("TimePool_test"):
        CNN_logits_reshape_test = tf.reshape(CNN_outputs_test, [1, time_pool_size, state_size])
        CNN_logits_TimePool_test = tf.layers.max_pooling1d(inputs = CNN_logits_reshape_test, pool_size = time_pool_size, strides = time_pool_size)
    
    with tf.name_scope("RNN_input_reshape_test"):
        RNN_input_reshape_test = tf.reshape(CNN_logits_TimePool_train, [1, state_size])
    
    with tf.variable_scope("RNN_state", reuse = tf.AUTO_REUSE):
        RNN_state_test = tf.get_variable("RNN_state_test", [state_size], initializer=tf.constant_initializer(0.0))
    
    with tf.name_scope("RNN_cell_test"):
        updated_RNN_state_test = RNN_cell(RNN_input_reshape_test, RNN_state_test)
        Update_RNN_state_test = RNN_state_test.assign(updated_RNN_state_test)
    
    with tf.name_scope("RNN_softmax_test"):
        with tf.control_dependencies(Update_RNN_state_test):
            RNN_logits_test = RNN_softmax(RNN_state_test)
        with tf.name_scope("RNN_cell_train"):
        init_state = tf.zeros([BATCH_SIZE, state_size])
        state = init_state
        RNN_state_train = []
        for rnn_input_train in RNN_inputs_train:
            state = LSTM_cell(rnn_input_train, state)
            RNN_state_train.append(state)
        final_state_train = RNN_state_train[-1]
    
'''
    