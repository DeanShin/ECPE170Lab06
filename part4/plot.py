#!/usr/bin/python3

# Plotting tool for Memory Mountain program
# Jeff Shafer

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import matplotlib.pyplot as plt
import numpy as np
from io import StringIO
import sys

# Useful links:
#
# Importing data from file:
#  http://docs.scipy.org/doc/numpy/user/basics.io.genfromtxt.html
# 3D surface plotting:
#  http://matplotlib.sourceforge.net/examples/mplot3d/surface3d_demo.html

print("Processing data file " + sys.argv[1])

# Import data from text file:
#   delimeter=None:  Separate data elements by any white space
#   skip_header=3:   Ignore the first 3 lines in file (they're not data!)
#   usecols=(1-64):  Ignore the first column (col #0)
Z = np.genfromtxt(sys.argv[1], delimiter=None, skip_header=3,usecols=np.arange(1,65,1))
#print Z

# Prepare X and Y axis

# X axis is 1-64, inclusive 
# (representing stride of 1-64)
X = np.arange(1, 65, 1)
#print X

# Y axis is 0-14, inclusive
# (representing various total array sizes)
Y = np.arange(0, 15, 1)
Y_labels = ['32m','16m','8m','4m','2m','1024k','512k','256k','128k','64k','32k','16k','8k','4k','2k']
#print Y
#print Y_labels

# Plot it!
fig = plt.figure()
ax = fig.gca(projection='3d')
X, Y = np.meshgrid(X, Y)

surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.jet,
        linewidth=0, antialiased=True)
plt.xticks(range(0,65,8), size='small')
plt.xlabel("Access Stride")
plt.yticks(range(0,len(Y_labels),1), Y_labels, size='small')
plt.ylabel("Array Size (bytes)")
plt.title("Bandwidth (MB/sec)")

#ax.zaxis.set_major_locator(LinearLocator(10))
#ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

fig.colorbar(surf, shrink=0.5, aspect=5)

plt.show()

