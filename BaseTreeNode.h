#pragma once

#include <vector>
using std::vector;

typedef unsigned char byte;
typedef vector<vector<byte>> matrix;

const byte N = 4;

struct BaseTreeNode {
	matrix m;
	BaseTreeNode* parent;
	byte zeroX = 0, zeroY = 0;

	BaseTreeNode(matrix m) : m(m), parent(nullptr) {}

	BaseTreeNode(matrix m, BaseTreeNode* parent) : m(m), parent(parent) {}

	byte getManhattan() {
		byte res = 0;
		for (byte i = 0; i < N; i++)
			for (byte j = 0; j < N; j++) {
				byte v = m[i][j];
				if (!v) continue;
				res += abs(i - (v - 1) / N) + abs(j - (v - 1) % N);
			}
		return res;
	}

	bool isGoal() {
		for (byte i = 0; i < N; i++)
			for (byte j = 0; j < N; j++) {
				if ((i < N - 1 || j < N - 1) && m[i][j] != i * N + j + 1) return false;
				else if (i == N - 1 && j == N - 1 && m[i][j]) return false;
			}
		return true;
	}

};
