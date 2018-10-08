import tensorflow as tf
import matplotlib.pyplot as plt

image_raw_data = tf.gfile.FastGFile('img.jpg', 'rb').read()

with tf.Session() as sess:
    img_data = tf.image.decode_jpeg(image_raw_data)
    print(img_data.eval())

    plt.imshow(img_data.eval())
    # plt.show()
    plt.waitforbuttonpress()

    img_data = tf.image.convert_image_dtype(img_data, dtype=tf.float32)
    # encoded_image = tf.image.encode_jpeg(img_data)
    # with tf.gfile.GFile('img_write.jpg', 'wb') as f:
        # f.write(encoded_image.eval())

    # resize image
    resized = tf.image.resize_images(img_data, (300, 300), method=0)
    # print(img_data.get_shape())
    plt.imshow(resized.eval())
    plt.waitforbuttonpress()

    # image padding or crop
    croped = tf.image.resize_image_with_crop_or_pad(img_data, 500, 500)
    padded = tf.image.resize_image_with_crop_or_pad(img_data, 3000, 3000)
    plt.imshow(croped.eval())
    plt.waitforbuttonpress()
    plt.imshow(padded.eval())
    plt.waitforbuttonpress()

    # image flip
    flipped = tf.image.flip_up_down(img_data)
    plt.imshow(flipped.eval())
    plt.waitforbuttonpress()

    flipped = tf.image.flip_left_right(img_data)
    plt.imshow(flipped.eval())
    plt.waitforbuttonpress()

    transposed = tf.image.transpose_image(img_data)
    plt.imshow(transposed.eval())
    plt.waitforbuttonpress()

    # set brightness
    adjusted = tf.image.adjust_brightness(img_data, -0.5)
    plt.imshow(adjusted.eval())
    plt.waitforbuttonpress()

    # set contrast
    adjusted = tf.image.adjust_contrast(img_data, -5)
    plt.imshow(adjusted.eval())
    plt.waitforbuttonpress()


































