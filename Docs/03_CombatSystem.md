# 03. 戦闘システム

## 1. 戦闘状態

```text
[Neutral]
    +--> [Attack]
    +--> [Dodge]
    +--> [Jump]
    +--> [Parry]
    +--> [Heal]
    +--> [Exhausted]
    +--> [Hit / Stagger]
    +--> [Dead]
```

初期Vertical Sliceは剣のみを対象とします。状態はGameplay Tagで管理します。

```text
State.Action.Attacking
State.Action.Dodging
State.Action.Jumping
State.Action.Parrying
State.Action.Healing
State.Action.Exhausted
State.Reaction.Hit
State.Reaction.Staggered
State.Reaction.Downed
State.Dead
```

## 2. 攻撃フェーズ

```text
[Startup]
    ↓
[Commitment]
    ↓
[Active]
    ↓
[Recovery]
    ↓
[Neutral / Next Combo]
```

キャンセル・Combo・Hitbox等の受付期間はAnim Notify StateまたはGameplay Tagで表現します。

```text
Window.Cancel.Dodge
Window.Combo.AcceptInput
Window.Hitbox.Active
Window.Counter.Available
Window.FatalAttack.Available
```

## 3. Input / Gameplay Action / Issueの境界

Enhanced InputのBindingとライフサイクル管理は`IPlayerInputComponent`を入口とします。Gameplay Actionの単位とActorComponentの単位は同一と断定しません。

- Dodgeは1 Actionで、Normal Dodge / Perfect Dodgeは結果分岐。
- Light Attackは1 Action。
- Heavy AttackはLight Attackとは別Action。
- Combo AttackはLight / Heavyの単体実装とは別の統合Action / Featureとして扱う。
- Gameplay Tag、GAS、責務、ライフサイクルを考慮してComponent構成を決定する。

## 4. Dodge

Dodge Input Tagは1つです。通常回避とジャスト回避で別Input Actionを作りません。

```text
[Dodge Input]
      ↓
[実行条件 / Stamina確認]
      +-- NG --> [Reject / Buffer]
      ↓
[State.Action.Dodging]
      ↓
[移動入力あり？]
   ├─ Yes → 入力方向へRoll
   └─ No  → 後方へBack Step
      ↓
[Invincible Window]
[Perfect Dodge Window]
      ↓
[Enemy Attackとの関係を評価]
   ├─ Perfect Window成立 → Perfect Dodge Result
   ├─ Invincibleのみ成立 → Normal Dodge / No Damage
   └─ 無敵外でHit          → Damage
      ↓
[Recovery / Neutral]
```

確定事項：

- Invincible WindowとPerfect Dodge Windowは別々の調整値。
- 具体的な時間は開発中に調整可能とする。
- 空中Dodge不可。
- Dodge中に敵Collisionをすり抜けない。
- Normal / Perfectの結果通知は、用途に応じて別のGameplay Tag / Gameplay Eventを使用できる。
- Perfect Dodgeは別ActionではなくDodge Actionの結果。

## 5. スタミナ

消費対象：通常攻撃、強攻撃、回避、ジャスト回避後の反撃、パリィ等。最後の消費から一定時間後に回復を開始します。

```text
Stamina <= 0
     ↓
[State.Action.Exhausted]
     +--> 通常移動       : 可能
     +--> カメラ操作     : 可能
     +--> ロックオン解除 : 可能
     +--> ジャンプ       : 不可
     +--> 攻撃           : 不可
     +--> 回避           : 不可
     +--> パリィ         : 不可
     ↓
Stamina >= ExhaustedRecoveryThreshold
     ↓
[Neutral]
```

## 6. Perfect Dodge Result

成功条件は、Dodge Actionが有効で、敵攻撃判定とPerfect Dodge Windowが重なることです。

```text
[Perfect Dodge Result]
      +--> 短いHit Stop
      +--> HUD通知
      +--> 結果通知Tag / Event
      +--> 対象敵を記録
      +--> Counter受付状態
```

- スローモーションは使用しない。
- 反撃は強制しない。
- Counter受付中の攻撃入力で剣固有Counterへ派生できる。

## 7. パリィ

- 初期Vertical Sliceでは剣固有。
- 攻撃属性ごとにパリィ可否を設定する。
- 失敗時に専用硬直を発生させる。
- 成功時に敵の体勢値を大きく削る。
- 体勢値0時のみDown / Fatal Attackへ接続する。

## 8. HP・死亡・撃破

### プレイヤー

```text
[Damage]
   ↓
Health更新
   +-- Health > 0 --> [継続]
   ↓
Health <= 0
   ↓
[State.Dead]
   ↓
[実行中Combat処理終了]
   ↓
[Death / DeathDrop / Respawn System]
```

死亡後のDeathDrop・Auto Save・Respawnは`Docs/09_SaveCheckpointDeath.md`へ委譲します。

### 通常敵

- HP0以下で撃破状態へ1回だけ遷移する。
- 攻撃Ability、AI移動、攻撃枠を終了・解放する。
- 1体撃破ごとに強化素材とGoldを直接所持値へ付与する。
- 報酬量はゲームデータから取得する。マスターデータ読込方式そのものは別設計とする。

### ボス

- HP0以下で撃破状態へ1回だけ遷移する。
- AI評価と攻撃Abilityを停止する。
- Goldを付与する。
- 初回討伐時のみ固有収集Itemを直接Inventoryへ付与する。
- 報酬付与完了後にBoss DefeatedのSave要求を発行する。
- 初期Vertical SliceではBoss再戦を実装しない。

## 9. 体勢値

敵はHPとは独立して体勢値を持ち、0でDownします。HP0による撃破状態は体勢Downより優先します。

## 10. 回復

- 回数制限付き回復Item。
- Checkpointで補充。
- 使用中に攻撃を受けると中断。
- ボスAIは回復Abilityの確定済み発動状態を評価可能。

### [戻る](../README.md#ドキュメント一覧)
