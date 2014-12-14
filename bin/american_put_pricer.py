import ctypes
from ctypes import c_double
from ctypes import c_int

def american_put(v, r, d, T, strike, spot, 
                 num_paths = 1000, 
                 path_length=50,
                 num_bases = 6):
    """
    Evaulates price for American put option
    Inputs:

    v: volatility
    r: interest rate
    d: divident rate
    T: expiration time
    strike: strike price
    spot: spot price
    num_paths: number of brownian motion to be simulated
    path_length: number of discrititized excercise time 
    num_bases: number of base functions to be used
    
    return: price of the option"""

    lsmc_lib = ctypes.cdll.LoadLibrary('./least_square_mc_lib.so')
    pricer   = lsmc_lib.american_put
    pricer.restype = ctypes.c_double

    option_value = pricer(c_double(v), c_double(r), c_double(d), c_double(T),
                          c_double(strike), c_double(spot),
                          c_int(num_paths), c_int(path_length),
                          c_int(num_bases))
    return option_value
