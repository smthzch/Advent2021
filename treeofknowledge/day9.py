import numpy as np

def read_day9(path):
    with open(path, 'r') as f:
        seg_strings = [[int(char) for char in line.strip()] for line in f.readlines()]
    return np.array(seg_strings, dtype=int)

def watershed(dat):
    n_neigh = 4
    neighbors = np.array([
        [-1, 0],
        [0, 1],
        [1,0],
        [0,-1]
    ])
    N, K = dat.shape
    D = N * K
    y, x = np.where(dat >= 0)
    locs = np.concatenate([y[:,None], x[:,None]], axis = 1)
    assert locs.shape[0] == D
    visited = np.zeros((N,K), dtype = bool)
    basins = np.zeros((N,K), dtype = int)
    cur_nodes = []
    cur_basin = 0
    l = lambda i: (locs[i,0], locs[i,1])
    for i in range(D):
        if not visited[l(i)]:
            visited[l(i)] = True
            if dat[l(i)] < 9:
                cur_nodes += [locs[i,:]]
                cur_basin += 1
        while len(cur_nodes) > 0:
            node = cur_nodes.pop()
            basins[node[0], node[1]] = cur_basin
            # add neighbors if appropriate
            for n in range(n_neigh):
                next_node = node + neighbors[n,:]
                if next_node[0] >=0 and \
                   next_node[0] < N and \
                   next_node[1] >= 0 and \
                   next_node[1] < K and \
                   not visited[next_node[0], next_node[1]]:
                   visited[next_node[0], next_node[1]] = True
                   if dat[next_node[0], next_node[1]] < 9:
                       cur_nodes += [next_node]
    return basins


def solve(path):
    dat = read_day9(path)
    N, K = dat.shape
    # get derivative
    hdif1 = (dat[:,1:] - dat[:,:-1]) < 0
    hdif2 = (dat[:,:-1] - dat[:,1:]) < 0
    hdif1 = np.concatenate([np.ones((N, 1), dtype=int), hdif1], axis = 1)
    hdif2 = np.concatenate([hdif2, np.ones((N, 1), dtype=int)], axis = 1)
    hdif = hdif1 * hdif2

    vdif1 = (dat[1:,:] - dat[:-1,:]) < 0
    vdif2 = (dat[:-1,:] - dat[1:,:]) < 0
    vdif1 = np.concatenate([np.ones((1, K), dtype=int), vdif1], axis = 0)
    vdif2 = np.concatenate([vdif2, np.ones((1, K), dtype=int)], axis = 0)
    vdif = vdif1 * vdif2
    # find minimums, calc risk
    minimums = (hdif * vdif)
    min_ix = np.where(minimums > 0)
    risk = (dat[min_ix[0], min_ix[1]] + 1).sum()

    # find basins
    basins = watershed(dat)
    n_basins = basins.max()
    areas = np.zeros(n_basins, dtype = int)
    for i in range(1, n_basins + 1):
        areas[i - 1] = (basins[basins == i] * 0 + 1).sum()
    big_areas = np.sort(areas)[-3:].prod()

    return {
        'part1': risk,
        'part2': big_areas
    }