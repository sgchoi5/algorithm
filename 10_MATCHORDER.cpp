#include <cstdio>  
#include <vector>  
#include <set>  
using namespace std;
// 출전 순서 정하기 문제를 해결하는 탐욕적 알고리즘  
int order(const vector<int>& russian, const vector<int>& korean) {
    int n = russian.size(), wins = 0;
    // 아직 남아 있는 선수들의 레이팅  
    multiset<int> ratings(korean.begin(), korean.end());
    for (int rus = 0; rus < n; ++rus) {
        // 가장 레이팅이 높은 한국 선수가 이길 수 없는 경우  
        // 가장 레이팅이 낮은 선수와 경기시킨다  
        if (*ratings.rbegin() < russian[rus])
            ratings.erase(ratings.begin());
        // 이 외의 경우 이길 수 있는 선수 중 가장 레이팅이 낮은 선수와 경기시킨다  
        else {
            ratings.erase(ratings.lower_bound(russian[rus]));
            ++wins;
        }
    }
    return wins;
}
int main(void) {
    int T, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        vector<int> rus, kor;
        rus.resize(N);
        kor.resize(N);
        for (int i = 0; i < N; i++)
            scanf("%d", &rus[i]);
        for (int i = 0; i < N; i++)
            scanf("%d", &kor[i]);
        printf("%d\n", order(rus, kor));
    }
    return 0;
}