# FR-BOSS-007 Playerの直近行動と戦闘傾向を評価する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-007` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#127` |
| 関連要件・設計 | `FR-BOSS-008`～`010`, `BOSS-AI-COMMON` |

## 2. 目的
Playerの確定済み行動履歴から短期傾向と戦闘全体傾向を取得し、BossのAttack選択が固定周期化しないようにする。

## 3. 確定仕様・スコープ
- 直近数秒の実行済みActionを履歴として保持する。
- 戦闘開始からのRange Bias、Dodge傾向等の集計値を保持可能にする。
- 未反映Inputや将来Action予測は利用しない。
- 履歴・傾向をAttack Score Modifierへ利用する。

## 4. 基本フロー
```text
Player Action確定
↓
Action Historyへ記録
↓
短期Window集計
↓
Battle Trend更新
↓
Boss Contextへ提供
↓
Attack Scoreへ反映
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Action History | 実行済みAction記録 |
| Trend集計 | 短期 / 戦闘全体傾向生成 |
| Evaluator | Modifierへ利用 |

## 6. 状態 / Gameplay Tag
履歴へ記録するActionは確定済みGameplay Event / Tagを利用可能とする。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Action History Window | 短期集計期間 | 調整値 |
| Action Records | 実行済み行動 | Runtime |
| Battle Trend Counters | 戦闘傾向 | Runtime |
| History / Trend Modifiers | Score補正 | 調整値 |

## 8. UI / HUD / Animation / Feedback
Gameplay HUD表示は不要。DebugでRecent Action、Dodge Rate、Range Bias等を確認可能にする。

## 9. 異常系・終了条件
- Encounter終了時に履歴を次戦へ意図せず持ち越さない。
- 無効Action Eventを集計しない。
- 履歴サイズを無制限に増加させない。

## 10. 受入条件
- [ ] 実行済みActionを時系列で記録できる。
- [ ] 直近Windowと戦闘全体傾向を分けて集計できる。
- [ ] ScoreへModifierとして利用できる。
- [ ] Debugで主要傾向を確認できる。

## 11. 依存・Issue反映
### 依存
- Player Action結果通知

### Issue反映
- `#127`へAction History / Battle Trendを反映する。

## 12. 未決事項
なし
