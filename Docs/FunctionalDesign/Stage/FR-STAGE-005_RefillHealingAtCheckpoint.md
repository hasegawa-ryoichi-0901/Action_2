# FR-STAGE-005 Checkpoint Rest時にPlayerを回復・補充する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-005` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#91`, `#93` |
| 関連要件・設計 | `FR-STAGE-003`, `FR-PLAYER-018`, `FR-SAVE-002` |

## 2. 目的
Checkpoint RestでPlayerの攻略Resourceを回復し、次の探索 / 戦闘を開始できる状態へ戻す。

## 3. 確定仕様・スコープ
- RestでHPをFullにする。
- RestでStaminaをFullにする。
- Healing ItemをMax Countまで補充する。
- Rest状態確定後にAuto Saveする。

## 4. 基本フロー
```text
Checkpoint Rest
↓
HP Full
↓
Stamina Full / Exhausted解除
↓
Healing Item Full
↓
Enemy Respawn
↓
Rest確定 → Auto Save
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Player Attribute | HP / Stamina回復 |
| Healing Resource | Item補充 |
| Checkpoint | Rest順序管理 |

## 6. 状態 / Gameplay Tag
`State.Action.Exhausted`等、回復後に成立しない一時状態を解除する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| MaxHealth / MaxStamina | Full回復 | Runtime / Gameplay Data |
| MaxHealingItemCount | 補充上限 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
HUDへHP / Stamina / Healing Itemの更新を反映する。Rest演出はAsset側で調整可能。

## 9. 異常系・終了条件
- Max値を超えて設定しない。
- Restを多重適用しない。
- Dead状態Playerへ通常Restを適用しない。

## 10. 受入条件
- [ ] HP / StaminaをFullにできる。
- [ ] Healing ItemをMaxまで補充できる。
- [ ] Exhausted等の矛盾状態を残さない。
- [ ] HUDへ反映できる。

## 11. 依存・Issue反映
### 依存
- `FR-STAGE-003`, `FR-PLAYER-018`

### Issue反映
- `#93`へPlayer回復 / 補充を反映する。

## 12. 未決事項
なし
