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
print(f'Fuel :{tok.day7.solve2(path)}')
