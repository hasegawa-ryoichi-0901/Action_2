# [FR-STAGE-014] 通常敵撃破報酬の獲得

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-014` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#97`, `#99` |
| 関連要件・設計 | `FR-ENEMY-010`, Player Inventory, `Docs/17_MasterDataCsvArchitecture.md` |

## 2. 目的
通常Enemy DefeatをUpgrade Material / Gold獲得へ接続し、Weapon Upgrade用Resourceを供給する。

## 3. 確定仕様・スコープ
- Enemy1体のDefeatedにつきRewardを1回だけ付与する。
- Initial VSではUpgrade Material + Goldを含む。
- RewardはPlayer Inventoryへ直接加算しWorld Drop Actorを生成しない。
- `EnemyId → RewardId → 0..N Reward Entry(ItemId / Amount)`の契約を利用する。
- Reward Entry数にGameplay付与ロジック構造を依存させない。

## 4. 基本フロー
```text
Enemy Defeated
↓
EnemyId → RewardId
↓
0..N Reward Entry取得
↓
各Item / AmountをPlayer Inventoryへ加算
↓
HUD / Feedback更新
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Enemy Defeat | Reward通知 |
| Reward Provider | RewardId解決・Entry取得 |
| Player Inventory | Item / Gold保持 |
| HUD | 所持値更新 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| EnemyId | Enemy識別 | Master Data |
| RewardId | Reward集合 | Master Data |
| ItemId / Amount | 0..N Reward | Master Data |

## 8. UI / HUD / Animation / Feedback
Gold / Upgrade Material所持値をHUDへ反映し、必要に応じ取得Feedbackを表示する。

## 9. 異常系・終了条件
- 多重Defeat通知でRewardを重複付与しない。
- 無効RewardId / ItemIdでCrashしない。
- World Drop Actorを生成しない。

## 10. 受入条件
- [ ] Enemy Defeated後だけRewardを付与できる。
- [ ] RewardIdから0..N Entryを取得できる。
- [ ] 各RewardをInventoryへ1回加算できる。
- [ ] Entry数変更で付与ロジックを変更しない。

## 11. 依存・Issue反映
### 依存
- `#98` Enemy Defeat
- Player Inventory

### Issue反映
- `#97`親、`#99` Reward Provider / Inventory付与として扱う。

## 12. 未決事項
なし
