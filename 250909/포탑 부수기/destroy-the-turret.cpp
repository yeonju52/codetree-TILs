#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 12;

int N, M, K, board[MAX][MAX], vis[MAX][MAX];
struct arxy {
    int a, r, x, y;
    bool operator<(const arxy &other) const {
        if (a != other.a) return a < other.a;
        if (r != other.r) return r > other.r;
        if ((x + y) != (other.x + other.y)) return (x + y) > (other.x + other.y);
        return y > other.y;
    }
};
vector<arxy> arr;
pair<int, int> prePath[MAX][MAX];

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, -1, 1, -1, 1};
void display();

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    memset(board, 0, sizeof(board));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
            if(board[i][j]) arr.push_back({board[i][j], 0, i, j});
        }
    }

    for (int k = 1; k <= K; k++) {
        // 1. 공격자 선정
        auto st = min_element(arr.begin(), arr.end());
        int power = st->a + N + M;
        board[st->x][st->y] = power;
        
        // 2. 공격받는 자 선정
        auto ed = *max_element(arr.begin(), arr.end());
        
        // 2.1 레이저 공격 시도
        for (int i = 0; i < N; i++) { // 초기화
            for (int j = 0; j < M; j++) {
                prePath[i][j] = {-1, -1};
            }
        }
        bool laser = false;
        memset(vis, 0, sizeof(vis));
        queue<pair<int, int>> q;
        vis[st->x][st->y] = 1;
        q.push({st->x, st->y});
        
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            int x = cur.first, y = cur.second;
            if (x == ed.x && y == ed.y) {
                laser = true;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0) nx = N - 1;
                else if (nx >= N) nx = 0;
                if (ny < 0) ny = M - 1;
                else if (ny >= M) ny = 0;
                if (vis[nx][ny] || !board[nx][ny]) continue;
                vis[nx][ny] = 1;
                q.push({nx, ny});
                prePath[nx][ny] = {x, y};
            }
        }

        memset(vis, 0, sizeof(vis)); // 공격받은 포탑 표시
        vis[st->x][st->y] = 1;
        if (laser) { // 레이저 공격
            int x = ed.x, y = ed.y;
            board[x][y] = max(board[x][y] - power, 0);
            vis[x][y] = 1;
            while (true) {
                auto cur = prePath[x][y];
                x = cur.first, y = cur.second;
                if (x == st->x && y == st->y) break;
                board[x][y] = max(board[x][y] - (power / 2), 0);
                vis[x][y] = 1;
            }
        }
        else { // 포탄 공격
            int x = ed.x, y = ed.y;
            board[x][y] = max(board[x][y] - power, 0);
            vis[x][y] = 1;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0) nx = N - 1;
                else if (nx >= N) nx = 0;
                if (ny < 0) ny = M - 1;
                else if (ny >= M) ny = 0;
                if (!vis[nx][ny] && board[nx][ny]) { // 포탑 공격 시, 자기 자신도 공격하면 x
                    board[nx][ny] = max(board[nx][ny] - (power / 2), 0);
                    vis[nx][ny] = 1;
                }
            }
        }

        // 4. 포탑 정비
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!vis[i][j] && board[i][j]) board[i][j]++;
            }
        }

        st->r = k; // 공격한 시기 업데이트
        auto iter = arr.begin(); // board 변화 갱신
        while(iter != arr.end()) {
            if (board[iter->x][iter->y]) {
                iter->a = board[iter->x][iter->y];
                iter++;
            }
            else {
                iter = arr.erase(iter);
            }
        }
        // display();
        if (arr.size() == 1) break;
    }

    cout << max_element(arr.begin(), arr.end())->a;
    return 0;
}

void display() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

