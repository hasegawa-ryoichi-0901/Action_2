# NFR-MAINT-005 Gameplay TagでGameplay状態を一元管理する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-MAINT-005`](../../01_Requirements.md#nfr-maint-005) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#140](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/140) |
| 関連要件・設計 | [Combat System](../../03_CombatSystem.md), [GAS Design](../../05_GASDesign.md) |

## 2. 目的
Attack、Dodge、Parry、Healing、Reaction等の状態を個別boolへ分散させず、System間で共通解釈できるGameplay Tagへ整理する。

## 3. 確定仕様・スコープ
- Action状態、Reaction状態、Window、Attack Property等を用途別Tag階層で管理する。
- Input TagとGameplay State / Result Tagは用途を区別する。
- DodgeのInput Tagは1つとし、Perfect Dodge等の結果通知には別Result / Event Tagを利用可能にする。
- 同じ意味の状態を複数bool / Tagで二重管理しない。

## 4. 基本フロー
```text
Gameplay状態開始
↓
対応Tag付与
↓
他SystemがTagを条件 / 通知として参照
↓
状態終了 / Cancel
↓
Tag解除
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Gameplay Tag定義 | 命名・階層管理 |
| 各Gameplay System | 自分が所有するTag Lifecycle管理 |
| GAS / Rule | Tagによる可否・状態判定 |

## 6. 状態 / Gameplay Tag
代表例：`State.Action.Attacking`、`State.Action.Dodging`、`State.Action.Healing`、`State.Reaction.Downed`、`Window.PerfectDodge`、`Window.Parry.Active`等。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Native / Config Gameplay Tags | 状態識別 | Config / Code |
| Tag Ownership | 付与・解除責務 | Design |
| Tag Conditions | Ability可否 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
HUD / Animationは必要なGameplay Tag / Eventを参照して表示を切り替えられるが、Tagの正本を所有しない。

## 9. 異常系・終了条件
- Cancel / Death / Owner破棄後に一時Tagを残さない。
- 同じ意味を複数Tagで表現して判定を分岐させない。
- Input TagとState Tagを混同しない。

## 10. 受入条件
- [ ] 主要Action / Reaction / WindowをTagで識別できる。
- [ ] Tagの付与・解除Ownerを説明できる。
- [ ] Cancel / Death後に一時Tagが残らない。
- [ ] Input / State / Resultの用途を区別できる。

## 11. 依存・Issue反映
### 依存
- GAS / Gameplay Tag基盤

### Issue反映
- [#140](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/140)で主要TagとLifecycleを横断監査する。

## 12. 未決事項
なし
