# NFR-PERF-004 RTX3060開発環境で継続計測する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-PERF-004` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#134` |
| 関連要件・設計 | `NFR-PERF-001`～`003`, `NFR-PERF-005`, `NFR-PERF-006` |

## 2. 目的
同一GPU環境を継続的な比較基準として使用し、実装変更によるPerformance退行を追跡する。

## 3. 確定仕様・スコープ
- RTX3060搭載開発環境を基準計測環境とする。
- 解像度・Graphics・Build・Scenarioを記録する。
- 大きなGameplay / Rendering変更後に再計測できるようにする。

## 4. 基本フロー
```text
基準環境確認
↓
同一Build条件 / Scenario
↓
FPS / Frame Time / Thread / GPU計測
↓
結果記録
↓
過去結果と比較
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Performance Test | 基準環境で計測 |
| Documentation | 条件と結果記録 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| GPU / CPU / Build情報 | 計測条件 | Measurement |
| Resolution / Graphics | 再現条件 | Measurement |
| Scenario | 比較条件 | Test Data |
| Metrics | Performance結果 | Measurement |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- 異なるGraphics条件の結果を単純比較しない。
- Background Process等の明確な外乱がある計測は再取得する。

## 10. 受入条件
- [ ] RTX3060環境で基準計測できる。
- [ ] 計測条件を記録できる。
- [ ] 変更前後の結果を比較できる。

## 11. 依存・Issue反映
### 依存
- Performance Scenario

### Issue反映
- `#134`へ基準環境・条件記録を反映する。

## 12. 未決事項
なし
