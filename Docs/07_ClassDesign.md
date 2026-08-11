# 07. クラス設計

## 1. 方針

現行実装を正とし、存在しないClass / Interface / Adapterを基本設計上の確定実装として扱いません。`ABasePlayer`と`IPlayerInputComponent`を入力基盤として拡張し、GAS、Targeting、Inventory、Save、Stage Progressionを段階的に追加します。

`1 Action = 1 ActorComponent`は前提にしません。Component粒度はGameplay Tag、GAS、責務、Lifecycle、テスト容易性に応じて機能ごとに決定します。

## 2. 現在のPlayer Input基盤

```text
ABasePlayer
  ↓ discovers / manages
IPlayerInputComponent
  ↓
UBasePlayerInputComponent派生
  ├─ Move → CharacterMovement
  ├─ Look → Controller / Camera
  ├─ Combat → ASC / Gameplay Ability
  └─ Targeting → Targeting System
```

`ABasePlayer`は具体Input Component型へ個別依存せず、Input Tag、Setup、Teardown、Pressed Stateの共通契約で管理します。

## 3. Player Gameplay責務

```text
Player Character / ABasePlayer
├─ Input
├─ Camera
├─ ASC Avatar
├─ Targeting
└─ Interaction

PlayerState候補
├─ AbilitySystemComponent
└─ CharacterAttributeSet

Player Inventory
├─ Gold
├─ Upgrade Material
├─ Boss Unique Item
└─ Healing Item / Inventory系所持データ
```

Gold、Upgrade Material、Boss Unique ItemはすべてPlayer Inventoryを正本とします。HUD、Weapon Upgrade、Reward、DeathDrop、SaveはInventoryの値を利用します。

## 4. Player Reaction

PlayerはHit / Stagger / Downの3段階Reactionを持ちます。Enemy / Boss Attack Dataが持つReaction蓄積値を内部加算し、閾値に応じてReactionへ遷移します。蓄積値はHUDへ表示しません。

```text
Attack Hit
↓
Damage / Reaction値取得
↓
Health <= 0 ? → Dead
↓ No
Reaction累積
├─ Down
├─ Stagger
└─ Hit
```

## 5. Fatal Attack

```text
Enemy Down
↓
Down Animation
↓
Fatal Attack受付Collision / Window ON
↓
Playerが範囲内でAttack Input
↓
Fatal Attack基準Transformへ位置合わせ
↓
UGA_FatalAttack
↓
Fatal Attack Montage
↓
Fatal Damage
```

Down終了、Enemy Defeat、Fatal Attack成立時に受付を無効化します。

## 6. Movement / Camera

通常移動は現行`UPlayerMoveInputComponent → AddMovementInput → CharacterMovement`を維持します。Moverは将来検証対象で、必要性が確認されるまでAdapterを先行追加しません。

Cameraは`UPlayerLookInputComponent → Controller Yaw/Pitch → CameraBoom / FollowCamera`を基本とし、LockOn中はTargeting側の追従を優先します。Player Death中もCamera Lookは許可します。

## 7. Boss AI

```text
Boss AI Controller
├─ StateTree
├─ Combat Context
├─ Attack Evaluator
├─ Action History
└─ Debug Presentation
```

Boss AIは距離、Healing、Stamina、Action History、Phase等を評価してAttack候補をScore化します。各Boss基本設計は、その要件で利用した入力値・Score・選択結果をDebug表示で確認可能にします。

## 8. Checkpoint

確定処理順は次です。

```text
Interaction
↓
ActiveCheckpoint更新
↓
Menu Open
↓
Rest処理確定
├─ HP Full
├─ Stamina Full
├─ Healing Item補充
└─ Normal Enemy Respawn
↓
Auto Save
```

Weapon UpgradeはCheckpoint Menuから行いますが、Upgrade完了自体はAuto Save契機にしません。

## 9. Player Death / DeathDrop / Respawn

```text
Health <= 0
↓
Death Animation
↓
旧DeathDropがあれば本体・内容を完全消失
↓
Player Inventoryから新DeathDropへ移動
├─ Upgrade Material 100%
└─ Gold 100%
↓
DeathDrop座標・格納内容確定
↓
Auto Save
↓
CameraでDeathDrop確認
↓
Fade Out
↓
ActiveCheckpoint / 未設定時PlayerStartへRespawn
↓
HP / Stamina / Healing Item Full
↓
Normal Enemy Respawn
↓
Fade In
```

未回収DeathDropの座標と格納内容はSave / Load対象です。JSON形式は別Architecture Designで定義します。

## 10. Boss Defeat / Stage Clear

確定フローは次です。

```text
Boss HP <= 0
↓
Boss Defeated
↓
Gold付与
↓
初回固有Item付与
↓
Reward確定
↓
Auto Save
↓
PlayerがClear Areaへ移動
↓
Clear Trigger
↓
Skippable Ending
↓
Title
```

Boss Defeat後のStage Clear自体では追加Auto Saveを行いません。

## 11. Title / UI

```text
Game Boot → Intro → Title
Title
├─ Continue → Play Start
├─ Load Game → Save Data Select → Play Start
├─ New Game → Tutorial Text → Tutorial → Play Start
├─ Config
└─ Exit

Ending → Title
```

Gameplay HUDはHP、Stamina、Healing Item、Gold、Upgrade Material、LockOn Marker、Boss HP、Perfect Dodge Feedback、Save状態、Tutorial表示を提供します。

## 12. Data / Master Data境界

各FR基本設計に必要データを記載し、DB Schema、CSV Reader、JSON Save Schemaは別Architecture Designへ分離します。Gameplay実装は具体的CSV Readerへ直接依存しません。

Rewardは`RewardID -> 0..N Item`の関係を扱える契約とし、Reward件数をコード構造へ埋め込みません。

### [戻る](../README.md#ドキュメント一覧)
