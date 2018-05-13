#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

// 코드 19.3 외계 신호 분석 문제를 해결하는 가장 간단한 알고리즘
int simple(const vector<int>& signals, int k) {
	int ret = 0;
	for (int head = 0; head < signals.size(); ++head) {
		int sum = 0;
		for (int tail = head; tail < signals.size(); ++tail) {
			// sum은 [head, tail] 구간의 합니다
			sum += signals[tail];
			if (sum == k)
				ret++;
			if (sum >= k)
				break;
		}
	}
	return ret;
}

// 코드 19.4 외계 신호 분석 문제를 해결하는 최적화된 알고리즘
int optimized(const vector<int>& signals, int k) {
	int ret = 0, tail = 0, rangeSum = signals[0];
	for (int head = 0; head < signals.size(); ++head) {
		// rangeSum 이 k 이상인 최초의 구간을 만날 때까지 tail을 옮긴다
		while (rangeSum < k && tail + 1 < signals.size())
			rangeSum += signals[++tail];

		if (rangeSum == k)
			ret++;

		// signals[head]는 이제 구간에서 빠진다
		rangeSum -= signals[head];
	}
	return ret;
}

// 코드 19.6 외계 신호 분석 문제에서 사용하는 선형 합동 난수 생성기의 구현

struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};

// 코드 19.5 외계 신호 분석 문제를 해결하는 온라인 알고리즘
int countRanges(int k, int n) {
	RNG rng; // 신호값을 생성하는 난수 생성기
	queue<int> range; // 현재 구간에 들어 있는 숫자들을 저장하는 큐
	int ret = 0, rangeSum = 0;
	for (int i = 0; i < n; i++) {
		// 구간에 숫자를 추가한다
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);

		// 구간의 합이 k를 초과하는 동안 구간에서 숫자를 뺀다
		while (rangeSum > k) {
			rangeSum -= range.front();
			range.pop();
		}

		if (rangeSum == k)
			ret++;
	}
	return ret;
}

int main(void) {
	int C, K, N;
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &K, &N);
		printf("%d\n", countRanges(K, N));
	}
	return 0;
}
