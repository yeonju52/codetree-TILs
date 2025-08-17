# [루돌프의 반란 | 2023 하반기 오후 1번 문제](https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/rudolph-rebellion)

> 문제 링크: https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/rudolph-rebellion

| 수행 시간 | 메모리 사용량 | 날짜 / 시간 |
|------------|---------------|------------|
| 8ms        | 0MB           | 2025-08-17 / 19:20 |


- **처음 풀이 소요 시간:** 3시간
- **틀린 이유:** 문제를 정확히 이해하지 못함 (기절한 산타가 다시 충돌할 때, 기절해야하는 턴이 갱신되어야함)

```cpp
// 초기 로직 (정상 상태의 산타만 고려)
if(alive[board[rr][rc]] != 1) alive[board[rr][rc]] = 2;
// 수정 후 로직 (탈락하지 않은 산타 모두 (기절한 산타 포함))
if(alive[board[rr][rc]]) alive[board[rr][rc]] = 2;
```

- **오류를 찾는 데 걸린 시간:** +1시간