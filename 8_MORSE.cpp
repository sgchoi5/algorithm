#include <cstdio>
#include <string>
#include <cstring> // memset
using namespace std;

int min(int a, int b) {
	return a < b ? a : b;
}

// 코드 9.6 모든 모스 신호를 만드는 완전 탐색 알고리즘
// s: 지금까지 만든 신호
// n: 더 필요한 -의 개수
// m: 더 필요한 o의 개수
void generate(int n, int m, string s) {
	// 기저 사례: n = m = 0
	if (n == 0 && m == 0) {
		printf("%s\n", s.c_str());
		return;
	}
	if (n > 0)
		generate(n - 1, m, s + "-");
	if (m > 0)
		generate(n, m - 1, s + "o");
}

// 코드 9.7 k - 1 개를 건너뛰고 첫 번째 신호를 출력하는 알고리즘
int skip;
// skip개를 건너뛰고 출력한다
void generate2(int n, int m, string s) {
	// 기저 사례: skip < 0
	if (skip < 0)
		return;
	// 기저 사례: n = m = 0
	if (n == 0 && m == 0) {
		// 더 건너뛸 신호가 없는 경우
		if (skip == 0)
			printf("%s\n", s.c_str());
		--skip;
		return;
	}
	if (n > 0)
		generate2(n - 1, m, s + "-");
	if (m > 0)
		generate2(n, m - 1, s + "o");
}

// 코드 9.8 K - 1 개 건너뛰고 첫 번째 신호를 출력하는 알고리즘
// K 의 최대값 +100. 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다
const int M = 1000000000 + 100;
int bino[201][201];
// 필요한 모든 이항계수를 미리 계산해둔다
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; ++i) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; ++j)
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
	}
}
//skip개를 건너뛰고 출력한다
void generate3(int n, int m, string s) {
	// 기저 사례: skip < 0
	if (skip < 0)
		return;
	// 기저 사례: n = m = 0;
	if (n == 0 && m == 0) {
		if (skip == 0)
			printf("%s\n", s.c_str());
		--skip;
		return;
	}
	if (bino[n + m][n] <= skip) {
		skip -= bino[n + m][n];
		return;
	}
	if (n > 0)
		generate3(n - 1, m, s + "-");
	if (m > 0)
		generate3(n, m - 1, s + "o");
}

// 코드 9.9 k번째 신호를 계산하는 알고리즘
// n개의 -, m개의 o 로 구성된 신호 중 skip개를 건너뛰고
// 만들어지는 신호를 반환한다
string kth(int n, int m, int skip) {
	// n == 0 인 경우 나머지 부분은 전부 o일 수밖에 없다
	if (n == 0)
		return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1])
		return "-" + kth(n - 1, m, skip);
	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}


int main(void) {
	int C, n, m, k;
	scanf("%d", &C);
	// 3, 4)
	calcBino();

	while (C--) {
		scanf("%d %d %d", &n, &m, &k);
		// 1)
		// 2)
		//skip = k - 1;
		//generate2(n, m, string{});
		// 3)
		//skip = k - 1;
		//generate3(n, m, string{});
		// 4)
		printf("%s\n", kth(n, m, k - 1).c_str());
	}
	
	return 0;
}
