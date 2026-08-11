# FR-BOSS-016 Boss撃破時にGoldと初回固有Itemを獲得する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-016` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#100`, `#102` |
| 関連設計 | `FR-BOSS-015`, `FR-SAVE-004`, `FR-STAGE-013` |

## 2. 目的

Boss Defeatへ通常敵と異なるRewardを与え、初回討伐を固有ItemとしてPlayer Inventoryへ保持する。

## 3. 確定仕様・基本フロー

```text
[Boss Defeated]
      ↓
[Boss RewardIdからReward Entry取得]
      ↓
[GoldをPlayer Inventoryへ付与]
      ↓
[初回固有Item取得済み？]
   ├─ Yes → 追加付与なし
   └─ No  → 固有ItemをPlayer Inventoryへ付与
      ↓
[Reward確定]
      ↓
[FR-SAVE-004 Auto Save]
```

- Gold / Boss Unique ItemはPlayer Inventoryを正本とする。
- Bossは通常のUpgrade Materialを付与しない。
- 初回固有Itemは初回討伐時だけ付与する。
- World Dropは生成しない。
- Reward Masterは0..N Reward Entryを扱える構造とし、Reward件数へGameplayロジックを依存させない。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Boss Defeat | Reward開始Eventを1回通知する |
| Reward System | RewardIdを解決し0..N Entryを取得する |
| Player Inventory | Gold / Unique Itemの正本・加算・重複防止 |
| Save System | Reward確定後にAuto Saveする |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。First Defeat Item取得済み状態を永続化できること。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| BossId | Boss識別 | Master Data |
| RewardId | Reward参照 | Master Data |
| Reward Entry (ItemId / Amount) | Gold等の0..N報酬 | Master Data |
| FirstDefeatUniqueItemId | 初回固有Item | Master Data |
| FirstDefeatClaimed | 重複取得防止 | Save Data |

## 7. UI / Animation / Feedback

- Gold / Unique Item獲得FeedbackをHUD / Result表示へ通知可能にする。
- 表示方法はUI設計側で調整する。

## 8. 異常系・終了条件

- 同一Boss Defeat EventでRewardを重複付与しない。
- 取得済み初回固有Itemを再付与しない。
- RewardId / ItemId不正時は不正参照でCrashせず開発用Errorを検出可能にする。

## 9. 受入条件

- [ ] Boss Defeated確定前にRewardを付与しない。
- [ ] GoldをPlayer Inventoryへ1回だけ付与できる。
- [ ] 初回時だけUnique ItemをInventoryへ付与できる。
- [ ] Boss Rewardとして通常Upgrade Materialを付与しない。
- [ ] Reward確定後にAuto Saveへ接続できる。
- [ ] Reward Entry数が変わっても付与ロジック構造を変更しない。

## 10. 依存・Issue反映

- `#100`, `#102`, `#103`

## 11. 未決事項

なし。具体Reward量はMaster Data調整項目とする。
