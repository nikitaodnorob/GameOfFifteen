#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <chrono>
#include "AStar.h"
#include "BaseTreeNode.h"

using std::cin;
using std::cout;
using namespace std::chrono;

bool isHaveSolution(matrix m) {
	//разворачиваем матрицу в массив
	vector<byte> arr;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			arr.push_back(m[i][j]);

	//считаем по формуле N = sum(i=1 to 15)n_i + e
	//n_i - после костяшки с числом i есть n_i квадратиков с числами меньших i
	//e - номер ряда пустой клетки (считая с 1), e=0 при нечетных N
	int sumN = 0, e = 0;
	if (!(N % 2))
		for (int i = 0; i < N*N; i++)
			if (arr[i] == 0) 
				e = i / N + 1;

	for (int i = 0; i < N*N; i++) {
		int v = arr[i];
		if (!v) continue;
		for (int j = i + 1; j < N*N; j++) {
			if (!arr[j]) continue;
			if (arr[j] < v) sumN++;
		}
	}

	//если N нечетна, позиция неразрешима
	return !((sumN + e) & 1);
}

void printAnswer(BaseTreeNode* result) {
	if (result == nullptr) {
		cout << "We have an error!\n";
		return;
	}
	vector<matrix> ans;
	while (result) {
		ans.push_back(result->m);
		result = result->parent;
	}
	if (!ans.size()) {
		cout << "We have an error!\n";
		return;
	}
	cout << ans.size() - 1 << " steps:\n";
	for (int i = ans.size() - 1; i >= 0; i--) {
		matrix m = ans[i];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				byte c = m[i][j];
				if (c < 10) cout << (char)(c + '0') << "\t";
				else cout << (char)(c + 'A' - 10) << "\t";
			}
			cout << "\n";
		}
		cout << "=========================\n";
	}
}

void readMatrix(matrix& m, int& zeroX, int& zeroY) {
	cout << "Enter the start position: ";
	m = matrix(N, vector<byte>(N));
	byte c;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> c;
			if (c >= '0' && c <= '9') m[i][j] = c - '0';
			else if (c >= 'a' && c <= 'z') m[i][j] = c - 'a' + 10;
			else if (c >= 'A' && c <= 'Z') m[i][j] = c - 'A' + 10;
			if (c == '0') {
				zeroX = i;
				zeroY = j;
			}
		}
}

void printTime(steady_clock::time_point t1, steady_clock::time_point t2) {
	cout << "Time: ";
	double ms = duration_cast<microseconds>(t2 - t1).count() / 1000.0;
	double sec = duration_cast<milliseconds>(t2 - t1).count() / 1000.0;
	if (ms < 1000) cout << ms << " ms\n";
	else cout << sec << " sec\n";
}

void solveAStar(matrix m, int zeroX, int zeroY) {
	auto t1 = high_resolution_clock::now();
	BaseTreeNode* result = AStar::solve(m, zeroX, zeroY);
	auto t2 = high_resolution_clock::now();
	printAnswer(result);
	printTime(t1, t2);
}

int main() {
	matrix m(N, vector<byte>(N));
	int zeroX, zeroY;

	//123056789ABCDEF4 - 19 steps, 8.5 ms
	//2F03716A5CD49E8B - 40 steps, 1.09 sec
	//51EAFD7B94C83260 - 52 steps, 45 sec, 1650 MB Memory
	//365CA48ED9FB0217 - 49 steps, 99 sec, 2975 MB Memory
	readMatrix(m, zeroX, zeroY);
			
	if (!isHaveSolution(m)) cout << "No solution!\n";
	else {
		//solve
		solveAStar(m, zeroX, zeroY);
	}
}