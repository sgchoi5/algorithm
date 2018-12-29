// 코드 28.8 간선을 구분하는 깊이 우선 탐색의 구현

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;
// discovered[i] = i 번 정점의 발견 순서
// finished[i] = dfs(i)가 종료했으면 1, 아니면 0
vector<int> discovered, finished;
// 지금까지 발견된 정점의 수
int counter;

void dfs2(int here) {
	discovered[here] = counter++;
	// 모든 인접 정점을 순회하면서
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		printf("(%d, %d) is a ");
		// 아직 방문한 적 없다면 방문한다
		if (discovered[there] == -1) {
			printf("tree edge\n");
			dfs2(there);
		}
		// 만약 there가 here보다 늦게 발견됐으면 there는 here의 후손이다
		else if (discovered[here] < discovered[there])
			printf("forward edge\n");
		// 만약 dfs2(there)가 아직 종료하지 않았으면 there는 here의 선조다  
		else if (finished[there] == 0)
			printf("back edge\n");
		// 이 외의 경우는 모두 교차 간선
		else
			printf("cross egde\n");
	}
	finished[here] = 1;
}
