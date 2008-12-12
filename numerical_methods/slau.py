from numpy.linalg import det
from numpy.core import *

def kramer(a, b):
    d = det(a)
    x = []
    for j in xrange(1, len(b)+1):
        aj = a.copy()
        for k in xrange(1, len(b)+1):
            aj[k-1][j-1] = b[k-1]
        dj = det(aj)
        x.append(1.0*dj/d)
    return x
