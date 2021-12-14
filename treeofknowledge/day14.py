def read_data(path):
    with open(path, 'r') as f:
        seed = f.readline().strip()
        f.readline() # skip empty line
        rules = {
            line.split(' ')[0]: line.split(' ')[2].strip()
            for line in f.readlines()
        }
    return seed, rules

def step(pairs, rules):
    new_pairs = {pair: 0 for pair in pairs.keys()}
    for k in pairs:
        n = pairs[k]
        insert = rules[k]
        pair_0 = k[0] + insert
        pair_1 = insert + k[1]
        new_pairs[pair_0] += n
        new_pairs[pair_1] += n
    return new_pairs

def count_elements(pairs, rules, start, end):
    elements = {element: 0 for element in set(rules.values())}
    for k in pairs:
        elements[k[0]] += pairs[k]
        elements[k[1]] += pairs[k]
    # everything double counted except the ends
    elements[start] -= 1
    elements[end] -= 1
    for k in elements:
        elements[k] /= 2
    # put the ends back
    elements[start] += 1
    elements[end] += 1
    return elements

def solve(path):
    seed, rules = read_data(path)
    pairs = {rule: 0 for rule in rules.keys()}
    
    for i in range(len(seed) - 1):
        pairs[seed[i:(i + 2)]] += 1

    T = 40
    for _ in range(T):
        pairs = step(pairs, rules)

    # count the elements and get min/max
    elements = count_elements(pairs, rules, seed[0], seed[-1])
    max_e = ''
    max_c = 0
    min_e = ''
    min_c = 1e15
    for k in elements:
        count = elements[k]
        if count > max_c:
            max_c = count
            max_e = k
        if count < min_c:
            min_c = count
            min_e = k

    print(f'Max element {max_e}: {max_c}')
    print(f'Min element {min_e}: {min_c}')
    print(f'Max - min: {max_c - min_c}')
