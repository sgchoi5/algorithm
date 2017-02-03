#include <cstdio>  
#include <vector>  
#include <algorithm>  
using namespace std;
// 배열의 구간 최소 쿼리(RMQ) 문제를 해결하는 구간 트리의 초기화  
// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현  
struct RMQ {
    // 배열의 길이  
    int n;
    // 각 구간의 최소치  
    vector<int> rangeMin;
    RMQ(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n - 1, 1);
    }
    // node 노드가 array[left..right] 배열을 표현할 때  
    // node 를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다  
    int init(const vector<int>& array, int left, int right, int node) {
        if (left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
    // RMQ 문제를 푸는 구간 트리에서 질의 연산의 구현  
#ifndef INT_MAX  
    const int INT_MAX = numeric_limits<int>::max();
#endif  
    // node 가 표현하는 범위 array[nodeLeft, nodeRight]가 주어질 때  
    // 이 범위와 array[left, right[ 의 교집합의 최소치를 구한다  
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        // 두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨  
        if (right < nodeLeft || nodeRight < left)
            return INT_MAX;
        // node가 표현하는 범위가 array[left..right] 에 완전히 포함되는 경우  
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        // 양쪽 구간을 나눠서 푼 뒤 결과를 합친다  
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
            query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
    // query()를 외부에서 호출하기 위한 인터페이스  
    int query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
    // RMQ 문제를 푸는 구간 트리에서 갱신 연산의 구현  
    // array[index] = newValue 로 바뀌었을 때 node 를 루트로 하는  
    // 구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다  
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        //index 가 노드의 표현하는 구간과 상관없는 경우엔 무시한다  
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        // 트리의 리프까지 내려온 경우  
        if (nodeLeft == nodeRight)
            return rangeMin[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(
            update(index, newValue, node * 2, nodeLeft, mid),
            update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
    }
    // update() 를 외부에서 호출하기 위한 인터페이스  
    int udpate(int index, int newValue) {
        return update(index, newValue, 1, 0, n - 1);
    }
};
// 최대치와 최소치의 차이를 찾는 문제로  
// RMQ 를 재활용한다  
int main(void) {
    vector<int> minArray;
    vector<int> maxArray;
    int C, N, Q, a, b;
    scanf("%d", &C);
    while (C--) {
        scanf("%d %d", &N, &Q);
        minArray.resize(N);
        maxArray.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &minArray[i]);
            maxArray[i] = minArray[i] * -1;
        }
        RMQ minRMQ(minArray);
        RMQ maxRMQ(maxArray);
        for (int i = 0; i < Q; i++) {
            scanf("%d %d", &a, &b);
            printf("%d\n", maxRMQ.query(a, b) * -1 - minRMQ.query(a, b));
        }
    }
    return 0;
}