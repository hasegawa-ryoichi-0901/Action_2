# FR-PLAYER-022 Down中の敵へFatal Attackを実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-022` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | 未割当 |
| 関連設計 | `FR-ENEMY-007`, `FR-ENEMY-008` |

## 2. 目的

EnemyのPosture BreakによるDownへ明確な攻撃報酬を与え、Down中だけPlayerがFatal Attackを実行できるようにする。

## 3. 確定仕様・スコープ

- EnemyはDown中にDown Animationを再生する。
- EnemyがDown中の間だけFatal Attack受付状態とFatal Attack受付Collisionを有効にする。
- Playerが受付Collision圏内で攻撃ボタン / キーを入力した場合にFatal Attackを開始する。
- Fatal Attack成立時はPlayerをEnemy側に定義されたFatal Attack基準座標へ位置合わせする。
- Gameplay処理は`UGA_FatalAttack`を使用する。
- Fatal Attack専用Montageを再生する。
- Fatal Damageを対象Enemyへ適用する。
- EnemyのDown状態終了、Defeat、Fatal Attack成立時に受付状態とCollisionを無効化する。
- Defeated EnemyへFatal Attackを開始しない。

## 4. 基本フロー

```text
[Enemy Posture <= 0]
  ↓
[Enemy Down + Down Animation]
  ↓
[Fatal Attack受付State / Collision ON]
  ↓
[PlayerがCollision圏内でAttack Input]
  +-- 条件NG --> [通常Attack / Reject]
  ↓
[Target固定]
  ↓
[PlayerをFatal Attack基準座標へ位置合わせ]
  ↓
[UGA_FatalAttack]
  ↓
[Fatal Attack Montage]
  ↓
[Fatal Damage]
  ↓
[受付State / Collision OFF]
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Enemy Down処理 | Down状態、Down Animation、Fatal受付開始・終了 |
| Fatal Attack受付Collision | Playerが実行可能範囲内かを判定する |
| Player Combat入力 | Attack InputをFatal Attack要求へ接続する |
| `UGA_FatalAttack` | 実行条件、Target固定、位置合わせ要求、Montage、Damage、終了処理 |
| Animation | Fatal Attack Montage / Enemy Reactionを表示する |

## 6. 状態・Gameplay Tag

| State / Tag | 用途 |
|---|---|
| `State.Reaction.Downed` | Enemy Down状態 |
| `Window.FatalAttack.Available` | Fatal Attack受付中 |
| `State.Action.FatalAttacking` | Player Fatal Attack実行中 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| FatalAttackPosition / Transform | Fatal Attack開始時のPlayer位置・向き | Enemy / Fatal Attack定義 |
| FatalAttackDamage | Fatal Damage量 | Attack Master Data |
| FatalAttackMontage | Player Fatal Attack Animation | Asset参照 |
| DownAnimation | Enemy Down中Animation | Asset参照 |
| FatalAttackCollision | Fatal Attack受付範囲 | Runtime / Actor設定 |
| FatalAttackWindow | Down中の受付状態 | Runtime State |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Enemy Down Animation、Player Fatal Attack Montage、Enemy Fatal Reaction |
| Camera | Fatal Attack中に必要なCamera補正はMontage /演出実装時に調整可能 |
| UI / HUD | Fatal Attack専用表示は必須にしない |

## 9. 異常系・終了条件

- EnemyがDown終了した場合は受付Collisionと`Window.FatalAttack.Available`を解除する。
- EnemyがFatal Attack開始前にDefeatedした場合は開始しない。
- Fatal Attack開始後にTarget参照が無効になった場合はAbilityを安全にCancelする。
- 多重Attack InputでFatal Attackを二重起動しない。
- Ability終了 / Cancel時にTarget参照、位置合わせ状態、Gameplay Tagを残さない。

## 10. 受入条件

- [ ] Enemy Posture<=0でDown Animationを再生し、Fatal Attack受付状態になる。
- [ ] Down中かつ受付Collision圏内のAttack InputでのみFatal Attackを開始できる。
- [ ] 開始時にPlayerがFatal Attack基準座標へ位置合わせされる。
- [ ] `UGA_FatalAttack`からFatal Attack Montageを再生できる。
- [ ] Fatal Damageを対象へ1回だけ適用できる。
- [ ] Down終了・Defeat・Fatal成立時に受付を無効化できる。
- [ ] 多重入力・Target無効化で重複DamageやCrashを起こさない。

## 11. 依存・Issue反映

- `FR-ENEMY-007` Enemy Down
- `FR-ENEMY-008` Fatal Attack受付
- Light Attack共有Combat基盤 / Damage基盤 / Montage連携
- Fatal Attackは独立したPlayer Gameplay Action Issueとして管理する。

## 12. 未決事項

なし。Fatal Attackの具体Damage値、Animation Asset、位置合わせ補間時間は調整項目とする。
