# 基本設計ドキュメント一覧

> `Docs/01_Requirements.md` の各要件を基本設計へ具体化する索引です。
> 初期Vertical Sliceは剣のみを対象とし、斧・弓はPost-Vertical Slice Featureとして扱います。

## 1. 作成方針

- 機能要件72件、非機能要件18件の合計90件を管理する。
- 各基本設計は「目的 / 確定仕様 / 基本フロー / 責務 / 状態 / 必要データ / UI・Animation / 異常系 / 受入条件 / 依存 / 未決事項」を必要な範囲だけ記載する。
- 全FRに`必要データ`欄を設け、DB / CSV / Data Asset等の保存方式とは分離する。
- Player Inputは`IPlayerInputComponent`を正とする。
- `1 Action = 1 ActorComponent`は前提とせず、Component粒度は仕様・Gameplay Tag・GAS・責務に応じて決定する。
- Component粒度はAction Issue作成・実装開始のBlockerにしない。
- Gameplay Actionは親Issue、独立した実装単位は実装Issueとして管理する。
- 原則1実装Issue = 1 PRとする。
- 現在存在しない`IMovementDriver` / `UMovementAdapterComponent`を初期Vertical Sliceの前提としない。
- 数値調整・アセット最終選定は実装中に変更可能とし、Issue作成を妨げない。
- 基本設計で確定した実装範囲・必要データ・UI/Animation・異常系・受入条件は関連Issueへ反映する。ただし設計書全文のコピーは行わない。

## 2. プレイヤー（23件）

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-PLAYER-001` | 三人称移動 | Initial VS | [ThirdPersonMovement](Player/FR-PLAYER-001_ThirdPersonMovement.md) |
| `FR-PLAYER-002` | Gamepad / Keyboard-Mouse同等操作 | Initial VS | [EquivalentInputDevices](Player/FR-PLAYER-002_EquivalentInputDevices.md) |
| `FR-PLAYER-003` | Jump | Initial VS | [Jump](Player/FR-PLAYER-003_Jump.md) |
| `FR-PLAYER-004` | Air Attack | Initial VS | [AirAttack](Player/FR-PLAYER-004_AirAttack.md) |
| `FR-PLAYER-005` | Soft Lock | Initial VS | [SoftLock](Player/FR-PLAYER-005_SoftLock.md) |
| `FR-PLAYER-006` | Manual LockOn / Toggle解除 | Initial VS | [ManualLockOn](Player/FR-PLAYER-006_ManualLockOn.md) |
| `FR-PLAYER-007` | Target Switch / 対象死亡時解除 | Initial VS | [SwitchLockTarget](Player/FR-PLAYER-007_SwitchLockTarget.md) |
| `FR-PLAYER-008` | Checkpointで武器変更 | Post-VS | [ChangeWeaponAtCheckpoint](Player/FR-PLAYER-008_ChangeWeaponAtCheckpoint.md) |
| `FR-PLAYER-009` | 戦闘中武器変更禁止 | Post-VS | [BlockWeaponChangeInCombat](Player/FR-PLAYER-009_BlockWeaponChangeInCombat.md) |
| `FR-PLAYER-010` | Light / Heavy Combo + Commitment / Cancel | Initial VS | [LightHeavyCombo](Player/FR-PLAYER-010_LightHeavyCombo.md) |
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
| `FR-PLAYER-022` | Down中EnemyへのFatal Attack | Initial VS | [FatalAttack](Player/FR-PLAYER-022_FatalAttack.md) |
| `FR-PLAYER-023` | Hit / Stagger / Down Reaction | Initial VS | [HitStaggerDown](Player/FR-PLAYER-023_HitStaggerDown.md) |

## 3. 敵（10件）

`FR-ENEMY-001`～`FR-ENEMY-010`をInitial VSで管理します。`FR-ENEMY-007/008`はEnemy Down Animation、Fatal Attack受付State / Collision、受付終了までを担当し、Player側実行は`FR-PLAYER-022`が担当します。

## 4. ボス（16件）

`FR-BOSS-001`～`FR-BOSS-013`、`FR-BOSS-015`、`FR-BOSS-016`はInitial VSです。`FR-BOSS-014`はBow追加後のPost-VSです。

Boss AIの各基本設計には、その要件で評価・選択した内容を確認できるDebug観点を含めます。Debugを別Gameplay Requirementへ分離せず、Boss AI設計の検証責務として管理します。

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-BOSS-014` | Bow Gap Closer | Post-VS | [BowRangeGapCloser](Boss/FR-BOSS-014_BowRangeGapCloser.md) |
| `FR-BOSS-015` | HP0で撃破 → Reward → Save → Clear Area → Ending → Title | Initial VS | [DefeatAtZeroHealth](Boss/FR-BOSS-015_DefeatAtZeroHealth.md) |
| `FR-BOSS-016` | Gold + 初回固有収集Item報酬 | Initial VS | [FirstDefeatReward](Boss/FR-BOSS-016_FirstDefeatReward.md) |

## 5. ステージ・進行（14件）

`FR-STAGE-001`～`FR-STAGE-014`を管理します。`FR-STAGE-006`はPost-VS、`FR-STAGE-011`はCouldです。

DeathDropは`FR-STAGE-008`～`010`で、Player Inventoryが所持するUpgrade MaterialとGoldを共通回収対象Resourceとして扱います。死亡時は**Upgrade Material 100% + Gold 100%**を1つのDeathDropへ移し、未回収状態で再死亡した場合は旧DeathDropと内容を完全消失させます。

Checkpointは次の順で処理します。

```text
Interaction
↓
ActiveCheckpoint更新
↓
Menu Open
↓
Rest処理確定
├ HP / Stamina回復
├ Healing Item補充
└ Normal Enemy Respawn
↓
Auto Save
```

## 6. セーブ（7件）

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-SAVE-001` | 1 Save Slot | Initial VS | [SingleSaveSlot](Save/FR-SAVE-001_SingleSaveSlot.md) |
| `FR-SAVE-002` | Checkpoint Rest確定後Auto Save | Initial VS | [AutosaveAtCheckpoint](Save/FR-SAVE-002_AutosaveAtCheckpoint.md) |
| `FR-SAVE-003` | Checkpoint Manual Save | Initial VS | [ManualSaveAtCheckpoint](Save/FR-SAVE-003_ManualSaveAtCheckpoint.md) |
| `FR-SAVE-004` | Boss Reward後Auto Save | Initial VS | [AutosaveAfterBossDefeat](Save/FR-SAVE-004_AutosaveAfterBossDefeat.md) |
| `FR-SAVE-005` | DeathDrop生成 / 回収後Auto Save + 未回収Drop復元 | Initial VS | [AutosaveDeathDropLifecycle](Save/FR-SAVE-005_AutosaveDeathDropLifecycle.md) |
| `FR-SAVE-006` | Settings変更時Save | Initial VS | [SaveSettingsOnChange](Save/FR-SAVE-006_SaveSettingsOnChange.md) |
| `FR-SAVE-007` | Steam Cloud | Post-VS | [SteamCloudAdditional](Save/FR-SAVE-007_SteamCloudAdditional.md) |

武器強化完了時とStage Clear時はAuto Save契機ではありません。DeathDropの座標・格納内容はSave / Load対象ですが、JSON Schemaは別Architecture Designで扱います。

## 7. UI / HUD（2件）

| ID | 要件 | 範囲 | 基本設計 |
|---|---|---|---|
| `FR-UI-001` | Boot / Intro / Title / Continue / Load / New Game / Config / Exit | Initial VS | [TitleAndStartFlow](UI/FR-UI-001_TitleAndStartFlow.md) |
| `FR-UI-002` | Gameplay HUD | Initial VS | [GameplayHUD](UI/FR-UI-002_GameplayHUD.md) |

## 8. 非機能要件（18件）

Performance 6件、Maintainability 6件、Quality 6件を管理します。

Maintainabilityでは`IPlayerInputComponent`を入力基盤の正とし、Component粒度は固定しません。Moverは将来検証対象です。

## 9. Data / Master Data方針

各FRの基本設計に`必要データ`を必須記載します。DB Schema、CSV形式、CSV Reader、JSON Save Schema等の具体Architectureは別ドキュメントで定義します。

RewardはReward件数に依存しないMaster構造とし、概念上は次の関係を持ちます。

```text
EnemyID(PK) -> RewardID
RewardID -> ItemID / Amount ... (0..N)
```

Gameplay側は「RewardIDから0..N件のReward Itemを取得する」契約へ依存し、Rewardが1件か2件かをコード構造へ埋め込みません。

## 10. Future Feature

斧・弓のFuture Feature IDと仕様は`Docs/01_Requirements.md`および`Docs/04_WeaponSystem.md`を正とします。初期Vertical SliceのIssue依存グラフへ含めません。

## 11. Issue作成・同期条件

1. ゲーム上の挙動が確定している。
2. Issue境界を変更する未解決事項が残っていない。
3. 依存する基本設計が存在する。
4. 既存実装との差分・重複を確認している。
5. 実装Issue単独で受入確認できる。
6. 基本設計で確定した実装範囲・必要データ・UI/Animation・異常系・受入条件がIssueへ反映されている。

詳細なIssue階層ルールは`Docs/14_RepositoryOperation.md`を参照します。
