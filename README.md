
## 시뮬레이션
1. 풀이 핵심 키: 회전
   - rot { 0, 90, 180, 270 } = ```{ (x, y), (y, N - 1 - x), (M - 1 - y, N - 1 - x), (M - 1 - y, x) }```
      - ```N = 5, M = 5, (1, 3)```으로 검산하자
   - 기준 1: 정사각형: 직사각형인 경우, 90도랑 270도일 때, ```swap(N, M)```은 필수
   - 기준 2: (0, 0) 부터 시작
     - (0, 0)이 아닌 다른 위치에서 시작한다면, (offsetX, offsetY)에서 (0, 0)로 밀기
     - 원상 복구: ```[nx + offsetX][ny + offsetY]```
   - 코드 짤 때 순서 조심
       ```tmp[y][N - 1 - x] = arr[x][y]``` -> ```arr[x][y] = tmp[x][y]``` (반대로 하면 문제 생김)
