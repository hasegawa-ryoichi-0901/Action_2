# 08. データ設計

## 1. データ駆動方針

C++には処理と制約を実装し、武器・攻撃・敵・強化の調整値はPrimary Data AssetまたはData Tableへ分離します。

```text
[C++ System]
    |
    +--> 実行ロジック
    +--> バリデーション
    +--> 状態遷移
    +--> デバッグ
    |
    v
[Data Asset / Data Table]
    |
    +--> 数値
    +--> Ability
    +--> Montage
    +--> VFX
    +--> SE
    +--> Gameplay Tag
```

## 2. 武器定義

```text
FWeaponDefinition
  WeaponId
  WeaponType
  DisplayName
  WeaponActorClass
  AbilitySet
  LightComboDefinition
  HeavyAttackDefinition
  ChargeAttackDefinition
  DodgeAttackDefinition
  AirAttackDefinition
  CounterAttackDefinition
  FatalAttackDefinition
  StaggerResistance
  CounterWindowDuration
  DodgeType
  UpgradeTable
```

## 3. 攻撃定義

```text
FAttackDefinition
  AttackId
  AbilityClass
  Montage
  SectionName
  StaminaCost
  HealthDamage
  PostureDamage
  AttackTags
  ParryPolicy
  GuardPolicy
  HitStopDuration
  MotionWarpPolicy
  ComboBranches
  Cooldown
  VFX
  SFX
```

## 4. 敵定義

```text
FEnemyDefinition
  EnemyId
  CharacterClass
  MaxHealth
  MaxPosture
  PostureRecoveryEnabled
  PostureRecoveryDelay
  PostureRecoveryRate
  AttackDefinitions
  BehaviorProfile
  MeleeSlotPolicy
  RangedSlotPolicy
  RewardDefinition
```

## 5. ボス攻撃定義

```text
FBossAttackDefinition
  AttackId
  AbilityClass
  RequiredPhase
  MinimumRange
  MaximumRange
  RequiredAngle
  BaseScore
  Cooldown
  RepetitionPenalty
  PlayerWeaponModifiers
  PlayerStaminaModifiers
  HealingStateModifier
  RangeTrendModifier
  ComboBranches
  RecoveryWindow
```

## 6. 武器強化

```text
FWeaponUpgradeRow
  WeaponId
  UpgradeLevel
  RequiredMaterialType
  RequiredMaterialAmount
  AttackPowerMultiplier
  PostureDamageMultiplier
  GrantedAbilities
  RemovedAbilities
```

素材は初期仕様では共通ですが、`RequiredMaterialType`を持たせ、後から武器別素材へ変更可能にします。

## 7. Gameplay Tagによる可否

パリィ可否などはboolの乱立を避け、攻撃Tagで表現します。

```text
Attack.Property.Parryable
Attack.Property.Unparryable
Attack.Property.Guardable
Attack.Property.GuardBreak
Attack.Type.Grab
Attack.Type.Projectile
```

## 8. データバリデーション

開発支援機能として次を検証します。

- AbilityClassが設定されている
- Montageが設定されている
- StaminaCostが0未満ではない
- 攻撃距離のMinがMax以下
- コンボ派生先が存在する
- パリィ可否Tagが矛盾していない
- 武器強化レベルが連続している
- 必要素材が負数ではない
- ボス攻撃が少なくとも1フェーズで有効
