import numpy as np

def solve(path):
    opens = ['(', '[', '{', '<']
    closes = {'(': ')', '[': ']', '{': '}', '<': '>'}
    er_costs = {')': 3, ']': 57, '}': 1197, '>': 25137}
    open_costs = {')': 1, ']': 2, '}': 3, '>': 4}
    stack = []  # track what the current order of opens are
    part1_cost = 0
    part2_costs = []
    with open(path, 'r') as f:
        for line in f.readlines():
            clean = line.strip()
            stack = []
            part2_cost = 0
            for char in clean:
                if char in opens: # if open add to open stack
                    stack += [char]
                if char in closes.values(): # if closes pop off end of open stack
                    to_close = stack[-1]
                    stack = stack[:-1]
                    if char != closes[to_close]: # check to see if matches proper close
                        part1_cost += er_costs[char]
                        stack = []
                        break
            while len(stack) > 0: #if incomplete pop off stack until properly closed
                to_close = closes[stack[-1]]
                stack = stack[:-1]
                part2_cost *= 5 # buncha weird math for scoring
                part2_cost += open_costs[to_close]
            if part2_cost > 0:
                part2_costs += [part2_cost]
    p2 = np.array(part2_costs, dtype=int)
    med_cost = int(np.median(p2))

    return {
        'part1': part1_cost,
        'part2': med_cost
    }
