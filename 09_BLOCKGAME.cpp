#include <cstdio>
#include <vector>
using namespace std;

// 코드 9.22 블록 게임 문제를 해결하는 동적 계획법 알고리즘
vector<int> moves;
inline int cell(int y, int x) {
	return 1 << (y * 5 + x);
}

// 게임판에 놓을 수 있는 블록들의 위치를 미리 계산한다
void precalc() {
	// 세 칸짜리 L자 모양 블록으로 계산한다
	for (int y = 0; y < 4; ++y)
		for (int x = 0; x < 4; ++x) {
			vector<int> cells;
			for (int dy = 0; dy < 2; ++dy)
				for (int dx = 0; dx < 2; ++dx)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cells[i]);
		}
	// 두 칸짜리 블록들을 계산한다
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
// 현재 게임판 상태가 board일 때 현재 차례인 사람이 승리할지 여부를 반환한다
// (y, x) 칸에 블록이 있다. <=> (y*5+x)번 비트가 켜져 있다

char play(int board) {
	// 메모이제이션
	char& ret = cache[board];
	if (ret != -1)
		return ret;
	ret = 0;
	// 모든 수를 고려한다
	for (int i = 0; i < moves.size(); ++i)
		// 이 수를 이 게임판에 놓을 수 있는가 확인
		if ((moves[i] & board) == 0)
			if (!play(board | moves[i])) {
				ret = 1;
				break;
			}
	return ret;
}

char line[6];

int main(void) {
	int C, boardState;
	precalc();

	scanf("%d\n", &C);
	while (C--) {
		boardState = 0;
		for (int i = (1 << 25) - 1; i >= 0; i--) {
			cache[i] = -1;
		}

		for (int i = 0; i < 5; i++) {
			gets(line);
			for (int j = 0; j < 5; j++) {
				if (line[j] == '#') {
					boardState += cell(i, j);
				}
			}
		}

		if (play(boardState) > 0)
			printf("WINNING\n");
		else
			printf("LOSING\n");
	}
	return 0;
 }
