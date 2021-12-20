import numpy as np
from itertools import product

def read(path):
    arrays = []
    with open(path,'r') as f:
        new_array = None
        for line in f:
            if line[:3] == '---':
                if new_array:
                    arrays += [np.array(new_array)]
                new_array = []
            elif line == '\n':
                pass
            else:
                new_array += [[int(x) for x in line.strip().split(',')]]
    return arrays

rotations = list(product([0,1,2,3], [0,1,3], [0,2]))

def rotate(x, axis, theta):
    c = np.cos(theta)
    s = np.sin(theta)
    R = np.array([
        [
            [1,0,0],
            [0,c,-s],
            [0,s,c]
        ],
        [
            [c,0,-s],
            [0,1,0],
            [s,0,c]
        ],
        [
            [c,-s,0],
            [s,c,0],
            [0,0,1]
        ]
    ])
    return R[axis,:,:] @ x

class ParticleFilter:
    def __init__(self, truth, comp, n_particles, iters):
        self.truth = truth
        self.comp = comp
        self.N = n_particles
        self.iters = iters

        # generate particles
        self.particles = np.random.randint(-2000, 2000, size=(self.N, 3))
        self.weights = np.ones(self.N)

    def fit(self):
        self.find_best_rotation()
        for _ in self.iters:
            self.jitter()
            self.score()
            self.select()

    def jitter(self):
        self.weights = np.ones(self.N)
        self.particles += self.random.randint(-1, 1, size=(self.N, 3))

    def score(self):
        min_scores = np.ones(self.N) * float('inf')
        # find pairwise best match of points
        

    def find_best_rotation(self):
        for rotation in rotations:
            y = self.comp.copy()
            for d, amount in enumerate(rotation):
                y = rotate(y, d, amount * np.pi * 0.5)

    def select(self):
        keep_ix = np.random.choice(self.N, self.N, replace=True, p=self.weights)
        self.particles = self.particles[keep_ix,:]
        self.weights = self.weights[keep_ix]

def solve(path):
    arrays = read(path)
    print(arrays)

if __name__ == '__main__':
    path = 'data/day19_ex.txt'
    solve(path)