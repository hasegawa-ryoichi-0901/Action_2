# [FR-PLAYER-019] 通常回避

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-019`](../../01_Requirements.md#fr-player-019) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#52](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52), [#53](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/53), [#54](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/54), [#55](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/55), [#56](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/56), [#57](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/57) |
| 関連要件・設計 | [`FR-PLAYER-011`](../../01_Requirements.md#fr-player-011), [`FR-PLAYER-014`](../../01_Requirements.md#fr-player-014), [Combat System](../../03_CombatSystem.md) |

## 2. 目的

Player基本Dodge Actionとして、Move Inputに応じたRoll / Back StepとDamage回避Windowを提供する。

## 3. 確定仕様・スコープ

- Input TagはDodgeのみ。
- Move Inputがある場合は現在のMove Input方向へRollする。
- Move Inputがない場合はCharacter後方へBack Stepする。
- Grounded時のみ開始し、Air Dodgeは行わない。
- Enemy Collisionを通過しない。
- Dodge中はInvincible Windowを持つ。
- Perfect Dodgeは同一ActionのResultで`FR-PLAYER-014`が扱う。

## 4. 基本フロー

```text
Dodge Input
↓
Grounded / Stamina / 禁止状態確認
↓
Move Inputあり?
├ Yes → Input方向Roll
└ No → Back Step
↓
Dodge State + Invincible Window
↓
Animation終了 / Cancel
↓
通常状態
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input層 | Dodge Input配送 |
| Dodge Ability | Cost、State、Window |
| Movement / Animation | Roll / Back Step移動と表現 |
| Collision | Enemyを通過しない物理制約 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Dodging` | Dodge実行中 |
| Invincible Window状態 | Damage無効判定。具体TagはTag設計へ従う |
| `Window.PerfectDodge` | Perfect判定。別調整値 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Dodge Stamina Cost | 実行Cost | 調整値 |
| Roll / Back Step Montage | Animation | Asset |
| Dodge Distance / Duration | 移動 | 調整値 |
| Invincible Window | Damage無効 | 調整値 |
| Perfect Window | Perfect判定 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Move InputありRoll、なしBack Step |
| VFX / SE | Normal Dodgeは必要最小限。Perfectは`FR-PLAYER-014`で区別する |

## 9. 異常系・終了条件

- Airborne / Death / Down / Exhausted等の禁止状態で開始しない。
- Enemy CollisionをDodge中も無効化しない。
- End / CancelでDodge Tag、Invincible、Windowを解除する。
- 多重InputでDodgeを重複開始しない。

## 10. 受入条件

- [ ] Move InputありでInput方向Roll、なしでBack Stepできる。
- [ ] Grounded時だけ開始できる。
- [ ] Enemy Collisionを通過しない。
- [ ] Invincible Window中の対象Damageを無効化できる。
- [ ] Perfect WindowをInvincible Windowと独立調整できる。

## 11. 依存・Issue反映

### 依存
- [#61 Stamina](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61)
- [`FR-PLAYER-014`](../../01_Requirements.md#fr-player-014)

### Issue反映
- [#52](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52)を親Issueとして[#53](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/53)～[#57](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/57)へInput、Ability、Movement、Window、Resultを分割する。

## 12. 未決事項

なし
