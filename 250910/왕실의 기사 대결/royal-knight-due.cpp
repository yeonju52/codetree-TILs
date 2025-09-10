#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 42, MMAX = 32;

int N, M, Q, A[MAX][MAX], board[MAX][MAX]; // 1좌표 = 1기사

int dx[4] = {-1, 0, 1, 0}; // 상우하좌
int dy[4] = {0, 1, 0, -1};

struct Entity{
    int r, c, h, w, k;
};
vector<Entity> arr;

int vis[MMAX], dead[MMAX], res[MMAX]; // 기사 방문 여부, 죽은 기사 여부, 대미지 합계

bool sucMove(int idx, int dir) {
    queue<pair<int, int>> q;
    memset(vis, 0, sizeof(vis));

    int R = arr[idx].r, C = arr[idx].c, H = R + arr[idx].h, W = C + arr[idx].w;
    vis[idx] = 1;
    for (int i = R; i < H; i++) {
        for (int j = C; j < W; j++) {
            int nx = i + dx[dir], ny = j + dy[dir];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) return false;
            if (A[nx][ny] == 2) return false;
            q.push({nx, ny});
        }
    }

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;
        if (board[x][y] > 0 && !vis[board[x][y]]) {
            int nidx = board[x][y];
            vis[nidx] = 1;
            R = arr[nidx].r, C = arr[nidx].c, H = R + arr[nidx].h, W = C + arr[nidx].w;
            for (int i = R; i < H; i++) {
                for (int j = C; j < W; j++) {
                    int nx = i + dx[dir], ny = j + dy[dir];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) return false;
                    if (A[nx][ny] == 2) return false;
                    q.push({nx, ny});
                }
            }
        }
    }
    return true;
}

void display(const int A[MAX][MAX]);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    memset(A, 0, sizeof(A));
    memset(board, 0, sizeof(board));
    memset(dead, 0, sizeof(dead));
    memset(res, 0, sizeof(res));

    cin >> N >> M >> Q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    arr.push_back({-1, -1, -1, -1, -1}); // 1-based;
    for (int i = 1; i <= M; i++) {
        int r, c, h, w, k; cin >> r >> c >> h >> w >> k;
        r--, c--; // 0-based
        arr.push_back({r, c, h, w, k});
    }

    while(Q--) {
        int idx, dir; cin >> idx >> dir;
        
        if (dead[idx]) continue;
        memset(board, 0, sizeof(board));
        for (int cur = 1; cur <= M; cur++) {
            if (dead[cur]) continue;
            int R = arr[cur].r, C = arr[cur].c, H = R + arr[cur].h, W = C + arr[cur].w;
            for (int r = R; r < H; r++) {
                for (int c = C; c < W; c++) {
                    board[r][c] = cur;
                }
            }
        }

        // 이동 성공
        if(sucMove(idx, dir)) {
            // 방문 vis로 기사 옮기기
            for (int cur = 1; cur <= M; cur++) {
                if (!vis[cur]) continue;
                arr[cur].r += dx[dir], arr[cur].c += dy[dir];
            }

            // 대결 이미지
            for (int cur = 1; cur <= M; cur++) {
                if (cur == idx || !vis[cur]) continue;
                int R = arr[cur].r, C = arr[cur].c, H = R + arr[cur].h, W = C + arr[cur].w;
                for (int r = R; r < H; r++) {
                    for (int c = C; c < W; c++) {
                        if (arr[cur].k == 0) break; // 가지치기
                        if (A[r][c] == 1) {
                            res[cur]++;
                            arr[cur].k--;
                        }
                    }
                }
            }

            for (int cur = 1; cur <= M; cur++) {
                if (arr[cur].k == 0) dead[cur] = 1;
            }
            // display(board);
        }
    }
    
    int ans = 0;
    for (int cur = 1; cur <= M; cur++) {
        if (!dead[cur]) ans += res[cur];
    }
    cout << ans;
    return 0;
}

void display(const int A[MAX][MAX]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}