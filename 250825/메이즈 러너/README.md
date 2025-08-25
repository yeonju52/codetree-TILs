# [메이즈 러너 | 2023 상반기 오후 1번 문제](https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/maze-runner)

> 문제 링크: https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/maze-runner

| 수행 시간 | 메모리 사용량 | 날짜 / 시간 |
|------------|---------------|------------|
| 7ms        | 0MB           | 2025-08-25 / 22:58 |


- **처음 풀이 소요 시간:** 3시간 반
- **런타임 에러:**
  - arr.size() 인 M의 개수가 계속 바뀜 (삭제하기 때문)
  - 배열 삭제 시, it++ 주의
  ```cpp
  auto it = arr.begin();
  while(it != arr.end()) {
      int x = it->first, y = it->second;
      bool update = false;
      for (int i = 0; i < 4; i++) {
          int nx = x + dx[i], ny = y + dy[i];
          // 조건 생략
          if (ex == nx && ey == ny) {
              it = arr.erase(it);
              update = true;
          }
          else {
              *it = {nx, ny};
              it++;
              update = true;
          }
          break;
      }
      if (!update) it++;
  }

  M = arr.size(); // 변수 update 필수
  ```

- **오류를 찾는 데 걸린 시간:** +30분
