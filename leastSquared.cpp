// LeastSquares.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;


vector<float> get_jth_col(vector<vector<float>>&B, int J) {
	vector<float>col;
	for (int i = 0; i < (int)B.size(); i++) {
		for (int j = 0; j <(int) B[0].size(); j++) {
			if (j == J)
				col.push_back(B[i][j]);
		}
	}
	return col;
}

vector<vector<float>> init_mxn(int m, int n) {
	vector<vector<float>> A;
	for (int i = 0; i < m; i++) {
		vector<float>row;
		for (int j = 0; j < n; j++) {
			row.push_back(0);
		}
		A.push_back(row);
	}
	return A;
}

vector<vector<float>> mxn_transpose(vector<vector<float>>&T) {
	int m = T.size();
	int n = T[0].size();
	vector<vector<float>>_A = init_mxn(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			_A[i][j] = T[j][i];
		}
	}
	return _A;
}

float vector_dot(vector<float>&U, vector<float>&V) {
	if (U.size() != V.size()) {
		printf("error vmul: vectors must be same size: exiting with code 1\n");
		exit(1);
	}
	float ss = 0;
	for (int i = 0; i < (int)U.size(); i++) {
		ss += U[i] * V[i];
	}
	return ss;
}

vector<vector<float>> matrix_mul_AB(vector<vector<float>>&A, vector<vector<float>>&B, int an, int am, int bn, int bm) {
	if (an != bm) {
		printf("error mmul: matrices inner dimensions must agree: exiting with code 2\n");
		exit(2);
	}
	float ij_dot_prod;
	vector<vector<float>>C = init_mxn(am, bn);
	for (int i = 0; i < am; i++) {
		vector<float>a_row_i = A[i]; //get ith row of A
		for (int j = 0; j < bn; j++) {
			vector<float>b_col_j = get_jth_col(B, j);
			float vmul = vector_dot(a_row_i, b_col_j);
			C[i][j] = vmul;
		}
	}
	return C;
}

vector<float> vector_sub(vector<float>&A, vector<float>&B) {
	vector<float>C;
	for (int i = 0; i < (int)A.size(); i++) {
		C.push_back(A[i] - B[i]);
	}
	return C;
}

vector<float> get_proj_A_onto_B(vector<float>&A, vector<float>&B) {
	vector<float>proj;
	vector<float>Bh;
	float s1 = vector_dot(A, B);
	float s2 = vector_dot(B, B);
	float op = s1 / s2;
	for (int i = 0; i < (int)B.size(); i++) {
		Bh.push_back(B[i] * op);
	}
	return Bh;
}

vector<vector<float>> get_Q(vector<vector<float>>&A) {
	int num_cols = A[0].size();
	vector<float>v1 = get_jth_col(A, 0);
	vector<vector<float>>orthogonal_vecs;
	orthogonal_vecs.push_back(v1);
	for (int i = 1; i < num_cols; i++) {
		vector<float>xn = get_jth_col(A, i);
		vector<float>vn;
		vector<float>proj;
		for (int k = 0; k < (int)xn.size(); k++) {
			vn.push_back(xn[k]);
		}
		for (int j = 0; j < i; j++) {
			proj = get_proj_A_onto_B(xn, orthogonal_vecs[j]);
			vn = vector_sub(vn, proj);
		}
		orthogonal_vecs.push_back(vn);
	}
	return orthogonal_vecs;
}

void print_matrix(vector<vector<float>>&A, int m, int n) {
	for (int i = 0; i<m; i++) {
		printf("[");
		for (int j = 0; j<n; j++) {
			printf("%f,", A[i][j]);
		}
		printf("]\n");
	}
}


int main()
{
	vector<vector<float>>A = { {1.0,2.0,4.0}, 
							   {3.0,4.0,6.0},
							   {12.0,2.0,66.0}};

	vector<vector<float>>_Q = get_Q(A);
	printf("%f", vector_dot(_Q[1], _Q[2]));
	
	int usr_in;
	cin >> usr_in;
    return usr_in;
}

