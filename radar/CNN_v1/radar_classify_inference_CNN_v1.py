import tensorflow as tf
import numpy as np
from tensorflow.python.ops import variables
from tensorflow.contrib import rnn

import scipy.io as sio

import win_unicode_console
win_unicode_console.enable()

import os
import time
PROCESS = time.strftime("%Y%m%d_%H%M%S")

from radar_classify_network_CNN_v1 import *

ROOTDIR = 'D:\\radar\\'

DATADIR =  ROOTDIR + "data\\"
SAVEDIR = ROOTDIR + 'save\\'
WRITERDIR = ROOTDIR + 'writer\\'
OUTPUTDIR = ROOTDIR + 'output\\'

TESTDATADIR =  DATADIR + "test\\"
TESTOUTPUTDIR =  OUTPUTDIR + "test\\"

TESTOUTPUTPATH = TESTOUTPUTDIR + PROCESS + '/'
if not os.path.exists( TESTOUTPUTPATH ):
    os.makedirs( TESTOUTPUTPATH )

SAVEFILE = SAVEDIR + "20180731_052255\\step_7300.ckpt"

if __name__ == '__main__':

    # graph
    
    # inference
    tf.reset_default_graph()
    
    test_data_name_list = []
    filename_list = []
    
    for _,_,filenames in os.walk(TESTDATADIR):
        for filename in filenames:
            filename_split = os.path.splitext(filename)
            
            ext = filename_split[1]
            if ext == '.mat':
                name = filename_split[0]
                nameparse = name.split("_")
                groundtruth = nameparse[0]
                test_data_name = name
                test_data_name_list.append(test_data_name)
                filename_list.append(filename)
    BATCH_SIZE_inference = len(filename_list)
    radar_inference_batch_data = np.zeros([BATCH_SIZE_inference, frame_size, chirp_size, channel_size],dtype=np.float32)
    ground_truth = np.zeros([BATCH_SIZE_inference],dtype=np.int32)
    for filename_iter in range(BATCH_SIZE_inference):
        matdata = sio.loadmat(TESTDATADIR + filename_list[filename_iter])
        radar_inference_batch_data[filename_iter,:,:,:] = matdata['radar_data']
        ground_truth[filename_iter] = matdata['ground_truth']
    
    radar_inference_batch_data_placeholder = tf.placeholder(dtype = tf.float32,shape=[BATCH_SIZE_inference, frame_size, chirp_size, channel_size])
    
    with tf.name_scope("CNN_inference"):
        CNN_logits_inference = CNN_cell(radar_inference_batch_data_placeholder, tf.AUTO_REUSE)
    
    with tf.name_scope("softmax_inference"):
        CNN_softmax_inference = tf.nn.softmax(CNN_logits_inference)
    
    # sess
    
    init = tf.global_variables_initializer()
    saver = tf.train.Saver()
    graph = tf.get_default_graph()

    with tf.Session() as sess:
        saver.restore(sess,SAVEFILE)
        ground_truth_inference_batch_onehot = sess.run(CNN_softmax_inference, feed_dict={radar_inference_batch_data_placeholder:radar_inference_batch_data})
        
        sess.close()
    
    for filename_iter in range(BATCH_SIZE_inference):
        sio.savemat( TESTOUTPUTPATH + filename_list[filename_iter] + '_test_result.mat',{'ground_truth_inference_onehot': ground_truth_inference_batch_onehot[filename_iter,:],'ground_truth': ground_truth[filename_iter]},'-v6')

    
