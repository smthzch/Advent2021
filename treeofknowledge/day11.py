import numpy as np

def read_day11(path):
    with open(path, 'r') as f:
        seg_strings = [[int(char) for char in line.strip()] for line in f.readlines()]
    return np.array(seg_strings, dtype=int)

def tick(dat):
    n_neigh = 8
    neighbors = [
        [-1,-1],
        [-1, 0],
        [-1,1],
        [0, 1],
        [1,1],
        [1,0],
        [1,-1],
        [0,-1]
    ]
    N, M = dat.shape
    flashed = np.zeros_like(dat)
    dat += 1
    i_, j_ = np.where(dat == 10)
    locs = list(zip(i_.tolist(), j_.tolist()))
    flashes = 0
    simultaneous = False
    while len(locs) > 0:
        i, j = locs.pop(0)
        flashed[i, j] = 1
        for neigh in neighbors:
            ni = i + neigh[0]
            nj = j + neigh[1]
            if ni >= 0 and \
                    ni < N and \
                    nj >= 0 and \
                    nj < M:
                dat[ni, nj] += 1
                if dat[ni, nj] == 10:
                    locs += [[ni, nj]]
    dat[flashed == 1] = 0
    flashes = flashed.sum()
    if flashes == (N * M):
        simultaneous = True
    return flashes, simultaneous 

def solve(path):
    dat = read_day11(path)
    T = 1000
    flashed = 0
    step_simultaneous = 0
    for t in range(T):
        flashes, simultaneous = tick(dat)
        if t < 100:
            flashed += flashes
        if simultaneous:
            step_simultaneous = t + 1
            break

    return {
        'part1': flashed,
        'part2': step_simultaneous
    }