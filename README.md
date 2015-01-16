A suite of tool to do financial analyses. Focus on option pricing using Monte 
arlo simulation.

Contains:

Random number generator class; 
Pathgeneration class which generates geometric brownian motion; 
Matrix class to do Linear algebra; 
Option class; 
Base function class; 
Least square Monte Carlo simulation class; 
...

Tests for each classes are in ./src/test


Currently, implemented an interface to price American option and a Python 
wrapper for it. More different kinds of options can be implemented easily in 
using this library.

Usage:

in the current directory, type

    make -f makefile_ctypes

to build a shared library ./bin/least_square_mc_lib.so. In ./bin, there is a 
Python wrapper american_put_pricer.py which uses this shared library. To use 
this wrapper, in Python, type

    from american_put_pricer import american_put
    C = american_put(volatility, interest_rate, divident, expiry, strike, spot)

See the wrapper file for details.

