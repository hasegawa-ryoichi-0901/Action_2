# FR-BOSS-008 状況に応じてAttack候補Scoreを変更する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-008` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#128` |
| 関連要件・設計 | `FR-BOSS-003`, `005`～`007`, `009`～`013`, `BOSS-AI-COMMON` |

## 2. 目的
Combat Contextを用いてAttack候補を数値評価し、Bossが状況に合うAttackを選択できるようにする。

## 3. 確定仕様・スコープ
- 各AttackはBase Scoreを持つ。
- Distance、Player State、History、Battle Trend、Phase、Position等のModifierを加算する。
- CooldownとRepetition Penaltyを減算する。
- 条件不成立Candidateを選択対象外にできる。
- Final Scoreと内訳をDebug表示できる。

## 4. 基本フロー
```text
Attack Candidates取得
↓
各Candidateの利用条件確認
↓
Base Score
+ Context Modifiers
- Cooldown / Repetition Penalty
↓
Final Score算出
↓
有効候補から選択
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Attack Definition | Base Score / 条件 / Modifier定義 |
| Evaluator | Score計算・選択 |
| Combat Context | 入力値提供 |
| Debug | Score内訳表示 |

## 6. 状態 / Gameplay Tag
Attack可否にPhase、Cooldown、Ability State等の確定状態を利用する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Base Score | 基礎評価 | Master Data |
| Context Modifiers | 状況補正 | Master Data |
| Cooldown | 再使用制限 | 調整値 |
| Repetition Penalty | 連続使用抑制 | 調整値 |
| Candidate Conditions | 利用可否 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
Gameplay HUD表示は不要。DebugでCandidate List、Base Score、各Modifier、Final Score、Selected Attackを確認可能にする。

## 9. 異常系・終了条件
- Candidateが0件の場合にCrashせず安全なFallback行動へ戻る。
- NaN / 無効Scoreを選択しない。
- Defeated後にScore計算しない。

## 10. 受入条件
- [ ] 複数Candidateを同一契約でScore計算できる。
- [ ] Context ModifierとPenaltyを反映できる。
- [ ] 無効Candidateを除外できる。
- [ ] 選択理由をDebugで追跡できる。

## 11. 依存・Issue反映
### 依存
- `#127` Combat Context

### Issue反映
- `#128`へCandidate生成、Score、Penalty、Debugを反映する。

## 12. 未決事項
なし
