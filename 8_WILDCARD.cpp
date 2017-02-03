#include <iostream>  
#include <string>  
#include <vector>  
#include <algorithm>  
using namespace std;
// WILDCARD 문제를 해결하는 동적 계획법 알고리즘  
// -1은 아직 답이 계산되지 않았음을 의미한다  
// 1은 해당 입력들이 서로 대응됨을 의미한다  
// 0은 해당 입력들이 서로 대응되지 않음을 의미한다  
int cache[101][101];
// 패턴과 문자열  
string W, S;
// 와일드카드 패턴 W[w..] 문자열 S[s..] 에 대응되는지 여부를 반환한다  
bool matchMemoized(int w, int s) {
    // 메모이제이션  
    int& ret = cache[w][s];
    if (ret != -1)
        return ret;
    // W[w] 와 S[s] 를 맞춰나간다  
    while (s < S.size() && w < W.size() &&
        (W[w] == '?' || W[w] == S[s])) {
        ++w;
        ++s;
    }
    // 더이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다  
    // 2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참  
    if (w == W.size())
        return ret = (s == S.size());
    // 4. *를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀 호출하면서 확인한다  
    if (W[w] == '*')
        for (int skip = 0; skip + s <= S.size(); ++skip)
            if (matchMemoized(w + 1, s + skip))
                return ret = 1;
    // 3. 이 외의 경우에는 모두 대응되지 않는다  
    return ret = 0;
}
bool matchMemoized2(int w, int s) {
    // 메모이제이션  
    int& ret = cache[w][s];
    if (ret != -1)
        return ret;
    // W[w] 와 S[s] 를 맞춰나간다  
    if (w < W.size() && s < S.size() &&
        (W[w] == '?' || W[w] == S[s]))
        return ret = matchMemoized2(w + 1, s + 1);
    // 더이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다  
    // 2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참  
    if (w == W.size())
        return ret = (s == S.size());
    // 4. *를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀 호출하면서 확인한다  
    if (W[w] == '*') {
        if (matchMemoized2(w + 1, s) ||
            (s < S.size() && matchMemoized2(w, s + 1)))
            return ret = 1;
    }
    // 3. 이 외의 경우에는 모두 대응되지 않는다  
    return ret = 0;
}
void init(void) {
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            cache[i][j] = -1;
        }
    }
}
int main(void) {
    int C, count;
    vector<string> result;
    std::ios::sync_with_stdio(false);
    cin >> C;
    W.reserve(101);
    S.reserve(101);
    while (C--) {
        count = 0;
        cin >> W;
        cin >> count;
        while (count--) {
            init();
            cin >> S;
            if (matchMemoized2(0, 0))
                result.push_back(S);
            S.clear();
        }
        W.clear();
        sort(result.begin(), result.end());
        for (string n : result)
            cout << n << endl;
        result.clear();
    }
    return 0;
}