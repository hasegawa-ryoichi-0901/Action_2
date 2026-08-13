# NFR-PERF-003 120fpsを挑戦目標とする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-PERF-003` |
| 優先度 | `Should` |
| 対応範囲 | `Initial Vertical Slice / Optimization` |
| 設計状態 | `Draft` |
| 関連Issue | `#135` |
| 関連要件・設計 | `NFR-PERF-002`, `NFR-PERF-004`～`006` |

## 2. 目的
60fps最低目標を維持した上で、余力がある場合により高いFrame Rateへ最適化できる基準を持つ。

## 3. 確定仕様・スコープ
- 120fpsは挑戦目標でありInitial VS完成条件の最低ラインではない。
- 60fps要件を犠牲にして120fps専用設計へ変更しない。
- 1080p基準条件で計測する。

## 4. 基本フロー
```text
60fps Gate達成
↓
Optimization余力確認
↓
120fps条件で計測
↓
Bottleneck分析
↓
効果の高い改善だけ適用
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Performance Review | 挑戦目標評価 |
| Gameplay / Rendering | 費用対効果の高い最適化 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| FPS / Frame Time | 120fps評価 | Measurement |
| Optimization Result | 改善前後比較 | Measurement |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- 120fps未達をInitial VS不合格理由にしない。
- 品質 / 可読性を大幅に損なう最適化を無条件に採用しない。

## 10. 受入条件
- [ ] 60fps最低目標と120fps挑戦目標を区別できる。
- [ ] 120fps条件のFrame Timeを測定できる。
- [ ] 最適化前後を比較できる。

## 11. 依存・Issue反映
### 依存
- `NFR-PERF-002`

### Issue反映
- `#135`内で60fps Gateとは別の挑戦目標として扱う。

## 12. 未決事項
なし
