# FR-ENEMY-001 近接通常Enemyを実装する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-001` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#119` |
| 関連要件・設計 | `FR-ENEMY-003`～`005`, `FR-ENEMY-006`, `Docs/06_EnemyAI.md` |

## 2. 目的
近距離でPlayerへ接近・攻撃する通常Enemyを用意し、複数Enemy戦の基本構成要素とする。

## 3. 確定仕様・スコープ
- Playerを有効Targetとして認識し近接Attack Rangeまで接近する。
- 近接AttackはMelee Attack Slot取得後のみ開始する。
- Down / Defeated中は通常AIとAttackを停止する。
- Target無効化時は追跡・Attackを終了する。

## 4. 基本フロー
```text
Player認識
↓
Attack Range内?
├ No → 接近 / Reposition
└ Yes
  ↓
Melee Slot取得
├ 失敗 → Wait / Circle
└ 成功 → Attack選択 → Ability実行 → Slot解放
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Enemy AI | Target認識、接近、Attack要求 |
| Attack Coordinator | Melee Slot管理 |
| Combat / Ability | Attack実行 |
| Enemy State | Down / Defeated可否提供 |

## 6. 状態 / Gameplay Tag
`State.Reaction.Downed`、Defeated状態をAI停止条件として参照する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Attack Range | Attack開始距離 | 調整値 |
| Movement Parameters | 接近速度等 | 調整値 |
| Attack Definitions | Attack候補 | Master Data |
| Behavior Profile | AI調整 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| Animation | 移動、近接Attack、Hit / Down / Death |
| VFX / SE | Attack予兆とHit Feedback |

## 9. 異常系・終了条件
- Slot取得後にCancel / Down / Defeatした場合は必ず解放する。
- Target無効時にAI TaskやAbilityを残さない。
- 同一Attackを多重開始しない。

## 10. 受入条件
- [ ] Playerへ接近できる。
- [ ] Melee Slot取得後だけAttackできる。
- [ ] Down / Defeated中にAttackしない。
- [ ] Attack終了・中断時にSlotを解放できる。

## 11. 依存・Issue反映
### 依存
- `#121` Attack Coordinator
- `#122` Health / Posture

### Issue反映
- `#119`へTarget、Range、Slot、Attack、Cleanupを反映する。

## 12. 未決事項
なし
