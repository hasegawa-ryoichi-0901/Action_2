# 02. ゲームデザイン

## 1. プレイヤー体験

本作の中心は「プレイヤーを操作すること」と「敵との戦闘」です。

移動とカメラは軽快に反応し、攻撃には一定のコミットを持たせます。これにより、入力遅延による鈍さではなく、攻撃選択の責任によって重量感を表現します。

初期Vertical Sliceでは剣のみを使用し、移動・回避・攻撃・パリィ・死亡・再開・ボス撃破・エンディング到達までの体験を完成させます。斧と弓はVertical Slice完成後の追加Featureとします。

## 2. 入力体験

入力はEnhanced Inputを使用し、プレイヤーにアタッチされた入力Componentを`IPlayerInputComponent`で共通管理します。

`ABasePlayer`は個別入力Componentの具体型へ依存せず、Input Tag、Setup、Teardown、押下状態の共通契約を通じて管理します。Gameplay ActionとActorComponentの粒度は同一とは限らず、Gameplay Tag・GAS・責務分離を考慮して実装時に決定します。

## 3. 戦闘テンポ

- 移動：軽快
- カメラ：高い入力応答性
- 通常攻撃：武器ごとに異なるコミット
- 通常回避：位置調整と被弾回避の基本防御
- ジャスト回避：同じDodge Action中に敵攻撃とPerfect Dodge Windowが重なった場合の追加成功判定
- パリィ：剣固有の高リスク防御
- スローモーション：使用しない
- ジャスト回避成功演出：短いヒットストップとHUD表示

Dodge Input Tagは1つとし、通常回避とジャスト回避は別入力・別Actionにしません。結果通知は用途に応じたGameplay Tag / Gameplay Eventへ分離します。

## 4. Dodge

```text
[Dodge Input]
      ↓
[移動入力あり？]
   ├─ Yes → 入力方向へRoll
   └─ No  → キャラクター後方へBack Step
      ↓
[Dodge実行]
   ├─ Invincible Window
   └─ Perfect Dodge Window
      ↓
[敵Attackとの関係を評価]
   ├─ Perfect Window成立 → Perfect Dodge
   ├─ Invincibleのみ成立 → Normal Dodge / No Damage
   └─ 無敵外でHit          → Damage
```

- Invincible WindowとPerfect Dodge Windowは別々の調整値を持つ。
- 数値は開発中に調整可能とする。
- 空中Dodgeは不可。
- Dodge中も敵Collisionをすり抜けない。

## 5. ロックオン・カメラ

- 非ロックオン時は通常のYaw / Pitch Camera Lookを使用する。
- ロックオン中のみCameraが対象へ追従し、通常Camera Lookは無効化する。
- ロックオン入力を再度行うと解除する。
- 対象切替はCamera Lookとは別の左右専用入力で行う。
- ロックオン対象が死亡または無効になった場合はロックオンを自動解除する。

## 6. HP・撃破

### プレイヤー

- HPが0以下になった時点で死亡状態へ遷移する。
- 死亡状態では戦闘行動を終了するが、Camera Lookは許可する。
- Death Animation完了後にDeathDropを生成し、PlayerがCameraで確認できる状態を作ってからFade Outへ進む。

### 通常敵

- HPが0以下になった時点で撃破状態へ遷移する。
- 攻撃・移動・攻撃枠占有を終了する。
- 1体撃破ごとに強化素材とGoldを直接所持値へ加算する。

### ボス

- HPが0以下になった時点で撃破状態へ遷移する。
- Goldを直接付与する。
- 初回討伐時のみ固有収集Itemを直接Inventoryへ付与する。
- 初期Vertical SliceではBoss再戦を実装しない。

## 7. 強化ループ

```text
[通常敵撃破]
      ↓
[強化素材 + Gold獲得]
      ↓
[Checkpoint Menu]
      ↓
[Gold + 強化素材を確認]
      ↓
[武器強化]
```

Goldの用途は武器強化のみです。武器強化はCheckpointでのみ実行できます。

## 8. 死亡ループ

```text
[Player HP <= 0]
      ↓
[Death Animation]
      ↓
[以前のDeathDropがある場合は本体・内容を全消失]
      ↓
[死亡地点に新しいDeathDrop生成]
   ├─ 所持強化素材 100% を格納
   ├─ 所持Gold 70% を格納
   └─ 所持Gold 30% を消失
      ↓
[DeathDrop状態確定後Auto Save]
      ↓
[CameraでDeathDropを確認]
      ↓
[Fade Out]
      ↓
[最後のCheckpoint / 未使用ならPlayerStartへRespawn]
   ├─ HP全回復
   ├─ Stamina全回復
   ├─ Healing Item全補充
   └─ 通常敵復活
```

DeathDropを回収すると格納された強化素材とGoldを全量返却し、その直後にAuto Saveします。Save/Load後も未回収DeathDropのゲーム上の状態は復元対象とします。保存媒体・JSON構造などの永続化アーキテクチャは別設計で扱います。

## 9. CheckpointとSave

Checkpointで操作してMenuを開いた時点でAuto Saveします。Checkpoint MenuからManual Saveも可能です。

進行Auto Saveは次のタイミングに限定します。

- Checkpoint Menuを開いた時
- DeathDrop生成内容が確定した時
- DeathDrop回収が完了した時
- Boss撃破報酬の付与が完了した時

武器強化そのもの、およびStage ClearそのものではAuto Saveしません。設定データは進行データとは別に、設定変更時に保存します。

## 10. Stage Clear

Boss撃破だけでは即座にStage Clearへ遷移しません。

```text
[Boss Defeat]
      ↓
[報酬付与]
      ↓
[Auto Save]
      ↓
[クリア用エリアへ移動]
      ↓
[城 / 洞窟 / 祠等のClear Trigger Collisionへ進入]
      ↓
[Ending Sequence]
   └─ Skip可能
      ↓
[Titleへ戻る]
```

Clear Triggerの具体的な場所・見た目・Ending演出内容はMap制作時に決定しますが、上記の進行ロジックを基本仕様とします。

## 11. 将来武器Feature

### 斧

Vertical Slice完成後に、低速・高威力・高い体勢削り・高い怯み耐性を持つ武器として追加します。ガード / 受け止め、スーパーアーマー、3段通常コンボ、チャージ攻撃、回避攻撃、ジャスト回避反撃を候補とします。

### 弓

Vertical Slice完成後に、遠距離戦・肩越し照準・スタミナ消費射撃・距離減衰・弱点攻撃を持つ武器として追加します。弓による遠距離維持に対し、ボス側には専用Gap Closerを追加します。

## 12. ストーリー

初期版ではストーリー制作工数を抑えます。導入テキストは必須とし、Ending Sequenceの具体的な内容はMap・アセット確定後に決定します。

### [戻る](../README.md#ドキュメント一覧)
