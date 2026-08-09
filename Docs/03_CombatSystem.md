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

初期Vertical Sliceは剣のみを対象とします。斧のGuard / Receiveと弓固有処理はPost-Vertical Slice Featureです。

状態はGameplay Tagで管理します。

```text
State.Action.Attacking
State.Action.Dodging
State.Action.Jumping
State.Action.Parrying
State.Action.Guarding
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
    |
    | 一部の軽攻撃のみ回避キャンセル候補
    v
[Commitment]
    |
    | 原則キャンセル不可
    v
[Active]
    |
    | 攻撃判定有効
    v
[Recovery]
    |
    | 後半で次入力を受付
    v
[Neutral / Next Combo]
```

キャンセル可能期間はAnim Notify StateまたはGameplay Tagで管理します。

```text
Window.Cancel.Dodge
Window.Combo.AcceptInput
Window.Hitbox.Active
Window.Counter.Available
Window.FatalAttack.Available
```

## 3. 入力と入力バッファ

Enhanced InputのBindingとライフサイクル管理は`IPlayerInputComponent`を入口とします。Move / Lookのような直接操作は各入力Componentがゲームプレイ処理へ接続し、攻撃・回避・パリィ等の戦闘入力はGAS入力処理へ接続します。

入力バッファ対象：

- 通常攻撃
- 強攻撃
- 回避
- ジャンプ
- パリィ
- 武器スキル
- ジャスト回避反撃
- Post-Vertical SliceではGuard等を追加

優先順位候補：

```text
死亡・強制リアクション
        ↓
ジャスト回避反撃
        ↓
回避
        ↓
パリィ
        ↓
武器スキル
        ↓
強攻撃
        ↓
通常攻撃
```

## 4. 通常回避

通常回避は防御と位置調整の基本行動です。

```text
[Dodge Input]
      |
      v
[実行条件 / Stamina確認]
      |
      +-- NG --> [Reject / Buffer]
      |
      v
[State.Action.Dodging]
      |
      v
[回避移動・Animation]
      |
      +--> 敵攻撃とPerfect Dodge Windowが重なる
      |        ↓
      |   [Perfect Dodge Success]
      |
      +--> 条件を満たさない
               ↓
          [Normal Dodge]
      |
      v
[Recovery / Neutral]
```

- 通常回避とジャスト回避は同じ回避入力から開始する。
- ジャスト回避条件を満たさなくても通常回避として成立可能とする。
- 回避はスタミナを消費する。
- 死亡・ダウン・息切れ等の禁止状態では開始できない。
- 回避方向、無敵時間、移動距離、空中回避可否、敵をすり抜けるかは実装Issue開始前に確定する。

## 5. スタミナ

### 消費対象

- 通常攻撃
- 強攻撃
- チャージ攻撃
- 回避
- ジャスト回避反撃
- パリィ
- Post-Vertical SliceのGuard / 武器スキル / 弓射撃

### 回復

- 最後のスタミナ消費から一定時間後に回復を開始する。
- 回復開始遅延、回復量、息切れ解除閾値はデータで設定する。

### 枯渇

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

## 6. ジャスト回避

### 成功条件

- 回避Abilityが有効。
- 敵攻撃判定とジャスト回避受付時間が重なる。
- プレイヤーが死亡・ダウン・息切れ中ではない。

### 成功処理

```text
[Enemy Attack]
      ↓
[Dodge Window Check]
      +-- Failed --> [Normal Dodge / Hit]
      ↓
[Perfect Dodge Success]
      +--> 短いヒットストップ
      +--> HUDカウンター表示
      +--> Counter Gameplay Tag付与
      +--> 対象敵を記録
      ↓
[攻撃入力待ち]
      +-- 入力なし・時間切れ --> [通常状態]
      ↓
[Sword Counter]
```

- スローモーションは発生させない。
- 反撃は強制しない。
- 有効時間中に攻撃入力した場合だけ専用反撃へ派生する。
- 反撃はスタミナを消費する。
- 有効時間は武器データで設定する。
- 反撃時に対象敵へ向きを自動補正する。

## 7. パリィ

- 初期Vertical Sliceでは剣固有。
- 攻撃属性ごとにパリィ可否を設定する。
- 失敗時に専用硬直を発生させる。
- 成功時に敵の体勢値を大きく削る。
- 体勢値が0になった場合のみダウンと致命攻撃へ接続する。

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
[実行中Ability / 入力 / 一時状態を終了]
   ↓
[Death / Respawn System]
```

死亡状態への遷移は1回だけ行い、死亡後の素材DropとCheckpoint Respawnは`Docs/09_SaveCheckpointDeath.md`へ委譲します。

### 通常敵

- HPが0以下になったら撃破状態へ1回だけ遷移する。
- 撃破時に攻撃Ability、AI移動、攻撃枠を終了・解放する。
- 報酬はEnemy DefinitionのReward Definition等のデータから付与する設計候補とする。

### ボス

- HPが0以下になったら撃破状態へ1回だけ遷移する。
- 撃破後はAI評価と攻撃Abilityを停止する。
- Boss Defeated Eventをステージ進行とセーブへ通知する。

## 9. 体勢値

### 敵

- HPとは独立して保持する。
- 攻撃ごとに体勢ダメージを設定する。
- 敵データごとに自然回復の有無と回復速度を設定する。
- 0になるとダウンする。
- ダウン時に正面・背後の両方から致命攻撃可能とする。
- HP0の撃破状態は体勢ダウンより優先する。

### プレイヤー

独立した体勢ゲージは基本的に使用せず、武器に応じたStaggerResistanceを反映します。初期Vertical Sliceでは剣の値を使用し、斧・弓差分はPost-Vertical Sliceで追加します。

## 10. 回復

- 回数制限付き回復アイテム。
- チェックポイントで補充。
- 使用中に攻撃を受けると中断。
- ボスAIは回復Abilityの確定済み発動状態を評価可能。
- 回復量、使用回数、使用時間は未確定データとする。

### [戻る](../README.md#ドキュメント一覧)
