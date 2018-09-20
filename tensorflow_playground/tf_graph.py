# -*- coding: utf-8 -*-
import tensorflow as tf

g1 = tf.Graph()
with g1.as_default():
    v = tf.get_variable(
        'v', shape=[1], initializer=tf.zeros_initializer()
    )

g2 = tf.Graph()
with g2.as_default():
    v = tf.get_variable(
        'v', shape=[1], initializer=tf.ones_initializer()
    )

with tf.Session(graph=g1) as sess:
    # tf.initialize_all_variables().run()
    tf.global_variables_initializer().run()
    with tf.variable_scope('', reuse=True):
        print('\t\tg1\n')
        print(sess.run(tf.get_variable('v')))

with tf.Session(graph=g2) as sess:
    tf.global_variables_initializer().run()
    # tf.initialize_all_variables().run()
    with tf.variable_scope('', reuse=True):
        print('\t\tg2\n')
        print(sess.run(tf.get_variable('v')))

# set graph on GPU device
g = tf.Graph()

with g.device('/gpu:0'):
    a = tf.constant(1, name='a')
    b = tf.constant(2.0, name='b')
    result = a + b