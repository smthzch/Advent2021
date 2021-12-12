import numpy as np
import time
import multiprocessing as mp

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

# part 1 stochastic search
def random_walk_1(nodes, mat, seed):
    np.random.seed(seed)
    to_visit = mat.copy()
    trail = 'start'
    node = 'start'
    # build trail to end
    while node != 'end':
        i = nodes.index(node)
        # cannot revisit this lil node
        if node.islower():
            to_visit[:,i] = 0
        # find which nodes can jump to
        options = np.where(to_visit[i,:] == 1)[0]
        if len(options) == 0:
            return 'fail'
        # randomly select node
        i = np.random.choice(options)
        node = nodes[i]
        trail +='-' + node
    return trail

# part 2 stochastic search
def visit_lils(nodes, mat, lils):
    for lil in lils:
        i = nodes.index(lil)
        mat[:,i] = 0


def random_walk_2(nodes, mat, seed):
    np.random.seed(seed)
    to_visit = mat.copy()
    trail = 'start'
    node = 'start'
    # track when lowercase node revisited
    lil_visits = []
    revisits = True
    # cannot revisit start
    i = nodes.index(node)
    to_visit[:,i] = 0
    # build trail to end
    while node != 'end':
        i = nodes.index(node)
        if node.islower():
            # if havent visited lil node twice
            if revisits:
                # cannot revisit lil nodes anymore
                if node in lil_visits:
                    revisits = False
                    visit_lils(nodes, to_visit, lil_visits) # mark all visited lil nodes as unvisitable
                # add to list of lil nodes visited
                else:
                    lil_visits += [node]
            # cannot revisit this node
            else:
                to_visit[:,i] = 0
        # find which nodes can jump to
        options = np.where(to_visit[i,:] == 1)[0]
        if len(options) == 0:
            return 'fail'
        # randomly select node
        i = np.random.choice(options)
        node = nodes[i]
        trail +='-' + node
    return trail

def solve(inpath, iters_1, iters_2, seed):
    np.random.seed(seed)
    nodes, mat = read_day12(inpath)

    # track trails visited as a set
    trails_1 = set()
    trails_2 = set()

    with mp.Pool(processes = mp.cpu_count()) as pool:
        # part 1
        st = time.perf_counter()
        args = (
            [nodes, mat, np.random.randint(1, 1e9)] for i in range(iters_1)
        )
        results = pool.starmap(random_walk_1, args)
        for trail in results:
            if trail != 'fail':
                trails_1.add(trail)
        tim = time.perf_counter() - st
        print(f'Part 1 runtime: {round(tim / 60, 1)} minutes')

        # part 2
        st = time.perf_counter()
        args = (
            [nodes, mat, np.random.randint(1, 1e9)] for i in range(iters_2)
        )
        results = pool.starmap(random_walk_2, args)
        for trail in results:
            if trail != 'fail':
                trails_2.add(trail)
        tim = time.perf_counter() - st
        print(f'Part 2 runtime: {round(tim / 60, 1)} minutes')

    return {
        'part1': len(trails_1),
        'part2': len(trails_2)
    }
