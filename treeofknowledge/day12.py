import numpy as np
import pickle
import time

def read_day12(path):
    nodes = set()
    edges = []
    with open(path, 'r') as f:
        for line in f.readlines():
            connect = line.strip().split('-')
            nodes.update(connect)
            edges += [connect]
    nodes = list(nodes)
    nodes.sort()
    N = len(nodes)
    mat = np.zeros((N,N), dtype=int)
    for edge in edges:
        i = nodes.index(edge[0])
        j = nodes.index(edge[1])
        mat[i, j] = 1
        mat[j, i] = 1
    return nodes, mat

def random_walk(nodes, mat):
    to_visit = mat.copy()
    trail = 'start'
    node = 'start'
    while node != 'end':
        i = nodes.index(node)
        if node.islower():
            to_visit[:,i] = 0
        options = np.where(to_visit[i,:] == 1)[0]
        if len(options) == 0:
            return 'fail'
        i = np.random.choice(options)
        node = nodes[i]
        trail +='-' + node
    return trail

def solve(inpath, iters):
    nodes, mat = read_day12(inpath)   
    trails = set()
    
    st = time.perf_counter()
    for i in range(iters):
        trail = random_walk(nodes, mat)
        if trail != 'fail':
            trails.add(trail)
    tim = time.perf_counter() - st
    
    print(f'Runtime: {round(tim / 60, 1)} minutes')

    return {
        'part1': len(trails),
        'part2': 0
    }
