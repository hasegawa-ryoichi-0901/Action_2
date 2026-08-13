# NFR-PERF-001 1920x1080を基準解像度とする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-PERF-001` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#134` |
| 関連要件・設計 | `NFR-PERF-002`～`006` |

## 2. 目的
Performance計測条件を揃えるため、Initial VSの基準解像度を1920x1080へ固定する。

## 3. 確定仕様・スコープ
- 1920x1080をPerformance基準解像度とする。
- FPS / Frame Time比較は同一Graphics条件を記録して行う。
- 最終的な他解像度対応を否定する要件ではない。

## 4. 基本フロー
```text
Performance Build起動
↓
Resolution = 1920x1080
↓
Graphics条件確認
↓
同一Scenarioで計測
↓
結果記録
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Performance Test | 解像度・条件固定 |
| Build / Config | 計測条件設定 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Resolution | 計測条件 | 1920x1080 |
| Graphics Settings | 条件再現 | Measurement |
| Test Scenario | 比較対象 | Test Data |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- 異なるResolution / Graphics条件の結果を同一基準として比較しない。

## 10. 受入条件
- [ ] 1080p条件でPerformance計測できる。
- [ ] Graphics条件を結果と一緒に記録できる。
- [ ] 同一Scenarioで再計測できる。

## 11. 依存・Issue反映
### 依存
- Performance計測Build

### Issue反映
- `#134`へ基準解像度と計測条件を反映する。

## 12. 未決事項
なし
