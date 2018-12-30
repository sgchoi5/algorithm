#include <cstdio>
#include <vector>
using namespace std;

// 코드 28.11 감시 카메라 문제를 해결하는 알고리즘의 구현

const int MAX_V = 1000;

int V;
vector<int> adj[MAX_V];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

// 지금까지 설치한 카메라의 총 수
int installed;
// here로부터 기이 우선 탐색을 하고, here의 정보를 반환한다
int dfs(int here) {
	visited[here] = true;
	int children[3] = { 0, 0, 0 };
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (!visited[there])
			++children[dfs(there)];
	}
	// 자손 노드 중 감시되지 않는 노드가 있을 경우 카메라를 설치한다
	if (children[UNWATCHED]) {
		++installed;
		return INSTALLED;
	}
	// 자손 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요가 없다
	if (children[INSTALLED])
		return WATCHED;
	return UNWATCHED;
}

// 그래프를 감시하는 데 필요한 카메라의 최소 수를 반환한다
int installCamera() {
	installed = 0;
	visited = vector<bool>(V, false);
	for (int u = 0; u < V; ++u)
		if (!visited[u] && dfs(u) == UNWATCHED)
			++installed;
	return installed;
}

int main(void) {
	int C, G, H, u, v;
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &G, &H);
		V = G;
		for (int i = 0; i < H; i++) {
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		printf("%d\n", installCamera());
		for (int i = 0; i < V; i++) {
			adj[i].clear();
		}
	}
}
