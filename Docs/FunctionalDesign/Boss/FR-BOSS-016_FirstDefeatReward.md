# FR-BOSS-016 Boss撃破時にGoldと初回固有Itemを獲得する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-016` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#100`, `#102` |
| 関連要件・設計 | `FR-BOSS-015`, `FR-SAVE-004`, `Docs/17_MasterDataCsvArchitecture.md` |

## 2. 目的
Boss DefeatのRewardとしてGoldと初回討伐証明用の固有収集ItemをPlayer Inventoryへ付与する。

## 3. 確定仕様・スコープ
- Boss Defeated後にRewardIdから0..N Reward Entryを取得する。
- GoldをPlayer Inventoryへ直接付与する。
- 初回討伐かつ未取得の場合だけ固有収集Itemを直接付与する。
- Bossは通常Upgrade Materialを付与しない。
- Initial VSではBoss再戦を実装しない。
- Reward確定後にAuto Saveへ通知する。

## 4. 基本フロー
```text
Boss Defeated
↓
RewardId解決
↓
Gold付与
↓
FirstDefeatClaimed?
├ Yes → Skip Unique Item
└ No → Unique Item付与 → Claimed更新
↓
Reward確定
↓
Auto Save Request
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Reward Provider | RewardIdからEntry取得 |
| Player Inventory | Gold / Unique Item保持 |
| Boss Progress | 初回取得状態判定 |
| Save | Reward確定状態保存 |

## 6. 状態 / Gameplay Tag
Reward自体に継続Gameplay Tagは不要。FirstDefeatClaimedは進行状態として保持する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| BossId | Boss識別 | Master Data |
| RewardId | Reward集合識別 | Master Data |
| Reward Entry(ItemId / Amount) | 0..N Reward | Master Data |
| First Defeat Unique ItemId | 初回Item | Master Data |
| FirstDefeatClaimed | 再取得防止 | Runtime / Save |

## 8. UI / HUD / Animation / Feedback
Gold / Unique Item取得FeedbackをUIへ通知可能にする。GoldはGameplay HUD所持値へ反映する。

## 9. 異常系・終了条件
- 同一DefeatでRewardを重複付与しない。
- Claimed済みUnique Itemを再付与しない。
- RewardId / ItemId不正時にCrashせず検出可能にする。

## 10. 受入条件
- [ ] Boss Defeated後にGoldを1回付与できる。
- [ ] 初回時だけUnique Itemを付与できる。
- [ ] Boss RewardとしてUpgrade Materialを付与しない。
- [ ] Reward確定後にAuto Saveへ1回通知できる。

## 11. 依存・Issue反映
### 依存
- `#101` Boss Defeated
- Player Inventory

### Issue反映
- `#102`へReward Provider、Inventory、初回判定を反映する。

## 12. 未決事項
なし
