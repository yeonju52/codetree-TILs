#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX = 12;

int N, M, K, board[MAX][MAX], backup[MAX][MAX], ex, ey, ans = 0;
vector<int> bToA[MAX * MAX];
vector<pair<int, int>> arr;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void solution(int t);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        int r, c; cin >> r >> c;
        arr.push_back({r - 1, c - 1}); // 0-based 로 변경
    }
    
    cin >> ex >> ey; ex--, ey--;
    board[ex][ey] = -1; // exit 표시

    for (int t = 0; t < K; t++) {
        if (arr.empty()) break;
        solution(t);
        // cout << t + 1 << "번째 턴\n";
        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < N; j++) {
        //         if (bToA[i * N + j].empty()) cout << setw(2) << board[i][j] << " ";
        //         else cout << setw(2) <<  "-2 ";
        //     }
        //     cout << "\n";
        // }
        // // for (auto &a : arr) cout << a.first << "," << a.second << " ";
        // cout << ans << " ";
        // cout << ex << "," << ey << "\n\n";
    }
    cout << ans << "\n" << ex + 1 << " " << ey + 1;

    return 0;
}

void solution(int t) {
    auto it = arr.begin();
    while(it != arr.end()) {
        int x = it->first, y = it->second;
        bool update = false;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!isValid(nx, ny) || board[nx][ny] > 0) continue;
            if (abs(x - ex) + abs(y - ey) <= abs(nx - ex) + abs(ny - ey)) continue;
            ans++;
            if (ex == nx && ey == ny) {
                it = arr.erase(it);
                update = true;
            }
            else {
                *it = {nx, ny};
                it++;
                update = true;
            }
            // cout << x << "," << y << "->" << nx << "," << ny << "\n";
            break;
        }
        if (!update) it++;
    }
    
    M = arr.size();
    if (M == 0) return ;
    for (auto &a: bToA) a.clear();
    for (int m = 0; m < M; m++) {
        auto &cur = arr[m];
        int x = cur.first, y = cur.second;
        bToA[x * N + y].push_back(m);
    }

    // 가장 작은 정사각형 구하기
    int mn = MAX, rx = MAX, ry = MAX;
    for (auto &cur : arr) {
        int x = cur.first, y = cur.second;
        int L = max(abs(x - ex), abs(y - ey));
        if (mn < L) continue;
        if (mn > L) mn = L, rx = MAX, ry = MAX;
        for (int i = 0; i + L < N; i++) {
            for (int j = 0; j + L < N; j++) {
                if (i <= ex && ex <= i + L && j <= ey && ey <= j + L &&
                    i <= x  && x  <= i + L && j <= y  && y  <= j + L) {
                    if (i < rx || (i == rx && j < ry)) {
                        rx = i; ry = j;
                    }
                }
            }
        }
    }
    
    memcpy(backup, board, sizeof(backup));
    for (int i = 0; i <= mn; i++) {
        for (int j = 0; j <= mn; j++) {
            board[rx + j][ry + mn - i] = backup[rx + i][ry + j];
            for (auto& m : bToA[(rx + i) * N + ry + j]) {
                arr[m] = {rx + j, ry + mn - i};
                // cout << m << " " << "(" << arr[m].first << "," << arr[m].second << ")\n";
            }
        }
    }

    for (auto &a: bToA) a.clear();
    for (int m = 0; m < M; m++) {
        auto &cur = arr[m];
        int x = cur.first, y = cur.second;
        bToA[x * N + y].push_back(m);
    }

    for (int i = 0; i <= mn; i++) {
        for (int j = 0; j <= mn; j++) {
            if (board[rx + i][ry + j] == -1) ex = rx + i, ey = ry + j;
            else board[rx + i][ry + j] = max(board[rx + i][ry + j] - 1, 0);
        }
    }
}