import numpy as np

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




def solve(path):
    arrays = read(path)
    print(arrays)

if __name__ == '__main__':
    path = 'data/day19_ex.txt'
    solve(path)