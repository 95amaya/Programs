#!/usr/bin/env python
"""
Parallel HelloWorld using mpy4py python
wrapper for mpi. To run, type command:
mpiexec -n 1 python HelloWorld.py
"""

from mpi4py import MPI
import sys

size = MPI.COMM_WORLD.Get_size()
rank = MPI.COMM_WORLD.Get_rank()
name = MPI.Get_processor_name()

sys.stdout.write( 
    "Hello Parallel World! I am process %d of %d on %s.\n"
    % (rank, size, name))


