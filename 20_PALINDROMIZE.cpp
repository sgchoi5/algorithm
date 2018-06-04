#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 코드 20.3 단순한 문자열 알고리즘을 이용해 부분 일치 테이블 계산하기
// pi[]를 계산한다
// pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatchNative(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	// 단순한 문자열 검색 알고리즘을 구현한다
	for (int begin = 1; begin < m; ++begin) {
		for (int i = 0; i + begin < m; ++i) {
			if (N[begin + i] != N[i])
				break;
			// i+1 글자가 서로 대응되었다
			pi[begin + i] = max(pi[begin + i], i + 1);
		}
	}
	return pi;
}

// 코드 20. 4 KMP 알고리즘을 이용해 부분 일치 테이블을 생성하기

// N 에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해
// pi[]를 계산한다
// pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이

vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	// KMP로 자기 자신을 찾는다
	// N을 N에서 찾는다. begin = 0이면 자기 자신을 찾아버리니까 안 됨!
	int begin = 1, matched = 0;
	// 비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

// 코드 20.6 팰린드롬 만들기 문제를 해결하는 KMP 알고리즘의 변형

// a의 접미사이면서 b의 접두사인 문자열의 최대 길이를 구한다
int maxOverlab(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	// begin = matched = 0 에서부터 시작하자
	int begin = 0, matched = 0;
	while (begin < n) {
		// 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
		if (matched < m && a[begin + matched] == b[matched]) {
			++matched;
			if (begin + matched == n)
				return matched;
		}
		else {
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}

int main(void) {
	int C, len = 0;
	ios_base::sync_with_stdio(false);

	cin >> C;
	while (C--) {
		string a, b;
		cin >> a;
		len = a.length();
		b = a;
		reverse(b.begin(), b.end());
		cout << len * 2 - maxOverlab(a, b) << '\n';
	}

	return 0;
}
