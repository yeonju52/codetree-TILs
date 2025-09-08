#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 17;
int N, M, board[MAX][MAX], moved[MAX][MAX], alive[32];
vector<pair<int, int>> dst;
vector<pair<int, int>> src;

int dx[4] = {-1, 0, 0, 1}; // 상, 좌, 우, 하
int dy[4] = {0, -1, 1, 0};

struct dxy{
    int d, x, y;
    bool operator<(const dxy &other) const {
        if (d != other.d) return d > other.d;
        if (x != other.x) return x > other.x;
        return y > other.y;
    }
};

int vis[MAX][MAX];
bool find_src(int idx, int x, int y);
int bfs(int idx, int sx, int sy, int ex, int ey);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            cin >> board[i][j];

    dst.resize(M); src.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> dst[i].first >> dst[i].second;
        dst[i].first--, dst[i].second--;
    }

    memset(alive, 0, sizeof(alive));
    int T = 0;
    while(true) {
        for (int i = 0; i < min(T, M); i++) { 
            if (!alive[i]) continue;
            bfs(i, src[i].first, src[i].second, dst[i].first, dst[i].second);
        }

        for (int i = 0; i < min(T, M); i++) {
            if (!alive[i]) continue;
            if(src[i] == dst[i]) {
                alive[i] = 0;
                moved[dst[i].first][dst[i].second] = 1;
            }
        }

        if (T < M) {
            find_src(T, dst[T].first, dst[T].second);
            alive[T] = 1;
        }
        if (count(alive, alive + M, 1) == 0) break;
        T++;
    }
    cout << T + 1;
    return 0;
}

int bfs(int idx, int sx, int sy, int ex, int ey) {
    memset(vis, 0, sizeof(vis));
    queue<pair<int, int>> q;
    q.push({ex, ey});
    vis[ex][ey] = 1;

    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;
        for (int i = 0; i < 4; i++) { // 상, 좌, 우, 하
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (!(nx == sx && ny == sy) && moved[nx][ny]) continue;
            if (vis[nx][ny]) continue;
            vis[nx][ny] = vis[x][y] + 1;
            q.push({nx, ny});
        }
    }

    int dir = -1;
    for (int i = 0; i < 4; i++) {
        int nx = sx + dx[i], ny = sy + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (vis[nx][ny] > 0 && vis[nx][ny] == vis[sx][sy] - 1) {
            src[idx] = {nx, ny};
            dir = i;
            break;
        }
    }
    return dir;
}

bool find_src(int idx, int x, int y) {
    memset(vis, 0, sizeof(vis));
    priority_queue<dxy> pq;
    vis[x][y] = 1;
    pq.push({0, x, y}); // 여기서 d는 dist임

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        x = cur.x, y = cur.y;
        if (board[x][y] && !moved[x][y]) {
            src[idx] = {x, y};
            moved[x][y] = 1;
            return true;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N || vis[nx][ny]) continue;
            if (moved[nx][ny]) continue;
            vis[nx][ny] = 1;
            pq.push({cur.d + 1, nx, ny});
        }
    }
    return false;
}
