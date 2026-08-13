# FR-PLAYER-016 SwordでParryできる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-016`](../../01_Requirements.md#fr-player-016) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#115](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/115) |
| 関連要件・設計 | [`FR-BOSS-013`](../../01_Requirements.md#fr-boss-013), [Combat System](../../03_CombatSystem.md), [GAS Design](../../05_GASDesign.md) |

## 2. 目的

Sword防御Actionとして、Parry可能Attackを受付Window内で弾き、Enemy / Bossへ反撃可能な隙を作る。

## 3. 確定仕様・スコープ

- Parry専用InputからActionを開始する。
- Parry Window内に到達した`Attack.Property.Parryable`のみ成功させる。
- Unparryable Attackは成功させない。
- 成功時はEnemy / BossへParry Success Eventを1回通知する。
- 失敗時は設定されたRecoveryへ遷移可能とする。

## 4. 基本フロー

```text
Parry Input
↓
Parry Ability開始
↓
Parry Window Open
↓
Enemy Attack到達
├ Parryable + Window内 → Success Event
└ その他 → Failure / Recovery
↓
Window Close / End
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Parry Ability | Windowと状態管理 |
| Enemy / Boss Attack | Parry可否Tag提供 |
| Enemy / Boss Combat | Success Eventから隙へ遷移 |
| Animation | Parry Montage / Timing通知 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Parrying` | Parry実行中 |
| `Window.Parry.Active` | 成功判定期間 |
| `Attack.Property.Parryable` | Parry可能Attack |
| `Attack.Property.Unparryable` | Parry不可Attack |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Parry Window | 成功時間 | 調整値 |
| Failure Recovery | 失敗硬直 | 調整値 |
| Parry Montage | Animation | Asset |
| Attack Parry Policy / Tags | 可否判定 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Parry Montage、成功Reaction |
| VFX / SE | Success / Failureを区別するFeedback |

## 9. 異常系・終了条件

- Death / Cancel / Montage中断時にParry WindowとTagを解除する。
- 同一HitでSuccess Eventを重複通知しない。
- Unparryable Attackを誤って無効化しない。

## 10. 受入条件

- [ ] Parry InputからActionを開始できる。
- [ ] Window内のParryable Attackだけ成功する。
- [ ] Success EventをEnemy / Bossへ1回通知できる。
- [ ] Failure / Cancel後にWindowとTagが残らない。

## 11. 依存・Issue反映

### 依存
- [#58](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58), [#60](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/60)
- Enemy / Boss Attack Definition

### Issue反映
- [#115](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/115)へInput、Window、Attack Tag、Success Event、Failure Recoveryを反映する。

## 12. 未決事項

なし
