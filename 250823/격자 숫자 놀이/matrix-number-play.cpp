#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 101;
int R, C, K, A[MAX][MAX], backup[MAX], cnt[MAX];

void solR(const int &N, int &M);
void solC(int &N, const int &M);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C >> K;
    R--, C--;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> A[i][j];
        }
    }

    int N = 3, M = 3;
    int t = 0;
    while(t < MAX) {
        if (A[R][C] == K) break;
        if (N >= M) solR(N, M);
        else solC(N, M);
        t++;
    }
    
    if (A[R][C] == K) cout << t;
    else cout << -1;

    return 0;
}

void solC(int &N, const int &M) {
    for (int c = 0; c < M; c++) { // 한 행씩
        for (int i = 0; i < N; i++) backup[i] = A[i][c];
        for (int i = 0; i < N; i++) A[i][c] = 0;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < N; i++) cnt[backup[i]]++;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (int i = 1; i < MAX; i++) if(cnt[i]) pq.push({cnt[i], i});

        N = max(N, (int)pq.size() * 2);
        int idx = 0;
        while(!pq.empty()) {
            A[idx++][c] = pq.top().second;
            A[idx++][c] = pq.top().first;
            pq.pop();
        }
    }
}

void solR(const int &N, int &M) {
    for (int r = 0; r < N; r++) { // 한 행씩
        memcpy(backup, A[r], sizeof(backup));
        memset(A[r], 0, sizeof(A[r]));

        memset(cnt, 0, sizeof(cnt));
        for (int c = 0; c < M; c++) cnt[backup[c]]++;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (int i = 1; i < MAX; i++) if(cnt[i]) pq.push({cnt[i], i});

        M = max(M, (int)pq.size() * 2);
        int idx = 0;
        while(!pq.empty()) {
            A[r][idx++] = pq.top().second;
            A[r][idx++] = pq.top().first;
            pq.pop();
        }
    }
}
