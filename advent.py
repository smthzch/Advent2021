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
day8 = tok.day8.solve(path)
print(f'Total unique: {day8["part1"]}')
print(f'Total: {day8["part2"]}\n')

print('---Day 9---')
path = 'data/day9.txt'
day9 = tok.day9.solve(path)
print(f'Total minimums: {day9["part1"]}')
print(f'Product area: {day9["part2"]}\n')
