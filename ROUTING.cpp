#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int INF = 987654321;
const int MAX_V = 10000;
// 코드 30.1 다익스트라의 최단 거리 알고리즘의 구현

// 정점의 개수
int V;
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다
vector<pair<int, double> > adj[MAX_V];

vector<double> dijkstra(int src) {
	vector<double> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<double, int> > pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다
		if (dist[here] < cost)
			continue;
		// 인접한 정점들을 모두 검사한다
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			double nextDist = cost + log(adj[here][i].second);
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
	
	int C, /* V, */ N, M, a, b;
	double c;

	scanf("%d", &C);
	while (C--) {
		for (int i = 0; i < V; i++) {
			adj[i].clear();
		}

		scanf("%d %d", &N, &M);
		V = N;

		for (int i = 0; i < M; i++) {
			scanf("%d %d %lf", &a, &b, &c);
			adj[a].push_back({ b, c });
			adj[b].push_back({ a, c });
		}

		vector<double> dist = dijkstra(0);
		printf("%.10lf\n", exp(dist[N-1]));
	}
	return 0;
}
