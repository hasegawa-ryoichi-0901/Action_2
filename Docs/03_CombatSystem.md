# 03. 戦闘システム

## 1. 戦闘状態

```text
[Neutral]
    |
    +--> [Attack]
    |
    +--> [Dodge]
    |
    +--> [Jump]
    |
    +--> [Parry / Guard]
    |
    +--> [Heal]
    |
    +--> [Exhausted]
    |
    +--> [Hit / Stagger]
    |
    +--> [Dead]
```

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
    | 攻撃準備
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

## 3. 入力バッファ

### 対象入力

- 通常攻撃
- 強攻撃
- 回避
- ジャンプ
- パリィ
- ガード
- 武器スキル
- ジャスト回避反撃

### 優先順位候補

```text
死亡・強制リアクション
        |
        v
ジャスト回避反撃
        |
        v
回避
        |
        v
パリィ / ガード
        |
        v
武器スキル
        |
        v
強攻撃
        |
        v
通常攻撃
```

## 4. スタミナ

### 消費対象

- 通常攻撃
- 強攻撃
- チャージ攻撃
- 回避
- ジャスト回避反撃
- パリィ
- ガード
- 武器スキル
- 弓射撃

### 回復

- 最後のスタミナ消費から一定時間後に回復を開始する
- 回復開始遅延、回復量、息切れ解除閾値はデータで設定する

### 枯渇

```text
Stamina <= 0
     |
     v
[State.Action.Exhausted]
     |
     +--> 通常移動       : 可能
     +--> カメラ操作     : 可能
     +--> ロックオン解除 : 可能
     +--> ジャンプ       : 不可
     +--> 攻撃           : 不可
     +--> 回避           : 不可
     +--> ガード         : 不可
     +--> パリィ         : 不可
     |
     v
Stamina >= ExhaustedRecoveryThreshold
     |
     v
[Neutral]
```

## 5. ジャスト回避

### 成功条件

- 回避Abilityが有効
- 敵攻撃の判定とジャスト回避受付時間が重なる
- プレイヤーが死亡・ダウン・息切れ中ではない

### 成功処理

```text
[Enemy Attack]
      |
      v
[Dodge Window Check]
      |
      +-- Failed --> [Normal Dodge / Hit]
      |
      v
[Perfect Dodge Success]
      |
      +--> 短いヒットストップ
      +--> HUDカウンター表示
      +--> Counter Gameplay Tag付与
      +--> 対象敵を記録
      |
      v
[攻撃入力待ち]
      |
      +-- 入力なし・時間切れ --> [通常状態]
      |
      v
[Weapon Specific Counter]
```

### 仕様

- スローモーションは発生させない
- 反撃は強制しない
- 有効時間中に攻撃入力した場合だけ専用反撃へ派生する
- 反撃はスタミナを消費する
- 有効時間は武器データで設定する
- 反撃時に対象敵へ向きを自動補正する

## 6. パリィ

- 剣固有
- 攻撃属性ごとにパリィ可否を設定する
- 失敗時に専用硬直を発生させる
- 成功時に敵の体勢値を大きく削る
- 体勢値が0になった場合のみダウンと致命攻撃へ接続する

```text
[Parry Input]
      |
      v
[Parry Window]
      |
      +-- Parry不可攻撃 --> [失敗硬直 / 被弾]
      |
      +-- タイミング失敗 --> [失敗硬直 / 被弾]
      |
      v
[Parry Success]
      |
      v
[Posture Damage]
      |
      +-- Posture > 0 --> [敵リアクション]
      |
      v
[Enemy Down]
      |
      v
[Fatal Attack Available]
```

## 7. 体勢値

### 敵

- HPとは独立して保持する
- 攻撃ごとに体勢ダメージを設定する
- 敵データごとに自然回復の有無と回復速度を設定する
- 0になるとダウンする
- ダウン時に正面・背後の両方から致命攻撃可能

### プレイヤー

独立した体勢ゲージは持たず、装備武器に応じた怯み耐性を持たせます。

- 剣：標準
- 斧：高い
- 弓：低い

## 8. 回復

- 回数制限付き回復アイテム
- チェックポイントで補充
- 使用中に攻撃を受けると中断
- ボスAIは回復Abilityの確定済み発動状態を評価可能
- 回復量、使用回数、使用時間は未確定データとする
