#!/usr/bin/env python 

import numpy as np
import pylab
import sys

myfile = open(sys.argv[1])

data = np.genfromtxt(myfile, delimiter=",", unpack=True)
print data

x = np.arange(-64,64,1)
#for i in x:
#    i = i * 2*3.14159*8/128
pylab.plot(x, data[0], '-', x, data[1], '-', x, data[2])
pylab.xlabel('u')
pylab.ylabel('F(u)')
pylab.title('Function Frequency Domain')
pylab.legend(('Real', 'imaginary', 'magnitude'))
pylab.show()

