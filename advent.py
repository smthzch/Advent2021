import pickle
import os

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

print('---Day 10---')
path = 'data/day10.txt'
day10 = tok.day10.solve(path)
print(f'Illegal closing cost: {day10["part1"]}')
print(f'Incomplete cost: {day10["part2"]}\n')

print('---Day 11---')
path = 'data/day11.txt'
day11 = tok.day11.solve(path)
print(f'Flashed: {day11["part1"]}')
print(f'Step simultaneous: {day11["part2"]}\n')

print('---Day 12---')
path = 'data/day12.txt'
day12 = tok.day12.solve(path)
print(f'Paths: {day12["part1"]}')
print(f'Paths w/ revisit: {day12["part2"]}\n')
