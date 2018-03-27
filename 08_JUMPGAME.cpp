#include <cstdio>  
#define MAX 100  
int board[MAX + 1][MAX + 1];
int memo[MAX + 1][MAX + 1];
int TC, N;
void init(void) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            memo[i][j] = -1;
}
int jump(int y, int x) {
    if (y >= N || x >= N)
        return 0;
    if (y == N - 1 && x == N - 1)
        return 1;
    int& ret = memo[y][x];
    if (ret != -1)
        return ret;
    return ret = jump(y + board[y][x], x) || jump(y, x + board[y][x]);
}
int main(void) {
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                scanf("%d", &board[i][j]);
            }
        init();
        if (jump(0, 0) > 0)
            printf("%s", "YES\n");
        else
            printf("%s", "NO\n");
    }
    return 0;
}
