# FR-SAVE-004 Boss Reward確定後にAuto Saveする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-004` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#103` |
| 関連要件・設計 | `FR-BOSS-015`, `FR-BOSS-016`, `FR-STAGE-013` |

## 2. 目的
Boss DefeatとReward取得を同一進行状態として保存し、その後のClear Trigger進行と整合させる。

## 3. 確定仕様・スコープ
- Boss Defeated後、Goldと初回固有Itemを含むReward状態を確定する。
- Reward確定後にAuto Saveを1回発行する。
- Save完了後にClear Area / Trigger進行を許可する。
- Stage Clear / Clear Trigger進入では追加Auto Saveしない。

## 4. 基本フロー
```text
Boss Defeated
↓
Reward付与 / FirstDefeat更新
↓
Reward確定
↓
Auto Save
↓
Save完了
↓
Clear Trigger有効化
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Boss Reward | 保存前の状態確定 |
| Save基盤 | Snapshot保存 |
| Stage Progression | Save完了後のClear進行 |

## 6. 状態 / Gameplay Tag
Boss Defeated / FirstDefeatClaimed / Reward確定を進行状態として保持する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Boss Defeat State | 進行保存 | Runtime / Save |
| Inventory Reward State | Gold / Unique Item | Runtime / Save |
| FirstDefeatClaimed | 再取得防止 | Runtime / Save |

## 8. UI / HUD / Animation / Feedback
Save中 / 成功 / 失敗をHUDへ通知可能にする。

## 9. 異常系・終了条件
- Reward確定前にSaveしない。
- 同一Boss DefeatでSaveを重複発行しない。
- Save未完了でClear Triggerを有効化しない。

## 10. 受入条件
- [ ] Reward確定後に1回だけAuto Saveできる。
- [ ] Inventory / FirstDefeat状態を含めて保存できる。
- [ ] Save完了後にStage Progressionへ通知できる。

## 11. 依存・Issue反映
### 依存
- `#102` Boss Reward
- `#88` Save基盤

### Issue反映
- `#103`へReward後SaveとClear接続を反映する。

## 12. 未決事項
なし
