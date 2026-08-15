# NFR-PERF-002 60fpsを最低保証目標とする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-PERF-002`](../../01_Requirements.md#nfr-perf-002) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#135](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/135) |
| 関連要件・設計 | [`NFR-PERF-001`](../../01_Requirements.md#nfr-perf-001), [`NFR-PERF-004`](../../01_Requirements.md#nfr-perf-004)～[`006`](../../01_Requirements.md#nfr-perf-006) |

## 2. 目的
α版の操作応答とCombat品質を維持するため、基準環境で60fpsを最低保証目標とする。

## 3. 確定仕様・スコープ
- 1080p基準条件・RTX3060開発環境で60fpsを最低保証目標とする。
- 平均FPSだけでなくFrame Timeと大きなSpikeも確認する。
- 60fpsを満たさない場合はGame / Render / GPUの原因を分離して改善する。

## 4. 基本フロー
```text
基準Scenario実行
↓
FPS / Frame Time計測
↓
60fps目標を満たす?
├ Yes → 記録
└ No → Bottleneck分離 → 改善 → 再計測
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Performance Test | FPS / Frame Time計測 |
| Gameplay / Rendering | 原因箇所改善 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| FPS | 目標判定 | Measurement |
| Frame Time | 詳細判定 | Measurement |
| Test Scenario / Build | 再現条件 | Test Data |

## 8. UI / HUD / Animation / Feedback
なし。Development計測表示 / Profilerを利用する。

## 9. 異常系・終了条件
- 短時間の平均値だけで合格判定しない。
- Editor固有負荷のみをShipping Performanceと混同しない。

## 10. 受入条件
- [ ] 基準条件で60fps目標を検証できる。
- [ ] Frame Timeを同時確認できる。
- [ ] 未達時にBottleneck分析へ接続できる。

## 11. 依存・Issue反映
### 依存
- [#134](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/134)
- [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136)

### Issue反映
- [#135](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/135)へ60fps Gateを反映する。

## 12. 未決事項
なし
