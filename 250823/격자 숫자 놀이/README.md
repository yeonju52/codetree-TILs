# [격자 숫자 놀이| 2023 하반기 오후 1번 문제](https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/matrix-number-play)

> 문제 링크: https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/matrix-number-play

*동일한 문제: [[GOLD 4] 이차원 배열과 연산](https://www.acmicpc.net/problem/17140)

| 수행 시간 | 메모리 사용량 | 날짜 / 시간 |
|------------|---------------|------------|
| 9ms        | 0MB           | 2025-08-23 / 15:56 |


- **처음 풀이 소요 시간:** 1시간 반
- **틀린 이유:** `t = 0` 일 때를 고려하지 않음

```cpp
int t = 0;
while(t < MAX) {
    if (A[R][C] == K) break; // 조건을 만족하면, 즉시 종료
    // 로직
    t++;
}
```