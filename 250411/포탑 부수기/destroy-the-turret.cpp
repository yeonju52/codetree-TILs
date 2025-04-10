#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct info {
	int x, y, b, t;
};

struct pos {
	int x, y;
	bool operator==(const pos& other) const {
		return (x == other.x) && (y == other.y);
	}
};

const int MAX = 10;
int N, M, K;
int board[MAX][MAX];
int plen;
pos path[MAX * MAX];

bool compare(info &tar, info &comp) {
	if (tar.b != comp.b) return tar.b < comp.b;
	if (tar.t != comp.t) return tar.t > comp.t;
	if (tar.x + tar.y != comp.x + comp.y) return (tar.x + tar.y > comp.x + comp.y);
	if (tar.x != comp.x) return tar.x < comp.x;
	return false;
}

int dx[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
int dy[8] = { 1, 0, -1, 0, 1, -1, 1, -1 };

bool bfs(const pos st, const pos ed);
void display(const int arr[MAX][MAX]);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	memset(board, 0, sizeof(board));

	vector<info> men;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int b;
			cin >> b;
			if (b != 0) men.push_back({ i, j, b, 0 });
		}
	}

	for (auto &m : men) board[m.x][m.y] = m.b; // board 초기화

	for (int t = 1; t <= K; t++) {
		if ((int)men.size() < 2) break;

		// 공격자 선정
		info *minM = &men[0];
		for (int i = 1; i < (int)men.size(); i++) {
			if (compare(men[i], *minM)) {
				minM = &men[i];
			}
		}
		// 맞는자 선정
		info maxM = men[0];
		for (auto &m : men) {
			if (!compare(m, maxM)) {
				maxM = m;
			}
		}

		int sx = minM->x, sy = minM->y;
		// cout << "minM: (" << minM->x << "," << minM->y << ") b = " << minM->b << endl;
		// cout << "maxM: (" << maxM.x << "," << maxM.y << ") b = " << maxM.b << endl;

		minM->b += (N + M);
		board[sx][sy] = minM->b;
		minM->t = t;
		
		plen = 0;
		if (!bfs({ sx, sy }, { maxM.x, maxM.y })) { // 레이저 공격
			// 포탄 공격 모드로 넘어감
			for (int i = 0; i < 8; i++) {
				int nx = maxM.x + dx[i], ny = maxM.y + dy[i];
				nx = (nx + N) % N;
				ny = (ny + M) % M;
				if (board[nx][ny] == 0) continue;
				if (sx == nx && sy == ny) continue; // 공격자는 공격 대상에서 무시
				path[plen++] = { nx, ny };
			}
		}

		// 실제 공격
		board[maxM.x][maxM.y] -= minM->b;
		int amount = minM->b / 2;
		for (int i = 0; i < plen; i++) board[path[i].x][path[i].y] -= amount;

		// 포탑 부서짐
		auto iter = men.begin(); // minM 포인터이기 때문에, 삭제 과정에서 주소가 바뀌면서 minM이 달라짐
		while (iter != men.end()) {
			if (board[iter->x][iter->y] <= 0) {
				board[iter->x][iter->y] = 0;
				iter = men.erase(iter);
			}
			else ++iter;
		}

		// 포탑 정비
		// path에 없고, sx도 아니고, maxM도 아니어야함.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (board[i][j] <= 0) continue;
				bool isPath = false;
				for (int k = 0; k < plen; k++) {
					if (path[k].x == i && path[k].y == j) {
						isPath = true;
						break;
					}
				}
				if (isPath) continue;
				if (sx == i && sy == j) continue;
				if (maxM.x == i && maxM.y == j) continue;
				board[i][j]++;
			}
		}

		
		// 보드 변경사항 men에 반영
		for (auto &m : men) {
			m.b = board[m.x][m.y];
		}
		
		// cout << "path: ";
		// for (int i = 0; i < plen; i++) cout << path[i].x << "," << path[i].y << " ";
		// cout << "\n";
		// display(board);
	}
	
	// 맞는자 선정
	int ans = 0;
	for (auto &m : men) {
		ans = max(ans, m.b);
	}

	cout << ans << "\n";

	return 0;
}

pos vis[MAX][MAX];
bool bfs(const pos st, const pos ed) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			vis[i][j] = { -1, -1 };
		}
	}
	queue<pos> q;
	vis[st.x][st.y] = st;
	q.push(st);

	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		if (cur == ed) {
			pos prev = cur;
			while (!(prev == st)) {
				if (!(prev == ed)) path[plen++] = prev;
				prev = vis[prev.x][prev.y];
			}
			return true;
		}
		for (int i = 0; i < 4; i++) {
			int nx = (cur.x + dx[i] + N) % N, ny = (cur.y + dy[i] + M) % M;
			if (vis[nx][ny].x >= 0) continue;
			if (board[nx][ny] == 0) continue;
			vis[nx][ny] = cur;
			q.push({ nx, ny });
		}
	}
	return false;
}

void display(const int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
