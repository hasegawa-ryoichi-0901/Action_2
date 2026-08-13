# FR-ENEMY-003 通常戦で複数Enemyが同時に行動する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-003` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#121` |
| 関連要件・設計 | `FR-ENEMY-004`, `FR-ENEMY-005`, `Docs/06_EnemyAI.md` |

## 2. 目的
複数Enemyが同時にPlayerを認識・移動しつつ、Attack権だけを制御して集団戦を成立させる。

## 3. 確定仕様・スコープ
- 複数Enemyは同時に認識・移動・位置調整できる。
- Attack開始だけをMelee / Ranged Slotで制御する。
- Attack Slotを持たないEnemyはWait / Circle / Reposition等を行う。

## 4. 基本フロー
```text
複数EnemyがPlayer認識
↓
各Enemyが位置調整
↓
Attack希望
↓
CoordinatorへSlot Request
├ Granted → Attack
└ Denied → 非Attack行動継続
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| 各Enemy AI | 行動候補とSlot Request |
| Attack Coordinator | 同時Attack数制御 |

## 6. 状態 / Gameplay Tag
Attack Slot所有状態はCoordinatorを正とし、Gameplay Tagを必須としない。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Registered Enemies | 参加Enemy | Runtime |
| Slot Capacity | 同時Attack数 | 調整値 |
| Waiting Priority | 待機順序 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Enemy Destroy / Defeat / Downで登録・Slotを解放する。
- Slot二重取得・二重解放を防ぐ。

## 10. 受入条件
- [ ] 複数Enemyが同時にPlayerを追跡できる。
- [ ] SlotなしEnemyも停止せず非Attack行動を行える。
- [ ] Slot制御が`FR-ENEMY-004/005`へ接続する。

## 11. 依存・Issue反映
### 依存
- `FR-ENEMY-004`, `FR-ENEMY-005`

### Issue反映
- `#121`へ複数Enemy登録、Slot Request、待機行動を反映する。

## 12. 未決事項
なし
