# 07. クラス設計

## 1. 方針

設計書は実装済みのプレイヤー基盤を正として更新します。現在存在しない`IMovementDriver`、`UMovementAdapterComponent`、`UMoverDriver`、`UCharacterMovementDriver`は現行アーキテクチャの前提としません。

初期Vertical Sliceでは、既存の`ABasePlayer`と`IPlayerInputComponent`を入力基盤として拡張し、戦闘・Targeting・GAS等を段階的に追加します。

## 2. 現在のプレイヤー基盤

```text
+---------------------------------------------------+
| ABasePlayer                                       |
|---------------------------------------------------|
| CameraBoom / FollowCamera                         |
| DefaultMappingContext                             |
| TMap<InputTag, IPlayerInputComponent>             |
| SetupPlayerInputComponent                         |
| TeardownPlayerInputComponents                     |
| Enable / Disable MappingContext                   |
+-----------------------------+---------------------+
                              |
                              v
+---------------------------------------------------+
| IPlayerInputComponent                             |
|---------------------------------------------------|
| GetTaggedInputAction                              |
| IsPressed                                         |
| Setup                                             |
| Teardown                                          |
+-----------------------------+---------------------+
                              ^
                              |
+---------------------------------------------------+
| UBasePlayerInputComponent : UActorComponent       |
|---------------------------------------------------|
| TaggedInputAction                                 |
| bIsPressed                                        |
| BindActions                                       |
| HandleStarted / Completed / Canceled              |
+---------------+----------------------+------------+
                |                      |
                v                      v
+---------------------------+   +---------------------------+
| UPlayerMoveInputComponent |   | UPlayerLookInputComponent |
|---------------------------|   |---------------------------|
| Move / DoMove             |   | Look / DoLook             |
| AddMovementInput          |   | Controller Yaw / Pitch    |
+---------------------------+   +---------------------------+
```

### 責務

`ABasePlayer`:
- アタッチ済み`UBasePlayerInputComponent`を収集する。
- `IPlayerInputComponent`としてInput Tagごとに管理する。
- Input Tag重複を拒否する。
- `SetupPlayerInputComponent`再実行時に古いBindingをTeardownしてから再構築する。
- UnPossessed / EndPlayでMapping ContextとBindingを解除する。

`IPlayerInputComponent`:
- 入力Componentの共通契約を定義する。
- 個別Actionの実装内容そのものは規定しない。

`UBasePlayerInputComponent`:
- InputAction、Input Tag、押下状態、Bindingライフサイクルを共通化する。

派生Input Component:
- Move、Look、Jump、Combat等の個別入力をゲームプレイ要求へ変換する。

## 3. 入力からゲームプレイへの依存方向

```text
[Enhanced Input]
      ↓
[IPlayerInputComponent]
      |
      +--> [Move Input] ------> [Pawn / Character Movement]
      |
      +--> [Look Input] ------> [Controller / Camera]
      |
      +--> [Combat Input] ----> [ASC / Gameplay Ability]
      |
      +--> [Target Input] ----> [Targeting System]
```

入力Componentは入力受付と配送を担当し、戦闘ルール、ダメージ計算、AI、セーブ等を所有しません。

## 4. 初期Vertical Sliceで追加するプレイヤー責務

```text
ABasePlayer / Player Character
    |
    +-- Input Components
    |      +-- Move
    |      +-- Look
    |      +-- Jump
    |      +-- Dodge
    |      +-- Attack / Parry / Heal
    |      +-- LockOn
    |
    +-- AbilitySystem連携
    |      +-- Health / Stamina
    |      +-- Attack / Dodge / Parry / Heal
    |
    +-- Targeting
    |      +-- Soft Lock
    |      +-- Manual Lock
    |      +-- Target Switch
    |
    +-- Input Buffer
    |      +-- 保存 / 有効期限 / 優先順位 / 消費
    |
    +-- Interaction
           +-- Checkpoint
           +-- DeathDrop回収
```

これらの具体クラス名は実装Issueで既存命名との整合を確認して決定します。存在しないクラスを基本設計上の確定実装として扱いません。

## 5. Movement方針

現在の通常移動は`UPlayerMoveInputComponent`から`APawn::AddMovementInput`へ要求し、`ABasePlayer`はCharacterMovementを使用しています。

```text
[Move Input]
      ↓
[UPlayerMoveInputComponent]
      ↓
[Controller Yawから方向算出]
      ↓
[APawn::AddMovementInput]
      ↓
[CharacterMovement]
```

Moverは将来のプロトタイプ候補として残しますが、現時点ではMovement AdapterやMovement Driverを先行実装しません。Mover導入の具体的必要性が確認された場合のみ、戦闘・入力層へMover固有依存を漏らさない境界を設計します。

## 6. カメラ

`ABasePlayer`が`USpringArmComponent`と`UCameraComponent`を保持し、`UPlayerLookInputComponent`がControllerへYaw / Pitch入力を渡します。

```text
[Look Input]
      ↓
[UPlayerLookInputComponent]
      ↓
[AddControllerYawInput / PitchInput]
      ↓
[CameraBoom]
      ↓
[FollowCamera]
```

Targeting導入後は、自由カメラ操作とロックオン補正の責務境界をTargeting設計で定義します。

## 7. GAS / PlayerState候補

Combat実装時はASCをPlayerState側に配置する既存方針を維持します。`ABasePlayer`またはその派生Player CharacterをAvatar Actorとし、入力Componentから戦闘入力をASCへ配送します。

```text
AActionPlayerState候補
    +-- AbilitySystemComponent
    +-- CharacterAttributeSet

ABasePlayer / 派生Player Character
    +-- ASC Avatar
    +-- Input Components
    +-- Mesh / Collision / Camera
```

## 8. 武器

```text
AWeaponActor
    +-- Weapon Mesh
    +-- Hit Collision
    +-- WeaponDefinition

UWeaponDefinition / PrimaryDataAsset
    +-- WeaponType
    +-- AbilitySet
    +-- ComboDefinition
    +-- StaminaCost
    +-- StaggerResistance
    +-- PostureDamageMultiplier
    +-- DodgeDefinition
    +-- CounterWindowDuration
```

初期Vertical Sliceは剣のみ。斧・弓はPost-Vertical Slice Featureです。

## 9. 敵

```text
AEnemyCharacter候補
    +-- AbilitySystemComponent
    +-- AttributeSet
    +-- EnemyDefinition
    +-- CombatComponent
    +-- PerceptionContext

AEnemyAIController
    +-- Behavior Tree / Blackboard
```

HP0時にはAI、攻撃Ability、攻撃枠を終了して撃破状態へ遷移します。

## 10. ボスAI

```text
ABossAIController
    +-- StateTreeComponent
    +-- AttackEvaluator
    +-- ActionHistory
    +-- DebugPresenter

UEnemyAttackEvaluator
    +-- BuildContext
    +-- ScoreAttack
    +-- SelectAttack
    +-- RecordResult
```

Boss HP0時には評価・攻撃を停止し、Boss Defeated Eventをステージ進行へ通知します。

## 11. チェックポイント・死亡・進行

```text
ACheckpointActor
      ↓
Checkpoint管理
      +--> ActiveCheckpoint更新
      +--> Rest
      +--> Heal Refill
      +--> Enemy Respawn
      +--> Weapon Upgrade
      +--> Auto Save

Player Death
      ↓
DeathDrop生成
      ↓
ActiveCheckpoint Respawn

Boss Defeated
      ↓
Stage Clear
      ↓
Save / Clear Presentation
```

チェックポイント未有効化時のFallback Spawn、死亡からRespawnまでのタイミング、Boss SaveとStage Clear Saveの重複制御は未決事項として確定します。

### [戻る](../README.md#ドキュメント一覧)
