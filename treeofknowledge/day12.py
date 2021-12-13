import numpy as np

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
def random_walk_1(nodes, mat):
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

# part 2 recursive search
def visit_lils(nodes, mat, lils):
    for lil in lils:
        i = nodes.index(lil)
        mat[:,i] = 0

def recursive_search_1(i, nodes, to_visit):
    node = nodes[i]
    if node == 'end':
        return 1
    else:
        n_paths = 0
        if node.islower():
            to_visit[:,i] = 0
        # find which nodes can jump to
        options = np.where(to_visit[i,:] == 1)[0].tolist()
        if len(options) == 0:
            return 0
        for j in options:
            n_paths += recursive_search_1(j, nodes, to_visit.copy())
        return n_paths

def recursive_search_2(i, nodes, to_visit, revisits, lil_visits):
    node = nodes[i]
    if node == 'end':
        return 1
    else:
        n_paths = 0
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
        options = np.where(to_visit[i,:] == 1)[0].tolist()
        if len(options) == 0:
            return 0
        for j in options:
            # down the hole we go
            n_paths += recursive_search_2(j, nodes, to_visit.copy(), revisits, lil_visits.copy())
        return n_paths

def iterative_search_2(i, nodes, mat):
    revisits = True
    lil_visits = []
    n_paths = 0
    stack = [[i, mat.copy(), revisits, lil_visits.copy()]]
    while len(stack) > 0:
        i, to_visit, revisits, lil_visits = stack.pop()
        node = nodes[i]
        if node == 'end':
            n_paths += 1
        else:
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
            options = np.where(to_visit[i,:] == 1)[0].tolist()
            if len(options) == 0:
                continue
            for j in options:
                stack += [[j, to_visit.copy(), revisits, lil_visits.copy()]]
    return n_paths

def solve(path):
    nodes, mat = read_day12(path)
    # set start node and cannot revisit
    i = nodes.index('start')
    mat[:,i] = 0

    # part 1
    trails_1 = recursive_search_1(i, nodes, mat.copy())

    # part 2
    trails_2_1 = recursive_search_2(i, nodes, mat.copy(), True, [].copy())
    trails_2 = iterative_search_2(i, nodes, mat)

    assert trails_2_1 == trails_2

    return {
        'part1': trails_1,
        'part2': trails_2
    }
