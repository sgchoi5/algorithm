#include <cstdio>  
#include <string>  
#include <vector>  
using namespace std;
//KMP 알고리즘을 이용해 부분 일치 테이블을 생성하기  
// N 에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해  
// pi[i]를 계산한다  
// pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이  
vector<int> getPartialMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0);
    // KMP 로 자기 자신을 찾는다  
    // N 을 N 에서 찾는다. begin = 0 이면 자기 자신을 찾아버리니까 안됨!  
    int begin = 1, matched = 0;
    // 비교할 문자가 N 의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다  
    while (begin + matched < m)
    {
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
// S의 접두사도 되고 접미사도 되는 모든 문자열의 길이를 계산하기  
// s의 접두사도 되고 접미사도 되는 문자열들의 길이를 반환한다  
vector<int> getPrefixSuffix(const string& s) {
    vector<int> ret, pi = getPartialMatch(s);
    int k = s.size();
    while (k > 0) {
        // s[..k-1]는 답이다  
        ret.push_back(k);
        // s[..k-1]의 접미사도 되고 접두사도 되는 문자열도 답이다  
        k = pi[k - 1];
    }
    return ret;
}
int strlen(char* c) {
    int cnt = 0;
    while (*c++ != '\0')
        cnt++;
    return cnt;
}
char name[400001];
int main(void) {
    scanf("%s", name);
    scanf("%s", name + strlen(name));
    vector<int> ret = getPrefixSuffix(name);
    for (int i = ret.size() - 1; i >= 0; i--)
        printf("%d ", ret[i]);
    return 0;
}