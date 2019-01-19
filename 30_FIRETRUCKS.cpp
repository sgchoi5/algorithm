#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int INF = 987654321;
const int MAX_V = 1001;
// 코드 30.1 다익스트라의 최단 거리 알고리즘의 구현

// 정점의 개수
int V;
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다
vector<pair<int, int> > adj[MAX_V];

vector<int> dijkstra(int src) {
	vector<int> dist(V + 1, INF);
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

int main(void) {
	vector<int> firePlace;
	int C, /* V, */ E, n, m, a, b, t, ans;
	scanf("%d", &C);
	while (C--) {
		ans = 0;
		for (int i = 0; i <= V; i++) {
			adj[i].clear();
		}
		firePlace.clear();

		scanf("%d %d %d %d", &V, &E, &n, &m);

		for (int i = 0; i < E; i++) {
			scanf("%d %d %d", &a, &b, &t);
			adj[a].push_back({ b, t });
			adj[b].push_back({ a, t });
		}

		firePlace.assign(n, 0);
		for (int i = 0; i < n; i++) {
			scanf("%d", &firePlace[i]);
		}

		for (int i = 0; i < m; i++) {
			int temp;
			scanf("%d", &temp);
			adj[0].push_back({ temp, 0 });
			adj[temp].push_back({ 0, 0 });
		}

		vector<int> dist = dijkstra(0);
		for (int i = 0; i < n; i++) {
			ans += dist[firePlace[i]];
		}
		printf("%d\n", ans);
	}
	return 0;
}
