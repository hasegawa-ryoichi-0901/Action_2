# FR-SAVE-004 Boss撃破報酬の付与後にAuto Saveする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-004` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-BOSS-015`, `FR-BOSS-016`, `FR-STAGE-013` |

## 2. 目的

Boss撃破結果と報酬を同一の確定済み進行状態として保存し、報酬欠落や重複取得を防ぐ。

## 3. 基本フロー

```text
[Boss Defeated]
      ↓
[Gold付与]
      ↓
[初回討伐報酬判定]
      +-- 未取得 --> [固有収集Item付与]
      ↓
[報酬状態確定]
      ↓
[Auto Save Request]
      ↓
[Clear Areaへ進行可能]
```

Stage Clear自体はAuto Save契機ではありません。

## 4. 受入条件

- [ ] Boss撃破状態より前にSaveしない。
- [ ] Gold付与完了後にSaveする。
- [ ] 初回固有Itemを付与する場合は、その付与完了後にSaveする。
- [ ] 同一Boss撃破でSave要求が重複しない。
- [ ] Save後にClear Triggerへ進行できる。
- [ ] 初期Vertical SliceではBoss再戦を前提にしない。
