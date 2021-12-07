import numpy as np

def solve1(path):
    x = np.loadtxt(path, delimiter=',')
    m = np.median(x)
    return int(np.abs(x-m).sum())

def solve2(path):
    x = np.loadtxt(path, delimiter=',')
    m = np.round(x.sum() / x.shape[0] - .5)
    cost = lambda y: y*(y+1)/2
    return int(cost(np.abs(x-m)).sum())