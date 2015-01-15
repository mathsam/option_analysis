A suite of tool to do financial analyses. Focus on option pricing and volatility analysis.
Mainly uses Monte Carlo simulation for option pricing. 

Contains:

Random number generator class
Pathgeneration class which generates geometric brownian motion
Matrix class to do Linear algebra
Option class
Base function class
Least square Monte Carlo simulation class
...

Usage:

in the current directory, type

    make -f makefile_ctypes

to build a shared library ./bin/least_square_mc_lib.so. In ./bin, there is a 
Python wrapper which uses this shared library.

Tests for each classes are in ./src/test
