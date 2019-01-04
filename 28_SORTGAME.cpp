#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

// 코드 29.4 Sorting Game 문제를 빠르게 해결하는 너비 우선 탐색의 구현

map<vector<int>, int> toSort;
// [0, ..., n-1]의 모든 순열에 대해 toSort[]를 계산해 저장한다
void precalc(int n) {
	vector<int> perm(n);
	for (int i = 0; i < n; ++i)
		perm[i] = i;
	queue<vector<int> > q;
	q.push(perm);
	toSort[perm] = 0;
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];

		for (int i = 0; i < n; ++i) {
			for (int j = i + 2; j <= n; ++j) {
				reverse(here.begin() + i, here.begin() + j);
				if (toSort.count(here) == 0) {
					toSort[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}

int solve(const vector<int>& perm) {
	// perm을 [0, ..., n-1]의 순열로 변환한다
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; ++i) {
		int smaller = 0;
		for (int j = 0; j < n; ++j) {
			if (perm[j] < perm[i])
				++smaller;
			fixed[i] = smaller;
		}
	}
	return toSort[fixed];
}

int main(void) {
	int C, n;
	scanf("%d", &C);

	for (int i = 1; i <= 8; i++)
		precalc(i);

	while (C--) {
		scanf("%d", &n);
		vector<int> num(n, 0);
		for (int i = 0; i < n; i++) {
			scanf("%d", &num[i]);
		}
		printf("%d\n", solve(num));
	}
	return 0;
}
