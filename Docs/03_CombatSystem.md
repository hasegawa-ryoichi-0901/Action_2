# 03. 戦闘システム

## 1. 戦闘状態

```text
[Neutral]
    +--> [Attack]
    +--> [Dodge]
    +--> [Jump]
    +--> [Parry]
    +--> [Heal]
    +--> [Exhausted]
    +--> [Hit / Stagger / Down]
    +--> [Dead]
```

α版はSwordのみを対象とします。状態はGameplay Tagで管理します。

```text
State.Action.Attacking
State.Action.Dodging
State.Action.Jumping
State.Action.Parrying
State.Action.Healing
State.Action.Exhausted
State.Reaction.Hit
State.Reaction.Staggered
State.Reaction.Downed
State.Dead
```

## 2. 攻撃フェーズ

```text
[Startup]
    ↓
[Commitment]
    ↓
[Active]
    ↓
[Recovery]
    ↓
[Neutral / Next Combo]
```

Cancel・Combo・Hitbox等の受付期間はAnim Notify StateまたはGameplay Tagで表現します。

```text
Window.Cancel.Dodge
Window.Combo.AcceptInput
Window.Hitbox.Active
Window.Counter.Available
Window.FatalAttack.Available
```

## 3. Input / Gameplay Action / Issueの境界

Enhanced InputのBindingとLifecycle管理は`IPlayerInputComponent`を入口とします。Gameplay Actionの単位とActorComponentの単位は同一と断定しません。

- Dodgeは1 Actionで、Normal Dodge / Perfect Dodgeは結果分岐。
- Light Attackは1 Action。
- Heavy AttackはLight Attackとは別Action。
- Combo AttackはLight / Heavy単体実装とは別の統合Action / Featureとして扱う。
- Gameplay Tag、GAS、責務、Lifecycleを考慮してComponent構成を決定する。

## 4. Dodge

Dodge Input Tagは1つです。Normal DodgeとPerfect Dodgeで別Input Actionを作りません。

```text
[Dodge Input]
      ↓
[実行条件 / Stamina確認]
      +-- NG --> [Reject / Buffer]
      ↓
[State.Action.Dodging]
      ↓
[移動入力あり？]
   ├─ Yes → 入力方向へRoll
   └─ No  → 後方へBack Step
      ↓
[Invincible Window]
[Perfect Dodge Window]
      ↓
[Enemy Attackとの関係を評価]
   ├─ Perfect Window成立 → Perfect Dodge Result
   ├─ Invincibleのみ成立 → Normal Dodge / No Damage
   └─ 無敵外でHit          → Damage
      ↓
[Recovery / Neutral]
```

確定事項：

- Invincible WindowとPerfect Dodge Windowは別々の調整値。
- 具体的な時間は開発中に調整可能とする。
- Air Dodge不可。
- Dodge中にEnemy Collisionを通過しない。
- Normal / Perfectの結果通知は用途に応じて別のGameplay Tag / Gameplay Eventを使用できる。
- Perfect Dodgeは別ActionではなくDodge Actionの結果。

## 5. Stamina / Exhausted

消費対象：Light Attack、Heavy Attack、Dodge、Perfect Dodge後Counter、Parry等。最後の消費から一定時間後に回復を開始します。

```text
Stamina <= 0
     ↓
[State.Action.Exhausted]
     +--> 通常移動       : 可能
     +--> Camera操作     : 可能
     +--> LockOn解除     : 可能
     +--> Jump           : 不可
     +--> Attack         : 不可
     +--> Dodge          : 不可
     +--> Parry          : 不可
     ↓
Stamina >= ExhaustedRecoveryThreshold
     ↓
[Neutral]
```

Exhaustedの実装単位は[#152](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/152)で管理します。

## 6. Perfect Dodge Result

成功条件はDodge Actionが有効で、Enemy Attack判定とPerfect Dodge Windowが重なることです。

```text
[Perfect Dodge Result]
      +--> 短いHit Stop
      +--> HUD通知
      +--> 結果通知Tag / Event
      +--> 対象Enemyを記録
      +--> Counter受付状態
```

- Slow Motionは使用しない。
- Counterは強制しない。
- Counter受付中のAttack InputでSword固有Counterへ派生できる。

## 7. Parry / Fatal Attack

### Parry

- α版ではSword固有。
- Attack PropertyごとにParry可否を設定する。
- 失敗時に専用Recoveryを発生させる。
- 成功時にEnemy Postureを大きく削る。
- Posture 0時のみDown / Fatal Attackへ接続する。

### Fatal Attack

```text
Enemy Down
↓
Down Animation + Fatal受付Collision
↓
Collision内でPlayer Attack Input
↓
Fatal Attack基準TransformへPlayer位置合わせ
↓
UGA_FatalAttack
↓
Fatal Attack Montage
↓
Fatal Damage
```

Enemy Down終了 / Defeat / Fatal Attack成立時は受付を無効化します。

## 8. HP・Reaction・Death・Defeat

### Player

```text
[Enemy / Boss Attack Hit]
   ↓
Health Damage + Reaction蓄積
   ↓
Health <= 0?
   ├─ Yes → [State.Dead]
   └─ No  → Hit / Stagger / Down判定
```

- Hit / Stagger / Downの蓄積値はEnemy / Boss Attack Dataが持つ。
- 蓄積値は内部計算のみでHUDへ表示しない。
- DeathはReactionより優先する。
- DeathDrop・Auto Save・Respawnは`Docs/09_SaveCheckpointDeath.md`を正とする。

### Normal Enemy

- HP0以下でDefeatedへ1回だけ遷移する。
- Attack Ability、AI移動、Attack Slotを終了・解放する。
- Enemy1体撃破ごとにUpgrade MaterialとGoldをPlayer Inventoryへ直接付与する。
- Rewardは`RewardId -> 0..N Reward Entry`として取得する。

### Boss

- HP0以下でDefeatedへ1回だけ遷移する。
- AI評価とAttack Abilityを停止する。
- GoldをPlayer Inventoryへ付与する。
- 初回討伐時のみ固有収集ItemをPlayer Inventoryへ直接付与する。
- Reward確定後にAuto Saveする。
- α版ではBoss Replayを実装しない。

## 9. Posture

EnemyはHPとは独立してPostureを持ち、0でDownします。HP0によるDefeatはPosture Downより優先します。

## 10. Healing Item

確定フロー：

```text
Heal Input
↓
Item Count確認
↓
Heal Animation開始
↓
Healing Itemを1個消費
↓
Animation継続
├ 被弾 → Heal中断 / Itemは返却しない
└ 完了 → HP回復
```

- 回数制限付きHealing Item。
- Checkpoint Rest / Respawnで最大数まで補充する。
- Animation開始前にHealが成立しなければItemは消費しない。
- Animation開始直後にItemを消費し、その後の被弾 / Cancelでは返却しない。
- Boss AIは`State.Action.Healing`を評価可能。

### [戻る](../README.md#ドキュメント一覧)
