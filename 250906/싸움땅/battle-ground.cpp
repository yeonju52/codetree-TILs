#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 22;
int N, M, K;

struct Entity {
    int x, y, d, s, g;
};

int ans[32];
vector<Entity> arr;
priority_queue<int> board[MAX][MAX];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void display();

void pickup(Entity &cur) {
    if (!board[cur.x][cur.y].empty() && board[cur.x][cur.y].top() > cur.g) {
        int val = board[cur.x][cur.y].top(); board[cur.x][cur.y].pop();
        board[cur.x][cur.y].push(cur.g);
        cur.g = val;
    }
}

void move(Entity &cur) {
    int x = cur.x, y = cur.y, d = cur.d;
    for (int i = 0; i < 4; i++) {
        int nd = (d + i) % 4;
        int nx = x + dx[nd], ny = y + dy[nd];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

        bool flag = true;
        for (int j = 1; j <= M; j++) {
            if (arr[j].x == nx && arr[j].y == ny) {
                flag = false; break;
            }
        }
        if (flag) {
            cur.x = nx, cur.y = ny, cur.d = nd;
            pickup(cur);
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int g; cin >> g;
            board[i][j].push(g);
        }
    }

    arr.push_back({-1, -1, -1, -1});
    for (int i = 1; i <= M; i++) {
        int x, y, d, s; cin >> x >> y >> d >> s;
        arr.push_back({x - 1, y - 1, d, s, 0});
    }

    while(K--) {
        for (int i = 1; i <= M; i++) {
            // 1. 이동
            Entity &cur = arr[i];
            int x = cur.x, y = cur.y, d = cur.d;
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0) nx = 1, d = (d + 2) % 4;
            else if (nx >= N) nx = N - 2, d = (d + 2) % 4;
            if (ny < 0) ny = 1, d = (d + 2) % 4;
            else if (ny >= N) ny = N - 2, d = (d + 2) % 4;
            cur.x = nx, cur.y = ny, cur.d = d;
            
            // 2. 플레이어가 있다면,
            int oi = 0;
            for (int j = 1; j <= M; j++) {
                auto &other = arr[j];
                if (i == j) continue;
                if (other.x == cur.x && other.y == cur.y) { oi = j; break; }
            }

            if (oi != 0) {
                Entity &other = arr[oi];
                int widx = cur.s + cur.g > other.s + other.g || (cur.s + cur.g == other.s + other.g && cur.s > other.s) ? i : oi;
                int lidx = widx == i ? oi : i;
                
                ans[widx] += (arr[widx].s + arr[widx].g) - (arr[lidx].s + arr[lidx].g);
                if (arr[lidx].g > 0) {
                    board[nx][ny].push(arr[lidx].g);
                    arr[lidx].g = 0;
                }
                move(arr[lidx]);
                pickup(arr[widx]);
            }
            else {
                pickup(cur);
            }
        }
        // display();
        // for (int i = 1; i <= M; i++) {
        //     cout << i << "(" << arr[i].d << ") " << arr[i].x << "," << arr[i].y << " " << arr[i].s << "+" << arr[i].g << "\n";
        // }
        // display();
    }

    for (int i = 1; i <= M; i++) cout << ans[i] << " ";
    return 0;
}

void display() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j].top() << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
