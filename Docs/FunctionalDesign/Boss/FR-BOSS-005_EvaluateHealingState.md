# FR-BOSS-005 PlayerのHealing状態を評価する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-005` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#127` |
| 関連要件・設計 | `FR-PLAYER-018`, `FR-BOSS-008`, `BOSS-AI-COMMON` |

## 2. 目的
Playerが確定済みHealing Action中かをBoss Contextへ提供し、Attack候補Scoreへ反映する。

## 3. 確定仕様・スコープ
- `State.Action.Healing`等の確定済みHealing状態を参照する。
- Heal Inputそのものや未発動状態を先読みしない。
- Healing ModifierをAttack Scoreへ適用可能にする。

## 4. 基本フロー
```text
Combat Context更新
↓
Player Healing State取得
↓
Healing Modifier解決
↓
Candidate Scoreへ反映
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Player Heal | Healing State公開 |
| Boss Context | 状態取得 |
| Evaluator | Modifier適用 |

## 6. 状態 / Gameplay Tag
`State.Action.Healing`を評価情報として利用する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Healing State | Context | Runtime |
| Healing Modifier | Score補正 | 調整値 |

## 8. UI / HUD / Animation / Feedback
Gameplay表示は不要。DebugでHealing State / Modifierを表示可能にする。

## 9. 異常系・終了条件
- Healing終了後に古い状態を保持しない。
- Player参照無効時は評価を停止する。

## 10. 受入条件
- [ ] Healing中 / 非Healingを区別できる。
- [ ] Healing状態をScoreへ反映できる。
- [ ] 未発動Inputを参照しない。
- [ ] DebugでModifierを確認できる。

## 11. 依存・Issue反映
### 依存
- `FR-PLAYER-018`

### Issue反映
- `#127`へHealing Contextを反映する。

## 12. 未決事項
なし
