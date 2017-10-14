from random import *
from mat_funcs import *
#so far this will only work for a 3x3 matrix. still any 3x3 system of equations that is linearly
#independent can be solved
def get_A_inner(A):
    A_inner = []
    for i in range(1, len(A)):
        rowi = A[i]
        A_inner.append(rowi[1:])
    return A_inner

def merge_A_inner(A, A_inner):
    for i in range(1, len(A)):
        for j in range(1, len(A[0])):
            A[i][j] = A_inner[i-1][j-1]
    return A

def row_reduction(A):
    A = initialize_A(A) #our first column is now [1,0,0], our first row is now [1,x,y]
    A_inner = get_A_inner(A)
    print("A_inner: ", A_inner)
    A_inner = initialize_A(A_inner)
    A = merge_A_inner(A, A_inner)
    print("Final A: ", A)

A = [[0, 2, 3], [5,1,13], [2, 14 ,11]]
row_reduction(A)







