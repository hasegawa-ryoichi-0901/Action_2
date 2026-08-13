# FR-STAGE-008 死亡時にInventory ResourceをDeathDropへ移す

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-008` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#82`, `#84` |
| 関連要件・設計 | `FR-PLAYER-020`, `FR-STAGE-009`, `FR-STAGE-010`, `FR-SAVE-005` |

## 2. 目的
Player死亡にResource損失リスクを設け、未回収DeathDropの回収ループを成立させる。

## 3. 確定仕様・スコープ
- Death Animation完了後にDeathDrop処理へ進む。
- 旧未回収DeathDropが存在する場合は本体と中身を完全消失させる。
- Player InventoryのUpgrade Material 100%とGold 100%を新しい1つのDeathDropへ移す。
- 新DeathDropを死亡座標に生成する。
- 位置・格納内容確定後、Camera確認より前にAuto Saveする。

## 4. 基本フロー
```text
Death Animation完了
↓
旧DeathDropあり? → 完全消失
↓
Inventory Material100% + Gold100%を移動
↓
死亡座標へDeathDrop生成
↓
位置 / 内容確定
↓
Auto Save
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Player Inventory | Resource正本・移動元 |
| DeathDrop | Resource格納・位置保持 |
| Death Flow | 生成順序管理 |
| Save | 確定後Snapshot保存 |

## 6. 状態 / Gameplay Tag
Player `State.Dead`を前提とする。DeathDrop Active状態は進行Runtime / Save Stateとして管理する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Upgrade Material Amount | 格納 | Runtime |
| Gold Amount | 格納 | Runtime |
| Death Transform | Drop生成位置 | Runtime |
| Existing DeathDrop State | 旧Drop消失判定 | Runtime / Save |

## 8. UI / HUD / Animation / Feedback
DeathDrop ActorをCameraで確認可能にする。Inventory HUDは移動後のGold / Materialへ更新する。

## 9. 異常系・終了条件
- Resourceを複製・負値化しない。
- 旧Dropの中身を新Dropへ合算しない。
- Death1回につき新Dropを1つだけ生成する。

## 10. 受入条件
- [ ] Material / Goldを100% InventoryからDropへ移せる。
- [ ] 旧未回収Dropを完全消失できる。
- [ ] 死亡座標に新Dropを1つ生成できる。
- [ ] 確定後にAuto Saveへ接続できる。

## 11. 依存・Issue反映
### 依存
- `#83` Death State
- `#90` DeathDrop Auto Save

### Issue反映
- `#84`へResource移動、旧Drop消失、Transform、Save接続を反映する。

## 12. 未決事項
なし
