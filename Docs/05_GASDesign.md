# 05. Gameplay Ability System設計

## 1. 方針

Gameplay Ability Systemは、攻撃・回避・スタミナ・属性・状態・バフ・デバフを管理します。入力BindingそのものはGASの責務にせず、`IPlayerInputComponent`を入口とするプレイヤー入力層から必要なゲームプレイ要求を配送します。

Ability System ComponentはPlayerStateに配置する方針です。

```text
+----------------------------------+
| AActionPlayerState               |
|----------------------------------|
| UActionAbilitySystemComponent    |
| UCharacterAttributeSet           |
| UPostureAttributeSet             |
+----------------+-----------------+
                 | Owner
                 v
+----------------------------------+
| Player Character / ABasePlayer   |
|----------------------------------|
| ASC Avatar                       |
| Input Components                 |
| Animation / Physics              |
+----------------------------------+
```

## 2. プレイヤー入力との境界

現在の入力基盤は次を正とします。

```text
[Enhanced Input]
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent]
      ↓
[UBasePlayerInputComponent派生]
      |
      +--> Move / Lookなど直接処理
      |
      +--> Combat Input
              ↓
         [Ability Input Tag / Gameplay Request]
              ↓
         [ASC Input Processing]
```

- `IPlayerInputComponent`はInputActionのSetup / Teardown、Input Tag、押下状態の共通契約を定義する。
- `ABasePlayer`は具体的な派生入力Componentを列挙せず、Interface経由で管理する。
- Move / LookはGASを経由する必要がない。
- Attack / Dodge / Parry / Heal等は入力ComponentからASCへAbility入力として接続する。
- GAS側がEnhanced InputのMapping ContextやBindingライフサイクルを直接所有しない。
- 戦闘入力Componentを1Action単位にするか、複数Actionを集約するかは戦闘入力実装前に確定する。

## 3. AttributeSet

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

`Health <= 0`をプレイヤー・敵・ボスの死亡 / 撃破判定へ接続します。死亡 / 撃破遷移は同一Actorについて1回だけ確定させます。

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

## 4. Ability階層

```text
UActionGameplayAbility
    +--> UGA_AttackBase
    |       +--> UGA_LightAttack
    |       +--> UGA_HeavyAttack
    |       +--> UGA_ChargeAttack
    |       +--> UGA_AirAttack
    |       +--> UGA_DodgeAttack
    +--> UGA_Dodge
    +--> UGA_PerfectDodgeCounter
    +--> UGA_Parry
    +--> UGA_Guard              [Post-Vertical Slice]
    +--> UGA_FatalAttack
    +--> UGA_WeaponSkill
    +--> UGA_Heal
    +--> UGA_Jump
```

初期Vertical Sliceでは剣に必要なAbilityを優先し、斧・弓固有AbilityはPost-Vertical Sliceで追加します。

## 5. 戦闘Ability実行フロー

```text
[Enhanced Input]
      ↓
[IPlayerInputComponent実装]
      ↓
[Ability Input Tag / Gameplay Request]
      ↓
[ASC Input Processing]
      +--> 状態Tag確認
      +--> スタミナ確認
      +--> クールダウン確認
      +--> 武器条件確認
      +-- NG --> [Reject / Buffer]
      ↓
[Activate Ability]
      +--> Cost適用
      +--> Montage再生
      +--> Gameplay Tag付与
      +--> Hit / Dodge / Parry Window開始
      ↓
[終了 / Cancel]
```

Movement補正が必要なAbilityは、現在利用しているCharacterMovement等の移動APIへゲームプレイ層から要求します。実装されていない`IMovementDriver`や`UMovementAdapterComponent`を前提にはしません。Moverを将来評価する場合のみ、必要性が確認された時点で戦闘層とMover固有APIの境界を追加します。

## 6. Gameplay Tag案

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
Input.Move
Input.Look
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

Input Tagは`FTaggedInputAction`と入力Componentの識別にも使用可能とし、同一プレイヤー内の重複Tagは設定不備として扱います。

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

## 7. Montage

GASからの攻撃Montage再生は`UAbilityTask_PlayMontageAndWait`を基本候補とします。Montage NotifyとGameplay Eventを用いて、攻撃判定、コンボ受付、回避・パリィ受付等を同期します。

## 8. 初期化

```text
[PlayerState生成]
      ↓
[ASC / AttributeSet初期化]
      ↓
[Player Character Possessed]
      ↓
[InitAbilityActorInfo]
 Owner  = PlayerState
 Avatar = Player Character
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent::Setup]
      ↓
[Startup Ability付与]
      ↓
[剣Ability付与]
```

UnPossessed / EndPlay / InputComponent再構築時は、入力側が`Teardown()`を実行して古いBindingを残さないようにします。

### [戻る](../README.md#ドキュメント一覧)
