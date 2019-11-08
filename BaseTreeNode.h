#pragma once

#include <vector>
using std::vector;

typedef unsigned char byte;
typedef vector<vector<byte>> matrix;

const int N = 4;

struct BaseTreeNode {
	matrix m;
	BaseTreeNode* parent;
	byte zeroX = 0, zeroY = 0;

	BaseTreeNode(matrix m) : m(m), parent(nullptr) {}

	BaseTreeNode(matrix m, BaseTreeNode* parent) : m(m), parent(parent) {}

	int getManhattan() {
		int res = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				int v = m[i][j];
				if (!v) continue;
				res += abs(i - (v - 1) / N) + abs(j - (v - 1) % N);
			}
		return res;
	}

	bool isGoal() {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if ((i < N - 1 || j < N - 1) && m[i][j] != i * N + j + 1) return false;
				else if (i == N - 1 && j == N - 1 && m[i][j]) return false;
			}
		return true;
	}

};
