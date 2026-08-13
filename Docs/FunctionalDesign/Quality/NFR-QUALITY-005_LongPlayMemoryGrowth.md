# NFR-QUALITY-005 長時間PlayでMemory増加を確認する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-QUALITY-005` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#145` |
| 関連要件・設計 | `NFR-QUALITY-002`, `NFR-QUALITY-006` |

## 2. 目的
繰り返し戦闘・Death / Respawn・Level / UI遷移等で不要Object / Delegate / Asset参照が蓄積し続けないことを確認する。

## 3. 確定仕様・スコープ
- Initial VSの代表Loopを複数回繰り返してMemory推移を確認する。
- Enemy Respawn、DeathDrop、Ability / Montage、UI、Save / Load等の繰り返し箇所を重点確認する。
- 一時的な増加と回収されない継続増加を区別する。

## 4. 基本フロー
```text
Baseline Memory取得
↓
代表Gameplay Loopを反復
↓
一定間隔でMemory取得
↓
GC / 状態安定後を比較
↓
継続増加あり?
├ No → 記録
└ Yes → 参照 / Object Lifecycle分析
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Long Play Test | Loop反復・Memory記録 |
| 各System | Object / Delegate / Timer Lifecycle管理 |
| Profiling | 増加原因特定 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Memory Usage | 推移確認 | Measurement |
| Iteration Count / Duration | 再現条件 | Test Data |
| Object / Allocation Snapshot | 原因分析 | Measurement |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Streaming / Cache等の意図した増加とLeak候補を区別する。
- Test条件を記録せず単発Memory値だけで判断しない。

## 10. 受入条件
- [ ] 代表Loopを複数回反復してMemory推移を記録できる。
- [ ] 状態安定後に単調増加し続ける主要Leakがないことを確認できる。
- [ ] 増加がある場合にObject / System単位で原因分析できる。

## 11. 依存・Issue反映
### 依存
- Initial VS通しPlay可能状態

### Issue反映
- `#145`でLong Play Memory Testを実施する。

## 12. 未決事項
なし
