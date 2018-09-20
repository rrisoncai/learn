import tensorflow as tf
import numpy as np

from tensorflow.examples.tutorials.mnist import input_data

# load mnist data
mnist = input_data.read_data_sets("~/tf/datasets/mnist/", one_hot=True)

print("training datda size: ", mnist.train.num_examples)
print("validation data size: ", mnist.validation.num_examples)
print("Testing data size: ", mnist.test.num_examples)
# print("Example training data: ", mnist.train.images[0])
# print("Example training data label: ", mnist.train.labels[0])