#include <cstdio>
#include <string>
using namespace std;
/*
int abs(int a) {
    return a >= 0 ? a : -a;
}
*/
int min(int a, int b) {
    return a > b ? b : a;
}

// 코드 8.14 원주율 외우기 문제를 해결하는 동적 계획법 알고리즘
const int INF = 987654321;
string N;

// N[a..b] 구간의 난이도를 반환한다
int classify(int a, int b) {
    // 숫자 조각을 가져온다
    string M = N.substr(a, b - a + 1);
    // 첫 글자만으로 이루진 문자열과 같으면 난이도는 1
    if (M == string(M.size(), M[0]))
        return 1;
    // 등차수열인지 검사한다
    bool progressive = true;
    for (int i = 0; i < M.size() - 1; ++i)
        if (M[i + 1] - M[i] != M[1] - M[0])
            progressive = false;
    if (progressive && abs(M[1] - M[0]) == 1)
        return 2;
    // 두 수가 번갈아 등장하는지 확인한다
    bool alternative = true;
    for (int i = 0; i < M.size(); ++i)
        if (M[i] != M[i % 2])
            alternative = false;
    if (alternative) // 두 수가 번갈아 등장하면 난이도는 4
        return 4;
    if (progressive) // 공차가 1 아닌 등차수열의 난이도는 5
        return 5;
    return 10; // 이 외는 모두 난이도 10
}

int cache[10002];
// 수열 N[begin..]를 외우는 방법 중 난이도의 최소 합을 출력한다
int memorize(int begin) {
    // 기저 사례: 수열의 끝에 도달했을 경우
    if (begin == N.size())
        return 0;
    // 메모이제이션
    int& ret = cache[begin];
    if (ret != -1)
        return ret;
    ret = INF;
    for (int L = 3; L <= 5; ++L)
        if (begin + L <= N.size())
            ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
    return ret;
}

char PI[10001];

void init(int size) {
    for (int i = 0; i < size; i++) {
        cache[i] = -1;
    }
}

int main(void) {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%s\n", PI);
        N = PI;
        init(N.size());
        printf("%d\n", memorize(0));
    }
    return 0;
}