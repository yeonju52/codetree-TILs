//첫 번째 줄에 탐사의 반복 횟수 K와 벽면에 적힌 유물 조각의 개수 M이 공백을 사이에 두고 주어집니다.
//
//그 다음 5개의 줄에 걸쳐 유물의 각 행에 있는 유물 조각에 적혀 있는 숫자들이 공백을 사이에 두고 순서대로 주어집니다.
//
//그 다음 줄에는 벽면에 적힌 M개의 유물 조각 번호가 공백을 사이에 두고 순서대로 주어집니다.
//
//단, 초기에 주어지는 유적지에서는 탐사 진행 이전에 유물이 발견되지 않으며, 첫 번째 턴에서 탐사를 진행한 이후에는 항상 유물이 발견됨을 가정해도 좋습니다.

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int K, M;
int arr[7][7]; // 유적지 5x5
int wall[302];
int vis[7][7];

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int bfs(int x, int y)  { // 3이상이면, arr[i][j] = 0
	int chk[7][7];
	memset(chk, 0, sizeof(chk));
	queue<pair<int, int>> Q;
	Q.push({ x ,y });
	vis[x][y] = 1;
	chk[x][y] = 1;

	//int sum = 0;
	int cnt = 1;
	while (!Q.empty()) {
		pair<int, int> cur = Q.front(); Q.pop();
		int x = cur.first, y = cur.second;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || nx > 4 || ny < 0 || ny > 4) continue;
			if (arr[nx][ny] == 0) continue;
			if (!vis[nx][ny] && arr[x][y] == arr[nx][ny]) {
				Q.push({ nx, ny });
				vis[nx][ny] = 1;
				chk[nx][ny] = 1;
				cnt++;
			}
		}
	}
	if (cnt >= 3) {
		for (int i = 0; i <= 5; i++) {
			for (int j = 0; j <= 5; j++) {
				if (chk[i][j]) {
					//sum += arr[i][j];
					arr[i][j] = 0;
				}
			}
		}
	}
	else { cnt = 0; }
	return cnt;
}

int getScore() { // 1차 초기탐사
	int cnt = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!vis[i][j] && arr[i][j] > 0) cnt += bfs(i, j);
		}
	}
	return cnt;
}

void rotate(int x, int y, int dir) {
	int tmp[7][7];
	memset(tmp, 0, sizeof(tmp));
	int offi = x - 1, offj = y - 1;
	//cout << offi << " " << offj << '\n';
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//cout << "(" << i << "," << j << ") ";
			//cout << "(" << j << "," << 2 - i << ") -> ";
			//cout << "(" << i + offi << "," << j + offj << ") ";
			//cout << "(" << j + offj << "," << 2 - i + offi << ")\n";
			if (dir == 1) tmp[j + offi][2 - i + offj] = arr[i + offi][j + offj];
			else if (dir == 2) tmp[2 - i + offi][2 - j + offj] = arr[i + offi][j + offj];
			else if (dir == 3) tmp[2 - j + offi][i + offj] = arr[i + offi][j + offj];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[i + offi][j + offj] = tmp[i + offi][j + offj];
		}
	}
	return;
}

int setRotate_1st() { // 1차 획득
	int tmp[7][7];
	int maxi = 0;
	int mxx, mxy;
	int mxd = 0;
	for (int dir = 1; dir <= 3; dir++) {		
		for (int j = 1; j <= 3; j++) {	
			for (int i = 1; i <= 3; i++) {
				memcpy(tmp, arr, sizeof(arr));
				rotate(i, j, dir);
				int scr = getScore();
				if (maxi < scr) { // 1차 초기탐사
					mxx = i, mxy = j, mxd = dir;
					maxi = scr;
				}
				memcpy(arr, tmp, sizeof(tmp));
			}
		}
	}
	if (mxd == 0) return 0;
	// 실제 움직이기
	rotate(mxx, mxy, mxd);
	//cout << maxi << ": " << mxx + 1 << " " << mxy + 1 << " " << 90 * mxd << '\n';
	return getScore();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);
	
	int total = 0;
	memset(arr, 0, sizeof(arr));
	memset(wall, 0, sizeof(wall));

	cin >> K >> M;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> wall[i];
	}
	
	/// <summary>
	/// 로직
	/// </summary>
	/// <returns></returns>
	int widx = 0;
	int tmp = 0;
	while (K--) {
		total = 0;
		tmp = setRotate_1st(); // rotate + 1차 초기
		if (tmp == 0) break;
		total += tmp;
		// 2차 이후
		while(true){
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (arr[4 - j][i] == 0 && widx < M) arr[4 - j][i] = wall[widx++]; //cout << wall[widx] << ": (" << 4 - j << "," << i << ") ";
				}
			}
			tmp = getScore();
			total += tmp;
			if (tmp == 0) break;
			//if (widx >= M) break;
		}
		cout << total << " ";
	}

	return 0;
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << "\n";
	}*/
	/*for (int i = 0; i < M; i++) {
		cout << wall[i] << ' ';
	}*/
}