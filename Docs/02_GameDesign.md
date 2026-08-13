# 02. ゲームデザイン

## 1. Player Experience

本作の中心はPlayer操作とEnemyとのCombat。MovementとCameraは高い応答性を持たせ、Attackは入力遅延ではなくStartup / Commitment / Active / RecoveryとCancel制約によって重量感を表現する。

初期プレイアブル版ではSwordのみを使用し、Boot / Title、Tutorial、Movement、Dodge、Attack、Parry、Fatal Attack、Normal Enemy、Boss、Death / Respawn、Endingまでの一連の体験を完成させる。Axe / BowはPost-VSとする。

## 2. Boot / Title / Start

```text
Game Boot
↓
Intro
↓
Title
├─ Continue → Play Start
├─ Load Game → Save Data Select → Play Start
├─ New Game → Tutorial Text → Tutorial → Play Start
├─ Config
└─ Exit
```

Ending完了 / Skip後はTitleへ戻る。

## 3. Input

Enhanced Inputを使用し、PlayerへアタッチされたInput Componentを`IPlayerInputComponent`で共通管理する。Gameplay ActionとActorComponentの粒度は一致させず、Gameplay Tag、GAS、責務に応じて機能ごとに決定する。

## 4. Combat Tempo

- Move / Camera: 軽快かつ高応答。
- Light / Heavy Attack: Startup / Commitment / Active / Recoveryを持つ。
- Cancel: 許可Window内だけ成立する。
- Dodge: 1 ActionでNormal / Perfect Resultを扱う。
- Parry: Sword固有の高リスク防御。
- Fatal Attack: Enemy Down中の明確なCombat Reward Action。
- Slow Motionは使用しない。
- Perfect Dodge成功は短いHit StopとHUD Feedbackを使用する。

## 5. Dodge

```text
Dodge Input
↓
移動入力あり？
├─ Yes → 入力方向へRoll
└─ No  → 後方Back Step
↓
Invincible Window / Perfect Dodge Window
↓
Enemy Attackとの関係を評価
├─ Perfect成立 → Perfect Dodge Result
├─ Invincibleのみ → Normal Dodge / No Damage
└─ 無敵外 → Hit
```

Air Dodge不可、Enemy Collision非通過。Window時間・移動量は調整可能。

## 6. Player Reaction / Fatal Attack

PlayerはHit / Stagger / Downの3段階Reactionを持つ。Enemy / Boss Attack Dataが持つReaction蓄積値をPlayer内部で計算し、蓄積値そのものはHUDへ表示しない。DeathをReactionより優先する。

Enemy Posture<=0ではDown Animationを再生し、Down中のみFatal Attack受付Collision / Stateを有効化する。Playerが範囲内でAttack InputするとFatal Attack基準Transformへ位置合わせし、`UGA_FatalAttack`、Montage、Fatal Damageへ進む。Down終了 / Defeat / Fatal成立時に受付を解除する。

## 7. Targeting / Camera

- 非LockOn時はYaw / Pitch Camera Look。
- LockOn中は通常Lookを無効にしCurrent Targetへ追従。
- 同一LockOn入力で解除。
- Target Switchは別左右入力。
- Target死亡 / 無効化時は自動Lock解除。
- Death中もCamera Lookを許可する。

## 8. Inventory / Reward / Upgrade

Gold、Upgrade Material、Boss Unique ItemはPlayer Inventoryを正本とする。共通Inventory責務は[#153](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)で管理する。

Normal Enemy DefeatごとにReward Masterから0..N Reward Entryを取得してInventoryへ直接加算する。World Reward Actorは生成しない。

Weapon UpgradeはCheckpoint MenuでGold + Upgrade Materialを消費する。Upgrade完了自体はAuto Save契機にしない。

## 9. Healing Item

```text
Heal Input
↓
Healing Item Count確認
↓
Heal Animation開始
↓
Healing Itemを1個消費
↓
Animation継続
├─ 被弾 → Heal中断 / Item非返却
└─ 完了 → HP回復
```

Animation開始前にActionが成立しなければItemを消費しない。Animation開始直後に消費した後は、被弾・CancelされてもItemを返却しない。

## 10. Checkpoint

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

## 11. Death / DeathDrop / Respawn

```text
Player HP <= 0
↓
Death Animation
↓
旧未回収DeathDropがあれば本体・内容を完全消失
↓
Player Inventoryから新DeathDropへ全量移動
├─ Upgrade Material 100%
└─ Gold 100%
↓
死亡座標・格納内容確定
↓
Auto Save
↓
CameraでDeathDrop確認
↓
Fade Out
↓
ActiveCheckpoint / 未設定時PlayerStartへRespawn
├─ HP Full
├─ Stamina Full
├─ Healing Item Full
└─ Normal Enemy Respawn
↓
Fade In
```

未回収DeathDropの座標・内容はSave / Load後も復元する。JSON具体構造は別Architecture Designで扱う。

## 12. Boss Defeat / Stage Clear

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

Boss撃破直後にEndingへ自動遷移せず、Stage Clear自体では追加Auto Saveを行わない。

## 13. HUD

初期プレイアブル版で必要な表示：Player HP、Stamina、Healing Item、Gold、Upgrade Material、LockOn Marker、Boss HP、Perfect Dodge Feedback、Save状態、Tutorial表示。Player Reaction内部蓄積値は表示しない。

## 14. Future Weapons

Axe / Bowは初期プレイアブル版完成後に追加する。Weapon追加が初期プレイアブル版の完成条件を妨げないよう共通基盤を再利用する。

### [戻る](../README.md#ドキュメント一覧)
