# [NFR-PERF-005] 平均フレームレート・フレーム時間確認

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-PERF-005`](../../01_Requirements.md#nfr-perf-005) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136) |
| 関連要件・設計 | [`NFR-PERF-002`](../../01_Requirements.md#nfr-perf-002), [`NFR-PERF-006`](../../01_Requirements.md#nfr-perf-006) |

## 2. 目的
平均FPSでは見えにくいFrame Spikeや操作感の不安定さを検出するため、Frame Timeを主要指標として確認する。

## 3. 確定仕様・スコープ
- Performance検証ではFPSとFrame Timeをセットで記録する。
- Boss戦、複数Enemy、Death / Respawn、VFX発生等の代表Scenarioを確認する。
- 瞬間的な大きなFrame Spikeを原因分析対象とする。

## 4. 基本フロー
```text
代表Scenario実行
↓
FPS + Frame Time取得
↓
Spike確認
↓
発生地点特定
↓
Thread / GPU分析へ接続
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Performance Test | Frame Time計測・Spike記録 |
| Profiling | 発生原因特定 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Frame Time | Frame安定性 | Measurement |
| FPS | 補助指標 | Measurement |
| Scenario Marker | Spike発生箇所 | Test Data |

## 8. UI / HUD / Animation / Feedback
なし。Development Profiling表示を利用する。

## 9. 異常系・終了条件
- Average FPSだけで合格判定しない。
- 一度だけの外乱と再現可能なSpikeを区別するため再計測可能にする。

## 10. 受入条件
- [ ] 代表ScenarioでFrame Timeを記録できる。
- [ ] Spike発生地点を特定できる。
- [ ] `NFR-PERF-006`のBottleneck分析へ接続できる。

## 11. 依存・Issue反映
### 依存
- Performance計測環境

### Issue反映
- [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136)へFrame Time分析を反映する。

## 12. 未決事項
なし
