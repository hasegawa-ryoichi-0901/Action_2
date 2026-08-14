# 01. 要件定義

本ドキュメントは、Action_2で実装する機能要件・非機能要件と、初期プレイアブル版以降に追加するFuture Featureを定義します。

初期プレイアブル版は**剣のみ**を使用して、起動・タイトル・チュートリアル・移動・戦闘・通常敵・ボス・チェックポイント・死亡・セーブ・ステージクリアまでの一連のゲームループを完成させます。斧と弓は4～6カ月目の追加目標とします。

> 各FR / NFRの要件IDから、対応する基本設計ファイルへ直接移動できます。

## 1. 機能要件

### 1.1 プレイヤー

<a id="fr-player-001"></a>
- [`FR-PLAYER-001`](./FunctionalDesign/Player/FR-PLAYER-001_ThirdPersonMovement.md) 三人称視点で移動できる
<a id="fr-player-002"></a>
- [`FR-PLAYER-002`](./FunctionalDesign/Player/FR-PLAYER-002_EquivalentInputDevices.md) ゲームパッドとキーボード・マウスで同等に操作できる
<a id="fr-player-003"></a>
- [`FR-PLAYER-003`](./FunctionalDesign/Player/FR-PLAYER-003_Jump.md) ジャンプできる
<a id="fr-player-004"></a>
- [`FR-PLAYER-004`](./FunctionalDesign/Player/FR-PLAYER-004_AirAttack.md) 空中攻撃を実行できる
<a id="fr-player-005"></a>
- [`FR-PLAYER-005`](./FunctionalDesign/Player/FR-PLAYER-005_SoftLock.md) ソフトロックを使用できる
<a id="fr-player-006"></a>
- [`FR-PLAYER-006`](./FunctionalDesign/Player/FR-PLAYER-006_ManualLockOn.md) 手動ロックオンを使用でき、同じロックオン入力でもう一度押すと解除できる
<a id="fr-player-007"></a>
- [`FR-PLAYER-007`](./FunctionalDesign/Player/FR-PLAYER-007_SwitchLockTarget.md) ロックオン中に専用の左右入力で対象を切り替えられ、対象が死亡した場合は自動解除する
<a id="fr-player-008"></a>
- [`FR-PLAYER-008`](./FunctionalDesign/Player/FR-PLAYER-008_ChangeWeaponAtCheckpoint.md) 剣、斧、弓をチェックポイントで変更できる `[Post-VS]`
<a id="fr-player-009"></a>
- [`FR-PLAYER-009`](./FunctionalDesign/Player/FR-PLAYER-009_BlockWeaponChangeInCombat.md) 戦闘中は武器を変更できない `[Post-VS]`
<a id="fr-player-010"></a>
- [`FR-PLAYER-010`](./FunctionalDesign/Player/FR-PLAYER-010_LightHeavyCombo.md) 通常攻撃と強攻撃を組み合わせられ、Light / HeavyそれぞれがStartup / Commitment / Active / Recoveryと許可されたCancel Windowを持つ
<a id="fr-player-011"></a>
- [`FR-PLAYER-011`](./FunctionalDesign/Player/FR-PLAYER-011_StaminaCost.md) 攻撃と回避でスタミナを消費する
<a id="fr-player-012"></a>
- [`FR-PLAYER-012`](./FunctionalDesign/Player/FR-PLAYER-012_RejectInsufficientStamina.md) スタミナ不足時は対象行動を実行できない
<a id="fr-player-013"></a>
- [`FR-PLAYER-013`](./FunctionalDesign/Player/FR-PLAYER-013_ExhaustedState.md) スタミナ枯渇時に息切れ状態となる
<a id="fr-player-014"></a>
- [`FR-PLAYER-014`](./FunctionalDesign/Player/FR-PLAYER-014_PerfectDodge.md) 回避中、敵攻撃とジャスト回避判定時間が重なった場合にジャスト回避が成立する
<a id="fr-player-015"></a>
- [`FR-PLAYER-015`](./FunctionalDesign/Player/FR-PLAYER-015_WeaponCounterAfterPerfectDodge.md) ジャスト回避後に武器固有反撃を実行できる
<a id="fr-player-016"></a>
- [`FR-PLAYER-016`](./FunctionalDesign/Player/FR-PLAYER-016_SwordParry.md) 剣でパリィできる
<a id="fr-player-017"></a>
- [`FR-PLAYER-017`](./FunctionalDesign/Player/FR-PLAYER-017_AxeGuardOrReceive.md) 斧でガードまたは受け止めを実行できる `[Post-VS]`
<a id="fr-player-018"></a>
- [`FR-PLAYER-018`](./FunctionalDesign/Player/FR-PLAYER-018_LimitedHealingItem.md) 回数制限付き回復アイテムを使用できる
<a id="fr-player-019"></a>
- [`FR-PLAYER-019`](./FunctionalDesign/Player/FR-PLAYER-019_NormalDodge.md) 通常回避を実行できる
<a id="fr-player-020"></a>
- [`FR-PLAYER-020`](./FunctionalDesign/Player/FR-PLAYER-020_PlayerHealthAndDeath.md) プレイヤーはHPを持ち、HPが0以下になると死亡する
<a id="fr-player-021"></a>
- [`FR-PLAYER-021`](./FunctionalDesign/Player/FR-PLAYER-021_ThirdPersonCameraControl.md) 三人称カメラを操作でき、ロックオン中は通常Camera Lookを無効化して対象へ追従する
<a id="fr-player-022"></a>
- [`FR-PLAYER-022`](./FunctionalDesign/Player/FR-PLAYER-022_FatalAttack.md) Down中の敵のFatal Attack受付範囲内で攻撃入力した場合、PlayerをFatal Attack基準座標へ位置合わせし、`UGA_FatalAttack`とMontageを実行してFatal Damageを与えられる
<a id="fr-player-023"></a>
- [`FR-PLAYER-023`](./FunctionalDesign/Player/FR-PLAYER-023_HitStaggerDown.md) Playerは被弾時にHit / Stagger / Downの3段階Reactionを持ち、通常敵・Bossの攻撃データが持つ内部蓄積値を加算してReactionを判定する。蓄積値はPlayer HUDへ表示しない

### 1.2 敵

<a id="fr-enemy-001"></a>
- [`FR-ENEMY-001`](./FunctionalDesign/Enemy/FR-ENEMY-001_MeleeNormalEnemy.md) 近接通常敵を実装する
<a id="fr-enemy-002"></a>
- [`FR-ENEMY-002`](./FunctionalDesign/Enemy/FR-ENEMY-002_RangedNormalEnemy.md) 遠距離通常敵を実装する
<a id="fr-enemy-003"></a>
- [`FR-ENEMY-003`](./FunctionalDesign/Enemy/FR-ENEMY-003_ConcurrentNormalEnemies.md) 通常戦で複数の敵が同時に行動する
<a id="fr-enemy-004"></a>
- [`FR-ENEMY-004`](./FunctionalDesign/Enemy/FR-ENEMY-004_MaxTwoMeleeAttackers.md) 同時に近接攻撃する敵を最大2体に制限する
<a id="fr-enemy-005"></a>
- [`FR-ENEMY-005`](./FunctionalDesign/Enemy/FR-ENEMY-005_SeparateMeleeRangedSlots.md) 近接攻撃枠と遠距離攻撃枠を分離する
<a id="fr-enemy-006"></a>
- [`FR-ENEMY-006`](./FunctionalDesign/Enemy/FR-ENEMY-006_HealthAndPosture.md) HPと体勢値を持つ
<a id="fr-enemy-007"></a>
- [`FR-ENEMY-007`](./FunctionalDesign/Enemy/FR-ENEMY-007_DownAtZeroPosture.md) 体勢値が0になるとDown状態へ遷移し、Down Animationを再生する
<a id="fr-enemy-008"></a>
- [`FR-ENEMY-008`](./FunctionalDesign/Enemy/FR-ENEMY-008_FatalAttackOnDownedEnemy.md) Down中のみFatal Attack受付可能状態とFatal Attack受付Collisionを有効化し、Down終了・Defeat・Fatal Attack成立時に受付を無効化する
<a id="fr-enemy-009"></a>
- [`FR-ENEMY-009`](./FunctionalDesign/Enemy/FR-ENEMY-009_PerEnemyPostureRecovery.md) 敵ごとに体勢値の回復設定を変更できる
<a id="fr-enemy-010"></a>
- [`FR-ENEMY-010`](./FunctionalDesign/Enemy/FR-ENEMY-010_DefeatAtZeroHealth.md) HPが0以下になると撃破状態へ遷移する

### 1.3 ボス

<a id="fr-boss-001"></a>
- [`FR-BOSS-001`](./FunctionalDesign/Boss/FR-BOSS-001_OneOnOneBossBattle.md) 1対1で戦う
<a id="fr-boss-002"></a>
- [`FR-BOSS-002`](./FunctionalDesign/Boss/FR-BOSS-002_PhaseTwoAtHalfHealth.md) HP50%以下で第2フェーズへ移行する
<a id="fr-boss-003"></a>
- [`FR-BOSS-003`](./FunctionalDesign/Boss/FR-BOSS-003_EvaluatePlayerDistance.md) プレイヤーとの距離を評価する
<a id="fr-boss-004"></a>
- [`FR-BOSS-004`](./FunctionalDesign/Boss/FR-BOSS-004_EvaluateEquippedWeapon.md) プレイヤーの装備武器を評価する `[Post-VS]`
<a id="fr-boss-005"></a>
- [`FR-BOSS-005`](./FunctionalDesign/Boss/FR-BOSS-005_EvaluateHealingState.md) プレイヤーの回復状態を評価する
<a id="fr-boss-006"></a>
- [`FR-BOSS-006`](./FunctionalDesign/Boss/FR-BOSS-006_EvaluateRemainingStamina.md) プレイヤーの残りスタミナを評価する
<a id="fr-boss-007"></a>
- [`FR-BOSS-007`](./FunctionalDesign/Boss/FR-BOSS-007_EvaluateActionHistory.md) 直近数秒の行動と戦闘全体の傾向を評価する
<a id="fr-boss-008"></a>
- [`FR-BOSS-008`](./FunctionalDesign/Boss/FR-BOSS-008_ScoreAttackCandidates.md) 状況に応じて攻撃候補の評価値を変更する
<a id="fr-boss-009"></a>
- [`FR-BOSS-009`](./FunctionalDesign/Boss/FR-BOSS-009_AdaptApproachRetreatFrequency.md) 状況に応じて接近・離脱頻度を変更する
<a id="fr-boss-010"></a>
- [`FR-BOSS-010`](./FunctionalDesign/Boss/FR-BOSS-010_AdaptRangedAttackFrequency.md) 状況に応じて遠距離攻撃頻度を変更する
<a id="fr-boss-011"></a>
- [`FR-BOSS-011`](./FunctionalDesign/Boss/FR-BOSS-011_BranchAttackCombo.md) 攻撃コンボを分岐できる
<a id="fr-boss-012"></a>
- [`FR-BOSS-012`](./FunctionalDesign/Boss/FR-BOSS-012_LargeRecoveryAfterSpecificAttack.md) 特定攻撃後に大きな隙を持つ
<a id="fr-boss-013"></a>
- [`FR-BOSS-013`](./FunctionalDesign/Boss/FR-BOSS-013_CounterWindowAfterDefense.md) ジャスト回避またはパリィ成功時に反撃可能な隙を作る
<a id="fr-boss-014"></a>
- [`FR-BOSS-014`](./FunctionalDesign/Boss/FR-BOSS-014_BowRangeGapCloser.md) 弓で距離を取られた場合に専用接近行動を選択できる `[Post-VS]`
<a id="fr-boss-015"></a>
- [`FR-BOSS-015`](./FunctionalDesign/Boss/FR-BOSS-015_DefeatAtZeroHealth.md) HPが0以下になると撃破状態へ遷移する。撃破後はGold付与、初回固有Item付与、Reward確定、Auto Save、Clear Area進行、Clear Trigger、Ending、Titleの順で進行する
<a id="fr-boss-016"></a>
- [`FR-BOSS-016`](./FunctionalDesign/Boss/FR-BOSS-016_FirstDefeatReward.md) ボス撃破時にGoldを獲得し、初回討伐時のみ固有収集アイテムをPlayer Inventoryへ直接獲得できる

### 1.4 ステージ・進行

<a id="fr-stage-001"></a>
- [`FR-STAGE-001`](./FunctionalDesign/Stage/FR-STAGE-001_IntroText.md) New Game開始時にTutorial Textを表示し、その後Tutorialへ遷移する
<a id="fr-stage-002"></a>
- [`FR-STAGE-002`](./FunctionalDesign/Stage/FR-STAGE-002_Tutorial.md) チュートリアルを実施する
<a id="fr-stage-003"></a>
- [`FR-STAGE-003`](./FunctionalDesign/Stage/FR-STAGE-003_UseCheckpoint.md) チェックポイントをInteractionし、ActiveCheckpoint更新後にMenuを開き、Rest処理を確定できる
<a id="fr-stage-004"></a>
- [`FR-STAGE-004`](./FunctionalDesign/Stage/FR-STAGE-004_RespawnNormalEnemiesAtCheckpoint.md) Checkpoint Rest時に通常敵が復活する
<a id="fr-stage-005"></a>
- [`FR-STAGE-005`](./FunctionalDesign/Stage/FR-STAGE-005_RefillHealingAtCheckpoint.md) Checkpoint Rest時にHP / Staminaを回復し、回復アイテムを最大数まで補充する
<a id="fr-stage-006"></a>
- [`FR-STAGE-006`](./FunctionalDesign/Stage/FR-STAGE-006_WeaponMenuAtCheckpoint.md) チェックポイントで武器を変更する `[Post-VS]`
<a id="fr-stage-007"></a>
- [`FR-STAGE-007`](./FunctionalDesign/Stage/FR-STAGE-007_UpgradeWeaponAtCheckpoint.md) チェックポイントでGoldと強化素材を消費して武器を強化する
<a id="fr-stage-008"></a>
- [`FR-STAGE-008`](./FunctionalDesign/Stage/FR-STAGE-008_DropMaterialsOnDeath.md) 死亡時にPlayer Inventoryが所持する強化素材100%とGold100%を1つのDeathDropへ移す
<a id="fr-stage-009"></a>
- [`FR-STAGE-009`](./FunctionalDesign/Stage/FR-STAGE-009_RecoverDroppedMaterials.md) DeathDropを回収すると格納されている強化素材とGoldを全量Player Inventoryへ戻せる
<a id="fr-stage-010"></a>
- [`FR-STAGE-010`](./FunctionalDesign/Stage/FR-STAGE-010_ReplacePreviousDeathDrop.md) DeathDrop回収前に再死亡した場合は以前のDeathDropとその中身をすべて消失させ、新しい死亡地点に現在Inventoryが所持する強化素材100%とGold100%から新しいDeathDropを生成する
<a id="fr-stage-011"></a>
- [`FR-STAGE-011`](./FunctionalDesign/Stage/FR-STAGE-011_OptionalBossIntro.md) ボス登場演出は工数に余裕がある場合に実装する `[Could]`
<a id="fr-stage-012"></a>
- [`FR-STAGE-012`](./FunctionalDesign/Stage/FR-STAGE-012_RespawnAtLastCheckpoint.md) 死亡後、死亡Animation、DeathDrop生成・Auto Save、Camera確認、Fade Outを経て最後に有効化したCheckpointから再開する。未有効化時はPlayerStartから再開する
<a id="fr-stage-013"></a>
- [`FR-STAGE-013`](./FunctionalDesign/Stage/FR-STAGE-013_StageClearAfterBossDefeat.md) ボス撃破報酬の確定・Auto Save後、クリア用エリアのCollisionへ進入するとスキップ可能なEnding Sequenceへ遷移し、終了後Titleへ戻る
<a id="fr-stage-014"></a>
- [`FR-STAGE-014`](./FunctionalDesign/Stage/FR-STAGE-014_AcquireUpgradeMaterials.md) 通常敵1体の撃破ごとに強化素材とGoldをPlayer Inventoryへ直接加算できる

### 1.5 セーブ

<a id="fr-save-001"></a>
- [`FR-SAVE-001`](./FunctionalDesign/Save/FR-SAVE-001_SingleSaveSlot.md) セーブスロットは1つ
<a id="fr-save-002"></a>
- [`FR-SAVE-002`](./FunctionalDesign/Save/FR-SAVE-002_AutosaveAtCheckpoint.md) Checkpointで`Interaction → ActiveCheckpoint更新 → Menu Open → Rest処理確定 → Auto Save`の順に処理する
<a id="fr-save-003"></a>
- [`FR-SAVE-003`](./FunctionalDesign/Save/FR-SAVE-003_ManualSaveAtCheckpoint.md) Checkpoint Menuから手動セーブできる
<a id="fr-save-004"></a>
- [`FR-SAVE-004`](./FunctionalDesign/Save/FR-SAVE-004_AutosaveAfterBossDefeat.md) Boss撃破後、Goldと初回固有Itemを含むReward確定後に進行データをAuto Saveする
<a id="fr-save-005"></a>
- [`FR-SAVE-005`](./FunctionalDesign/Save/FR-SAVE-005_AutosaveDeathDropLifecycle.md) DeathDrop生成位置・格納データ確定後、およびDeathDrop回収完了後に進行データをAuto Saveする。未回収DeathDropはSave / Load後も死亡座標と格納内容を復元する
<a id="fr-save-006"></a>
- [`FR-SAVE-006`](./FunctionalDesign/Save/FR-SAVE-006_SaveSettingsOnChange.md) 設定変更時に設定データを保存する
<a id="fr-save-007"></a>
- [`FR-SAVE-007`](./FunctionalDesign/Save/FR-SAVE-007_SteamCloudAdditional.md) Steam CloudはSteam公開版の追加要件とする `[Post-VS]`

### 1.6 UI / HUD

<a id="fr-ui-001"></a>
- [`FR-UI-001`](./FunctionalDesign/UI/FR-UI-001_TitleAndStartFlow.md) ゲーム起動後にIntroを経てTitleを表示し、TitleからContinue / Load Game / New Game / Config / Exitを選択できる。New GameはTutorial TextとTutorialへ進み、ContinueはPlay Start、Load GameはSave Data選択へ進む。Ending終了後はTitleへ戻る
<a id="fr-ui-002"></a>
- [`FR-UI-002`](./FunctionalDesign/UI/FR-UI-002_GameplayHUD.md) 初期プレイアブル版で必要なGameplay HUDとしてPlayer HP、Stamina、Healing Item、Gold、Upgrade Material、LockOn Marker、Boss HP、Perfect Dodge Feedback、Save状態表示、Tutorial表示を提供する

## 2. 非機能要件

### 2.1 パフォーマンス

<a id="nfr-perf-001"></a>
- [`NFR-PERF-001`](./FunctionalDesign/Performance/NFR-PERF-001_BaselineResolution1080p.md) 1920x1080を基準解像度候補とする
<a id="nfr-perf-002"></a>
- [`NFR-PERF-002`](./FunctionalDesign/Performance/NFR-PERF-002_Minimum60Fps.md) 60fpsを最低保証目標とする
<a id="nfr-perf-003"></a>
- [`NFR-PERF-003`](./FunctionalDesign/Performance/NFR-PERF-003_Challenge120Fps.md) 120fpsを挑戦目標とする
<a id="nfr-perf-004"></a>
- [`NFR-PERF-004`](./FunctionalDesign/Performance/NFR-PERF-004_MeasureOnRtx3060.md) RTX 3060搭載開発環境で継続的に計測する
<a id="nfr-perf-005"></a>
- [`NFR-PERF-005`](./FunctionalDesign/Performance/NFR-PERF-005_InspectFrameTime.md) 平均fpsだけでなくフレーム時間を確認する
<a id="nfr-perf-006"></a>
- [`NFR-PERF-006`](./FunctionalDesign/Performance/NFR-PERF-006_SeparateBottlenecks.md) Game Thread、Render Thread、GPUのボトルネックを分離する

### 2.2 保守性

<a id="nfr-maint-001"></a>
- [`NFR-MAINT-001`](./FunctionalDesign/Maintainability/NFR-MAINT-001_DataDrivenGameplayContent.md) 武器、攻撃、敵、Ability、Reward等のGameplay Dataをデータ駆動で追加できる。各基本設計は必要データを明示し、Gameplay実装をCSV読込方式へ直接依存させない
<a id="nfr-maint-002"></a>
- [`NFR-MAINT-002`](./FunctionalDesign/Maintainability/NFR-MAINT-002_SeparateCppBlueprintResponsibilities.md) C++とBlueprintの責務を分離する
<a id="nfr-maint-003"></a>
- [`NFR-MAINT-003`](./FunctionalDesign/Maintainability/NFR-MAINT-003_PlayerInputComponentAbstraction.md) プレイヤー入力コンポーネントを`IPlayerInputComponent`で抽象化し、`ABasePlayer`が個別入力コンポーネントへ直接依存しない。Component粒度は固定せず、仕様と責務に応じて変更可能とする
<a id="nfr-maint-004"></a>
- [`NFR-MAINT-004`](./FunctionalDesign/Maintainability/NFR-MAINT-004_IsolateMoverDependency.md) Moverを検証・採用する場合でも、戦闘システムへMover固有型・固有APIの直接依存を持ち込まない
<a id="nfr-maint-005"></a>
- [`NFR-MAINT-005`](./FunctionalDesign/Maintainability/NFR-MAINT-005_CentralizeStateWithGameplayTags.md) Gameplay Tagで状態を一元管理する
<a id="nfr-maint-006"></a>
- [`NFR-MAINT-006`](./FunctionalDesign/Maintainability/NFR-MAINT-006_LimitTickUsage.md) Tickの使用を必要なクラスに限定する

### 2.3 品質

<a id="nfr-quality-001"></a>
- [`NFR-QUALITY-001`](./FunctionalDesign/Quality/NFR-QUALITY-001_ZeroProgressionBlockers.md) 進行不能バグを0件にする
<a id="nfr-quality-002"></a>
- [`NFR-QUALITY-002`](./FunctionalDesign/Quality/NFR-QUALITY-002_ZeroKnownCrashes.md) 既知のクラッシュを0件にする
<a id="nfr-quality-003"></a>
- [`NFR-QUALITY-003`](./FunctionalDesign/Quality/NFR-QUALITY-003_ClearWithBothInputDevices.md) ゲームパッドとキーボード・マウスの両方でクリア確認を行う
<a id="nfr-quality-004"></a>
- [`NFR-QUALITY-004`](./FunctionalDesign/Quality/NFR-QUALITY-004_CorruptSaveBehavior.md) セーブ破損時は破損SaveをGameplayへ適用せず削除し、New Gameを開始できる状態へ戻す
<a id="nfr-quality-005"></a>
- [`NFR-QUALITY-005`](./FunctionalDesign/Quality/NFR-QUALITY-005_LongPlayMemoryGrowth.md) 長時間プレイでメモリ増加を確認する
<a id="nfr-quality-006"></a>
- [`NFR-QUALITY-006`](./FunctionalDesign/Quality/NFR-QUALITY-006_FinalShippingVerification.md) Shippingビルドで最終確認を行う

## 3. Future Feature要件

初期プレイアブル版では実装せず、剣による初期プレイアブル版完成後の4～6カ月目を目安に追加します。

### 3.1 斧

既存の`FR-PLAYER-008`、`FR-PLAYER-009`、`FR-PLAYER-017`をPost-VSで有効化します。加えて次をFuture Feature候補とします。

- `FEATURE-AXE-001` 斧で3段の通常攻撃コンボを実行できる
- `FEATURE-AXE-002` 斧でチャージ攻撃を実行できる
- `FEATURE-AXE-003` 斧で回避攻撃を実行できる
- `FEATURE-AXE-004` 斧の指定攻撃にスーパーアーマー特性を設定できる
- `FEATURE-AXE-005` 斧のジャスト回避後に高威力の武器固有反撃を実行できる

### 3.2 弓

既存の`FR-PLAYER-008`、`FR-PLAYER-009`、`FR-BOSS-004`、`FR-BOSS-014`をPost-VSで有効化します。加えて次をFuture Feature候補とします。

- `FEATURE-BOW-001` 弓で遠距離射撃を実行できる
- `FEATURE-BOW-002` 弓を構えて肩越し照準を使用できる
- `FEATURE-BOW-003` 通常射撃は弾数を消費せず、射撃ごとにスタミナを消費する
- `FEATURE-BOW-004` 射撃距離に応じてダメージを減衰できる
- `FEATURE-BOW-005` 敵の弱点部位へ命中した場合に追加ダメージを与えられる
- `FEATURE-BOW-006` 弓のジャスト回避後に武器固有反撃を実行できる

## 4. 初期プレイアブル版対象外

- 斧の実装
- 弓の実装
- 複数武器の切り替え
- ボス再戦
- オンラインマルチプレイ
- ネットワーク同期
- Epic Online Services連携
- Steam Cloud
- 複数ロックオン部位
- リアルタイム武器切り替え
- 空中コンボ
- 大規模なストーリー
- フルボイス

### [戻る](../README.md)