# FR-PLAYER-017 AxeでGuardまたはReceiveを実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-017`](../../01_Requirements.md#fr-player-017) |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | `FEATURE-AXE-*`, [Weapon System](../../04_WeaponSystem.md) |

## 2. 目的

Axe固有防御として、Sword Parryとは異なるGuard / Receive系Actionを提供する。

## 3. 確定仕様・スコープ

- 初期プレイアブル版対象外。
- Axe装備時のみ利用可能とする。
- Guard / Receiveの詳細なDamage軽減・Stamina・Guard Break RuleはPost-VS実装前に確定する。

## 4. 基本フロー

```text
Axe Guard Input
↓
Axe装備確認
↓
Guard / Receive状態
↓
Attack受付
↓
Post-VSで確定するGuard Result
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Weapon / Ability | Axe防御Actionの実行 |
| Enemy Attack | Guard可否 / Guard Break情報提供 |

## 6. 状態 / Gameplay Tag

`State.Action.Guarding`を候補とする。詳細TagはPost-VS設計で確定する。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Guard Policy | 防御Result | Gameplay Data |
| Stamina Cost / Damage Reduction | 防御Cost / 軽減 | 未決調整値 |
| Guard Montage | Animation | Asset |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Axe Guard / Receive Animation |
| VFX / SE | Guard成功 / Break Feedback |

## 9. 異常系・終了条件

- Sword / Bow装備時に開始しない。
- Death / Weapon ChangeでGuard状態を解除する。

## 10. 受入条件

- [ ] Axe装備時だけGuard Actionを開始できる。
- [ ] Post-VSで確定するGuard RuleをData Drivenで適用できる。
- [ ] 終了時にGuard状態を残さない。

## 11. 依存・Issue反映

### 依存
- Axe Future Feature
- [`FR-PLAYER-008`](../../01_Requirements.md#fr-player-008)

### Issue反映
- Post-VS RoadmapでGuard仕様確定後にIssue化する。

## 12. 未決事項

| 未決事項 | Issue作成前に確定必須 | 理由 |
|---|---|---|
| Guard / ReceiveのDamage軽減、Stamina、Guard Break Rule | Yes | Gameplay ResultとIssue境界が変わるため |
