#!/usr/bin/env python 

import numpy as np
import pylab
import sys

#myfile = open(sys.argv[1])

#data = np.genfromtxt(myfile, delimiter="\n")

x = np.arange(0,128,1)
#for i in x:
#    i = i * 2*3.14159*8/128
data = np.sin(x*2*3.14159*8/128)
pylab.plot(x, data)
pylab.xlabel('x')
pylab.ylabel('cos(x*2*pi*8x/N)')
pylab.title('Spatial Domain Cosine Function')
pylab.show()

