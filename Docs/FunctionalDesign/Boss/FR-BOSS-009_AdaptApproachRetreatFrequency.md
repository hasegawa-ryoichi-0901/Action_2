# FR-BOSS-009 状況に応じて接近・離脱頻度を変更する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-009` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#129` |
| 関連要件・設計 | `FR-BOSS-003`, `FR-BOSS-007`, `FR-BOSS-008` |

## 2. 目的
Playerとの距離・行動傾向に応じてBossの接近 / 離脱選択を変化させ、固定的な位置取りを避ける。

## 3. 確定仕様・スコープ
- Distance、Range Bias、Phase等からApproach / Retreat候補Scoreを補正する。
- 同一移動行動の固定周期反復を避ける。
- 補正係数をデータ調整可能とする。

## 4. 基本フロー
```text
Context更新
↓
Distance / Trend評価
↓
Approach / Retreat候補へModifier
↓
Score比較
↓
選択移動行動実行
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Context | Distance / Trend提供 |
| Evaluator | 移動候補Score補正 |
| Boss Movement | 選択行動実行 |

## 6. 状態 / Gameplay Tag
Current Phase / Defeated等のBoss Stateを選択条件に利用する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Approach / Retreat Base Score | 基礎頻度 | 調整値 |
| Range / Trend Modifiers | 状況適応 | 調整値 |
| Repetition Penalty | 反復抑制 | 調整値 |

## 8. UI / HUD / Animation / Feedback
DebugでApproach / Retreat Scoreと選択結果を確認可能にする。

## 9. 異常系・終了条件
- Nav / Movement失敗時に同一行動を無限再試行しない。
- Defeated / Target無効時に移動を停止する。

## 10. 受入条件
- [ ] 距離 / Trendで接近・離脱Scoreを変えられる。
- [ ] 同じ移動を固定周期で反復しない。
- [ ] Debugで補正と結果を確認できる。

## 11. 依存・Issue反映
### 依存
- `#127`, `#128`

### Issue反映
- `#129`へApproach / Retreat適応を反映する。

## 12. 未決事項
なし
