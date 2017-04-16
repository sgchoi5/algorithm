#include <cstdio>
#include <string>
using namespace std;

char board[5][6];
char word[11];
int dp[5][5][10];

void init(void) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 10; k++) {
				dp[i][j][k] = -1;
			}
		}
	}
}

bool inRange(const int& y, const int& x) {
	if (y < 0 || x < 0 || y > 4 || x > 4) {
		return false;
	}
	return true;
}

const int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[8] = {-1, 0, 1, -1, 0, 1, -1, 1};
// 5*5의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환
bool hasWord(int y, int x, int index, const string& word) {
	// 기저 사례1: 시작 위치가 범위 밖이면 무조건 실패
	if (!inRange(y, x))
		return false;
	// 기저 사례2: 첫 글자가 일치하지 않으면 실패
	if (board[y][x] != word[0])
		return false;
	// 기저 사례3: 단어 길이가 1이면 성공
	if (word.size()	== 1)
		return true;

	if (dp[y][x][index] != -1)
		return dp[y][x][index];

	int& ret = dp[y][x][index];
	ret = false;

	// 인접한 여덟 칸을 검사한다
	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction];
		int nextX = x + dx[direction];
		// 다음 칸이 범위 안에 있는지, 첫 글자는 일치하는 확인할 필요가 없다
		if (hasWord(nextY, nextX, index + 1, word.substr(1))) {
			ret = true;
			return ret;
		}
	}
	return ret;
}

int main(void) {
	int C, N;
	scanf("%d", &C);
	while (C--) {
		for (int i = 0; i < 5; i++)
			scanf("%s", board[i]);
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", word);
			bool found = false;
			init();
			for (int i = 0; i < 5 && !found; i++) {
				for (int j = 0; j < 5 && !found; j++) {
					if (board[i][j] == word[0])
						if (hasWord(i, j, 0, word))
							found = true;
				}
			}
			printf("%s %s\n", word, found ? "YES" : "NO");
		}
	}
	return 0;
}