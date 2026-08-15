# FR-STAGE-002 Tutorialを実施する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-002` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#133` |
| 関連要件・設計 | `FR-STAGE-001`, Player主要Action, `FR-UI-002` |

## 2. 目的
Initial VSで必要な基本操作を段階的に案内し、Playerが通常Gameplayへ移行できるようにする。

## 3. 確定仕様・スコープ
- Move / Look / Jump / Light / Heavy / Dodge / LockOn / Healing / Checkpoint等の主要操作をStep化できる。
- 各Stepは対象Gameplay Actionの成立をEvent等から検知して完了する。
- Tutorial UIとGameplay Ruleを分離する。
- 全Step完了後に通常進行へ遷移する。

## 4. 基本フロー
```text
Tutorial開始
↓
Current Step表示
↓
対象Action成立待ち
↓
Step Complete
↓
次Step
↓
全Step完了
↓
通常Gameplay
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Tutorial Flow | Step順序・完了管理 |
| Gameplay System | Action成立Event提供 |
| Tutorial UI | Current Step表示 |

## 6. 状態 / Gameplay Tag
Tutorial進行はStep状態を正とする。Gameplay Action Tagは完了Event識別に利用可能。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Tutorial Steps | 順序・対象Action | Master Data |
| Step Text | 表示 | Master Data |
| Completion Event / ActionId | 完了判定 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
Tutorial Text / Current StepをGameplay HUDへ表示する。

## 9. 異常系・終了条件
- 同じStepを重複完了しない。
- 関係ないAction Eventで次Stepへ進めない。
- Tutorial終了時に専用UI /入力制御を残さない。

## 10. 受入条件
- [ ] Stepを定義順に進行できる。
- [ ] 対象Action成立でStepを完了できる。
- [ ] 重複完了しない。
- [ ] 全Step完了後に通常進行へ遷移できる。

## 11. 依存・Issue反映
### 依存
- `#132` Tutorial Text
- Player主要Action実装

### Issue反映
- `#133`へStep Data、Event連携、HUD表示を反映する。

## 12. 未決事項
なし
