#include <cstdio>  
int max(int a, int b) {
    return a > b ? a : b;
}
int n, triangle[100][100];
int cache2[100][100];
// (y, x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.  
int path2(int y, int x) {
    // 기저 사례  
    if (y == n - 1)
        return triangle[y][x];
    // 메모이제이션  
    int& ret = cache2[y][x];
    if (ret != -1)
        return ret;
    return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}
int main(void) {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                scanf("%d", &triangle[i][j]);
                cache2[i][j] = -1;
            }
        }
        printf("%d\n", path2(0, 0));
    }
    return 0;
}
