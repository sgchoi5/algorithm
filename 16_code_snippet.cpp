#include <iostream>
using namespace std;

// boolean bitset for large size
// 35,000 * 50,000 bytes == 208 MB
// 20,000 * 50,000 bytes == 119 MB
const unsigned int MAX_N = 30000 * 50000;
unsigned char large[(MAX_N + 7) / 8];

inline bool bitIsTrue(unsigned int k) {
	return large[k >> 3] & (1 << (k & 7));
}

inline void bitSetTrue(unsigned int k) {
	large[k >> 3] |= 1 << (k & 7);
}

inline void bitSetFalse(unsigned int k) {
	large[k >> 3] &= ~(1 << (k & 7));
}

bool check(int n) {
	for (int i = 0; i < n; i++) {
		bitSetTrue(i);
	}

	for (int i = 0; i < n; i++) {
		if (!bitIsTrue(i)) {
			cout << "Something wrong!" << '\n';
			return false;
		}
	}

	for (int i = 0; i < n; i++) {
		bitSetFalse(i);
	}

	for (int i = 0; i < n; i++) {
		if (bitIsTrue(i)) {
			cout << "Something wrong!" << '\n';
			return false;
		}
	}
	cout << "Passed! (size: " << n << ")\n";
	return true;
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cout.tie(NULL);

	for (int i = 1; i < MAX_N; i *= 1000) {
		if (!check(i))
			break;
	}

	return 0;
}
