#include <cstdio>  
#include <vector>  
#include <queue>  
#include <functional>  
using namespace std;
// 정수를 답는 최대 힙 heap에 새 원소 newValue를 삽입한다  
void push_heap(vector<int>& heap, int newValue) {
    // 힙의 맨 끝에 newValue를 삽입한다  
    heap.push_back(newValue);
    // 현재 newValue의 위치  
    int idx = heap.size() - 1;
    // 루트에 도달하거나 newValue 이상의 원소를 가진 조상을 만날 때까지  
    while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
        swap(heap[idx], heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}
// 정수를 담는 최대 힙 heap에서 heap[0]를 제거한다  
void pop_heap(vector<int>& heap) {
    // 힙의 맨 끝에서 값을 가져와 루트에 덮어씌운다  
    heap[0] = heap.back();
    heap.pop_back();
    int here = 0;
    while (true) {
        int left = here * 2 + 1, right = here * 2 + 2;
        // 리프에 도달한 경우  
        if (left >= heap.size()) break;
        // heap[here]가 내려갈 위치를 찾는다  
        int next = here;
        if (heap[next] < heap[left])
            next = left;
        if (right < heap.size() && heap[next] < heap[right])
            next = right;
        if (next == here) break;
        swap(heap[here], heap[next]);
        here = next;
    }
}
struct RNG {
    int seed, a, b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next() {
        int ret = seed;
        seed = ((seed*(long long)a) + b) % 20090711;
        return ret;
    }
};
// 트립의 노드를 표현하는 객체의 구현   
typedef int KeyType;
// 트립의 한 노드를 저장한다   
struct Node {
    // 노드에 저장된 원소   
    KeyType key;
    // 이 노드의 우선순위(priority)   
    // 이 노드를 루트로 하는 서브트리의 크기(size)   
    int priority, size;
    // 두 자식 노드의 포인터   
    Node *left, *right;
    // 생성자에서 난수 우선순위를 생성하고, size와 left/right 를 초기화한다   
    Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {
    }
    void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
    void setRight(Node* newRight) { right = newRight; calcSize(); }
    // size 멤버를 갱신한다   
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};
typedef pair<Node*, Node*> NodePair;
// root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는   
// 두 개의 트립으로 분리한다   
NodePair split(Node* root, KeyType key) {
    if (root == NULL)
        return NodePair(NULL, NULL);
    // 루트가 key 미만이면 오른쪽 서브트리를 쪼갠다   
    if (root->key < key) {
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    // 루트가 key 이상이면 왼쪽 서브트리를 쪼갠다   
    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}
// root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의   
// 루트를 반환한다   
Node* insert(Node* root, Node* node) {
    if (root == NULL)
        return node;
    // node가 루트를 대체해야 한다. 해당 서브트리를 반으로 잘라   
    // 각각 자손으로 한다   
    if (root->priority < node->priority) {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if (node->key < root->key)
        root->setLeft(insert(root->left, node));
    else
        root->setRight(insert(root->right, node));
    return root;
}
// root를 루트로 하는 트리 중에서 k번째 원소를 반환한다   
Node* kth(Node* root, int k) {
    // 왼쪽 서브트리의 크기를 우선 계산한다   
    int leftSize = 0;
    if (root->left != NULL) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left, k);
    if (k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}
// rng가 생성하는 첫 n개의 난수를 수열에 추가하며 중간 값을 구한다  
int runningMedian(int n, RNG rng) {
    Node* root = NULL;
    int ret = 0;
    for (int cnt = 1; cnt <= n; ++cnt) {
        root = insert(root, new Node(rng.next()));
        int median = kth(root, (cnt + 1) / 2)->key;
        ret = (ret + median) % 20090711;
    }
    return ret;
}
int runningMedian2(int n, RNG rng) {
    priority_queue<int, vector<int>, less<int> > maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int ret = 0;
    // 반복문 불변식:  
    // 1. maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다  
    // 2. maxHeap.top() <= minHeap.top()  
    for (int cnt = 1; cnt <= n; ++cnt) {
        // 우선 1 번 불변식부터 만족시킨다  
        if (maxHeap.size() == minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        // 2 번 불변식이 깨졌을 경우 복구하자  
        if (!minHeap.empty() && !maxHeap.empty() &&
            minHeap.top() < maxHeap.top()) {
            int a = maxHeap.top(), b = minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret = (ret + maxHeap.top()) % 20090711;
    }
    return ret;
}
int main(void) {
    int T, N, a, b;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &a, &b);
        printf("%d\n", runningMedian(N, RNG(a, b)));
        //printf("%d\n", runningMedian2(N, RNG(a, b)));  
    }
    return 0;
}