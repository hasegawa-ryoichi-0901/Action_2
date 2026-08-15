# 基本設計ドキュメント一覧

> [`Docs/01_Requirements.md`](../01_Requirements.md) の各要件を、[`FunctionalDesign_Template.md`](FunctionalDesign_Template.md) の12章構成で具体化した索引です。
>
> **要件ID → 要件定義、基本設計 → 設計ファイル、Issue → GitHub Issue** の3方向へ直接移動できることを本一覧の必須条件とします。

## 1. 作成・運用方針

- 基本設計はテンプレートへ統一する。
- 基本設計内の`要件ID`は該当する要件定義AnchorへのLinkを必須とする。
- 基本設計内の`関連Issue`はIssueが存在する場合、GitHub Issue URLへのLinkを必須とする。
- Issue未作成のPost-VS要件のみ`未割当`を許可する。
- 全FRに`必要データ`を記載し、DB / CSV / JSON等の具体Architectureとは分離する。
- Gameplay ActionとActorComponentの粒度は一致させない。Component構成は仕様・Gameplay Tag・GAS・責務・Lifecycleに応じて決定する。
- 原則`1実装Issue = 1PR`とし、Gameplay Action / Systemの親IssueはTracking用途に使用する。

## 2. Player（23件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`FR-PLAYER-001`](../01_Requirements.md#fr-player-001) | [三人称視点での移動](Player/FR-PLAYER-001_ThirdPersonMovement.md) | [#110](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/110) |
| [`FR-PLAYER-002`](../01_Requirements.md#fr-player-002) | [ゲームパッド・キーボード／マウスでの同等操作](Player/FR-PLAYER-002_EquivalentInputDevices.md) | [#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111) |
| [`FR-PLAYER-003`](../01_Requirements.md#fr-player-003) | [ジャンプ](Player/FR-PLAYER-003_Jump.md) | [#108](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/108), [#109](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/109) |
| [`FR-PLAYER-004`](../01_Requirements.md#fr-player-004) | [空中攻撃](Player/FR-PLAYER-004_AirAttack.md) | [#112](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/112) |
| [`FR-PLAYER-005`](../01_Requirements.md#fr-player-005) | [ソフトロック](Player/FR-PLAYER-005_SoftLock.md) | [#113](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/113) |
| [`FR-PLAYER-006`](../01_Requirements.md#fr-player-006) | [手動ロックオン](Player/FR-PLAYER-006_ManualLockOn.md) | [#75](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/75) |
| [`FR-PLAYER-007`](../01_Requirements.md#fr-player-007) | [ロックオン対象の切り替え](Player/FR-PLAYER-007_SwitchLockTarget.md) | [#79](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/79) |
| [`FR-PLAYER-008`](../01_Requirements.md#fr-player-008) | [チェックポイントでの武器変更](Player/FR-PLAYER-008_ChangeWeaponAtCheckpoint.md) | 未割当（Post-VS） |
| [`FR-PLAYER-009`](../01_Requirements.md#fr-player-009) | [戦闘中の武器変更禁止](Player/FR-PLAYER-009_BlockWeaponChangeInCombat.md) | 未割当（Post-VS） |
| [`FR-PLAYER-010`](../01_Requirements.md#fr-player-010) | [弱攻撃・強攻撃・連続攻撃](Player/FR-PLAYER-010_LightHeavyCombo.md) | [#58](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58), [#67](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/67), [#71](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/71) |
| [`FR-PLAYER-011`](../01_Requirements.md#fr-player-011) | [攻撃・回避時のスタミナ消費](Player/FR-PLAYER-011_StaminaCost.md) | [#61](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61) |
| [`FR-PLAYER-012`](../01_Requirements.md#fr-player-012) | [スタミナ不足時のアクション拒否](Player/FR-PLAYER-012_RejectInsufficientStamina.md) | [#61](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61) |
| [`FR-PLAYER-013`](../01_Requirements.md#fr-player-013) | [スタミナ枯渇状態](Player/FR-PLAYER-013_ExhaustedState.md) | [#152](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/152) |
| [`FR-PLAYER-014`](../01_Requirements.md#fr-player-014) | [ジャスト回避](Player/FR-PLAYER-014_PerfectDodge.md) | [#52](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52) |
| [`FR-PLAYER-015`](../01_Requirements.md#fr-player-015) | [ジャスト回避後の武器固有反撃](Player/FR-PLAYER-015_WeaponCounterAfterPerfectDodge.md) | [#114](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/114) |
| [`FR-PLAYER-016`](../01_Requirements.md#fr-player-016) | [剣による受け流し](Player/FR-PLAYER-016_SwordParry.md) | [#115](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/115) |
| [`FR-PLAYER-017`](../01_Requirements.md#fr-player-017) | [斧による防御・受け止め](Player/FR-PLAYER-017_AxeGuardOrReceive.md) | 未割当（Post-VS） |
| [`FR-PLAYER-018`](../01_Requirements.md#fr-player-018) | [使用回数制限付き回復アイテム](Player/FR-PLAYER-018_LimitedHealingItem.md) | [#116](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/116) |
| [`FR-PLAYER-019`](../01_Requirements.md#fr-player-019) | [通常回避](Player/FR-PLAYER-019_NormalDodge.md) | [#52](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52) |
| [`FR-PLAYER-020`](../01_Requirements.md#fr-player-020) | [プレイヤーの体力・死亡](Player/FR-PLAYER-020_PlayerHealthAndDeath.md) | [#82](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/82), [#83](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/83) |
| [`FR-PLAYER-021`](../01_Requirements.md#fr-player-021) | [三人称カメラ操作](Player/FR-PLAYER-021_ThirdPersonCameraControl.md) | [#117](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/117) |
| [`FR-PLAYER-022`](../01_Requirements.md#fr-player-022) | [ダウン中の敵への致命攻撃](Player/FR-PLAYER-022_FatalAttack.md) | [#148](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/148) |
| [`FR-PLAYER-023`](../01_Requirements.md#fr-player-023) | [被弾・よろめき・ダウン反応](Player/FR-PLAYER-023_HitStaggerDown.md) | [#149](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/149) |

## 3. Enemy（10件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`FR-ENEMY-001`](../01_Requirements.md#fr-enemy-001) | [近接型通常敵の実装](Enemy/FR-ENEMY-001_MeleeNormalEnemy.md) | [#119](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/119) |
| [`FR-ENEMY-002`](../01_Requirements.md#fr-enemy-002) | [遠距離型通常敵の実装](Enemy/FR-ENEMY-002_RangedNormalEnemy.md) | [#120](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/120) |
| [`FR-ENEMY-003`](../01_Requirements.md#fr-enemy-003) | [通常戦での複数敵同時行動](Enemy/FR-ENEMY-003_ConcurrentNormalEnemies.md) | [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121) |
| [`FR-ENEMY-004`](../01_Requirements.md#fr-enemy-004) | [近接攻撃参加敵の最大2体制限](Enemy/FR-ENEMY-004_MaxTwoMeleeAttackers.md) | [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121) |
| [`FR-ENEMY-005`](../01_Requirements.md#fr-enemy-005) | [近接・遠距離攻撃枠の分離](Enemy/FR-ENEMY-005_SeparateMeleeRangedSlots.md) | [#121](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121) |
| [`FR-ENEMY-006`](../01_Requirements.md#fr-enemy-006) | [敵の体力・体勢](Enemy/FR-ENEMY-006_HealthAndPosture.md) | [#122](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/122) |
| [`FR-ENEMY-007`](../01_Requirements.md#fr-enemy-007) | [体勢値ゼロ時のダウン](Enemy/FR-ENEMY-007_DownAtZeroPosture.md) | [#123](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/123) |
| [`FR-ENEMY-008`](../01_Requirements.md#fr-enemy-008) | [ダウン中の致命攻撃受付](Enemy/FR-ENEMY-008_FatalAttackOnDownedEnemy.md) | [#123](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/123) |
| [`FR-ENEMY-009`](../01_Requirements.md#fr-enemy-009) | [敵ごとの体勢回復設定](Enemy/FR-ENEMY-009_PerEnemyPostureRecovery.md) | [#124](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/124) |
| [`FR-ENEMY-010`](../01_Requirements.md#fr-enemy-010) | [体力ゼロ時の敵撃破](Enemy/FR-ENEMY-010_DefeatAtZeroHealth.md) | [#97](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/97), [#98](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/98) |

## 4. Boss（16件）

ボスAI共通契約: [ボスAI共通設計](Boss/BossAI_CommonDesign.md)

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`FR-BOSS-001`](../01_Requirements.md#fr-boss-001) | [ボスとの一対一戦闘](Boss/FR-BOSS-001_OneOnOneBossBattle.md) | [#126](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/126) |
| [`FR-BOSS-002`](../01_Requirements.md#fr-boss-002) | [体力50%以下での第2段階移行](Boss/FR-BOSS-002_PhaseTwoAtHalfHealth.md) | [#126](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/126) |
| [`FR-BOSS-003`](../01_Requirements.md#fr-boss-003) | [プレイヤーとの距離評価](Boss/FR-BOSS-003_EvaluatePlayerDistance.md) | [#127](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/127) |
| [`FR-BOSS-004`](../01_Requirements.md#fr-boss-004) | [プレイヤーの装備武器評価](Boss/FR-BOSS-004_EvaluateEquippedWeapon.md) | 未割当（Post-VS） |
| [`FR-BOSS-005`](../01_Requirements.md#fr-boss-005) | [プレイヤーの回復状態評価](Boss/FR-BOSS-005_EvaluateHealingState.md) | [#127](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/127) |
| [`FR-BOSS-006`](../01_Requirements.md#fr-boss-006) | [プレイヤーの残りスタミナ評価](Boss/FR-BOSS-006_EvaluateRemainingStamina.md) | [#127](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/127) |
| [`FR-BOSS-007`](../01_Requirements.md#fr-boss-007) | [プレイヤーの直近行動・戦闘傾向評価](Boss/FR-BOSS-007_EvaluateActionHistory.md) | [#127](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/127) |
| [`FR-BOSS-008`](../01_Requirements.md#fr-boss-008) | [状況に応じた攻撃候補の採点](Boss/FR-BOSS-008_ScoreAttackCandidates.md) | [#128](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/128) |
| [`FR-BOSS-009`](../01_Requirements.md#fr-boss-009) | [状況に応じた接近・離脱頻度変更](Boss/FR-BOSS-009_AdaptApproachRetreatFrequency.md) | [#129](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/129) |
| [`FR-BOSS-010`](../01_Requirements.md#fr-boss-010) | [状況に応じた遠距離攻撃頻度変更](Boss/FR-BOSS-010_AdaptRangedAttackFrequency.md) | [#129](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/129) |
| [`FR-BOSS-011`](../01_Requirements.md#fr-boss-011) | [ボス攻撃コンボの分岐](Boss/FR-BOSS-011_BranchAttackCombo.md) | [#130](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/130) |
| [`FR-BOSS-012`](../01_Requirements.md#fr-boss-012) | [特定攻撃後の大きな硬直](Boss/FR-BOSS-012_LargeRecoveryAfterSpecificAttack.md) | [#131](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/131) |
| [`FR-BOSS-013`](../01_Requirements.md#fr-boss-013) | [ジャスト回避・受け流し成功後の反撃機会](Boss/FR-BOSS-013_CounterWindowAfterDefense.md) | [#131](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/131) |
| [`FR-BOSS-014`](../01_Requirements.md#fr-boss-014) | [弓で距離を取られた場合の専用接近行動](Boss/FR-BOSS-014_BowRangeGapCloser.md) | 未割当（Post-VS） |
| [`FR-BOSS-015`](../01_Requirements.md#fr-boss-015) | [体力ゼロ時のボス撃破](Boss/FR-BOSS-015_DefeatAtZeroHealth.md) | [#100](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/100), [#101](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/101) |
| [`FR-BOSS-016`](../01_Requirements.md#fr-boss-016) | [ボス初回撃破報酬](Boss/FR-BOSS-016_FirstDefeatReward.md) | [#100](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/100), [#102](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/102) |

## 5. Stage / Progression（14件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`FR-STAGE-001`](../01_Requirements.md#fr-stage-001) | [新規ゲーム開始時のチュートリアル文章表示](Stage/FR-STAGE-001_IntroText.md) | [#132](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/132) |
| [`FR-STAGE-002`](../01_Requirements.md#fr-stage-002) | [チュートリアルの実施](Stage/FR-STAGE-002_Tutorial.md) | [#133](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/133) |
| [`FR-STAGE-003`](../01_Requirements.md#fr-stage-003) | [チェックポイント利用・メニュー表示](Stage/FR-STAGE-003_UseCheckpoint.md) | [#91](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/91), [#92](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/92) |
| [`FR-STAGE-004`](../01_Requirements.md#fr-stage-004) | [チェックポイント休息時の通常敵再出現](Stage/FR-STAGE-004_RespawnNormalEnemiesAtCheckpoint.md) | [#93](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/93) |
| [`FR-STAGE-005`](../01_Requirements.md#fr-stage-005) | [チェックポイント休息時の回復・補充](Stage/FR-STAGE-005_RefillHealingAtCheckpoint.md) | [#93](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/93) |
| [`FR-STAGE-006`](../01_Requirements.md#fr-stage-006) | [チェックポイントの武器メニュー](Stage/FR-STAGE-006_WeaponMenuAtCheckpoint.md) | 未割当（Post-VS） |
| [`FR-STAGE-007`](../01_Requirements.md#fr-stage-007) | [チェックポイントでの武器強化](Stage/FR-STAGE-007_UpgradeWeaponAtCheckpoint.md) | [#94](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/94) |
| [`FR-STAGE-008`](../01_Requirements.md#fr-stage-008) | [死亡時の所持資源落下](Stage/FR-STAGE-008_DropMaterialsOnDeath.md) | [#82](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/82), [#84](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/84) |
| [`FR-STAGE-009`](../01_Requirements.md#fr-stage-009) | [死亡落とし物からの資源回収](Stage/FR-STAGE-009_RecoverDroppedMaterials.md) | [#86](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/86) |
| [`FR-STAGE-010`](../01_Requirements.md#fr-stage-010) | [再死亡時の未回収落とし物置換](Stage/FR-STAGE-010_ReplacePreviousDeathDrop.md) | [#82](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/82), [#86](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/86) |
| [`FR-STAGE-011`](../01_Requirements.md#fr-stage-011) | [任意追加可能なボス登場演出](Stage/FR-STAGE-011_OptionalBossIntro.md) | [#147](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/147) |
| [`FR-STAGE-012`](../01_Requirements.md#fr-stage-012) | [最後に有効化したチェックポイントからの再出現](Stage/FR-STAGE-012_RespawnAtLastCheckpoint.md) | [#85](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/85) |
| [`FR-STAGE-013`](../01_Requirements.md#fr-stage-013) | [ボス撃破後のクリア判定・エンディング遷移](Stage/FR-STAGE-013_StageClearAfterBossDefeat.md) | [#105](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/105) |
| [`FR-STAGE-014`](../01_Requirements.md#fr-stage-014) | [通常敵撃破報酬の獲得](Stage/FR-STAGE-014_AcquireUpgradeMaterials.md) | [#97](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/97), [#99](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/99) |

## 6. Save（7件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`FR-SAVE-001`](../01_Requirements.md#fr-save-001) | [単一セーブスロット](Save/FR-SAVE-001_SingleSaveSlot.md) | [#87](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/87), [#88](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/88) |
| [`FR-SAVE-002`](../01_Requirements.md#fr-save-002) | [チェックポイント休息確定後の自動保存](Save/FR-SAVE-002_AutosaveAtCheckpoint.md) | [#89](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89) |
| [`FR-SAVE-003`](../01_Requirements.md#fr-save-003) | [チェックポイントメニューからの手動保存](Save/FR-SAVE-003_ManualSaveAtCheckpoint.md) | [#89](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89) |
| [`FR-SAVE-004`](../01_Requirements.md#fr-save-004) | [ボス報酬確定後の自動保存](Save/FR-SAVE-004_AutosaveAfterBossDefeat.md) | [#103](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/103) |
| [`FR-SAVE-005`](../01_Requirements.md#fr-save-005) | [死亡落とし物の生成・回収後の自動保存と未回収物の復元](Save/FR-SAVE-005_AutosaveDeathDropLifecycle.md) | [#90](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/90) |
| [`FR-SAVE-006`](../01_Requirements.md#fr-save-006) | [設定変更時の保存](Save/FR-SAVE-006_SaveSettingsOnChange.md) | [#104](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/104) |
| [`FR-SAVE-007`](../01_Requirements.md#fr-save-007) | [Steamクラウドへのセーブデータ同期](Save/FR-SAVE-007_SteamCloudAdditional.md) | 未割当（Post-VS） |

## 7. UI / HUD（2件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`FR-UI-001`](../01_Requirements.md#fr-ui-001) | [タイトル・ゲーム開始フロー](UI/FR-UI-001_TitleAndStartFlow.md) | [#150](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/150) |
| [`FR-UI-002`](../01_Requirements.md#fr-ui-002) | [α版のゲームプレイ情報表示](UI/FR-UI-002_GameplayHUD.md) | [#151](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/151) |

## 8. Performance（6件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`NFR-PERF-001`](../01_Requirements.md#nfr-perf-001) | [1920×1080基準解像度](Performance/NFR-PERF-001_BaselineResolution1080p.md) | [#134](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/134) |
| [`NFR-PERF-002`](../01_Requirements.md#nfr-perf-002) | [最低60フレーム毎秒の保証目標](Performance/NFR-PERF-002_Minimum60Fps.md) | [#135](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/135) |
| [`NFR-PERF-003`](../01_Requirements.md#nfr-perf-003) | [120フレーム毎秒の挑戦目標](Performance/NFR-PERF-003_Challenge120Fps.md) | [#135](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/135) |
| [`NFR-PERF-004`](../01_Requirements.md#nfr-perf-004) | [RTX 3060開発環境での継続計測](Performance/NFR-PERF-004_MeasureOnRtx3060.md) | [#134](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/134) |
| [`NFR-PERF-005`](../01_Requirements.md#nfr-perf-005) | [平均フレームレート・フレーム時間確認](Performance/NFR-PERF-005_InspectFrameTime.md) | [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136) |
| [`NFR-PERF-006`](../01_Requirements.md#nfr-perf-006) | [ゲーム処理・描画処理・GPU間のボトルネック切り分け](Performance/NFR-PERF-006_SeparateBottlenecks.md) | [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136) |

## 9. Maintainability（6件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`NFR-MAINT-001`](../01_Requirements.md#nfr-maint-001) | [データ駆動によるゲーム内容追加](Maintainability/NFR-MAINT-001_DataDrivenGameplayContent.md) | [#137](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/137), [#155](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/155) |
| [`NFR-MAINT-002`](../01_Requirements.md#nfr-maint-002) | [C++・ブループリントの責務分離](Maintainability/NFR-MAINT-002_SeparateCppBlueprintResponsibilities.md) | [#138](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/138) |
| [`NFR-MAINT-003`](../01_Requirements.md#nfr-maint-003) | [IPlayerInputComponentによるプレイヤー入力の抽象化](Maintainability/NFR-MAINT-003_PlayerInputComponentAbstraction.md) | [#139](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139) |
| [`NFR-MAINT-004`](../01_Requirements.md#nfr-maint-004) | [Mover固有依存の戦闘機能からの分離](Maintainability/NFR-MAINT-004_IsolateMoverDependency.md) | [#139](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139) |
| [`NFR-MAINT-005`](../01_Requirements.md#nfr-maint-005) | [Gameplay Tagによるゲームプレイ状態の一元管理](Maintainability/NFR-MAINT-005_CentralizeStateWithGameplayTags.md) | [#140](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/140) |
| [`NFR-MAINT-006`](../01_Requirements.md#nfr-maint-006) | [必要箇所に限定したティック処理](Maintainability/NFR-MAINT-006_LimitTickUsage.md) | [#141](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/141) |

## 10. Quality（6件）

| 要件ID | 基本設計 | 関連Issue |
|---|---|---|
| [`NFR-QUALITY-001`](../01_Requirements.md#nfr-quality-001) | [進行不能バグゼロ](Quality/NFR-QUALITY-001_ZeroProgressionBlockers.md) | [#142](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/142) |
| [`NFR-QUALITY-002`](../01_Requirements.md#nfr-quality-002) | [既知クラッシュゼロ](Quality/NFR-QUALITY-002_ZeroKnownCrashes.md) | [#143](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/143) |
| [`NFR-QUALITY-003`](../01_Requirements.md#nfr-quality-003) | [ゲームパッド・キーボード／マウス双方でのクリア確認](Quality/NFR-QUALITY-003_ClearWithBothInputDevices.md) | [#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111) |
| [`NFR-QUALITY-004`](../01_Requirements.md#nfr-quality-004) | [セーブデータ破損時の動作](Quality/NFR-QUALITY-004_CorruptSaveBehavior.md) | [#144](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/144), [#154](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154) |
| [`NFR-QUALITY-005`](../01_Requirements.md#nfr-quality-005) | [長時間プレイ時のメモリ増加](Quality/NFR-QUALITY-005_LongPlayMemoryGrowth.md) | [#145](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/145) |
| [`NFR-QUALITY-006`](../01_Requirements.md#nfr-quality-006) | [出荷用ビルドの最終確認](Quality/NFR-QUALITY-006_FinalShippingVerification.md) | [#146](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/146) |

## 11. 共通基盤・Architecture Issue

要件を横断して利用する実装・Architectureは以下を参照します。

- [#153 Player Inventory基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)
- [#154 JSON Save Architecture](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)
- [#155 CSV / Master Data読込Architecture](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/155)

## 12. 確定済み主要フロー

### Checkpoint

```text
Interaction
↓
ActiveCheckpoint更新
↓
Menu Open
↓
Rest処理確定
├ HP / Stamina Full
├ Healing Item補充
└ Normal Enemy Respawn
↓
Auto Save
```

### Player Death

```text
HP <= 0
↓
Death Animation
↓
旧DeathDropがあれば完全消失
↓
Upgrade Material 100% + Gold 100%を新DeathDropへ移動
↓
DeathDrop位置・内容確定
↓
Auto Save
↓
Camera確認
↓
Fade Out
↓
Checkpoint / PlayerStartへRespawn
```

### Boss Defeat / Stage Clear

```text
Boss Defeated
↓
Gold + 初回固有Item
↓
Reward確定
↓
Auto Save
↓
Clear Area
↓
Clear Trigger
↓
Skippable Ending
↓
Title
```

## 13. Data / Architecture方針

- 各FRはGameplay上の`必要データ`を定義する。
- Rewardは`EnemyId / BossId → RewardId → 0..N Reward Entry(ItemId / Amount) → Player Inventory`を正とする。
- JSON Schemaは[`Docs/18_SaveJsonArchitecture.md`](../18_SaveJsonArchitecture.md)で定義する。
- Master Data / CSV Architectureは[`Docs/17_MasterDataCsvArchitecture.md`](../17_MasterDataCsvArchitecture.md)で定義する。

## 14. Issue同期条件

1. ゲーム上の挙動が確定している。
2. Issue境界を変更する未解決事項が残っていない。
3. 対応する要件・基本設計が存在する。
4. 既存実装との差分・重複を確認している。
5. 実装Issue単独で受入確認できる。
6. 基本設計の実装範囲・必要データ・UI / Animation・異常系・受入条件をIssueへ反映している。

### [READMEへ戻る](../../README.md#ドキュメント一覧)
