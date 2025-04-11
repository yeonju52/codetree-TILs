#include<iostream>
#include<cstring>
#include<vector>

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
int tree[MAX][MAX];
int vis[MAX][MAX]; // 디버깅용

//(상)(우)(하)(좌) 택
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void move(vector<posd> &theif, const posd &men);
int play(vector<posd> &theif, const posd &men);
void display(const int arr[MAX][MAX]);

int main(int argc, char** argv)
{
	int test_case;
	int T;

	ios::sync_with_stdio(0);
	cin.tie(0);

	//cin >> T;
	T = 1;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		//memset(board, 0, sizeof(board));
		memset(tree, 0, sizeof(tree));
		vector<posd> theif; // M까지

		cin >> N >> M >> H >> K;
		for (int i = 0; i < M; i++) {
			int x, y, d;
			cin >> x >> y >> d;
			theif.push_back({ x - 1, y - 1, d });
		}
		for (int i = 0; i < H; i++) {
			int x, y;
			cin >> x >> y;
			tree[x - 1][y - 1] = 1;
		}

		// 술래 경로 찾기
		posd cur = posd{ N / 2, N / 2, 0 };
		int max_cnt = 1, cnt = 0, plus = 1;
		bool flag = true;

		int ans = 0;
		for (int k = 1; k <= K; k++) {
			// 도망자 움직이기
			move(theif, cur);

			// 술래 업데이트
			//vis[cur.x][cur.y] = k;
			cur.x += dx[cur.d], cur.y += dy[cur.d];
			cnt++;

			if (cur == posd{ 0, 0, 0 }) {
				max_cnt = N, cnt = 1, flag = false, plus = -1;
				cur.d = 2;
			}
			else if (cur == posd{ N / 2, N / 2, 0 }) {
				max_cnt = 1, cnt = 0, flag = true, plus = 1;
				cur.d = 0;
			}
			if (cnt == max_cnt) { // 방향 변경
				cur.d = (cur.d + plus + 4) % 4;
				if (!flag) max_cnt += plus;
				flag = !flag;
				cnt = 0;
			}

			// 술래 잡기
			ans += k * play(theif, cur);

		}
		cout << ans << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

int play(vector<posd> &theif, const posd &men) {
	vector<posd> path = { {men.x, men.y}, {men.x + dx[men.d], men.y + dy[men.d]}, {men.x + 2 * dx[men.d], men.y + 2 * dy[men.d]} };

	int sum = 0;
	for (auto &m : path) {
		if (m.x < 0 || m.x >= N || m.y < 0 || m.y >= N) continue;
		if (tree[m.x][m.y]) continue;
		vector<posd>::iterator iter = theif.begin();
		while (iter != theif.end()) {
			if (m.x == iter->x && m.y == iter->y) {
				iter = theif.erase(iter);
				sum++;
			}
			else iter++;
		}
	}

	return sum;
}

void move(vector<posd> &theif, const posd &men) {
	for (auto &t : theif) {
		if (abs(t.x - men.x) + abs(t.y - men.y) > 3) continue;
		int nx = t.x + dx[t.d], ny = t.y + dy[t.d];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
			t.d ^= 2;
			nx = t.x + dx[t.d], ny = t.y + dy[t.d];
		}
		if (nx == men.x && ny == men.y) continue;
		t.x = nx, t.y = ny; // 업데이트
	}

}

void display(const int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}