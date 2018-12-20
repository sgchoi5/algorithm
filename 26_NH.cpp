#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>

using namespace std;

// 코드 26.5 아호-코라식 알고리즘을 위해 트라이의 각 노드에 추가적으로 계산해야 할 정보

// 알파벳 소문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; }

// 트라이의 한 노드를 나타내는 객체
struct TrieNode {
	int no;
	TrieNode* children[ALPHABETS];
	TrieNode* next[ALPHABETS];
	// 현 위치에서 끝나는 문자열의 번호
	int terminal;

	// 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
	TrieNode* fail;
	// 이 노드가 방문되었을 때 등장하는 문자열들의 번호
	vector<int> output;

	TrieNode() : terminal(-1), fail(NULL) {
		memset(children, 0, sizeof(children));
		memset(next, 0, sizeof(next));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i])
				delete children[i];
		}
	}

	// 이 노드를 루트로 하는 트라이에 번호가 id 인 문자열 key 를 추가한다
	void insert(const char* key, int id) {
		// 문자열이 끝나면 terminal 만 참으로 바꾸고 종료
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// 해당 자식 노드가 없다면 생성한다
			if (children[next] == NULL)
				children[next] = new TrieNode();
			// 해당 자식 노드로 재귀호출
			children[next]->insert(key + 1, id);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0)
			return this;
		int next = toNumber(*key);
		if (children[next] == NULL)
			return NULL;
		return children[next]->find(key + 1);
	}
};

// 코드 26.6 아호-코라식 알고리즘에서 실패 함수의 계산

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산한다.
void computeFailFunc(TrieNode* root) {
	// 루트에서부터 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결을 계산한다.
	queue<TrieNode*> q;
	// 루트의 실패 연결은 자기 자신
	root->fail = root;
	q.push(root);

	int num = 0; // 더해짐

	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();

		here->no = num++; // 더해짐

		// here 의 모든 노드에 대해 실패 연결을 계산하고 이들을 큐에 넣는다
		for (int edge = 0; edge < ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if (!child)
				continue;

			// 1레벨 노드의 실패 연결은 항상 루트
			if (here == root)
				child->fail = root;
			else {
				// 아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL)
					t = t->fail;
				if (t->children[edge])
					t = t->children[edge];
				child->fail = t;
			}
			// 출력 문자열 목록: 실패 연결에서 가져온 뒤,
			// 이 위치에서 끝나는 문자열이 있으면 추가한다
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

// 코드 26.7 아호-코라식 알고리즘의 실제 탐색 과정

// trie에 포함된 패턴들을 s에서 찾는다.
// s 내에서 패턴이 출현할 때마다 (마지막 글자, 패턴 번호) 의 쌍을 저장한다
vector<pair<int, int> > ahoCorasick(const string& s, TrieNode* root) {
	vector<pair<int, int> > ret;

	TrieNode* state = root;
	// 실제 루프 내는 KMP 와 별로 다를 것이 없다
	for (int i = 0; i < s.size(); ++i) {
		int chr = toNumber(s[i]);
		while (state != root && state->children[chr] == NULL)
			state = state->fail;
		if (state->children[chr])
			state = state->children[chr];
		for (int j = 0; j < state->output.size(); ++j)
			ret.push_back(make_pair(i, state->output[j]));
	}
	return ret;
}

// 코드 26.8 보안종결자 문제를 해결하는 동적 계획법 알고리즘
const int MOD = 10007;
int cache[101][1001];

// 앞으로 length 글자를 더 만들어야 하는데, 아호-코라식 알고리즘의
// 현재 상태가 state에 주어질 때 IDS 에 걸리지 않는 문자열의 수는?
int count(int length, TrieNode* state) {
	// 기저 사례: 이 상태에 문자열이 출현하면 곧장 종료
	if (state->output.size())
		return 0;
	// 기저 사례: 문자열을 전부 만든 경우
	if (length == 0)
		return 1;
	int& ret = cache[length][state->no];
	if (ret != -1)
		return ret;
	ret = 0;
	// 다음으로 letter 글자를 넣는 경우
	for (int letter = 0; letter < ALPHABETS; ++letter) {
		ret += count(length - 1, state->next[letter]);
		ret %= MOD;
	}
	return ret;
}

// 코드 26.9 트라이의 각 노드에 no와 next테이블을 계산하는 재귀 함수의 구현

// 상태 간의 전이 테이블을 next[]에 채운다. computeFailFunc()를 통해
// 이미 실패 함수가 계산되어 있다고 가정한다
void computeTransition(TrieNode* here, int& nodeCounter) {
	// 0에서 시작하는 번호를 매긴다: cache[]의 인덱스
	here->no = nodeCounter++;
	for (int chr = 0; chr < ALPHABETS; ++chr) {
		// next[] 값을 계산해 저장한다
		TrieNode* next = here;
		while (next != next->fail && next->children[chr] == NULL)
			next = next->fail;
		if (next->children[chr])
			next = next->children[chr];
		here->next[chr] = next;
		// 재귀적으로 모든 노드에 대해 전이 테이블을 계산한다
		if (here->children[chr])
			computeTransition(here->children[chr], nodeCounter);
	}
}

int main(void) {
	int C, N, M;
	scanf("%d", &C);
	while (C--) {
		memset(cache, -1, sizeof(cache));
		scanf("%d %d\n", &N, &M);

		TrieNode trie;
		char a[11];
		while (M--) {
			scanf("%s", a);
			trie.insert(a, M);
		}
		int nc = 0;
		computeFailFunc(&trie);
		computeTransition(&trie, nc);

		printf("%d\n", count(N, &trie));
	}
	return 0;
}
