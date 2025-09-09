# [코드트리 빵 | 2022 하반기 오후 1번 문제](https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/codetree-mon-bread)

> 문제 링크: https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/codetree-mon-bread

| 수행 시간 | 메모리 사용량 | 날짜 / 시간            |
| ----- | ------- | ------------------ |
| 8ms   | 0MB     | 2025-09-08 / 19:50 |

* **풀이 소요 시간:** 3시간 50분

- 주요 포인트1: src -> dst 의 최단거리의 '방향'을 알기 위해서는?
    - BFS 방향 (목적지 -> 출발지)로 역으로 찾아야 함
- 주요 포인트2: 최단거리를 찾을 때, 여러가지 후보가 있어서 우선순위를 고려해야한다면? (최단거리 + 우선순위)
    - BFS를 priority_queue<{dist, x, y}>로 구현하자