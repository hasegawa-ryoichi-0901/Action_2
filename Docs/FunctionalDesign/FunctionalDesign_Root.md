# 基本設計ドキュメント一覧

> `Docs/01_Requirements.md` の各要件を基本設計へ具体化する索引です。
> 初期Vertical Sliceは剣のみを対象とし、斧・弓はPost-Vertical Slice Featureとして扱います。

## 1. 作成方針

- 機能要件68件、非機能要件18件の合計86件を管理する。
- 要件、責務、状態、基本フロー、データ、受入条件、テスト、依存関係を要件IDで追跡する。
- Player Inputは`IPlayerInputComponent`を正とする。
- `1 Action = 1 ActorComponent`は前提としない。
- Gameplay Actionは親Issue、独立した実装単位は実装Issueとして管理する。
- 原則1実装Issue = 1 PRとする。
- 現在存在しない`IMovementDriver` / `UMovementAdapterComponent`を初期Vertical Sliceの前提としない。
- 数値調整・アセット最終選定は実装中に変更可能とし、Issue作成を妨げない。

## 2. プレイヤー（21件）

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-PLAYER-001` | 三人称移動 | Initial VS | [ThirdPersonMovement](Player/FR-PLAYER-001_ThirdPersonMovement.md) |
| `FR-PLAYER-002` | Gamepad / Keyboard-Mouse同等操作 | Initial VS | [EquivalentInputDevices](Player/FR-PLAYER-002_EquivalentInputDevices.md) |
| `FR-PLAYER-003` | Jump | Initial VS | [Jump](Player/FR-PLAYER-003_Jump.md) |
| `FR-PLAYER-004` | Air Attack | Initial VS | [AirAttack](Player/FR-PLAYER-004_AirAttack.md) |
| `FR-PLAYER-005` | Soft Lock | Initial VS | [SoftLock](Player/FR-PLAYER-005_SoftLock.md) |
| `FR-PLAYER-006` | Manual LockOn / Toggle解除 | Initial VS | [ManualLockOn](Player/FR-PLAYER-006_ManualLockOn.md) |
| `FR-PLAYER-007` | 専用左右入力でTarget Switch / 対象死亡時解除 | Initial VS | [SwitchLockTarget](Player/FR-PLAYER-007_SwitchLockTarget.md) |
| `FR-PLAYER-008` | Checkpointで武器変更 | Post-VS | [ChangeWeaponAtCheckpoint](Player/FR-PLAYER-008_ChangeWeaponAtCheckpoint.md) |
| `FR-PLAYER-009` | 戦闘中武器変更禁止 | Post-VS | [BlockWeaponChangeInCombat](Player/FR-PLAYER-009_BlockWeaponChangeInCombat.md) |
| `FR-PLAYER-010` | Light / Heavy Combo | Initial VS | [LightHeavyCombo](Player/FR-PLAYER-010_LightHeavyCombo.md) |
| `FR-PLAYER-011` | Stamina Cost | Initial VS | [StaminaCost](Player/FR-PLAYER-011_StaminaCost.md) |
| `FR-PLAYER-012` | Stamina不足時拒否 | Initial VS | [RejectInsufficientStamina](Player/FR-PLAYER-012_RejectInsufficientStamina.md) |
| `FR-PLAYER-013` | Exhausted | Initial VS | [ExhaustedState](Player/FR-PLAYER-013_ExhaustedState.md) |
| `FR-PLAYER-014` | Dodge Action内Perfect Dodge Result | Initial VS | [PerfectDodge](Player/FR-PLAYER-014_PerfectDodge.md) |
| `FR-PLAYER-015` | Perfect Dodge後Counter | Initial VS | [WeaponCounter](Player/FR-PLAYER-015_WeaponCounterAfterPerfectDodge.md) |
| `FR-PLAYER-016` | Sword Parry | Initial VS | [SwordParry](Player/FR-PLAYER-016_SwordParry.md) |
| `FR-PLAYER-017` | Axe Guard / Receive | Post-VS | [AxeGuardOrReceive](Player/FR-PLAYER-017_AxeGuardOrReceive.md) |
| `FR-PLAYER-018` | Healing Item | Initial VS | [LimitedHealingItem](Player/FR-PLAYER-018_LimitedHealingItem.md) |
| `FR-PLAYER-019` | Dodge Action / Normal Result | Initial VS | [NormalDodge](Player/FR-PLAYER-019_NormalDodge.md) |
| `FR-PLAYER-020` | Player HP / Death | Initial VS | [PlayerHealthAndDeath](Player/FR-PLAYER-020_PlayerHealthAndDeath.md) |
| `FR-PLAYER-021` | Camera / LockOn追従 | Initial VS | [ThirdPersonCameraControl](Player/FR-PLAYER-021_ThirdPersonCameraControl.md) |

## 3. 敵（10件）

`FR-ENEMY-001`～`FR-ENEMY-010`をInitial VSで管理します。撃破時報酬は`FR-STAGE-014`と連携します。

## 4. ボス（16件）

`FR-BOSS-001`～`FR-BOSS-013`、`FR-BOSS-015`、`FR-BOSS-016`はInitial VSです。`FR-BOSS-014`はBow追加後のPost-VSです。

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-BOSS-014` | Bow Gap Closer | Post-VS | [BowRangeGapCloser](Boss/FR-BOSS-014_BowRangeGapCloser.md) |
| `FR-BOSS-015` | HP0で撃破 | Initial VS | [DefeatAtZeroHealth](Boss/FR-BOSS-015_DefeatAtZeroHealth.md) |
| `FR-BOSS-016` | Gold + 初回固有収集Item報酬 | Initial VS | [FirstDefeatReward](Boss/FR-BOSS-016_FirstDefeatReward.md) |

## 5. ステージ・進行（14件）

`FR-STAGE-001`～`FR-STAGE-014`を管理します。`FR-STAGE-006`はPost-VS、`FR-STAGE-011`はCouldです。

特にDeathDropは`FR-STAGE-008`～`010`で、Upgrade MaterialとGoldを共通の回収対象Resourceとして扱います。Goldは死亡時70%をDeathDropへ格納し、30%を消失させます。

## 6. セーブ（7件）

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-SAVE-001` | 1 Save Slot | Initial VS | [SingleSaveSlot](Save/FR-SAVE-001_SingleSaveSlot.md) |
| `FR-SAVE-002` | Checkpoint Menu Open時Auto Save | Initial VS | [AutosaveAtCheckpoint](Save/FR-SAVE-002_AutosaveAtCheckpoint.md) |
| `FR-SAVE-003` | Checkpoint Manual Save | Initial VS | [ManualSaveAtCheckpoint](Save/FR-SAVE-003_ManualSaveAtCheckpoint.md) |
| `FR-SAVE-004` | Boss Reward後Auto Save | Initial VS | [AutosaveAfterBossDefeat](Save/FR-SAVE-004_AutosaveAfterBossDefeat.md) |
| `FR-SAVE-005` | DeathDrop生成 / 回収後Auto Save | Initial VS | [AutosaveDeathDropLifecycle](Save/FR-SAVE-005_AutosaveDeathDropLifecycle.md) |
| `FR-SAVE-006` | Settings変更時Save | Initial VS | [SaveSettingsOnChange](Save/FR-SAVE-006_SaveSettingsOnChange.md) |
| `FR-SAVE-007` | Steam Cloud | Post-VS | [SteamCloudAdditional](Save/FR-SAVE-007_SteamCloudAdditional.md) |

武器強化完了時とStage Clear時はAuto Save契機ではありません。

## 7. 非機能要件（18件）

Performance 6件、Maintainability 6件、Quality 6件を管理します。

Maintainabilityでは`IPlayerInputComponent`を入力基盤の正とし、Moverは将来検証対象とします。

## 8. Future Feature

斧・弓のFuture Feature IDと仕様は`Docs/01_Requirements.md`および`Docs/04_WeaponSystem.md`を正とします。初期Vertical SliceのIssue依存グラフへ含めません。

## 9. Issue作成前の確認条件

基本設計から実装Issueを作成する前に次を確認します。

1. ゲーム上の挙動が確定している。
2. Issue境界を変更する未解決事項が残っていない。
3. 依存する基本設計が存在する。
4. 既存実装との差分・重複を確認している。
5. 実装Issue単独で受入確認できる。

詳細なIssue階層ルールは`Docs/14_RepositoryOperation.md`を参照します。
