import ctypes
from numpy.ctypeslib import ndpointer


def get_rand_int(num, seed):
    """a python wrapper for C++ code
    return num random integers with seed"""
    randlib = ctypes.CDLL('./myrandlib.so')
    num  = int(num)
    seed = int(seed)
    randlib.n_rand.restype = ndpointer(dtype=ctypes.c_int, shape=(num,))
    randarray = randlib.n_rand(num, seed)
    return randarray

def get_rand_uniform(num, seed):
    """a python wrapper for C++ code
    return num uniformly distributed random number within (0,1)  with seed"""
    randlib = ctypes.CDLL('./myrandlib.so')
    num  = int(num)
    seed = int(seed)
    randlib.uniform_rand.restype = ndpointer(dtype=ctypes.c_double, shape=(num,))
    randarray = randlib.uniform_rand(num, seed)
    return randarray

def get_rand_normal(num, seed):
    """a python wrapper for C++ code
    return num normaly distributed random number with seed"""
    randlib = ctypes.CDLL('./myrandlib.so')
    num  = int(num)
    seed = int(seed)
    randlib.norm_rand.restype = ndpointer(dtype=ctypes.c_double, shape=(num,))
    randarray = randlib.norm_rand(num, seed)
    return randarray
