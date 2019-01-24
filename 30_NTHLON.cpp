#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

const int INF = 987654321;

// 코드 30.3 다익스트라 알고리즘을 이용해 철인 N종 경기 문제를 해결하기

// 정점의 개수
int V;
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다
vector<pair<int, int> > adj[410];
const int START = 401;

vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다
		if (dist[here] < cost)
			continue;
		// 인접한 정점들을 모두 검사한다
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

// (A국 선수의 예상 시간 - B국 선수의 예상 시간)의 정점 번호를 반환한다
int vertex(int delta) {
	return delta + 200;
}

// a[] = A국 선수의 종목별 예상 시간
// b[] = B국 선수의 종목별 예상 시간
int solve(const vector<int>& a, const vector<int>& b) {
	// 그래프를 만든다
	V = 402;
	for (int i = 0; i < V; i++)
		adj[i].clear();
	for (int i = 0; i < a.size(); i++) {
		int delta = a[i] - b[i];;
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}
	// 현재 차이
	for (int delta = -200; delta <= 200; ++delta) {
		// i번 종목을 뒤에 붙인다면?
		for (int i = 0; i < a.size(); ++i) {
			int next = delta + a[i] - b[i];
			// 시간 차이의 절대 값이 200을 넘는 정점은 만들 필요가 없다
			if (abs(next) > 200)
				continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(START);
	int ret = shortest[vertex(0)];
	if (ret == INF)
		return -1;
	return ret;
}

int main(void) {
	int C, M, ans;
	vector<int> a, b;
	scanf("%d", &C);
	while (C--) {
		a.clear();
		b.clear();
		scanf("%d", &M);
		a.assign(M, 0);
		b.assign(M, 0);
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &a[i], &b[i]);
		}
		ans = solve(a, b);
		if (ans != -1)
			printf("%d\n", ans);
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}
