import numpy as np

digits = np.array([
    [1,1,1,0,1,1,1],
    [0,0,1,0,0,1,0],
    [1,0,1,1,1,0,1],
    [1,0,1,1,0,1,1],
    [0,1,1,1,0,1,0],
    [1,1,0,1,0,1,1],
    [1,1,0,1,1,1,1],
    [1,0,1,0,0,1,0],
    [1,1,1,1,1,1,1],
    [1,1,1,1,0,1,1]
])

digit_map = dict(zip(['a','b','c','d','e','f','g'], range(7)))

digit_cov = np.round(np.cov(digits), 4)

def read_day8(path):
    with open(path, 'r') as f:
        seg_strings = [line.split('|') for line in f.readlines()]
    return seg_strings

def parse_segstr(segstr):
    segs = np.zeros(7, dtype=int)
    for dig in segstr:
        segs[digit_map[dig]] = 1
    return segs

def match_digits(covd, covs):
    # this decodes the mixed signals
    # by matching the covariances we can determine what the true digit is
    unfuzz = -np.ones(10, dtype=int)
    for i in range(10):
        intersect_size = np.zeros(10)
        for j in range(10):
            intersect_size[j] = np.intersect1d(covd[j,:], covs[i,:]).shape[0]
            
        if np.all(covs[i,:] == 0):
            unfuzz[i] = 8
            continue
        unfuzz[i] = np.argmax(intersect_size)
    return unfuzz

def match_fuzzy(segs, new_seg):
    for i in range(10):
        if(np.all(segs[i,:] == new_seg)): return i
    return -1

def solve(path):
    to_count = [1, 4, 7, 8]
    counter= dict(zip(to_count, [0] * len(to_count)))
    total = 0
    
    seg_strings = read_day8(path)
    
    for train, test in seg_strings:
        segs = np.array([parse_segstr(seg) for seg in train.split(' ')[0:10]]) # drop trailing space
        test_segs = np.array([parse_segstr(seg.strip()) for seg in test.split(' ')[1:]]) #drop leading space
        
        segs_cov = np.round(np.cov(segs), 4)
        unfuzz = match_digits(digit_cov, segs_cov)
        
        parsed = ''
        for i in range(test_segs.shape[0]):
            fuzzy_num = match_fuzzy(segs, test_segs[i,:])
            assert fuzzy_num != -1
            num = unfuzz[fuzzy_num]
            if num in to_count:
                counter[num] += 1
            parsed += str(num)
        total += int(parsed)
            
    return {
        'part1': sum(counter.values()),
        'part2': total
    }
