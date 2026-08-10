# FR-STAGE-014 通常敵撃破時にUpgrade MaterialとGoldを獲得する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-014` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-ENEMY-010`, `FR-STAGE-007` |

## 2. 基本フロー

```text
[Normal Enemy Defeated]
      ↓
[Reward値取得]
      ↓
[Upgrade Materialを直接加算]
[Goldを直接加算]
      ↓
[Reward通知]
```

## 3. 確定仕様

- Encounter単位ではなくEnemy1体ごとに付与する。
- World Drop Actorは生成しない。
- Upgrade MaterialとGoldをPlayer所持値へ直接加算する。
- Bossは通常のUpgrade Materialを付与しない。
- Reward量はゲームデータから取得するが、Master Data Readerの具体方式は別設計とする。

## 4. 受入条件

- [ ] Enemy Defeated確定前にRewardを付与しない。
- [ ] 1体につき1回だけMaterialとGoldを付与する。
- [ ] Reward取得のためのWorld Dropを生成しない。
- [ ] 同一Enemyの多重Defeat通知でRewardを重複付与しない。
