# FR-STAGE-010 DeathDrop回収前に再死亡すると以前のDeathDropを消失させる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-010` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 目的

未回収DeathDropを1つだけ保持する高リスクな死亡ループを成立させる。

## 3. 基本フロー

```text
[Player再死亡]
      ↓
[未回収DeathDropあり？]
      +-- Yes --> [旧DeathDrop本体を消去]
                   [旧DeathDrop内Material / Goldを永久消失]
      ↓
[現在Playerが所持しているResourceから新DeathDropを生成]
      +--> Material 100%
      +--> Gold 70%
      +--> Gold 30%消失
```

旧DeathDropの内容を新DeathDropへ引き継ぎません。

## 4. 受入条件

- [ ] World上に未回収DeathDropが最大1つだけ存在する。
- [ ] 再死亡時に旧DeathDrop本体が消える。
- [ ] 旧DeathDrop内ResourceはPlayerにも新DeathDropにも戻らない。
- [ ] 新DeathDropは再死亡時点のPlayer所持Resourceのみから計算する。
- [ ] Save/Load後も同じルールを維持する。
