# FR-BOSS-006 Playerの残りStaminaを評価する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-006` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#127` |
| 関連要件・設計 | `FR-PLAYER-011`～`013`, `FR-BOSS-008`, `BOSS-AI-COMMON` |

## 2. 目的
Playerの確定済みStamina状態をBoss Attack評価へ利用し、Resource状況に応じた行動選択を可能にする。

## 3. 確定仕様・スコープ
- Current / Max Staminaから必要な比率・区分をContextへ提供する。
- 未反映Costや将来入力は参照しない。
- Stamina ModifierをAttack Scoreへ適用可能にする。

## 4. 基本フロー
```text
Combat Context更新
↓
Player Stamina取得
↓
比率 / 区分計算
↓
Stamina Modifier解決
↓
Candidate Scoreへ反映
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Player Attribute | Stamina公開 |
| Boss Context | 比率 / 区分算出 |
| Evaluator | Modifier適用 |

## 6. 状態 / Gameplay Tag
`State.Action.Exhausted`を補助情報として参照可能。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Current / Max Stamina | Context | Runtime |
| Stamina Thresholds | 区分 | 調整値 |
| Stamina Modifiers | Score補正 | 調整値 |

## 8. UI / HUD / Animation / Feedback
Gameplay表示はPlayer HUDが担当。Boss DebugでStamina比率 / Modifierを確認可能にする。

## 9. 異常系・終了条件
- MaxStamina 0等の不正値で除算しない。
- Player無効時に評価停止する。

## 10. 受入条件
- [ ] Player Staminaを安全に取得できる。
- [ ] 比率 / 区分をScoreへ反映できる。
- [ ] Debugで評価値を確認できる。

## 11. 依存・Issue反映
### 依存
- `FR-PLAYER-011`～`013`

### Issue反映
- `#127`へStamina Contextを反映する。

## 12. 未決事項
なし
