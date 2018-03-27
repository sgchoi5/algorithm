#include <cstdio>
#include <string>
using namespace std;

char compressed[1001];

string reverse(string::iterator& it) {
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);
	// 각각 위와 아래 조각들의 위치를 바꾼다
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main(void) {
	int C;
	scanf("%d", &C);
	while (C--) {
		scanf("%s", compressed);
		string comp(compressed);

		string::iterator it = comp.begin();
		printf("%s\n", reverse(it).c_str());
	}
	return 0;
}
