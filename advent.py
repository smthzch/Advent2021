import treeofknowledge as tok

welcome = '''######################################
#
#
# ADVENT OF CODE 2021
#
#
######################################
'''
print(welcome)

print('---Day 7---')
path = 'data/day7.txt'
print(f'Fuel :{tok.day7.solve1(path)}')
print(f'Fuel :{tok.day7.solve2(path)}\n')

print('---Day 8---')
path = 'data/day8.txt'
sol = tok.day8.solve(path)
print(f'Total unique: {sol["part1"]}')
print(f'Total: {sol["part2"]}\n')

print('---Day 9---')
path = 'data/day9.txt'
sol = tok.day9.solve(path)
print(f'Total minimums: {sol["part1"]}')
print(f'Product area: {sol["part2"]}\n')

print('---Day 10---')
path = 'data/day10.txt'
sol = tok.day10.solve(path)
print(f'Illegal closing cost: {sol["part1"]}')
print(f'Incomplete cost: {sol["part2"]}\n')

print('---Day 11---')
path = 'data/day11.txt'
sol = tok.day11.solve(path)
print(f'Flashed: {sol["part1"]}')
print(f'Step simultaneous: {sol["part2"]}\n')

print('---Day 12---')
path = 'data/day12.txt'
sol = tok.day12.solve(path)
print(f'Paths: {sol["part1"]}')
print(f'Paths w/ revisit: {sol["part2"]}\n')

print('---Day 13---')
path = 'data/day13.txt'
sol = tok.day13.solve(path, plot=False)
print(f'First fold dots: {sol["part1"]}')
