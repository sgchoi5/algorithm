#include <cstdio>
#include <vector>
using namespace std;
// 코드 24.7 펜윅 트리의 완전한 구현

// 펜윅 트리의 구현. 가상의 배열 A[]의 부분 합을
// 빠르게 구현할 수 있도록 한다. 초기화시에는 A[]의
// 원소가 전부 0이라고 생각한다.

struct FenwickTree {
	vector<long long> tree;
	FenwickTree(int n) : tree(n + 1) {}
	// A[0..pos]의 부분 합을 구한다
	long long sum(int pos) {
		// 인덱스가 1 부터 시작한다고 생각하자
		++pos;
		long long ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			// 다음 구간을 찾기 위해 최종 비트를 지운다
			pos &= (pos - 1);
		}
		return ret;
	}
	// A[pos]에 val을 더한다
	void add(int pos, long long val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

// 코드 24.8 삽입 정렬 시간 재기 문젤르 펜윅 트리로 해결하기

// 펜윅 트리를 이용해 문제를 해결한다
long long coundMove(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}

int main(void) {
	int C, N;
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		vector<int> num;
		num.resize(N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &num[i]);
		}
		printf("%d\n", coundMove(num));
	}
	return 0;
}
