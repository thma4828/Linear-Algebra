from random import randint

def mat_vec_gen(n):
    #Function to generate a random matrix of dimension n x n
    #and a random vector of length n
     A = [[randint(1,100) for ii in range(n)] for jj in range(n)]
     x = [randint(1,100) for ii in range(n)]
     return A, x

def create_first_pivot(A):
    if A[0][0] == 1:
        return A
    row1 = A[0]
    print("cfp, row1: ", row1)
    init_v = row1[0]
    for i in range(len(row1)):
        j = row1[i] / init_v
        row1[i] = j
    A[0] = row1
    return A

def mat_vec(A, x):
    vec1 = []
    for row in A:
        sum_r = 0
        for j in range(len(x)):
            sum_r += (row[j] * x[j])
        vec1.append(sum_r)
    return vec1

def get_col_j(A, j):
    col_j = []
    for row in A:
        col_j.append(row[j])
    return col_j

def get_nonz_is(col):
    nonz_is = []
    for i in range(len(col)):
        if col[i] != 0:
            nonz_is.append(i)
    return nonz_is


def swap_rows(i, j, A):
    rowi = A[i]
    rowj = A[j]
    A[i] = rowj
    A[j] = rowi
    return A

def get_f_nonz_r(A):
    index = 0
    for r in A:
        index += 1
        if r[0] != 0:
            return r, index


def scalar_mul_row(row,  sm):
    for i in range(len(row)):
        row[i] = row[i] * sm
    return row

def vector_subtraction(c1, c2):
    for i in range(len(c1)):
        c1[i] = c1[i] - c2[i]
    return c1

def row_reduce_first_col(A):
    colj = get_col_j(A, 0)  # get this column
    print("colj: ", colj)
    nonz_is = get_nonz_is(colj)  # get nonzero indices of rows in this column
    for ri in range(1, len(A)):  # loop through rows (not first row)
        if ri in nonz_is:  # if nonzero element in row
            elem = A[ri][0]
            print("A was: ", A)
            sub_row = scalar_mul_row(A[0], elem)
            A[ri] = vector_subtraction(A[ri], sub_row)
            scalar_mul_row(A[0], (1 / elem))
            print("A is now: ", A)
    return A

def initialize_A(A):
    if A[0][0] == 0: #if we have a nonzero pivot
        first_nonzero_row, i = get_f_nonz_r(A)
        A = swap_rows(i, 0, A)
    A = create_first_pivot(A)  # A[0][0] is now 1 and other elements fractions
    print("A after creating first pivot as 1", A)
    A = row_reduce_first_col(A)
    return A

#def get_a_inner(A, i, j):

#def init_pivot(A, i, j):
    #if A[i][j] == 0:
        #A_inner =

