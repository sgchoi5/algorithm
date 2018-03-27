#include <cstdio>  
int price[1001];
int main(void) {
    int T;
    int L, N, count;
    double total, avg, temp;
    scanf("%d", &T);
    while (T--) {
        avg = 101;
        scanf("%d %d", &N, &L);
        for (int i = 0; i < N; i++)
            scanf("%d", &price[i]);
        for (int i = 0; i <= N - L; i++) {
            for (int k = L + i; k <= N; k++) {
                count = 0;
                total = 0;
                for (int j = i; j < k && j < N; j++) {
                    total += price[j];
                    count++;
                }
                temp = total / (double)count;
                if (avg > temp)
                    avg = temp;
            }
        }
        printf("%.10f\n", avg);
    }
    return 0;
}
