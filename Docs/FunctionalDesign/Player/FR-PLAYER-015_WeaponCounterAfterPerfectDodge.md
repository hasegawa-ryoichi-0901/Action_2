# FR-PLAYER-015 Perfect Dodge後にWeapon固有Counterを実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-015`](../../01_Requirements.md#fr-player-015) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#114](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/114) |
| 関連要件・設計 | [`FR-PLAYER-014`](../../01_Requirements.md#fr-player-014), [Weapon System](../../04_WeaponSystem.md) |

## 2. 目的

Perfect Dodge成功をAttack機会へ変換し、Sword固有Counter Actionを成立させる。

## 3. 確定仕様・スコープ

- Perfect Dodge成功時のみCounter受付状態を開始する。
- Normal Dodgeでは受付を開始しない。
- Perfect Resultで記録したAttack SourceをCounter Targetとして利用可能とする。
- 受付時間は調整可能とする。
- 初期プレイアブル版ではSword Counterを実装し、Axe / Bow固有CounterはPost-VSで追加する。

## 4. 基本フロー

```text
Perfect Dodge Success
↓
Counter Available Window開始
↓
Counter Input?
├ No → Timeout → 受付終了
└ Yes
  ↓
Target有効性確認
  ↓
Sword Counter実行
  ↓
Damage / Feedback
  ↓
受付終了
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Dodge Result | Counter受付開始通知 |
| Counter Ability | 実行可否、Target、Damage |
| Animation | Counter Montage |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `Window.Counter.Available` | Counter Input受付期間 |
| `State.Action.Attacking` | Counter実行中 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Counter Window Duration | 受付時間 | 調整値 |
| Counter Attack Definition | Sword Counter | Gameplay Data |
| Attack Source / Target | Counter対象 | Runtime |
| Montage / Damage | Counter内容 | Asset / 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Sword Counter Montage |
| VFX / SE | Counter成功Feedback |

## 9. 異常系・終了条件

- Timeout / Death / CancelでWindowとTarget参照を解除する。
- TargetがDefeated / Destroyされた場合はCounterを開始しない。
- Perfect Dodge1回につき受付を重複生成しない。

## 10. 受入条件

- [ ] Perfect Dodge後だけCounter受付状態になる。
- [ ] Normal Dodgeでは受付しない。
- [ ] Window内InputでSword Counterを開始できる。
- [ ] Timeout / Target無効化で安全に終了できる。

## 11. 依存・Issue反映

### 依存
- [#57 Perfect Dodge Result](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/57)
- [#58 Combat共有基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58)

### Issue反映
- [#114](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/114)へ受付Window、Target保持、Counter Cleanupを反映する。

## 12. 未決事項

なし
