# [미지의 공간 탈출 ![Gold2][g2]](https://www.codetree.ai/training-field/search/problems/escape-unknown-space)

|유형|출처|소요시간 / 평균시간|
|---|---|---|
|[BFS](https://www.codetree.ai/training-field/search/?tags=BFS)|[일반연습 / 문제은행](https://www.codetree.ai/training-field/home)|330+분 / 180+분|


### 잘못된 좌표 변환 하드코딩으로 2시간 디버깅하는 이슈..

- **문제 상황**: 3차원 BFS 구현 중, 평면 간 이동 로직에서 **하드코딩된 상수 인덱스(`2`)** 를 사용함.
- **헷갈린 배경**: 이전에 풀었던 **큐브(큐빙) 문제**에서 `2`를 자주 써서 습관적으로 박아버림.
- **실제 조건**: 맵의 크기를 고려하면 `2`가 아니라 **`M - 1`**로 처리했어야 함.

```cpp
arr[i][j] = arr[i][2];  // 잘못된 하드코딩
//        👇
arr[i][j] = arr[i][M - 1];  // 맵 크기 반영
```



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