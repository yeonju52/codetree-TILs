#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 22;

int N, M, K, board[MAX][MAX], vis[MAX][MAX], ans = 0;
pair<int, int> lbl[MAX][MAX], backup[MAX][MAX];

struct sdk {
    int s, d, k;
};

vector<vector<pair<int, int>>> arr;
vector<sdk> arr_info;
vector<int> scr;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

int playCol(int c);
void rotate(int r);
void display();

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    scr.resize(M, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) arr.push_back({{i, j}});
        }
    }

    // 팀 정보 저장
    for (auto &A : arr) {
        int x = A[0].first, y = A[0].second;
        vis[x][y] = 1;
        sdk info = {0, 1, 1};
        
        bool pass = true;
        while(pass) {
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if (board[x][y] != 2 && board[nx][ny] == 1) {
                    pass = false;
                    break; // 종료 조건
                }
                if (vis[nx][ny]) continue;
                int cur = board[x][y];
                int nxt = board[nx][ny];
                if (!nxt || (cur == 1 && (nxt == 3 || nxt == 4))) continue;
                if (nxt == cur || nxt == cur + 1) {
                    if (nxt < 4) info.k++;
                    vis[nx][ny] = 1;
                    A.push_back({nx, ny});
                    x = nx, y = ny;
                    break;
                }
            }
        }
        arr_info.push_back(info);
    }

    for (int k = 0; k < K; k++) {
        memset(board, 0, sizeof(board));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                lbl[i][j] = {0, 0};
            }
        }
        for (int m = 0; m < M; m++) {
            auto &A = arr[m];
            auto &info = arr_info[m];
            int L = A.size();

            // 정방향 (+1)
            info.s = (info.s - info.d + L) % L; // 이동
            
            // 이동 후 board 변화
            int idx = info.s, lb = 0;
            board[A[idx].first][A[idx].second] = 1;
            lbl[A[idx].first][A[idx].second] = {m, ++lb};
            for (int i = 1; i < info.k - 1; i++) {
                idx = (info.s + i * info.d + L) % L;
                board[A[idx].first][A[idx].second] = 2;
                lbl[A[idx].first][A[idx].second] = {m, ++lb};
            }
            idx = (info.s + (info.k - 1) * info.d + L) % L;
            board[A[idx].first][A[idx].second] = 3;
            lbl[A[idx].first][A[idx].second] = {m, ++lb};
            for (int i = info.k; i < L; i++) {
                idx = (info.s + i * info.d + L) % L;
                board[A[idx].first][A[idx].second] = 4;
            }
        }

        // display();
        rotate((k / N) % 4);
        // display();
        int m = playCol(k % N);
        if (m > -1) {
            // 역방향 (+0)
            arr_info[m].s = (arr_info[m].s + arr_info[m].d * (arr_info[m].k - 1) + arr[m].size()) % arr[m].size();
            arr_info[m].d *= -1;
        }
    }
    for (auto s : scr) ans += s;
    cout << ans << "\n";

    return 0;
}

int playCol(int c) {
    for (int j = 0; j < N; j++) {
        if (lbl[c][j].second > 0) {
            scr[lbl[c][j].first] += (lbl[c][j].second * lbl[c][j].second);
            return lbl[c][j].first;
        }
    }
    return -1;
}

void rotate(int r) {
    if (r == 0) return ;
    memcpy(backup, lbl, sizeof(backup));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            lbl[i][j] = {0, 0};
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (r == 1) lbl[j][N - 1 - i] = backup[i][j];
            else if (r == 2) lbl[N - 1 - i][N - 1 - j] = backup[i][j];
            else if (r == 3) lbl[N - 1 - j][i] = backup[i][j];
        }
    }
    return ;
}

void display() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << lbl[i][j].second << " ";
        }
        cout << "\n";
    }
}

