#!/usr/bin/env python

"""
Graph.py: Graph has some useful functions or snippets of code used for graph and network analysis.
"""

__author__ = "Ben Zheng"
__copyright__ = "MIT License"
__credits__ = []
__license__ = "MIT"
__version__ = "None"
__maintainer__ = "Ben Zheng"
__email__ = ""
__status__ = "Prototype"

'''A Naive implementation to find seating arrangement to find the maximum permutation. '''
def naive_max_perm(M, A=None):
	if A is None:
		A = set(range(len(M)))
	if len(A) == 1: #Base Case
		return A
	B = set(M[i] for i in A) #Improvement here!
	C = A - B
	if C:
		A.remove(C.pop())
		return naive_max_perm(M, A)
	return A

'''A FIFO approach to maximum permutation that shoud be O(M)'''
def max_perm(M):
	n = len(M)
	A = set(range(n))
	count = [0]*n
	for i in M:
		count[i] += 1
	Q = [i for i in A if count[i] == 0]
	while Q:
		i = Q.pop()
		A.remove(i)
		k = M[i]
		count[k] -= 1
		if count[k] == 0:
			Q.append(k)
	return A