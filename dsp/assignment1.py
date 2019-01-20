
import numpy as np

def scaled_fft_db(x):
    """ ASSIGNMENT 1

        Computes the FFT of the input buffer windowed by a Hann window, scales
        the output so that the maximum is at 96 dB. The output should be in
        decibels.

        Arguments:
        x: Input buffer.

        Returns:
        X: The FFT of x (windowed by Hanning window) in dB, scaled to have maximum at 96 dB.
    """

    # Your code goes here
    t = np.arange(512)
    hann = 1 - np.cos(NPY_PI_2 * t / 511)
    y = hann * x
    X = np.fft.fft(y)
    X = X / 512
    
    return X
