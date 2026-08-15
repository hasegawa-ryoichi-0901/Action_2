# [FR-ENEMY-005] 近接・遠距離攻撃枠の分離

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-ENEMY-005`](../../01_Requirements.md#fr-enemy-005) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#118](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/118), [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121) |
| 関連要件・設計 | [`FR-ENEMY-003`](../../01_Requirements.md#fr-enemy-003), [`FR-ENEMY-004`](../../01_Requirements.md#fr-enemy-004) |

## 2. 目的
Melee Attack制限とRanged Attack制限を独立調整し、片方のSlot使用がもう片方を不必要に停止しないようにする。

## 3. 確定仕様・スコープ
- Melee SlotとRanged Slotを別Poolで管理する。
- Melee最大数は`FR-ENEMY-004`の2体。
- Ranged最大数は調整可能とする。
- Enemyは実行するAttack種別に対応したSlotだけを取得する。

## 4. 基本フロー
```text
Attack Request
↓
Attack Type
├ Melee → Melee Pool Request
└ Ranged → Ranged Pool Request
↓
Granted時のみAttack
↓
対応PoolへRelease
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Attack Coordinator | Pool分離とCapacity管理 |
| Enemy AI | Attack Typeに応じたSlot要求 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Melee Capacity | 近接上限 | 2 |
| Ranged Capacity | 遠距離上限 | 調整値 |
| Attack Type | Pool選択 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Melee SlotをRanged Releaseで解放しない等、Poolを混同しない。
- Enemy終了時に所有する全Slotを解放する。

## 10. 受入条件
- [ ] Melee / Ranged Slotを別管理できる。
- [ ] 一方のCapacity到達が他方のAttackを直接禁止しない。
- [ ] Attack終了時に正しいPoolへReleaseできる。

## 11. 依存・Issue反映
### 依存
- [`FR-ENEMY-003`](../../01_Requirements.md#fr-enemy-003), [`FR-ENEMY-004`](../../01_Requirements.md#fr-enemy-004)

### Issue反映
- [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121)へPool分離とCapacity設定を反映する。

## 12. 未決事項
なし
