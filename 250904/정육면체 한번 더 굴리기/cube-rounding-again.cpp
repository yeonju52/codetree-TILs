#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 22;

struct info{
    int u, d, f, b, l, r;
};

info cube = {1, 6, 2, 5, 4, 3}; // 초기값

void rotateRight(); void rotateFront();
void rotateLeft(); void rotateBack();
int bfs(int x, int y);

int N, M, board[MAX][MAX], vis[MAX][MAX], cx, cy, cr;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    memset(board, 0, sizeof(board));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    cx = 0, cy = 0, cr = 0;

    int ans = 0;
    for (int i = 0; i < M; i++) {
        // 이동
        cx += dx[cr], cy += dy[cr];
        if (cx < 0) cx = 1, cr = (cr + 2) % 4;
        else if (cx >= N) cx = N - 2, cr = (cr + 2) % 4;
        if (cy < 0) cy = 1, cr = (cr + 2) % 4;
        else if (cy >= N) cy = N - 2, cr = (cr + 2) % 4;
        
        // 회전
        if (cr == 0) rotateRight();
        else if (cr == 1) rotateFront();
        else if (cr == 2) rotateLeft();
        else if (cr == 3) rotateBack();
        
        // cout << bfs(cx, cy) << " " << cx << "," << cy << " " << cube.u << "\n";
        ans += bfs(cx, cy);

        if (cube.d > board[cx][cy]) cr = (cr + 1) % 4; // 시계방향 90도
        else if (cube.d < board[cx][cy]) cr = (cr - 1 + 4) % 4; // 반시계방향 90도
    }

    cout << ans;

    return 0;
}

int bfs(int x, int y) {
    memset(vis, 0, sizeof(vis));
    queue<pair<int, int>> q;
    vis[x][y] = 1;
    q.push({x, y});
    
    int cnt = 0;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        cnt++;
        for (int i = 0; i < 4; i++) {
            int nx = cur.first + dx[i], ny = cur.second + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (vis[nx][ny] || board[nx][ny] != board[x][y]) continue;
            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }
    return cnt * board[x][y];
}

void rotateRight() { // 0
    info tmp = cube;
    cube.u = tmp.l, cube.d = tmp.r;
    cube.l = tmp.d, cube.r = tmp.u;
}

void rotateFront() { // 1
    info tmp = cube;
    cube.u = tmp.b, cube.d = tmp.f;
    cube.f = tmp.u, cube.b = tmp.d;
}

void rotateLeft() { // 2
    info tmp = cube;
    cube.u = tmp.r, cube.d = tmp.l;
    cube.l = tmp.u, cube.r = tmp.d;
}

void rotateBack() { // 3
    info tmp = cube;
    cube.u = tmp.f, cube.d = tmp.b;
    cube.f = tmp.d, cube.b = tmp.u;
}
