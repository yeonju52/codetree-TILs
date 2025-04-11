#include<iostream>
#include<cstring>

using namespace std;

const int MAX = 99;

struct posd {
	int x, y, d;
	bool operator==(const posd&other) const {
		return (other.x == x && other.y == y);
	}
};

struct pos {
	int x, y;
	bool operator==(const pos&other) const {
		return (other.x == x && other.y == y);
	}
};

int N, M, H, K;
int board[MAX][MAX];
posd theif[MAX * MAX]; // M까지
posd path[101];

//(상)(우)(하)(좌) 택
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void find_path();

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	ios::sync_with_stdio(0);
	cin.tie(0);

	//cin >> T;
	T = 1;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(board, 0, sizeof(board));
		memset(theif, 0, sizeof(theif));

		cin >> N >> M >> H >> K;
		for (int i = 0; i < M; i++) {
			int x, y, d;
			cin >> x >> y >> d;
			theif[i] = { x - 1, y - 1, d };
		}
		for (int i = 0; i < H; i++) {
			int x, y;
			cin >> x >> y;
			board[x - 1][y - 1] = 1;
		}

		// 술래 경로 찾기
		find_path();

		int ans = 0;
		for (int k = 1; k <= K; k++) {
			posd &men = path[k - 1];
			// 도망자 움직이기
			for (int i = 0; i < M; i++) {
				posd &t = theif[i];
				if (t.d < 0) continue;
				if (abs(t.x - men.x) + abs(t.y - men.y) > 3) continue;
				int nx = t.x + dx[t.d], ny = t.y + dy[t.d];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
					t.d ^= 2;
					nx = t.x + dx[t.d], ny = t.y + dy[t.d];
				}
				if (nx == men.x && ny == men.y) continue;
				t.x = nx, t.y = ny;
			}
			// 술래잡기
			men = path[k];
			int mx = men.x, my = men.y;
			for (int i = 0; i < 3; i++) {
				mx += dx[men.d], my += dy[men.d];
				for (int i = 0; i < M; i++) {
					posd &t = theif[i];
					if (t.d < 0) continue;
					if ((t.x == mx) && (t.y == my)) {
						if (board[t.x][t.y]) break;
						t.d = -1;
						ans += k;
						break;
					}
				}
			}
		}

		cout << ans << "\n";
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

void find_path() {
	posd start = { N / 2, N / 2, 0 };
	posd end = { 0, 0, 0 }; // 0, 0으로 변경 필요

	posd cur = start;
	int base = 1;
	int mode = 1;
	
	int k = 0;
	path[k++] = start; 
	while(k <= K) {
		int b = 2;
		while (b--) {
			for (int i = 0; i < base; i++ && k < K) {
				cur.x += dx[cur.d], cur.y += dy[cur.d];
				if (cur == end) { cur.d = 2; mode = -1; i = -1; base--;  b = 2; } // 방향 전환
				if (cur == start) { cur.d = 0; mode = 1; i = -1; b = 1; } // 반복문 초기화
				path[k++] = cur;
			}
			cur.d = (cur.d + (1 * mode) + 4) % 4;
			path[k - 1].d = cur.d; // 마지막은 보는 방향으로 바꾸기
		}
		base = base + (1 * mode);
	}

	return;
}