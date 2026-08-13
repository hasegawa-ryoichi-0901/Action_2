# NFR-QUALITY-002 既知のCrashを0件にする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-QUALITY-002` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#143` |
| 関連要件・設計 | `Docs/11_TestPlan.md`, `NFR-QUALITY-006` |

## 2. 目的
通常操作・異常系・Lifecycle境界で再現する既知CrashをRelease Buildへ残さない。

## 3. 確定仕様・スコープ
- Initial VSの主要Gameplay LoopとUI / Save / Level遷移を対象にCrash確認を行う。
- UObject / Actor無効参照、Delegate / Timer / Binding解除漏れ、Level遷移中処理を重点確認する。
- 再現可能な既知Crashが存在する状態をRelease完了としない。

## 4. 基本フロー
```text
代表Scenario / 異常系実行
↓
Crash発生?
├ No → 継続検証
└ Yes → Reproduction記録 → 原因修正 → 再検証
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| 各System | Lifecycle / 参照安全性保証 |
| Test | Crash Scenario実行・再現手順記録 |
| Release Verification | 既知Crash 0件確認 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Crash Log / Call Stack | 原因特定 | Test Evidence |
| Reproduction Steps | 再現 | Test Evidence |
| Build / Commit Id | 対象特定 | Test Evidence |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Target / Owner Destroy、UnPossessed、Level遷移、Save / Load中断等を検証する。
- Crash修正後は元Scenarioと周辺Regressionを再確認する。

## 10. 受入条件
- [ ] 主要Gameplay LoopでCrashしない。
- [ ] 代表Lifecycle境界でCrashしない。
- [ ] 既知の再現可能Crashが0件である。

## 11. 依存・Issue反映
### 依存
- Initial VS全System

### Issue反映
- `#143`をShipping前のCrash Gateとして扱う。

## 12. 未決事項
なし
