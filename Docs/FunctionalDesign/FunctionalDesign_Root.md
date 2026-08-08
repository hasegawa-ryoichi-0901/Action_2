# 基本設計ドキュメント一覧

> `Docs/01_Requirements.md` の各要件を、`FunctionalDesign_Template.md` の構成で1要件1ファイルへ具体化した索引です。
> 設計状態は初版のためすべて `Draft` です。TBDは各ファイルの「19. 未決事項」で追跡します。

## 1. 作成方針

- 機能要件59件、非機能要件18件の合計77件を収録する。
- 元要件、責務、状態、基本フロー、データ、受入条件、テスト、依存関係を要件ID単位で追跡する。
- Boss登場演出とSteam Cloudは要件を保持するが、Vertical Slice対象外の追加要件として扱う。
- 内部アルゴリズム、最終調整値、Asset選定は詳細設計・実装Issueで確定する。

## 2. トレーサビリティ

### 2.1 プレイヤー（18件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `FR-PLAYER-001` | 三人称視点で移動できる | `Must` | [FR-PLAYER-001_ThirdPersonMovement.md](Player/FR-PLAYER-001_ThirdPersonMovement.md) |
| `FR-PLAYER-002` | ゲームパッドとキーボード・マウスで同等に操作できる | `Must` | [FR-PLAYER-002_EquivalentInputDevices.md](Player/FR-PLAYER-002_EquivalentInputDevices.md) |
| `FR-PLAYER-003` | ジャンプできる | `Must` | [FR-PLAYER-003_Jump.md](Player/FR-PLAYER-003_Jump.md) |
| `FR-PLAYER-004` | 空中攻撃を実行できる | `Must` | [FR-PLAYER-004_AirAttack.md](Player/FR-PLAYER-004_AirAttack.md) |
| `FR-PLAYER-005` | ソフトロックを使用できる | `Must` | [FR-PLAYER-005_SoftLock.md](Player/FR-PLAYER-005_SoftLock.md) |
| `FR-PLAYER-006` | 手動ロックオンを使用できる | `Must` | [FR-PLAYER-006_ManualLockOn.md](Player/FR-PLAYER-006_ManualLockOn.md) |
| `FR-PLAYER-007` | ロックオン対象を切り替えられる | `Must` | [FR-PLAYER-007_SwitchLockTarget.md](Player/FR-PLAYER-007_SwitchLockTarget.md) |
| `FR-PLAYER-008` | 剣、斧、弓をチェックポイントで変更できる | `Must` | [FR-PLAYER-008_ChangeWeaponAtCheckpoint.md](Player/FR-PLAYER-008_ChangeWeaponAtCheckpoint.md) |
| `FR-PLAYER-009` | 戦闘中は武器を変更できない | `Must` | [FR-PLAYER-009_BlockWeaponChangeInCombat.md](Player/FR-PLAYER-009_BlockWeaponChangeInCombat.md) |
| `FR-PLAYER-010` | 通常攻撃と強攻撃を組み合わせられる | `Must` | [FR-PLAYER-010_LightHeavyCombo.md](Player/FR-PLAYER-010_LightHeavyCombo.md) |
| `FR-PLAYER-011` | 攻撃と回避でスタミナを消費する | `Must` | [FR-PLAYER-011_StaminaCost.md](Player/FR-PLAYER-011_StaminaCost.md) |
| `FR-PLAYER-012` | スタミナ不足時は対象行動を実行できない | `Must` | [FR-PLAYER-012_RejectInsufficientStamina.md](Player/FR-PLAYER-012_RejectInsufficientStamina.md) |
| `FR-PLAYER-013` | スタミナ枯渇時に息切れ状態となる | `Must` | [FR-PLAYER-013_ExhaustedState.md](Player/FR-PLAYER-013_ExhaustedState.md) |
| `FR-PLAYER-014` | ジャスト回避を実行できる | `Must` | [FR-PLAYER-014_PerfectDodge.md](Player/FR-PLAYER-014_PerfectDodge.md) |
| `FR-PLAYER-015` | ジャスト回避後に武器固有反撃を実行できる | `Must` | [FR-PLAYER-015_WeaponCounterAfterPerfectDodge.md](Player/FR-PLAYER-015_WeaponCounterAfterPerfectDodge.md) |
| `FR-PLAYER-016` | 剣でパリィできる | `Must` | [FR-PLAYER-016_SwordParry.md](Player/FR-PLAYER-016_SwordParry.md) |
| `FR-PLAYER-017` | 斧でガードまたは受け止めを実行できる | `Must` | [FR-PLAYER-017_AxeGuardOrReceive.md](Player/FR-PLAYER-017_AxeGuardOrReceive.md) |
| `FR-PLAYER-018` | 回数制限付き回復アイテムを使用できる | `Must` | [FR-PLAYER-018_LimitedHealingItem.md](Player/FR-PLAYER-018_LimitedHealingItem.md) |

### 2.2 敵（9件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `FR-ENEMY-001` | 近接通常敵を実装する | `Must` | [FR-ENEMY-001_MeleeNormalEnemy.md](Enemy/FR-ENEMY-001_MeleeNormalEnemy.md) |
| `FR-ENEMY-002` | 遠距離通常敵を実装する | `Must` | [FR-ENEMY-002_RangedNormalEnemy.md](Enemy/FR-ENEMY-002_RangedNormalEnemy.md) |
| `FR-ENEMY-003` | 通常戦で複数の敵が同時に行動する | `Must` | [FR-ENEMY-003_ConcurrentNormalEnemies.md](Enemy/FR-ENEMY-003_ConcurrentNormalEnemies.md) |
| `FR-ENEMY-004` | 同時に近接攻撃する敵を最大2体に制限する | `Must` | [FR-ENEMY-004_MaxTwoMeleeAttackers.md](Enemy/FR-ENEMY-004_MaxTwoMeleeAttackers.md) |
| `FR-ENEMY-005` | 近接攻撃枠と遠距離攻撃枠を分離する | `Must` | [FR-ENEMY-005_SeparateMeleeRangedSlots.md](Enemy/FR-ENEMY-005_SeparateMeleeRangedSlots.md) |
| `FR-ENEMY-006` | HPと体勢値を持つ | `Must` | [FR-ENEMY-006_HealthAndPosture.md](Enemy/FR-ENEMY-006_HealthAndPosture.md) |
| `FR-ENEMY-007` | 体勢値が0になるとダウンする | `Must` | [FR-ENEMY-007_DownAtZeroPosture.md](Enemy/FR-ENEMY-007_DownAtZeroPosture.md) |
| `FR-ENEMY-008` | ダウン時に専用致命攻撃を受ける | `Must` | [FR-ENEMY-008_FatalAttackOnDownedEnemy.md](Enemy/FR-ENEMY-008_FatalAttackOnDownedEnemy.md) |
| `FR-ENEMY-009` | 敵ごとに体勢値の回復設定を変更できる | `Must` | [FR-ENEMY-009_PerEnemyPostureRecovery.md](Enemy/FR-ENEMY-009_PerEnemyPostureRecovery.md) |

### 2.3 ボス（14件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `FR-BOSS-001` | 1対1で戦う | `Must` | [FR-BOSS-001_OneOnOneBossBattle.md](Boss/FR-BOSS-001_OneOnOneBossBattle.md) |
| `FR-BOSS-002` | HP50%以下で第2フェーズへ移行する | `Must` | [FR-BOSS-002_PhaseTwoAtHalfHealth.md](Boss/FR-BOSS-002_PhaseTwoAtHalfHealth.md) |
| `FR-BOSS-003` | プレイヤーとの距離を評価する | `Must` | [FR-BOSS-003_EvaluatePlayerDistance.md](Boss/FR-BOSS-003_EvaluatePlayerDistance.md) |
| `FR-BOSS-004` | プレイヤーの装備武器を評価する | `Must` | [FR-BOSS-004_EvaluateEquippedWeapon.md](Boss/FR-BOSS-004_EvaluateEquippedWeapon.md) |
| `FR-BOSS-005` | プレイヤーの回復状態を評価する | `Must` | [FR-BOSS-005_EvaluateHealingState.md](Boss/FR-BOSS-005_EvaluateHealingState.md) |
| `FR-BOSS-006` | プレイヤーの残りスタミナを評価する | `Must` | [FR-BOSS-006_EvaluateRemainingStamina.md](Boss/FR-BOSS-006_EvaluateRemainingStamina.md) |
| `FR-BOSS-007` | 直近数秒の行動と戦闘全体の傾向を評価する | `Must` | [FR-BOSS-007_EvaluateActionHistory.md](Boss/FR-BOSS-007_EvaluateActionHistory.md) |
| `FR-BOSS-008` | 状況に応じて攻撃候補の評価値を変更する | `Must` | [FR-BOSS-008_ScoreAttackCandidates.md](Boss/FR-BOSS-008_ScoreAttackCandidates.md) |
| `FR-BOSS-009` | 状況に応じて接近・離脱頻度を変更する | `Must` | [FR-BOSS-009_AdaptApproachRetreatFrequency.md](Boss/FR-BOSS-009_AdaptApproachRetreatFrequency.md) |
| `FR-BOSS-010` | 状況に応じて遠距離攻撃頻度を変更する | `Must` | [FR-BOSS-010_AdaptRangedAttackFrequency.md](Boss/FR-BOSS-010_AdaptRangedAttackFrequency.md) |
| `FR-BOSS-011` | 攻撃コンボを分岐できる | `Must` | [FR-BOSS-011_BranchAttackCombo.md](Boss/FR-BOSS-011_BranchAttackCombo.md) |
| `FR-BOSS-012` | 特定攻撃後に大きな隙を持つ | `Must` | [FR-BOSS-012_LargeRecoveryAfterSpecificAttack.md](Boss/FR-BOSS-012_LargeRecoveryAfterSpecificAttack.md) |
| `FR-BOSS-013` | ジャスト回避またはパリィ成功時に反撃可能な隙を作る | `Must` | [FR-BOSS-013_CounterWindowAfterDefense.md](Boss/FR-BOSS-013_CounterWindowAfterDefense.md) |
| `FR-BOSS-014` | 弓で距離を取られた場合に専用接近行動を選択できる | `Must` | [FR-BOSS-014_BowRangeGapCloser.md](Boss/FR-BOSS-014_BowRangeGapCloser.md) |

### 2.4 ステージ（11件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `FR-STAGE-001` | 導入テキストを表示する | `Must` | [FR-STAGE-001_IntroText.md](Stage/FR-STAGE-001_IntroText.md) |
| `FR-STAGE-002` | チュートリアルを実施する | `Must` | [FR-STAGE-002_Tutorial.md](Stage/FR-STAGE-002_Tutorial.md) |
| `FR-STAGE-003` | チェックポイントを使用できる | `Must` | [FR-STAGE-003_UseCheckpoint.md](Stage/FR-STAGE-003_UseCheckpoint.md) |
| `FR-STAGE-004` | チェックポイント使用時に通常敵が復活する | `Must` | [FR-STAGE-004_RespawnNormalEnemiesAtCheckpoint.md](Stage/FR-STAGE-004_RespawnNormalEnemiesAtCheckpoint.md) |
| `FR-STAGE-005` | チェックポイントで回復アイテムを補充する | `Must` | [FR-STAGE-005_RefillHealingAtCheckpoint.md](Stage/FR-STAGE-005_RefillHealingAtCheckpoint.md) |
| `FR-STAGE-006` | チェックポイントで武器を変更する | `Must` | [FR-STAGE-006_WeaponMenuAtCheckpoint.md](Stage/FR-STAGE-006_WeaponMenuAtCheckpoint.md) |
| `FR-STAGE-007` | チェックポイントで武器を強化する | `Must` | [FR-STAGE-007_UpgradeWeaponAtCheckpoint.md](Stage/FR-STAGE-007_UpgradeWeaponAtCheckpoint.md) |
| `FR-STAGE-008` | 死亡時に強化素材を落とす | `Must` | [FR-STAGE-008_DropMaterialsOnDeath.md](Stage/FR-STAGE-008_DropMaterialsOnDeath.md) |
| `FR-STAGE-009` | 落とした素材を回収できる | `Must` | [FR-STAGE-009_RecoverDroppedMaterials.md](Stage/FR-STAGE-009_RecoverDroppedMaterials.md) |
| `FR-STAGE-010` | 回収前に再死亡すると以前の素材が消滅する | `Must` | [FR-STAGE-010_ReplacePreviousDeathDrop.md](Stage/FR-STAGE-010_ReplacePreviousDeathDrop.md) |
| `FR-STAGE-011` | ボス登場演出は工数に余裕がある場合に実装する | `Could` | [FR-STAGE-011_OptionalBossIntro.md](Stage/FR-STAGE-011_OptionalBossIntro.md) |

### 2.5 セーブ（7件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `FR-SAVE-001` | セーブスロットは1つ | `Must` | [FR-SAVE-001_SingleSaveSlot.md](Save/FR-SAVE-001_SingleSaveSlot.md) |
| `FR-SAVE-002` | チェックポイント使用時にオートセーブする | `Must` | [FR-SAVE-002_AutosaveAtCheckpoint.md](Save/FR-SAVE-002_AutosaveAtCheckpoint.md) |
| `FR-SAVE-003` | 武器強化時にオートセーブする | `Must` | [FR-SAVE-003_AutosaveAfterWeaponUpgrade.md](Save/FR-SAVE-003_AutosaveAfterWeaponUpgrade.md) |
| `FR-SAVE-004` | ボス撃破時にオートセーブする | `Must` | [FR-SAVE-004_AutosaveAfterBossDefeat.md](Save/FR-SAVE-004_AutosaveAfterBossDefeat.md) |
| `FR-SAVE-005` | ステージクリア時にオートセーブする | `Must` | [FR-SAVE-005_AutosaveAtStageClear.md](Save/FR-SAVE-005_AutosaveAtStageClear.md) |
| `FR-SAVE-006` | 設定変更時に設定データを保存する | `Must` | [FR-SAVE-006_SaveSettingsOnChange.md](Save/FR-SAVE-006_SaveSettingsOnChange.md) |
| `FR-SAVE-007` | Steam CloudはSteam公開版の追加要件とする | `Could` | [FR-SAVE-007_SteamCloudAdditional.md](Save/FR-SAVE-007_SteamCloudAdditional.md) |

### 2.6 パフォーマンス（6件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `NFR-PERF-001` | 1920x1080を基準解像度候補とする | `Should` | [NFR-PERF-001_BaselineResolution1080p.md](Performance/NFR-PERF-001_BaselineResolution1080p.md) |
| `NFR-PERF-002` | 60fpsを最低保証目標とする | `Must` | [NFR-PERF-002_Minimum60Fps.md](Performance/NFR-PERF-002_Minimum60Fps.md) |
| `NFR-PERF-003` | 120fpsを挑戦目標とする | `Could` | [NFR-PERF-003_Challenge120Fps.md](Performance/NFR-PERF-003_Challenge120Fps.md) |
| `NFR-PERF-004` | RTX 3060搭載開発環境で継続的に計測する | `Must` | [NFR-PERF-004_MeasureOnRtx3060.md](Performance/NFR-PERF-004_MeasureOnRtx3060.md) |
| `NFR-PERF-005` | 平均fpsだけでなくフレーム時間を確認する | `Must` | [NFR-PERF-005_InspectFrameTime.md](Performance/NFR-PERF-005_InspectFrameTime.md) |
| `NFR-PERF-006` | Game Thread、Render Thread、GPUのボトルネックを分離する | `Must` | [NFR-PERF-006_SeparateBottlenecks.md](Performance/NFR-PERF-006_SeparateBottlenecks.md) |

### 2.7 保守性（6件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `NFR-MAINT-001` | 武器、攻撃、敵、Abilityをデータ駆動で追加できる | `Must` | [NFR-MAINT-001_DataDrivenGameplayContent.md](Maintainability/NFR-MAINT-001_DataDrivenGameplayContent.md) |
| `NFR-MAINT-002` | C++とBlueprintの責務を分離する | `Must` | [NFR-MAINT-002_SeparateCppBlueprintResponsibilities.md](Maintainability/NFR-MAINT-002_SeparateCppBlueprintResponsibilities.md) |
| `NFR-MAINT-003` | キャラクター移動実装をインターフェースで抽象化する | `Must` | [NFR-MAINT-003_MovementInterfaceAbstraction.md](Maintainability/NFR-MAINT-003_MovementInterfaceAbstraction.md) |
| `NFR-MAINT-004` | Moverを不採用にしても戦闘システムへ影響させない | `Must` | [NFR-MAINT-004_IsolateMoverDependency.md](Maintainability/NFR-MAINT-004_IsolateMoverDependency.md) |
| `NFR-MAINT-005` | Gameplay Tagで状態を一元管理する | `Must` | [NFR-MAINT-005_CentralizeStateWithGameplayTags.md](Maintainability/NFR-MAINT-005_CentralizeStateWithGameplayTags.md) |
| `NFR-MAINT-006` | Tickの使用を必要なクラスに限定する | `Must` | [NFR-MAINT-006_LimitTickUsage.md](Maintainability/NFR-MAINT-006_LimitTickUsage.md) |

### 2.8 品質（6件）

| 要件ID | 元要件 | 優先度 | 基本設計 |
|---|---|---|---|
| `NFR-QUALITY-001` | 進行不能バグを0件にする | `Must` | [NFR-QUALITY-001_ZeroProgressionBlockers.md](Quality/NFR-QUALITY-001_ZeroProgressionBlockers.md) |
| `NFR-QUALITY-002` | 既知のクラッシュを0件にする | `Must` | [NFR-QUALITY-002_ZeroKnownCrashes.md](Quality/NFR-QUALITY-002_ZeroKnownCrashes.md) |
| `NFR-QUALITY-003` | ゲームパッドとキーボード・マウスの両方でクリア確認を行う | `Must` | [NFR-QUALITY-003_ClearWithBothInputDevices.md](Quality/NFR-QUALITY-003_ClearWithBothInputDevices.md) |
| `NFR-QUALITY-004` | セーブ破損時の挙動を確認する | `Must` | [NFR-QUALITY-004_CorruptSaveBehavior.md](Quality/NFR-QUALITY-004_CorruptSaveBehavior.md) |
| `NFR-QUALITY-005` | 長時間プレイでメモリ増加を確認する | `Must` | [NFR-QUALITY-005_LongPlayMemoryGrowth.md](Quality/NFR-QUALITY-005_LongPlayMemoryGrowth.md) |
| `NFR-QUALITY-006` | Shippingビルドで最終確認を行う | `Must` | [NFR-QUALITY-006_FinalShippingVerification.md](Quality/NFR-QUALITY-006_FinalShippingVerification.md) |

## 11. 関連資料

- [基本設計テンプレート](FunctionalDesign_Template.md)
- [要件定義](../01_Requirements.md)
- [ゲームデザイン](../02_GameDesign.md)
- [戦闘システム](../03_CombatSystem.md)
- [武器システム](../04_WeaponSystem.md)
- [Gameplay Ability System設計](../05_GASDesign.md)
- [敵AI設計](../06_EnemyAI.md)
- [クラス設計](../07_ClassDesign.md)
- [データ設計](../08_DataDesign.md)
- [セーブ・チェックポイント・死亡](../09_SaveCheckpointDeath.md)
- [パフォーマンス要件](../10_PerformanceRequirements.md)
- [テスト計画](../11_TestPlan.md)
- [未確定事項](../15_OpenQuestions.md)

## 12. 変更履歴

| 日付 | 変更者 | 内容 |
|---|---|---|
| `2026-08-07` | `hasegawa` | 要件77件の基本設計とトレーサビリティ索引を初版作成 |
