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

def naive_max_perm(M, A=None):
	"""

	:param M: Matrix
	:param A: Use for base case
	:return: Return the maximum permutation
	"""
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

def max_perm(M):
	"""

	:param M: Martix
	:return: the maximum permutation with O(M)
	;Note: FIFO
	"""
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