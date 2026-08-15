# [NFR-QUALITY-001] 進行不能バグゼロ

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-QUALITY-001`](../../01_Requirements.md#nfr-quality-001) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#142](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/142) |
| 関連要件・設計 | [Test Plan](../../11_TestPlan.md), α版全機能要件 |

## 2. 目的
TitleからEnding後のTitle復帰まで、Playerが通常操作で進行できなくなる不具合を残さない。

## 3. 確定仕様・スコープ
- α版の必須進行経路を通しTestする。
- Death / Respawn、Checkpoint、Boss Defeat、Reward Save、Clear Trigger、Ending、Title復帰を重点確認する。
- 進行不能が再現した場合はRelease Gateを通過させない。

## 4. 基本フロー
```text
New Game / Continue
↓
Tutorial
↓
Normal Battle
↓
Checkpoint / Death / Respawn
↓
Boss
↓
Reward / Save
↓
Clear Trigger
↓
Ending
↓
Title
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Test Plan | 通しScenario定義 |
| 各Gameplay System | 進行状態の一意性保証 |
| Release Verification | 進行不能Bug 0件確認 |

## 6. 状態 / Gameplay Tag
各SystemのProgress Stateを確認対象とする。本要件固有Tagはなし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Test Scenario | 通し進行 | Test Data |
| Reproduction Steps | 不具合再現 | Test Evidence |
| Build / Commit Id | 検証対象 | Test Evidence |

## 8. UI / HUD / Animation / Feedback
進行に必要なMenu / Trigger / Feedbackが操作不能にならないことを確認する。

## 9. 異常系・終了条件
- Death直後、Save失敗、Target消失、Sequence Skip等の境界で進行不能にならない。
- 進行不能Bugが1件でも既知のままならRelease完了扱いにしない。

## 10. 受入条件
- [ ] New GameからEnding後Titleまで完走できる。
- [ ] Death / Respawnを挟んでも完走できる。
- [ ] Checkpoint / Save / Loadを使用しても完走できる。
- [ ] 既知の進行不能Bugが0件である。

## 11. 依存・Issue反映
### 依存
- α版主要Gameplay機能

### Issue反映
- [#142](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/142)をRelease前の進行確認Issueとして扱う。

## 12. 未決事項
なし
