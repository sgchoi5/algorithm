#include <cstdio>
#include <vector>

using namespace std;

int n, d, p, q;

// cahce[][] 는 -1 로 초기화해둔다
double cache[51][101];

// connected[i][j] = 마을 i, j가 연결되어 있나 여부
// deg[i] = 마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];


// 코드 8.22 두니발 박사의 탈옥 문제를 해결하는 완전 탐색 알고리즘

double search(vector<int>& path) {
	// 기저 사례:d일이 지난 경우
	if (path.size() == d + 1) {
		// 이 시나리오가 q에서 끝나지 않았다면 무효
		if (path.back() != q)
			return 0.0;
		// path의 출현 확율을 계산한다
		double ret = 1.0;
		for (int i = 0; i + 1 < path.size(); ++i)
			ret /= deg[path[i]];
		return ret;
	}
	double ret = 0;
	// 경로의 다음 위치를 결정한다
	for (int there = 0; there < n; ++there) {
		if (connected[path.back()][there]) {
			path.push_back(there);
			ret += search(path);
			path.pop_back();
		}
	}
	return ret;
}


// 코드 8.23 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘

// days일째에 here번 마을에 숨어 있다고 가정하고,
// 마지막 날에 q번 마을에 숨어 있을 조건부 확율을 반환한다.
double search2(int here, int days) {
	// 기저 사례: d일이 지난 경우
	if (days == d)
		return (here == q ? 1.0 : 0.0);

	// 메모이제이션
	double& ret = cache[here][days];
	if (ret > -0.5)
		return ret;
	ret = 0.0;
	for (int there = 0; there < n; ++there)
		if (connected[here][there]) {
			ret += search2(there, days + 1) / deg[here];
		}
	return ret;
}

// 코드 8.24 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘

double search3(int here, int days) {
	// 기저 사례: 0 일째
	if (days == 0)
		return (here == p ? 1.0 : 0.0);
	// 메모이제이션
	double& ret = cache[here][days];
	if (ret > -0.5)
		return ret;
	ret = 0.0;
	for (int there = 0; there < n; ++there)
		if (connected[here][there])
			ret += search3(there, days - 1) / deg[there];
	return ret;
}

#if 0 // 완전 탐색

int main(void) {
	int testcase, t;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &d, &p);
		for (int i = 0; i < n; i++) {
			deg[i] = 0;
			for (int j = 0; j < n; j++) {
				scanf("%d", &connected[i][j]);
				if (connected[i][j] == 1)
					deg[i]++;
			}
		}

		scanf("%d", &t);
		for (int i = 0; i < t; i++) {
			scanf("%d", &q);

			vector<int> path;
			path.push_back(p);
			if (i == 0)
			printf("%.8lf", search(path));
			else
			printf(" %.8lf", search(path));
		}
		printf("\n");
	}
	return 0;
}

#endif

#if 0 // DP1

int main(void) {
	int testcase, t;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &d, &p);
		for (int i = 0; i < n; i++) {
			deg[i] = 0;
			for (int j = 0; j < n; j++) {
				scanf("%d", &connected[i][j]);
				if (connected[i][j] == 1)
					deg[i]++;
			}
		}

		scanf("%d", &t);
		for (int i = 0; i < t; i++) {
			scanf("%d", &q);

			for (int i = 0; i <= n; i++) {
				for (int j = 0; j <= d; j++) {
					cache[i][j] = -1.0;
				}
			}

			if (i == 0)
				printf("%.8lf", search2(p, 0));
			else
				printf(" %.8lf", search2(p, 0));
		}
		printf("\n");
	}
	return 0;
}

#endif

int main(void) {
	int testcase, t;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &d, &p);
		for (int i = 0; i < n; i++) {
			deg[i] = 0;
			for (int j = 0; j < n; j++) {
				scanf("%d", &connected[i][j]);
				if (connected[i][j] == 1)
					deg[i]++;
			}
		}

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= d; j++) {
				cache[i][j] = -1.0;
			}
		}

		scanf("%d", &t);
		for (int i = 0; i < t; i++) {
			scanf("%d", &q);

			if (i == 0)
				printf("%.8lf", search3(q, d));
			else
				printf(" %.8lf", search3(q, d));
		}
		printf("\n");
	}
	return 0;
}
