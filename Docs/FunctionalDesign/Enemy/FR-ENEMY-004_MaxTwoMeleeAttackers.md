# FR-ENEMY-004 同時にMelee AttackするEnemyを最大2体に制限する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-ENEMY-004`](../../01_Requirements.md#fr-enemy-004) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#118](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/118), [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121) |
| 関連要件・設計 | [`FR-ENEMY-003`](../../01_Requirements.md#fr-enemy-003), [`FR-ENEMY-005`](../../01_Requirements.md#fr-enemy-005) |

## 2. 目的
集団戦でMelee Attackが同時多発しすぎることを防ぎ、Playerが認識・対応可能な圧力へ制御する。

## 3. 確定仕様・スコープ
- Melee Active Slotの最大数は2体とする。
- Slot取得済みEnemyだけがMelee Attackを開始できる。
- Attack終了 / Cancel / Down / Defeat / Owner破棄時にSlotを解放する。

## 4. 基本フロー
```text
Melee Attack Request
↓
Active Melee Count < 2?
├ No → Denied
└ Yes → Slot Grant → Attack → Release
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Attack Coordinator | 最大2 Slot保証 |
| Enemy AI | Slot取得後のAttack開始と終了通知 |

## 6. 状態 / Gameplay Tag
なし。Slot所有状態はCoordinator管理。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Max Melee Active | 最大数 | 確定値2 |
| Current Slot Owners | 所有Enemy | Runtime |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Slot Owner無効化時に自動回収可能にする。
- 同じEnemyへ複数Slotを付与しない。

## 10. 受入条件
- [ ] 同時Melee Attack Enemyが2体を超えない。
- [ ] 3体目以降のRequestを拒否 / 待機できる。
- [ ] 終了・中断でSlotを確実に解放できる。

## 11. 依存・Issue反映
### 依存
- [`FR-ENEMY-003`](../../01_Requirements.md#fr-enemy-003)

### Issue反映
- [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121)へMelee Max=2と解放条件を反映する。

## 12. 未決事項
なし
