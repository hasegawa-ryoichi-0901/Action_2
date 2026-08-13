# 基本設計ドキュメント一覧

> `Docs/01_Requirements.md` の各要件を基本設計へ具体化する索引です。
> 初期Vertical Sliceは剣のみを対象とし、斧・弓はPost-Vertical Slice Featureとして扱います。

## 1. 作成方針

- 機能要件72件、非機能要件18件の合計90件を管理する。
- **全90要件の基本設計は`FunctionalDesign_Template.md`の12章構成へ統一する。**
- 標準章は「基本情報 / 目的 / 確定仕様・スコープ / 基本フロー / 責務 / 状態・Gameplay Tag / 必要データ / UI・HUD・Animation・Feedback / 異常系・終了条件 / 受入条件 / 依存・Issue反映 / 未決事項」とする。
- 全FRに`必要データ`欄を設け、DB / CSV / JSON / Data Asset等の保存・読込方式とは分離する。
- Player Inputは`IPlayerInputComponent`を正とする。
- `1 Action = 1 ActorComponent`は前提とせず、Component粒度は仕様・Gameplay Tag・GAS・責務に応じて決定する。
- Component粒度はAction Issue作成・実装開始を妨げる未解決事項として扱わない。
- Gameplay Actionは親Issue、独立した実装単位は実装Issueとして管理する。
- 原則`1実装Issue = 1 PR`とする。
- 現在存在しない`IMovementDriver` / `UMovementAdapterComponent`を初期Vertical Sliceの前提としない。
- 数値調整・Asset最終選定は実装中に変更可能とし、Issue作成を妨げない。
- 基本設計で確定した実装範囲・必要データ・UI / Animation・異常系・受入条件は関連Issueへ反映する。ただし設計書全文のコピーは行わない。

## 2. Player（23件）

`FR-PLAYER-001`～`FR-PLAYER-023`を管理します。`FR-PLAYER-008`、`009`、`017`はPost-VSです。

特記事項：
- `FR-PLAYER-014` Perfect Dodgeは`FR-PLAYER-019` Dodge Actionの結果です。
- `FR-PLAYER-022`はDown中EnemyへのPlayer Fatal Attackです。
- `FR-PLAYER-023`はHit / Stagger / Downの内部Reaction蓄積を扱います。

## 3. Enemy（10件）

`FR-ENEMY-001`～`FR-ENEMY-010`をInitial VSで管理します。

- `FR-ENEMY-007`はDown状態とAnimation。
- `FR-ENEMY-008`はDown中のFatal Attack受付State / Collision。
- Player側のFatal Attack実行は`FR-PLAYER-022`が担当します。

## 4. Boss（16件）

`FR-BOSS-001`～`013`、`015`、`016`はInitial VS、`FR-BOSS-014`はPost-VSです。

Boss AIの共通判断・Debug契約は`Boss/BossAI_CommonDesign.md`に記載します。Debugを別Gameplay Featureには分離せず、各Boss AI要件の検証責務として扱います。

Boss Defeat以降は次を確定順序とします。

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
Ending
↓
Title
```

## 5. Stage / Progression（14件）

`FR-STAGE-001`～`FR-STAGE-014`を管理します。`FR-STAGE-006`はPost-VS、`FR-STAGE-011`はCouldです。

DeathDropはPlayer InventoryのUpgrade Material 100% + Gold 100%を格納します。未回収状態で再死亡した場合は旧DeathDropと内容を完全消失させます。

Checkpointは次の順で処理します。

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

## 6. Save（7件）

`FR-SAVE-001`～`007`を管理します。Steam CloudはPost-VSです。

- Progress Saveは1 Slot。
- CheckpointはRest確定後Auto Save。
- BossはReward確定後Auto Save。
- DeathDropは生成内容確定後 / 回収後Auto Save。
- 未回収DeathDropの位置・内容をSave / Load対象とする。
- Settings SaveはProgress Saveとは別契機。
- Weapon Upgrade完了時とStage Clear時はAuto Saveしない。

## 7. UI / HUD（2件）

- `FR-UI-001`: Boot / Intro / Title / Continue / Load / New Game / Config / Exit / Ending後Title復帰。
- `FR-UI-002`: HP / Stamina / Healing Item / Gold / Material / LockOn Marker / Boss HP / Perfect Dodge / Save / Tutorial HUD。

## 8. 非機能要件（18件）

- Performance: `NFR-PERF-001`～`006`
- Maintainability: `NFR-MAINT-001`～`006`
- Quality: `NFR-QUALITY-001`～`006`

非機能要件も機能要件と同じ12章テンプレートへ統一します。

## 9. Data / Architecture方針

各FRはGameplay上の`必要データ`を定義します。具体的なDB Schema、CSV形式、Reader、JSON Schema等は別Architecture Documentで定義します。

RewardのGameplay契約は次を正とします。

```text
EnemyId / BossId
↓
RewardId
↓
0..N Reward Entry(ItemId / Amount)
↓
Player Inventory
```

Gameplay付与ロジックをReward件数へ依存させません。

## 10. Future Feature

Axe / BowのFuture Featureは`Docs/01_Requirements.md`および`Docs/04_WeaponSystem.md`を正とし、Initial VS Issue依存グラフへ含めません。

## 11. Issue作成・同期条件

1. ゲーム上の挙動が確定している。
2. Issue境界を変更する未解決事項が残っていない。
3. 依存する基本設計が存在する。
4. 既存実装との差分・重複を確認している。
5. 実装Issue単独で受入確認できる。
6. 基本設計で確定した実装範囲・必要データ・UI / Animation・異常系・受入条件がIssueへ反映されている。

詳細なIssue階層ルールは`Docs/14_RepositoryOperation.md`を参照します。
