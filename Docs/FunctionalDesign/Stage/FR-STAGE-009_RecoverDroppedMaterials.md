# FR-STAGE-009 DeathDropからResourceを回収できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-009` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 基本フロー

```text
[PlayerがDeathDrop回収条件を満たす]
      ↓
[DeathDrop内容取得]
      ↓
[Upgrade Material全量返却]
[Gold全量返却]
      ↓
[DeathDrop消去]
      ↓
[Auto Save]
```

## 3. 確定仕様

- DeathDropに格納されているUpgrade MaterialとGoldを全量回収する。
- 回収は1回だけ成立する。
- 回収完了後にDeathDropを消去する。
- 回収完了直後にAuto Saveする。

## 4. 受入条件

- [ ] 格納Material / Goldが全量Playerへ返却される。
- [ ] 同一DeathDropを二重回収できない。
- [ ] 回収後にDeathDropがWorldへ残らない。
- [ ] 回収完了後にAuto Save要求を1回発行する。
