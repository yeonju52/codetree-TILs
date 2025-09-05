#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 17;

int N, M, d, p, board[MAX][MAX], backup[MAX][MAX];
vector<pair<int, int>> arr;

int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

bool isOk(int x, int y) { return x >= 0 && x < N && y >= 0 && y < N; }

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
    arr = { {N - 2, 0}, {N - 2, 1}, {N - 1, 0}, {N - 1, 1} }; // 초기화

    while(M--) {
        cin >> d >> p;
        d--;

        for (auto &cur : arr) {
            cur = { (cur.first + dx[d] * p + N) % N, (cur.second + dy[d] * p + N) % N };
            board[cur.first][cur.second]++;
        }

        memcpy(backup, board, sizeof(board));
        for (auto &cur : arr) {
            for (auto &r : vector<int>({1, 3, 5, 7})) {
                int nx = cur.first + dx[r], ny = cur.second + dy[r];
                if (isOk(nx, ny) && backup[nx][ny] > 0) board[cur.first][cur.second]++;
            }
        }

        vector<pair<int, int>> narr;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (find(arr.begin(), arr.end(), make_pair(i, j)) != arr.end()) continue;
                if (board[i][j] > 1) {
                    board[i][j] -= 2;
                    narr.push_back({i, j});
                }
            }
        }
        arr = narr;
        if (arr.empty()) break;
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ans += board[i][j];
        }
    }
    cout << ans;

    return 0;
}
