# FR-PLAYER-022 Down中EnemyへFatal Attackを実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-022`](../../01_Requirements.md#fr-player-022) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#148](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/148) |
| 関連要件・設計 | [`FR-ENEMY-007`](../../01_Requirements.md#fr-enemy-007), [`FR-ENEMY-008`](../../01_Requirements.md#fr-enemy-008), [GAS Design](../../05_GASDesign.md) |

## 2. 目的

Enemy Posture Breakを高DamageのPlayer Actionへ接続し、Down状態への明確なCombat Rewardを提供する。

## 3. 確定仕様・スコープ

- EnemyはDown中Animationを再生しFatal Attack受付State / Collisionを有効化する。
- Playerが受付Collision圏内でAttack Inputした場合にFatal Attackを開始する。
- 開始時にPlayerをEnemy側Fatal Attack基準Transformへ位置合わせする。
- `UGA_FatalAttack`を使用する。
- Player Fatal Attack Montageを再生しFatal Damageを1回だけ適用する。
- Enemy Down終了 / Defeat / Fatal Attack成立時に受付を無効化する。

## 4. 基本フロー

```text
Enemy Down
↓
Fatal Attack受付State / Collision ON
↓
PlayerがCollision内でAttack Input
↓
Target有効性確認
↓
Fatal Attack Transformへ位置合わせ
↓
UGA_FatalAttack
↓
Montage
↓
Fatal Damage
↓
受付終了
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Enemy Down処理 | 受付State / Collision / Transform提供 |
| Player Input / Combat | Attack InputからFatal Action選択 |
| `UGA_FatalAttack` | 位置合わせ、Montage、Damage、Cleanup |
| Damage基盤 | Fatal Damage適用 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Reaction.Downed` | Enemy Down中 |
| `Window.FatalAttack.Available` | Fatal Attack受付可能 |
| `State.Action.FatalAttacking` | Player Fatal Attack中 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| FatalAttack Transform | Player位置合わせ | Runtime / Gameplay Data |
| Fatal Damage | Damage量 | 調整値 |
| Fatal Attack Montage | Player Animation | Asset |
| Down Animation | Enemy Animation | Asset |
| Fatal Attack Collision Shape / Size | 受付範囲 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Enemy Down、Player Fatal Attack、Enemy Fatal Reaction |
| UI / HUD | 受付状態を参照可能とする。専用Prompt表示は必須としない |
| VFX / SE | Fatal成立を通常Hitと区別するFeedback |

## 9. 異常系・終了条件

- Defeated / Down終了済みEnemyへ開始しない。
- 多重Attack Inputで二重起動しない。
- Target無効化 / Ability Cancelで位置合わせ、Tag、Target参照を解除する。
- Fatal Damageを重複適用しない。

## 10. 受入条件

- [ ] Down中かつ受付Collision内のAttack Inputでのみ開始できる。
- [ ] PlayerをFatal Attack Transformへ位置合わせできる。
- [ ] `UGA_FatalAttack`とMontageを実行できる。
- [ ] Fatal Damageを1回だけ適用できる。
- [ ] Down終了 / Defeat / Fatal成立時に受付を無効化できる。

## 11. 依存・Issue反映

### 依存
- [#123 Enemy Down / 受付](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/123)
- [#62 Damage](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/62)
- [#64 Montage Event](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/64)

### Issue反映
- [#148](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/148)へ位置合わせ、Ability、Montage、Damage、Cleanupを反映する。

## 12. 未決事項

なし
