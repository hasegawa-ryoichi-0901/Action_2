# [FR-BOSS-011] ボス攻撃コンボの分岐

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-011` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#130` |
| 関連要件・設計 | `FR-BOSS-003`, `FR-BOSS-008`, `BOSS-AI-COMMON` |

## 2. 目的
Bossの1回のAttackからPlayer距離・状態・Phase等に応じて後続Attackを分岐させる。

## 3. 確定仕様・スコープ
- Attack Definitionから後続候補を参照できる。
- Branch条件にPlayer距離、状態、Phase等の確定Contextを使用できる。
- 条件不成立時はComboを終了し通常Attack選択へ戻る。
- Cancel / Defeat時はBranch状態を破棄する。

## 4. 基本フロー
```text
Boss Attack実行
↓
Combo Branch Window / 判定点
↓
後続候補取得
↓
条件評価
├ 有効候補あり → 次Attack
└ なし → Combo終了 → 通常選択
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Attack Definition | Branch候補 / 条件定義 |
| Combo Evaluator | 条件評価・次Attack選択 |
| Ability | Attack連続実行 |

## 6. 状態 / Gameplay Tag
Attack中Stateと必要なCombo Windowを利用する。具体TagはAttack設計に従う。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Combo Branches | 後続候補 | Master Data |
| Branch Conditions | 分岐条件 | Gameplay Data |
| Branch Window / Timing | 評価時点 | 調整値 |

## 8. UI / HUD / Animation / Feedback
Animationは各Attack Montageを利用する。DebugでBranch候補・条件・選択結果を確認可能にする。

## 9. 異常系・終了条件
- 存在しないBranch先を実行しない。
- Cancel / DefeatでComboを継続しない。
- Branch循環で無限Comboにならないようデータ検証可能にする。

## 10. 受入条件
- [ ] Attack Dataから後続候補を取得できる。
- [ ] Context条件でBranchを選択できる。
- [ ] 条件不成立時に通常選択へ戻れる。
- [ ] DebugでBranch理由を確認できる。

## 11. 依存・Issue反映
### 依存
- `#128` Attack Score / Context

### Issue反映
- `#130`へBranch Data、条件、Cleanup、Debugを反映する。

## 12. 未決事項
なし
