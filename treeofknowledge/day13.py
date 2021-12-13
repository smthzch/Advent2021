import numpy as np

def read_day13(path):
    mat = np.zeros((10000, 10000), dtype=int)
    folds = []
    with open(path, 'r') as f:
        for line in f.readlines():
            if line[0] == 'f':
                line_split = line.strip().split('=')
                dim = 0 if line_split[0][-1] == 'y' else 1
                folds += [[dim, line_split[1]]]
            else:
                j, i = line.strip().split(',')
                mat[i,j] = 1
    maxi = np.argmax(mat, axis=0)
    maxj = np.argmax(mat, axis=1)
    return mat[:maxi, :maxj], folds

def fold(mat, axis, ix):
    stop_ix = mat.shape[axis] - ix + 1
    for ix in range(ix + 1, stop_ix + 1)
        np.argwhere()
        mat[]

def solve(path):
    mat, folds = read_day13(path)


    return {
        'part1': 0,
        'part2': 0
    }
