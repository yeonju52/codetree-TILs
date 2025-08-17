#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 52, PMAX = 32;
const int INF = 0x3f3f3f3f;

int N, M, P, C, D, rr, rc, board[MAX][MAX], alive[PMAX], scr[PMAX];

struct pos {
    int r, c;
};

vector<pos> att;

// 상우하좌
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void moveSanta(int n, int dst, int fx, int fy);
void display(int t, string tt, const int arr[MAX][MAX]);

bool cmpAttack(const pos &tar, pos &other) {
    if (tar.r == other.r) return tar.c > other.c;
    return tar.r > other.r;
}

int getDst(const pos &it) {
    return (it.r - rr) * (it.r - rr) + (it.c - rc) * (it.c - rc);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> P >> C >> D;
    cin >> rr >> rc;
    
    fill(alive, alive + PMAX, 1);
    att.resize(P + 1);
    for (int i = 1; i <= P; i++) {
        int n, r, c;
        cin >> n >> r >> c;
        att[n] = {r, c};
        board[r][c] = n;
    }

    for (int t = 1; t <= M; t++) {
        // display(t, "초기", board);
        // 1. 루돌프의 움직임
        // 1.1 가까운 산타찾기
        pos tar;
        int mn = INF;
        for (int i = 1; i <= P; i++) {
            auto &it = att[i];
            if (!alive[i]) continue;
            int val = getDst(it);
            if (val < mn) mn = val, tar = it;
            else if (val == mn && cmpAttack(it, tar)) mn = val, tar = it;
        }
        
        // 1.2. 가까운 산타의 방향으로 이동하기
        int fx = rr, fy = rc;
        if (rr < tar.r) rr += 1;
        else if (rr > tar.r) rr -= 1;
        if (rc < tar.c) rc += 1;
        else if (rc > tar.c) rc -= 1;
        
        fx = rr - fx, fy = rc - fy;
        // 1.3 루돌프 충돌 -> 산타 + C
        if (board[rr][rc] > 0) {
            scr[board[rr][rc]] += C;
            if(alive[board[rr][rc]]) alive[board[rr][rc]] = 2; // 기절
            // 산타 밀려나감
            moveSanta(board[rr][rc], C, fx, fy);
        }
        // display(t, "루돌프", board);

        // 2. 산타의 움직임
        // 2.1. 산타는 1번부터 P번까지 순서대로 움직임
        for (int i = 1; i <= P; i++) {
            if (alive[i] != 1) continue;
            // 이미 산타가 있거나 게임판 밖으로 움직 x, 루돌프로부터 가까워지지 않는다면 무효
            int x = att[i].r, y = att[i].c, dir = -1;
            int base_dst = getDst(pos{x, y}), mn_dst = INF, cur_dst;
            for (int r = 0; r < 4; r++) {
                int nx = x + dx[r], ny = y + dy[r];
                if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
                if (board[nx][ny] > 0) continue;
                cur_dst = getDst(pos{nx, ny});
                if (base_dst > cur_dst) {
                    if (mn_dst > cur_dst) {
                        mn_dst = cur_dst;
                        dir = r;
                    }
                }
            }
            if (dir < 0) continue;
            
            // 실제 이동
            board[x][y] = 0;
            att[i].r = x + dx[dir], att[i].c = y + dy[dir];
            board[att[i].r][att[i].c] = i;
            if (board[rr][rc] > 0) { // 루돌프위 위치와 같다면?
                scr[board[rr][rc]] += D;
                if (alive[board[rr][rc]]) alive[board[rr][rc]] = 2; // 기절
                // 산타 밀려나감
                moveSanta(i, D, -dx[dir], -dy[dir]);
            }
            // display(t, to_string(i) + "번 산타", board);
        }

        // 기절 프로세스
        for (int i = 1; i <= P; i++) {
            if (!alive[i]) continue;
            scr[i]++;
            if (alive[i] == 2) alive[i] = 3; // 다음턴 3까지
            else if (alive[i] == 3) alive[i] = 1;
        }
    }
    for (int i = 1; i <= P; i++) cout << scr[i] << " ";

    return 0;
}

void moveSanta(int n, int dst, int fx, int fy) { // 확인 안 해봄
    int x = att[n].r + fx * dst, y = att[n].c + fy * dst;
    while(true) {
        // 이동한 위치가 범위에 벗어났는지 확인
        if (x < 1 || x > N || y < 1 || y > N) {
            alive[n] = 0;
            // cout << n << "번 산타 아웃\n";
            break;
        }
        att[n].r = x, att[n].c = y;
        if (!board[x][y]) break;
        // 이동한 위치에 산타가 또 있다면 연쇄
        // cout << n << "번째 산타 이동" << x << "," << y << "\n";
        n = board[x][y]; // 실제 이동전 위치로 산타 번호 찾기
        x += fx, y += fy;
    }

    memset(board, 0, sizeof(board));
    for (int i = 1; i <= P; i++) {
        if (!alive[i]) continue;
        board[att[i].r][att[i].c] = i;
    }
}

void display(int t, string tt, const int arr[MAX][MAX]) {
    cout << t << "번 턴 - " << tt << "\n";
    cout << "루돌프 좌표: " << rr << "," << rc << "\n";
    cout << "산타 좌표: \n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << arr[i][j];
        }
        cout << "\n";
    }
}
