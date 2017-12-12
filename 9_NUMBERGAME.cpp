// http://gooddaytocode.blogspot.kr/
// 회고
// 1) 

#include <cstdio>

int max(int a, int b) {
	return a > b ? a : b;;
}

// 코드 9.21 숫자 게임 문제를 해결하는 동적 계획법 알고리즘

const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];

int play(int left, int right) {
	// 기저 사례: 모든 수가 다 없어졌을 때
	if (left > right)
		return 0;

	int& ret = cache[left][right];
	if (ret != EMPTY)
		return ret;
	// 수를 가져가는 경우
	ret = max(board[left] - play(left + 1, right),
		board[right] - play(left, right - 1));
	// 수를 없애는 경우
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));
		ret = max(ret, -play(left, right - 2));
	}
	return ret;
}

int main(void) {
	int C, n;
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &board[i]);
			for (int j = i; j < n; j++) {
				cache[i][j] = EMPTY;
			}
		}

		printf("%d\n", play(0, n-1));
	}
	
	return 0;
}
