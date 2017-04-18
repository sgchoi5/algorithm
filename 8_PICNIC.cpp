#include <cstdio>

// 코드 6.5 소풍 문제를 해결하는 재귀 호출 코드

int n, m;
bool areFriends[10][10];

void init(void) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			areFriends[i][j] = false;
		}
	}
}

// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]) {
	// 남은 학생들 중 가장 번호가 빠른 학생을 찾는다
	int firstFree = -1;
	for (int i = 0; i < n; ++i) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}
	// 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니
	//            종료한다
	if (firstFree == -1)
		return 1;
	int ret = 0;
	// 이 학생과 짝지을 학생을 결정한다
	for (int pairWith = firstFree + 1; pairWith < n; ++pairWith) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}

int main(void) {
	int C, f1, f2;
	scanf("%d", &C);
	while (C--) {
		bool completed[10] = { 0 };
		scanf("%d %d", &n, &m);
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &f1, &f2);
			areFriends[f1][f2] = areFriends[f2][f1] = true;
		}
		printf("%d\n", countPairings(completed));
	}
    return 0;
}
