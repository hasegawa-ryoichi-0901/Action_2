# FR-STAGE-009 DeathDropからResourceを回収する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-009` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#86`, `#90` |
| 関連要件・設計 | `FR-STAGE-008`, `FR-STAGE-010`, `FR-SAVE-005` |

## 2. 目的
未回収DeathDropへ戻ることで失ったUpgrade Material / GoldをPlayer Inventoryへ全量復元できるようにする。

## 3. 確定仕様・スコープ
- PlayerがDeathDrop回収範囲へ入った場合に回収する。
- 格納MaterialとGoldを全量Player Inventoryへ戻す。
- 回収後にDeathDrop Actorを消去する。
- 回収完了後にAuto Saveする。

## 4. 基本フロー
```text
Player enters Recovery Range
↓
DeathDrop Active確認
↓
Material / Gold全量をInventoryへ返却
↓
DeathDrop Active解除 / Actor消去
↓
Auto Save
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| DeathDrop | 格納内容・回収判定 |
| Player Inventory | Resource受取 |
| Save | 回収済み状態保存 |

## 6. 状態 / Gameplay Tag
DeathDrop Active / Recovered状態をRuntime / Save Stateとして管理する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Stored Material / Gold | 回収量 | Runtime / Save |
| Recovery Range | 回収判定 | 調整値 |
| Active State | 二重回収防止 | Runtime / Save |

## 8. UI / HUD / Animation / Feedback
Inventory HUDへ回収後Resourceを反映し、回収Feedbackを表示可能にする。

## 9. 異常系・終了条件
- 同じDeathDropを二重回収しない。
- Inventory加算後にActor消去失敗しても再加算しないようTransaction順序を一意にする。

## 10. 受入条件
- [ ] Active DeathDropからMaterial / Goldを全量回収できる。
- [ ] 回収後にDropを消去できる。
- [ ] 二重回収できない。
- [ ] 回収完了後にAuto Saveできる。

## 11. 依存・Issue反映
### 依存
- `FR-STAGE-008`

### Issue反映
- `#86`へ回収 / Active State、`#90`へ回収後Saveを反映する。

## 12. 未決事項
なし
