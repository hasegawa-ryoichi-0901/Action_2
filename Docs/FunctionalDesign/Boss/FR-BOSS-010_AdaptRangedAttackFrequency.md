# FR-BOSS-010 状況に応じてRanged Attack頻度を変更する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-010` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#129` |
| 関連要件・設計 | `FR-BOSS-003`, `FR-BOSS-007`, `FR-BOSS-008` |

## 2. 目的
Playerが長距離を維持する等の状況に応じてRanged Attack候補の評価を変化させる。

## 3. 確定仕様・スコープ
- Distance、Battle Range Bias、Phase等からRanged Attack Scoreを補正する。
- Ranged Attackを固定周期で使用しない。
- Initial VSではSword Playerを対象としBow固有Gap Closerは`FR-BOSS-014`へ分離する。

## 4. 基本フロー
```text
Context更新
↓
Distance / Range Trend評価
↓
Ranged Candidate Modifier適用
↓
Attack Score比較
↓
選択された場合のみRanged Attack
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Context | Distance / Range Trend提供 |
| Evaluator | Ranged Modifier適用 |
| Ability | Ranged Attack実行 |

## 6. 状態 / Gameplay Tag
Phase、Cooldown、Defeated等を候補可否に利用する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Ranged Base Score | 基礎頻度 | Master Data |
| Range Modifiers | 距離補正 | 調整値 |
| Cooldown / Repetition Penalty | 使用頻度制御 | 調整値 |

## 8. UI / HUD / Animation / Feedback
DebugでRanged Candidate Score / Modifier / Cooldownを確認可能にする。

## 9. 異常系・終了条件
- Ranged Attack Data無効時に候補から除外する。
- Defeated / Target無効時に実行しない。

## 10. 受入条件
- [ ] 距離 / TrendでRanged Scoreを補正できる。
- [ ] Cooldown / Repetitionを考慮できる。
- [ ] Debugで補正結果を確認できる。

## 11. 依存・Issue反映
### 依存
- `#127`, `#128`

### Issue反映
- `#129`へRanged頻度適応を反映する。

## 12. 未決事項
なし
