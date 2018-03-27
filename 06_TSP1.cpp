#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10;
const int INF = 987654321;

// 코드 6.7 여행하는 외판원 문제를 해결하는 재귀 호출 알고리즘

int N; // 도시의 수
double dist[MAX][MAX]; // 두 도시 간의 거리를 저장하는 배열
// path: 지금까지 만든 경로
// visited: 각 도시의 방문 여부
// currentLength: 지금까지 만든 경로의 길이
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	// 기저 사례: 모든 도시를 다 방문했을 때는 시작 도시로 돌아가고 종료한다
	if (path.size() == N)
		return currentLength /* + dist[path[0]][path.back()] */;
	
	double ret = INF; // 매우 큰 값으로 초기화
	// 다음 방문할 도시를 전부 시도해 본다
	for (int next = 0; next < N; ++next) {
		if (visited[next])
			continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;
		// 나머지 경로를 재귀 호출을 통해 완성하고 가장 짧은 경로의 길이를 얻는다
		double cand = shortestPath(path, visited, currentLength + dist[here][next]);
		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}

int main(void) {
	int C;
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%lf", &dist[i][j]);
			}
		}
		double ans = INF;
		for (int i = 0; i < N; i++) {
			vector<int> path;
			path.push_back(i);
			vector<bool> visited(N, 0);
			visited[i] = true;
			ans = min(shortestPath(path, visited, 0), ans);
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}
