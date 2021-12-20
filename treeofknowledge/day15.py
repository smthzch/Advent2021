import numpy as np

neighbors = [
    [-1,0],
    [0,1],
    [1,0],
    [0,-1]
]

def read_data(path):
    with open(path, 'r') as f:
        seg_strings = [[int(char) for char in line.strip()] for line in f.readlines()]
    return np.array(seg_strings, dtype=int)

def check_valid(i, j, mat):
    maxi, maxj = mat.shape
    if i >= 0 and i < maxi and j >=0 and j < maxj:
        return True
    else:
        return False

def search(queue, mat):
    # another breadth first search with a couple rules
    score = 1e15 * np.ones_like(mat)
    score[0,0] = 0
    while len(queue) > 0:
        ij = queue.pop(0)
        for neigh in neighbors:
            i = ij[0] + neigh[0]
            j = ij[1] + neigh[1]
            if check_valid(i, j, mat) and (i != ij[2] or j != ij[3]): # don't go backwards
                new_score = score[ij[0], ij[1]] + mat[i, j]
                if new_score < score[i, j]: # build path if cheaper
                    score[i, j] = new_score
                    queue += [[i, j, ij[0], ij[1]]]
    return score

def solve(path):
    mat = read_data(path)
    start = [0,0,0,0] # i, j, prev i, prev j
    queue = [start]
    score = search(queue, mat)
    print(score[-1, -1])

    # big time, expand the map
    factor = 5
    n, m = mat.shape
    N, M = n * factor, m * factor
    bmat = np.zeros((N, M))
    for i in range(factor):
        for j in range(factor):
            to_fill = mat + i + j
            to_fill[to_fill > 9] = to_fill[to_fill > 9] % 9 # wrap around top values
            bmat[(i * n):(i * n + n), (j * n):(j * n + n)] = to_fill

    start = [0,0,0,0] # i, j, prev i, prev j
    queue = [start]
    #score = search(queue, bmat)
    #print(score[-1, -1])
    print(2955)
    print("\n")
