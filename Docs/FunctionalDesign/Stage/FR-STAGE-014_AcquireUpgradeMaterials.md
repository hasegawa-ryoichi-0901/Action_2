# FR-STAGE-014 通常敵Defeat時にRewardを獲得する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-014` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#97`, `#99` |
| 関連設計 | `FR-ENEMY-010`, `FR-STAGE-007` |

## 2. 目的

通常敵1体のDefeatをPlayer Inventoryの強化Resource獲得へ接続する。

## 3. 確定仕様・基本フロー

```text
[Normal Enemy Defeated]
      ↓
[EnemyIdからRewardId取得]
      ↓
[RewardIdから0..N Reward Entry取得]
      ↓
[各Item / AmountをPlayer Inventoryへ加算]
      ↓
[Reward Feedback]
```

- RewardはEncounter単位ではなくEnemy1体ごとに1回だけ付与する。
- Initial VSの通常敵RewardにはUpgrade MaterialとGoldを含める。
- World Drop Actorは生成しない。
- Gold / Upgrade MaterialはPlayer Inventoryを正本とする。
- Reward件数にGameplayロジックを依存させない。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Enemy Defeat | Reward要求を1回発行する |
| Reward System | EnemyId→RewardId→0..N Entryを解決する |
| Player Inventory | Item / Amountを加算する |
| HUD | Reward取得Feedbackを表示可能にする |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。同一EnemyのReward付与済み状態を識別できること。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| EnemyId | Reward参照元 | Master Data |
| RewardId | Reward Group参照 | Master Data |
| ItemId | Reward Item識別 | Master Data |
| Amount | 付与数 | Master Data |

## 7. UI / Animation / Feedback

Gold / Upgrade Material取得をHUDへ通知可能にする。Visualは`FR-UI-002`側で調整する。

## 8. 異常系・終了条件

- Defeated確定前にRewardを付与しない。
- 同一Enemyの多重Defeat EventでRewardを重複付与しない。
- RewardId / ItemId不正時にCrashしない。

## 9. 受入条件

- [ ] Enemy1体のDefeatedにつきRewardを1回だけ付与できる。
- [ ] RewardIdから0..N Entryを取得できる。
- [ ] Upgrade Material / GoldをPlayer Inventoryへ直接加算できる。
- [ ] World Drop Actorを生成しない。
- [ ] Reward Entry数を変更してもGameplay付与ロジック構造を変更しない。
- [ ] 多重Defeat通知でRewardを重複付与しない。

## 10. 依存・Issue反映

- `#97`, `#99`

## 11. 未決事項

なし。具体Reward量はMaster Data調整項目とする。
