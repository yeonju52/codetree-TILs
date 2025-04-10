# [메두사와 전사들 ![Gold1][g1]](https://www.codetree.ai/training-field/search/problems/medusa-and-warriors)

## 리팩토링
![alt text](refactoring_logic.png)

```cpp
vector<vector<int>> dir = { {0, 5, 4}, {1, 6, 7}, {2, 6, 4}, {3, 5, 7} };
// 1) area: 메두사 그림자 영역 1 체크
view(x, y, 1, dir[i]);

// 2) area: 전사 그림자 영역 3 체크
for (pos &war : warrior) {
    if (area[war.x][war.y] != 1) continue; // 1일 때만 신경 써야
    if (war.status) continue;
    double diffx = x - war.x, diffy = y - war.y;
    if (diffx == 0 || diffy == 0) view(war.x, war.y, 3, { dir[i][0] });
    else if (diffx / diffy < 0) view(war.x, war.y, 3, { dir[i][0], dir[i][1] });
    else view(war.x, war.y, 3, { dir[i][0], dir[i][2] });
}
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