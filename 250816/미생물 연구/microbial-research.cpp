#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int MAX = 17;
int N, Q, board[MAX][MAX], vis[MAX][MAX], ans;
vector<pair<int, int>> bio[52];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int getGc(int x, int y);
bool moveSimulation(vector<pair<int, int>> &tar, int idx);
int bfs(int x, int y);
void display(string tt, const int arr[MAX][MAX]);

bool cmpX(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first < b.first;
}

bool cmpY(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;

    for (int lb = 1; lb <= Q; lb++) {
        // 0. 초기화
        ans = 0;

        // 1.1 미생물 투입
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        for (int i = r1; i < r2; i++) {
            for (int j = c1; j < c2; j++) {
                if (board[i][j] > 0) {
                    auto &tar = bio[board[i][j]];
                    tar.erase(find(tar.begin(), tar.end(), make_pair(i, j)));
                }
                board[i][j] = lb;
                bio[lb].push_back({i, j});
            }
        }

        // 1.2. 둘 이상으로 나누진 경우 없애기
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i < lb; i++) {
            if (bio[i].empty()) continue;
            int cnt = bfs(bio[i][0].first, bio[i][0].second);
            // 다르면 지우기
            // cout << i << "번 군집화: " << bio[i].size() << "," << cnt << "\n";
            if (bio[i].size() != cnt) {
                for (const auto &rmv : bio[i]) board[rmv.first][rmv.second] = 0;
                bio[i].clear();
            }
        }
        // display("이전", board);

        // 2.1. 최대 넓이 무리 선택, 같다면 lb이 작은 순
        vector<pair<int, int>> mvOrder; // 넓이, -작은순
        int mxLb = 0, mx = 0;
        for (int i = 1; i <= lb; i++) {
            if (bio[i].size() == 0) continue;
            mvOrder.push_back({bio[i].size(), -i});
        }
        sort(mvOrder.begin(), mvOrder.end(), greater<pair<int, int>>());

        // 2.2 실제 이동
        memset(board, 0, sizeof(board)); // 보드 초기화
        auto it = mvOrder.begin();
        while (it != mvOrder.end()) {
            int idx = -(it->second);
            auto &tar = bio[idx];
            // cout << lb << "번째 실험에서 " << idx << "번째 군집화 (" << it->first << "개) ";
            if (moveSimulation(tar, idx)) it++;
            else it = mvOrder.erase(it);
            // if (moveSimulation(diffx, diffy, tar, idx)) cout << "옮기기 성공\n";
            // else cout << "옮기기 실패\n";
        }
        // display("결과", board);

        // 3.1 인접한 그룹 찾기
        for (auto &it : mvOrder) {
            memset(vis, 0, sizeof(vis));
            int x = bio[-it.second][0].first, y = bio[-it.second][0].second;
            if (vis[x][y] || board[x][y] == 0) continue;
            ans += getGc(x, y);
        }
        cout << ans << "\n";
    }
    return 0;
}

int getGc(int x, int y) {
    queue<pair<int, int>> q;
    int g1 = board[x][y];
    unordered_set<int> gc;
    q.push({x, y});
    vis[x][y] = 1;

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        x = cur.first, y = cur.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (vis[nx][ny]) continue;
            if (board[nx][ny] == g1) {
                q.push({nx, ny});
                vis[nx][ny] = 1;
            }
            else if (board[nx][ny] > g1) {
                gc.insert(board[nx][ny]);
            }
        }
    }

    if (gc.empty()) return 0;
    
    // 스코어 계산
    int scr = 0;
    for (auto &g2: gc) scr += bio[g1].size() * bio[g2].size();
    return scr;
}

bool moveSimulation(vector<pair<int, int>> &tar, int idx) {
    int diffx = min_element(tar.begin(), tar.end(), cmpX)->first;
    int diffy = min_element(tar.begin(), tar.end(), cmpY)->second;

    vector<pair<int, int>> nxt;
    for (int bx = 0; bx < N; bx++) {
        for (int by = 0; by < N; by++) {
            bool pass = true;
            nxt.clear();
            for (auto cur : tar) {
                int x = cur.first - diffx + bx, y = cur.second - diffy + by;
                if (x < 0 || x >= N || y < 0 || y >= N || board[x][y] > 0) {
                    pass = false;
                    break;
                }
                nxt.push_back({x, y});
            }
            if (pass) {
                for (auto &cur : nxt) board[cur.first][cur.second] = idx;
                tar = nxt;
                return true;
            }
        }
    }
    tar.clear();
    return false;
}

int bfs(int x, int y) {
    int res = 0;
    queue<pair<int, int>> q;
    
    q.push({x, y});
    vis[x][y] = 1;

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        x = cur.first, y = cur.second;
        res++;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (vis[nx][ny]) continue;
            if (board[x][y] == board[nx][ny]) {
                q.push({nx, ny});
                vis[nx][ny] = 1;
            }
        }
    }

    return res;
}

void display(string tt, const int arr[MAX][MAX]) {
    cout << tt << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

