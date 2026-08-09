# 基本設計ドキュメント一覧

> `Docs/01_Requirements.md` の各要件を基本設計へ具体化する索引です。
> 初期Vertical Sliceは剣のみを対象とし、斧・弓はPost-Vertical Slice Featureとして扱います。

## 1. 作成方針

- 機能要件67件、非機能要件18件の合計85件を管理する。
- 要件、責務、状態、基本フロー、データ、受入条件、テスト、依存関係を要件IDで追跡する。
- 実装済みコードと設計が競合する場合は、意図を確認した上で現在採用しているアーキテクチャへ同期する。
- Player Inputは`IPlayerInputComponent`を正とする。
- 現在存在しない`IMovementDriver` / `UMovementAdapterComponent`を初期Vertical Sliceの前提としない。
- 未決事項は`Docs/15_OpenQuestions.md`で管理し、実装Issue開始前に必要な項目を確定する。

## 2. プレイヤー（21件）

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-PLAYER-001` | 三人称視点で移動できる | Initial VS | [ThirdPersonMovement](Player/FR-PLAYER-001_ThirdPersonMovement.md) |
| `FR-PLAYER-002` | Gamepad / Keyboard-Mouseで同等に操作できる | Initial VS | [EquivalentInputDevices](Player/FR-PLAYER-002_EquivalentInputDevices.md) |
| `FR-PLAYER-003` | ジャンプできる | Initial VS | [Jump](Player/FR-PLAYER-003_Jump.md) |
| `FR-PLAYER-004` | 空中攻撃を実行できる | Initial VS | [AirAttack](Player/FR-PLAYER-004_AirAttack.md) |
| `FR-PLAYER-005` | ソフトロックを使用できる | Initial VS | [SoftLock](Player/FR-PLAYER-005_SoftLock.md) |
| `FR-PLAYER-006` | 手動ロックオンを使用できる | Initial VS | [ManualLockOn](Player/FR-PLAYER-006_ManualLockOn.md) |
| `FR-PLAYER-007` | ロックオン対象を切り替えられる | Initial VS | [SwitchLockTarget](Player/FR-PLAYER-007_SwitchLockTarget.md) |
| `FR-PLAYER-008` | 剣・斧・弓をCheckpointで変更できる | Post-VS | [ChangeWeaponAtCheckpoint](Player/FR-PLAYER-008_ChangeWeaponAtCheckpoint.md) |
| `FR-PLAYER-009` | 戦闘中は武器変更できない | Post-VS | [BlockWeaponChangeInCombat](Player/FR-PLAYER-009_BlockWeaponChangeInCombat.md) |
| `FR-PLAYER-010` | 通常攻撃と強攻撃を組み合わせられる | Initial VS | [LightHeavyCombo](Player/FR-PLAYER-010_LightHeavyCombo.md) |
| `FR-PLAYER-011` | 攻撃と回避でStamina消費 | Initial VS | [StaminaCost](Player/FR-PLAYER-011_StaminaCost.md) |
| `FR-PLAYER-012` | Stamina不足時に行動不可 | Initial VS | [RejectInsufficientStamina](Player/FR-PLAYER-012_RejectInsufficientStamina.md) |
| `FR-PLAYER-013` | Stamina枯渇で息切れ | Initial VS | [ExhaustedState](Player/FR-PLAYER-013_ExhaustedState.md) |
| `FR-PLAYER-014` | ジャスト回避 | Initial VS | [PerfectDodge](Player/FR-PLAYER-014_PerfectDodge.md) |
| `FR-PLAYER-015` | ジャスト回避後の武器固有反撃 | Initial VS | [WeaponCounter](Player/FR-PLAYER-015_WeaponCounterAfterPerfectDodge.md) |
| `FR-PLAYER-016` | 剣でパリィ | Initial VS | [SwordParry](Player/FR-PLAYER-016_SwordParry.md) |
| `FR-PLAYER-017` | 斧でGuard / Receive | Post-VS | [AxeGuardOrReceive](Player/FR-PLAYER-017_AxeGuardOrReceive.md) |
| `FR-PLAYER-018` | 回数制限付き回復Item | Initial VS | [LimitedHealingItem](Player/FR-PLAYER-018_LimitedHealingItem.md) |
| `FR-PLAYER-019` | 通常回避 | Initial VS | [NormalDodge](Player/FR-PLAYER-019_NormalDodge.md) |
| `FR-PLAYER-020` | Player HP / Death | Initial VS | [PlayerHealthAndDeath](Player/FR-PLAYER-020_PlayerHealthAndDeath.md) |
| `FR-PLAYER-021` | 三人称Camera操作 | Initial VS | [ThirdPersonCameraControl](Player/FR-PLAYER-021_ThirdPersonCameraControl.md) |

## 3. 敵（10件）

既存`FR-ENEMY-001`～`FR-ENEMY-009`に加え、以下を追加します。

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-ENEMY-010` | HP0以下で撃破 | Initial VS | [DefeatAtZeroHealth](Enemy/FR-ENEMY-010_DefeatAtZeroHealth.md) |

既存設計は[Enemy](Enemy/)を参照してください。

## 4. ボス（15件）

既存`FR-BOSS-001`～`FR-BOSS-013`はInitial VS、`FR-BOSS-014`はBow追加後のPost-VSとします。

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-BOSS-014` | Bow遠距離維持への専用Gap Closer | Post-VS | [BowRangeGapCloser](Boss/FR-BOSS-014_BowRangeGapCloser.md) |
| `FR-BOSS-015` | HP0以下で撃破 | Initial VS | [DefeatAtZeroHealth](Boss/FR-BOSS-015_DefeatAtZeroHealth.md) |

`FR-BOSS-004`の装備武器評価は設計を保持するが、複数武器による差分評価はPost-VSで有効化します。

## 5. ステージ・進行（14件）

既存`FR-STAGE-001`～`FR-STAGE-011`に以下を追加します。`FR-STAGE-006`武器変更はPost-VS、`FR-STAGE-011`Boss IntroはCouldです。

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-STAGE-012` | 最後のCheckpointからRespawn | Initial VS | [RespawnAtLastCheckpoint](Stage/FR-STAGE-012_RespawnAtLastCheckpoint.md) |
| `FR-STAGE-013` | Boss撃破後Stage Clear | Initial VS | [StageClearAfterBossDefeat](Stage/FR-STAGE-013_StageClearAfterBossDefeat.md) |
| `FR-STAGE-014` | 戦闘報酬で強化素材獲得 | Initial VS | [AcquireUpgradeMaterials](Stage/FR-STAGE-014_AcquireUpgradeMaterials.md) |

## 6. セーブ（7件）

`FR-SAVE-001`～`FR-SAVE-006`はInitial VSで管理します。`FR-SAVE-007` Steam CloudはPost-VSです。既存設計は[Save](Save/)を参照してください。

## 7. 非機能要件（18件）

### Performance（6件）

`NFR-PERF-001`～`NFR-PERF-006`。既存設計は[Performance](Performance/)を参照してください。

### Maintainability（6件）

| ID | 要件 | 基本設計 |
|---|---|---|
| `NFR-MAINT-001` | Data Driven Gameplay Content | [DataDrivenGameplayContent](Maintainability/NFR-MAINT-001_DataDrivenGameplayContent.md) |
| `NFR-MAINT-002` | C++ / Blueprint責務分離 | [SeparateCppBlueprintResponsibilities](Maintainability/NFR-MAINT-002_SeparateCppBlueprintResponsibilities.md) |
| `NFR-MAINT-003` | `IPlayerInputComponent`による入力Component抽象化 | [PlayerInputComponentAbstraction](Maintainability/NFR-MAINT-003_PlayerInputComponentAbstraction.md) |
| `NFR-MAINT-004` | Mover固有依存をCombatへ漏らさない | [IsolateMoverDependency](Maintainability/NFR-MAINT-004_IsolateMoverDependency.md) |
| `NFR-MAINT-005` | Gameplay Tagで状態一元管理 | [CentralizeStateWithGameplayTags](Maintainability/NFR-MAINT-005_CentralizeStateWithGameplayTags.md) |
| `NFR-MAINT-006` | Tick使用制限 | [LimitTickUsage](Maintainability/NFR-MAINT-006_LimitTickUsage.md) |

### Quality（6件）

`NFR-QUALITY-001`～`NFR-QUALITY-006`。既存設計は[Quality](Quality/)を参照してください。

## 8. Future Feature

斧・弓のFuture Feature IDと仕様は`Docs/01_Requirements.md`および`Docs/04_WeaponSystem.md`を正とします。これらは初期Vertical SliceのIssue依存グラフへ含めません。

## 9. Issue化Gate

基本設計から実装Issueを作成する前に以下を満たします。

1. 対象要件の未決事項のうち実装をBlockする項目が解消済み。
2. 依存する基本設計が存在する。
3. 既存実装との差分が確認済み。
4. 1 Issueが単独で実装・テスト・レビュー可能。
5. 原則1 Issue = 1 PRとする。

現時点では`Docs/15_OpenQuestions.md`に初期Vertical Sliceの未確定仕様が残るため、該当機能のIssue作成は保留します。
