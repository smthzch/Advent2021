import numpy as np
import matplotlib.pyplot as plt

def read_day13(path):
    mat = np.zeros((10000, 10000), dtype=int)
    folds = []
    with open(path, 'r') as f:
        for line in f.readlines():
            if line[0] == 'f':
                line_split = line.strip().split('=')
                dim = 0 if line_split[0][-1] == 'y' else 1
                folds += [[dim, int(line_split[1])]]
            elif line.strip() == '':
                continue
            else:
                j, i = [int(x) for x in line.strip().split(',')]
                mat[i,j] = 1
    maxi, maxj = np.where(mat == 1)
    maxi = max(maxi) + 1
    maxj = max(maxj) + 1
    return mat[:maxi, :maxj], folds

def fold_mat(mat, axis, fold):
    stop_ix = mat.shape[axis] - fold
    for ix in range(1, stop_ix):
        if axis == 0:
            to_flip = np.argwhere(mat[fold + ix, :] == 1).flatten()
            fold_ix = np.ones_like(to_flip) * (fold - ix)
            mat[fold_ix, to_flip] += 1
        elif axis == 1:
            to_flip = np.argwhere(mat[:, fold + ix] == 1).flatten()
            fold_ix = np.ones_like(to_flip) * (fold - ix)
            mat[to_flip, fold_ix] += 1
    mat[mat >= 1] = 1
    if axis == 0:
        return mat[:fold,:]
    else:
        return mat[:,:fold]

def solve(path, plot):
    mat, folds = read_day13(path)

    first = True
    first_dots = 0
    for fold in folds:
        mat = fold_mat(mat, fold[0], fold[1])
        if first:
            first_dots = mat.sum()
            first = False

    if plot:
        plt.imshow(mat)
        plt.show()

    return {
        'part1': first_dots
    }
