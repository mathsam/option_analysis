import ctypes
from numpy.ctypeslib import ndpointer


def get_n_rand_int(num, seed):
    """a python wrapper for C++ code
    return num random integers with seed"""
    randlib = ctypes.CDLL('./myrandlib.so')
    num  = int(num)
    seed = int(seed)
    randlib.n_rand.restype = ndpointer(dtype=ctypes.c_int, shape=(num,))
    randarray = randlib.n_rand(num, seed)
    return randarray
