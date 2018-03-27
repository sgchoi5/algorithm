#include <cstdio>  
int max(int a, int b) {
    return a > b ? a : b;
}

int n;
int cache[501], S[501];
// S[start] 에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다
int lis2(int start) {
    int& ret = cache[start];
    if (ret != -1)
        return ret;
    // 항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for (int next = start + 1; next < n; ++next)
        if (S[start] < S[next])
            ret = max(ret, lis2(next) + 1);
    return ret;
}

int main(void) {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &S[i]);
            cache[i] = -1;
        }

        int maxLen = 0;
        for (int begin = 0; begin < n; ++begin)
            maxLen = max(maxLen, lis2(begin));

        printf("%d\n", maxLen);
    }
    return 0;
}
