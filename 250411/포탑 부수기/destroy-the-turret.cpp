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
int path[MAX][MAX];

bool compare(info &tar, info &comp) {
	if (tar.b != comp.b) return tar.b < comp.b;
	if (tar.t != comp.t) return tar.t > comp.t;
	if (tar.x + tar.y != comp.x + comp.y) return (tar.x + tar.y > comp.x + comp.y);
	if (tar.x != comp.x) return tar.x > comp.x;
	return false;
}

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

bool bfs(pos st, pos ed);
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

	int t = 1;
	while (t < K + 1) { // K + 1
		// 공격자 선정
		info& minM = men[0];
		for (auto &m : men) {
			if (compare(m, minM)) {
				minM = m;
			}
		}

		// 맞는자 선정
		info maxM = men[0];
		for (auto &m : men) {
			if (!compare(m, maxM)) {
				maxM = m;
			}
		}
		
		// 레이저 공격
		memset(path, 0, sizeof(path));
		if (!bfs({minM.x, minM.y}, {maxM.x, maxM.y})) { // 레이저 공격
			// 포탄 공격 모드로 넘어감
			memset(path, 0, sizeof(path));
			path[maxM.x][maxM.y] = 2;
			for (int i = 0; i < 8; i++) {
				int nx = maxM.x + dx[i], ny = maxM.y + dy[i];
				if (nx < 0) nx = N - 1;
				else if (ny < 0) ny = M - 1;
				else if (nx >= N) nx = 0;
				else if (ny >= M) ny = 0;
				if (board[nx][ny] == 1) continue;
				path[nx][ny] = 1;
			}
		}

		// 실제 공격
		minM.b += (N + M);
		for (auto &m : men) {
			if (path[m.x][m.y] == 1) m.b -= (minM.b / 2);
			else if (path[m.x][m.y] == 2) m.b -= minM.b;
		}
		minM.t = t;
		
		// 포탑 부서짐
		auto iter = men.begin();
		while (iter != men.end()) {
			if (iter->b <= 0) {
				board[iter->x][iter->y] = 1;
				men.erase(iter);
			}
			else ++iter;
		}

		// 포탑 정비
		for (auto &m : men) {
			if (minM.x == m.x && minM.y == m.y) continue;
			if (path[m.x][m.y] > 0) continue;
			m.b++;
		}

		t++;
		if (men.size() < 2) break;
	}

	int ans = men[0].b;
	for (auto &m : men) {
		ans = max(ans, m.b);
	}

	cout << ans << "\n";

	return 0;
}

pos vis[MAX][MAX];
bool bfs(pos st, pos ed) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			vis[i][j] = {-1, -1};
		}
	}
	queue<pos> q;
	vis[st.x][st.y] = st;
	q.push(st);

	while(!q.empty()) {
		pos cur = q.front(); q.pop();
		if (cur == ed) {
			pos prev = cur;
			while (!(prev == st)) {
				if (prev == ed) path[prev.x][prev.y] = 2;
				else path[prev.x][prev.y] = 1;
				prev = vis[prev.x][prev.y];
			}
			return true;
		}
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i], ny = cur.y + dy[i];
			if (nx < 0) nx = N - 1;
			else if (ny < 0) ny = M - 1;
			else if (nx >= N) nx = 0;
			else if (ny >= M) ny = 0;
			if (vis[nx][ny].x >= 0) continue;
			if (board[nx][ny]) continue;
			vis[nx][ny] = cur;
			q.push({nx, ny});
		}
	}
	return false;
}

void display(const int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}