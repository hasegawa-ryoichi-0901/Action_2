# FR-UI-002 Initial Vertical SliceのGameplay HUDを提供する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-UI-002` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | 未割当 |

## 2. 目的

Playerが戦闘・進行・Save状態を把握するために必要な情報だけをHUDへ表示する。

## 3. 確定仕様・スコープ

Initial Vertical Sliceで必要なHUD要素を次とする。

- Player HP
- Player Stamina
- Healing Item残数
- Gold
- Upgrade Material
- LockOn Marker
- Boss HP
- Perfect Dodge成功Feedback
- Save中 / Save完了 / Save失敗の状態表示
- Tutorial Text / Tutorial進行表示

Player Reaction用の内部蓄積値は表示しない。

## 4. 基本フロー

```text
[Gameplay State / Attribute / Event変更]
  ↓
[HUDへ通知]
  ↓
[対象Widget更新]
```

LockOn Marker、Perfect Dodge、Save表示等はEvent駆動を優先し、毎FrameのActor全検索を前提にしない。

## 5. 責務

| 対象 | 責務 |
|---|---|
| Gameplay System / ASC / Inventory | HUDへ必要な状態・値を提供する |
| HUD / Widget | 表示とPresentationのみを担当する |
| Targeting | Current TargetとLockOn解除を通知する |
| Save System | Save状態を通知する |
| Tutorial | 現在Step / Textを通知する |

## 6. 状態・Gameplay Tag

要件ごとの既存State / Eventを参照し、HUD専用のGameplay Ruleを作らない。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Health / MaxHealth | Player HP表示 | Runtime Attribute |
| Stamina / MaxStamina | Stamina表示 | Runtime Attribute |
| HealingItemCount | 回復残数 | Runtime / Inventory |
| Gold | 所持Gold表示 | Player Inventory |
| UpgradeMaterial | 所持素材表示 | Player Inventory |
| CurrentLockTarget | LockOn Marker | Runtime Target |
| Boss Health / MaxHealth | Boss HP表示 | Runtime Attribute |
| Tutorial Text | Tutorial表示 | UI Data |
| Save State | Save Feedback | Runtime Event |

## 8. UI / HUD / Animation / Feedback

本要件そのものがUI / HUD設計。Visual Style、Layout、色、Animation尺は調整可能とする。

## 9. 異常系・終了条件

- Target無効化時にLockOn Markerを残さない。
- Boss非Encounter時にBoss HPを残さない。
- Level Transition / Title復帰時にGameplay HUDを残さない。
- Save失敗時に成功表示を出さない。

## 10. 受入条件

- [ ] Initial Vertical Sliceで必要なHUD要素を表示できる。
- [ ] Attribute / Inventory変化がHUDへ反映される。
- [ ] LockOn解除時にMarkerが消える。
- [ ] Perfect Dodge成功時のみ成功Feedbackを出せる。
- [ ] Save成功 / 失敗を区別できる。
- [ ] Player Reaction内部蓄積値を表示しない。
- [ ] Title / Endingへ遷移した際にGameplay HUDが残らない。

## 11. 依存・Issue反映

各Gameplay Systemの実装Issueでは、その機能に必要なHUD要素の通知契約までを受入条件へ含める。Visual実装は本UI Issueで統合する。

## 12. 未決事項

なし。Layout / Art / Animationは調整項目とする。
