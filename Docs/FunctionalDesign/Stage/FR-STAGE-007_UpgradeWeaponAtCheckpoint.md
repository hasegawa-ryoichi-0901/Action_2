# FR-STAGE-007 Checkpointで武器を強化する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-007` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 目的

通常敵から獲得したUpgrade MaterialとGoldを、Checkpointでのみ武器成長へ変換する。

## 3. 基本フロー

```text
[Checkpoint Menu]
      ↓
[Weapon Upgrade選択]
      ↓
[次Level存在確認]
      ↓
[Gold Cost確認]
      ↓
[Upgrade Material Cost確認]
      +-- 不足 --> [Reject / Resource変更なし]
      ↓
[Gold + Materialを同一Transactionで消費]
      ↓
[Weapon Level / Parameter / Ability更新]
      ↓
[結果表示]
```

## 4. 確定仕様

- UpgradeはCheckpoint Menu内でのみ可能。
- GoldとUpgrade Materialの両方が必要。
- Goldの用途はWeapon Upgradeのみ。
- Cost量はゲームデータから取得する。
- Upgrade完了自体はAuto Save契機ではない。
- Playerは必要に応じてCheckpoint MenuからManual Saveできる。

## 5. 受入条件

- [ ] Checkpoint外からUpgradeできない。
- [ ] GoldまたはMaterialのどちらか不足時は何も消費しない。
- [ ] 成功時のみ両Resourceを消費する。
- [ ] Upgrade結果が即時反映される。
- [ ] Upgrade完了だけではAuto Saveしない。
