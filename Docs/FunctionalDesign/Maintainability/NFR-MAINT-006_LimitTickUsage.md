# NFR-MAINT-006 Tickの使用を必要な箇所に限定する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-MAINT-006` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#141` |
| 関連要件・設計 | `NFR-PERF-005`, `NFR-PERF-006` |

## 2. 目的
不要な毎Frame処理を削減し、Actor数やSystem増加によるGame Thread負荷と保守コストを抑える。

## 3. 確定仕様・スコープ
- Event、Delegate、Timer、Ability Task、StateTree / Behavior Tree更新等で代替できる処理は常時Tickを使用しない。
- Tickが必要な処理は理由・有効期間・停止条件を明確にする。
- 非アクティブ時はTick無効化 / 頻度低減を検討する。
- 毎Frameの全Actor検索を前提にしない。

## 4. 基本フロー
```text
毎Frame更新が必要か確認
↓
Event / Timer等で代替可能?
├ Yes → Tickを使わない
└ No → Tick利用理由を明示
        ↓
      Active期間だけ有効化
        ↓
      終了時に停止
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| 各Class / Component | Tick必要性判断・Lifecycle管理 |
| Performance Review | Tick Cost確認 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Tick Enabled State | Lifecycle確認 | Runtime |
| Tick Interval | 頻度調整 | 調整値 |
| Profiling Result | 負荷確認 | Measurement |

## 8. UI / HUD / Animation / Feedback
なし。開発時はProfiler / Stat結果で確認する。

## 9. 異常系・終了条件
- Owner非アクティブ / Destroy後にTickを継続しない。
- Event処理とTick処理で同じ更新を二重実行しない。

## 10. 受入条件
- [ ] 常時Tickを使用する箇所に必要性を説明できる。
- [ ] Event / Timerで代替可能な毎Frame処理を排除できる。
- [ ] 非アクティブ時に不要Tickを停止できる。
- [ ] Tick負荷をProfilingで確認できる。

## 11. 依存・Issue反映
### 依存
- Performance計測環境

### Issue反映
- `#141`でTick利用箇所を監査する。

## 12. 未決事項
なし
