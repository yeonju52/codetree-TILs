# [메두사와 전사들 ![Gold1][g1]](https://www.codetree.ai/training-field/search/problems/medusa-and-warriors)

|유형|출처|소요시간 / 평균시간|
|---|---|---|
|[BFS](https://www.codetree.ai/training-field/search/?tags=BFS), [Simulation](https://www.codetree.ai/training-field/search/?tags=Simulation)|[일반연습 / 문제은행](https://www.codetree.ai/training-field/home)|1일 / 180+분|

### 헷갈렸던 부분 정리

#### 1. 메두사의 이동을 `BFS`로 구현해야 하나?
> 메두사는 **BFS로 맨해튼 최단거리 경로를 계산**해야 하고,
> 전사는 **각 턴마다 맨해튼 거리 기준으로 그리디하게 움직인다**.

처음에는 매 턴마다 맨해튼 거리를 기준으로 가까워지는 방향으로 이동하는 **그리디 방식**을 떠올렸지만, 문제는 **최단 경로**를 구하는 것이기 때문에 **`BFS`로 구현하는 것이 맞다**.

반면, **전사의 이동은 '맨해튼 거리'를 기준으로 그리디하게 움직이는 방식**이 맞다. (1순위: 상하좌우, 2순위: 좌우상하)
즉, 두 캐릭터의 이동 방식은 **다르다**.

> 문제 설명에서 "모든 경로 이동은 맨해튼 거리를 보장한다"고 나와 있는데,
이는 단순히 "이동은 상하좌우 4방향만 가능하다"는 의미이며, 이 조건 하에서는 **BFS로 탐색한 경로의 거리 = 맨해튼 거리**가 성립한다.

#### 2. 메두사의 이동 – 최단 경로 저장 로직
- BFS에서 `vis[nx][ny] = {x, y};`로 이전 위치를 저장.
- 도착 시 `vis` 배열을 거꾸로 따라가며 경로 복원:
```cpp
pair<int, int> prev = cur;
while (!(prev.X == st.X && prev.Y == st.Y)) {
    route[rlen++] = prev; // 이전 경로 저장
    prev = vis[prev.X][prev.Y]; // 경로 업데이트
}
```

> ⚠️ `x = vis[x][y].X, y = vis[x][y].Y;`처럼 순차적으로 갱신하면   **`x`가 바뀐 상태로 `vis[x][y]`를 참조하게 되어** 오류 발생


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