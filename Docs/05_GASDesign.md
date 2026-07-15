# 05. Gameplay Ability System設計

## 1. 方針

Gameplay Ability Systemは、攻撃・回避・スタミナ・属性・状態・バフ・デバフを管理します。

Ability System ComponentはPlayerStateに配置します。

```text
+----------------------------------+
| AActionPlayerState               |
|----------------------------------|
| UActionAbilitySystemComponent    |
| UCharacterAttributeSet           |
| UPostureAttributeSet             |
+----------------+-----------------+
                 |
                 | Owner
                 v
+----------------------------------+
| AActionPlayerCharacter           |
|----------------------------------|
| ASCのAvatar Actor                |
| 入力・アニメーション・物理表現   |
+----------------------------------+
```

この構成により、Characterが再生成された場合もPlayerState側のAbilityと属性を維持しやすくします。

## 2. AttributeSet

### CharacterAttributeSet

```text
Health
MaxHealth
Stamina
MaxStamina
AttackPower
DefensePower
StaminaRecoveryRate
StaminaRecoveryDelay
ExhaustedRecoveryThreshold
HealingItemCount
MaxHealingItemCount
UpgradeMaterial
```

### PostureAttributeSet

```text
Posture
MaxPosture
PostureRecoveryRate
PostureRecoveryDelay
StaggerResistance
PostureDamageMultiplier
```

プレイヤーは独立した体勢ゲージを基本的に使用せず、StaggerResistanceを武器データから反映します。

## 3. Ability階層

```text
UActionGameplayAbility
    |
    +--> UGA_AttackBase
    |       |
    |       +--> UGA_LightAttack
    |       +--> UGA_HeavyAttack
    |       +--> UGA_ChargeAttack
    |       +--> UGA_AirAttack
    |       +--> UGA_DodgeAttack
    |
    +--> UGA_Dodge
    +--> UGA_PerfectDodgeCounter
    +--> UGA_Parry
    +--> UGA_Guard
    +--> UGA_FatalAttack
    +--> UGA_WeaponSkill
    +--> UGA_Heal
    +--> UGA_Jump
```

## 4. Ability実行フロー

```text
[Enhanced Input]
      |
      v
[Ability Input Tag]
      |
      v
[ASC Input Processing]
      |
      +--> 状態Tag確認
      +--> スタミナ確認
      +--> クールダウン確認
      +--> 武器条件確認
      |
      +-- NG --> [Reject / Buffer]
      |
      v
[Activate Ability]
      |
      +--> Cost適用
      +--> Montage再生
      +--> Gameplay Tag付与
      +--> Hit Window開始
      +--> Movement Request
      |
      v
[終了 / Cancel]
```

## 5. Gameplay Tag案

### 状態

```text
State.Action.Attacking
State.Action.Dodging
State.Action.Parrying
State.Action.Guarding
State.Action.Healing
State.Action.Exhausted
State.Action.FatalAttacking
State.Reaction.Hit
State.Reaction.Staggered
State.Reaction.Downed
State.Dead
```

### 入力

```text
Input.Attack.Light
Input.Attack.Heavy
Input.Attack.Charge
Input.Dodge
Input.Jump
Input.Parry
Input.Guard
Input.Heal
Input.LockOn
Input.WeaponSkill.Primary
Input.WeaponSkill.Secondary
```

### ウィンドウ

```text
Window.Hitbox.Active
Window.Combo.AcceptInput
Window.Cancel.Dodge
Window.PerfectDodge
Window.Counter.Available
Window.Parry.Active
Window.FatalAttack.Available
```

### 攻撃属性

```text
Attack.Type.Melee
Attack.Type.Ranged
Attack.Type.Grab
Attack.Type.Heavy
Attack.Type.Projectile
Attack.Property.Parryable
Attack.Property.Unparryable
Attack.Property.GuardBreak
```

## 6. Montage

GASからの攻撃Montage再生は`UAbilityTask_PlayMontageAndWait`を基本候補とします。

```text
[Gameplay Ability]
      |
      v
[Play Montage And Wait]
      |
      +--> OnCompleted
      +--> OnBlendOut
      +--> OnInterrupted
      +--> OnCancelled
```

Montage NotifyとGameplay Eventを用いて、攻撃判定、コンボ受付、移動補正を同期します。

## 7. 初期化

```text
[PlayerState生成]
      |
      v
[ASC / AttributeSet初期化]
      |
      v
[PlayerCharacter Possessed]
      |
      v
[InitAbilityActorInfo]
 Owner  = PlayerState
 Avatar = PlayerCharacter
      |
      v
[Startup Ability付与]
      |
      v
[装備武器Ability付与]
```
