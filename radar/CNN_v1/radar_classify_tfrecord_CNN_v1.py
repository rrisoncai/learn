import tensorflow as tf
import numpy as np
import os
import scipy.io as sio
import random


ROOTDIR = 'D:\\radar\\'
DATADIR =  ROOTDIR + "data\\"
RECORD_DATADIR =  DATADIR + "CNN_input\\output\\"


trainwriter= tf.python_io.TFRecordWriter( RECORD_DATADIR + "train.tfrecord")

for _, _, fs in os.walk(RECORD_DATADIR):
    
    fs_random=random.sample(fs, len(fs))
    
    for f in fs_random:
        if (os.path.splitext(f)[1] == '.mat'):
            
            data = sio.loadmat(RECORD_DATADIR + f)
            
            sample = tf.train.Example(features=tf.train.Features(feature={
            "label": tf.train.Feature(bytes_list=tf.train.BytesList(value=[(data['ground_truth']).astype(np.int32).tobytes()])),
            'radar_data': tf.train.Feature(bytes_list=tf.train.BytesList(value=[(data['radar_data']).astype(np.float32).tobytes()])),
            }))
            
            trainwriter.write(sample.SerializeToString())

trainwriter.close()
