# NFR-PERF-006 Game Thread / Render Thread / GPUのBottleneckを分離する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-PERF-006`](../../01_Requirements.md#nfr-perf-006) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136) |
| 関連要件・設計 | [`NFR-PERF-005`](../../01_Requirements.md#nfr-perf-005), [`NFR-MAINT-006`](../../01_Requirements.md#nfr-maint-006) |

## 2. 目的
Performance未達時に推測だけで最適化せず、Game Thread、Render Thread、GPUのどこが支配的かを特定して改善する。

## 3. 確定仕様・スコープ
- Frame Time悪化時に主要Thread / GPUの処理時間を比較する。
- Game Thread負荷、Render Thread負荷、GPU負荷を分離して記録する。
- 原因箇所に応じてGameplay、Rendering、Asset、Tick等の改善対象を決定する。

## 4. 基本フロー
```text
Frame Time未達 / Spike
↓
Game / Render / GPU Time取得
↓
支配的Bottleneck判定
↓
該当Systemを詳細Profiling
↓
改善
↓
同条件で再計測
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Profiling | Thread / GPU時間取得 |
| Gameplay / Rendering | 該当原因の改善 |
| Performance Test | 改善前後比較 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Game Thread Time | CPU Gameplay負荷 | Measurement |
| Render Thread Time | CPU Render負荷 | Measurement |
| GPU Time | GPU負荷 | Measurement |
| Capture / Scenario | 再現 | Measurement |

## 8. UI / HUD / Animation / Feedback
なし。UEのProfiling / Stat情報をDevelopment用途で利用する。

## 9. 異常系・終了条件
- 一つのMetricだけで原因を断定しない。
- Profiling機能自体のOverheadを考慮して比較する。

## 10. 受入条件
- [ ] Game / Render / GPU時間を分離して確認できる。
- [ ] 支配的Bottleneckを特定できる。
- [ ] 改善後に同条件で再計測できる。

## 11. 依存・Issue反映
### 依存
- [`NFR-PERF-005`](../../01_Requirements.md#nfr-perf-005)

### Issue反映
- [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136)へThread / GPU分離分析を反映する。

## 12. 未決事項
なし
