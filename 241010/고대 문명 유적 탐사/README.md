# [고대 문명 유적 탐사 ![Gold4][g4]](https://www.codetree.ai/training-field/frequent-problems/problems/ancient-ruin-exploration)

|유형|출처|
|---|---|
|[Simulation](https://www.codetree.ai/training-field/search/?tags=Simulation), [BFS](https://www.codetree.ai/training-field/search/?tags=BFS)|[기출문제](https://www.codetree.ai/training-field/frequent-problems)|

1. 풀이 핵심 키: 회전
   - rot { 0, 90, 180, 270 } = ```{ (x, y), (y, N - 1 - x), (M - 1 - y, N - 1 - x), (M - 1 - y, x) }```
      - ```N = 5, M = 5, (1, 3)```으로 검산하자
   - 기준 1: 정사각형: 직사각형인 경우, 90도랑 270도일 때, ```swap(N, M)```은 필수
   - 기준 2: (0, 0) 부터 시작
     - (0, 0)이 아닌 다른 위치에서 시작한다면, (offsetX, offsetY)에서 (0, 0)로 밀기
     - 원상 복구: ```[nx + offsetX][ny + offsetY]```
   - 코드 짤 때 순서 조심
       ```tmp[y][N - 1 - x] = arr[x][y]``` -> ```arr[x][y] = tmp[x][y]``` (반대로 하면 문제 생김)





[b5]: https://img.shields.io/badge/Bronze_5-%235D3E31.svg
[b4]: https://img.shields.io/badge/Bronze_4-%235D3E31.svg
[b3]: https://img.shields.io/badge/Bronze_3-%235D3E31.svg
[b2]: https://img.shields.io/badge/Bronze_2-%235D3E31.svg
[b1]: https://img.shields.io/badge/Bronze_1-%235D3E31.svg
[s5]: https://img.shields.io/badge/Silver_5-%23394960.svg
[s4]: https://img.shields.io/badge/Silver_4-%23394960.svg
[s3]: https://img.shields.io/badge/Silver_3-%23394960.svg
[s2]: https://img.shields.io/badge/Silver_2-%23394960.svg
[s1]: https://img.shields.io/badge/Silver_1-%23394960.svg
[g5]: https://img.shields.io/badge/Gold_5-%23FFC433.svg
[g4]: https://img.shields.io/badge/Gold_4-%23FFC433.svg
[g3]: https://img.shields.io/badge/Gold_3-%23FFC433.svg
[g2]: https://img.shields.io/badge/Gold_2-%23FFC433.svg
[g1]: https://img.shields.io/badge/Gold_1-%23FFC433.svg
[p5]: https://img.shields.io/badge/Platinum_5-%2376DDD8.svg
[p4]: https://img.shields.io/badge/Platinum_4-%2376DDD8.svg
[p3]: https://img.shields.io/badge/Platinum_3-%2376DDD8.svg
[p2]: https://img.shields.io/badge/Platinum_2-%2376DDD8.svg
[p1]: https://img.shields.io/badge/Platinum_1-%2376DDD8.svg
[passed]: https://img.shields.io/badge/Passed-%23009D27.svg
[failed]: https://img.shields.io/badge/Failed-%23D24D57.svg
[easy]: https://img.shields.io/badge/쉬움-%235cb85c.svg?for-the-badge
[medium]: https://img.shields.io/badge/보통-%23FFC433.svg?for-the-badge
[hard]: https://img.shields.io/badge/어려움-%23D24D57.svg?for-the-badge
