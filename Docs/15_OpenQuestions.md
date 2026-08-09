# 15. 未確定事項・プロトタイプ検証項目

本ドキュメントは、要件自体は確定しているが実装Issue開始前に決める必要がある仕様、またはPost-Vertical Sliceのプロトタイプ項目を管理します。

## 1. 初期Vertical Sliceで実装前に確定する項目

### 1.1 通常回避 `FR-PLAYER-019`

- 回避方向：移動入力基準 / キャラクター向き基準
- 移動入力なしで回避した場合の方向
- 通常回避の無敵時間の有無と受付区間
- 回避移動距離・時間
- 空中で回避可能か
- 回避中に敵Collisionをすり抜けるか
- 回避Animation：ステップ / ローリング / Asset依存

### 1.2 Player HP・死亡 `FR-PLAYER-020`

- Health<=0確定後、Death Animation完了を待ってRespawnするか固定時間で遷移するか
- 死亡時に停止・CancelするAbility / Animation / Interactionの共通ルール
- Death状態中のCamera操作可否

### 1.3 Checkpoint Respawn `FR-STAGE-012`

- ActiveCheckpointが未設定の場合のFallback Spawn
- Respawn時にStaminaを全回復するか
- Respawn直後の入力再有効化タイミング
- DeathDrop生成 / Respawn時にAutoSaveするか

### 1.4 Enemy Defeat `FR-ENEMY-010`

- Defeat確定後にActorを即Destroyするか、Death Animation完了後にDestroy / Disableするか
- Collision / Targeting対象から外すタイミング
- Reward付与タイミング

### 1.5 Boss Defeat / Stage Clear `FR-BOSS-015` `FR-STAGE-013`

- Boss Defeat演出完了を待ってStage Clearへ遷移するか
- Boss Defeat SaveとStage Clear Saveが連続した場合のSave Request集約 / 直列化方式
- Stage Clear後のUI・操作ロック・終了遷移

### 1.6 強化素材獲得 `FR-STAGE-014`

- 通常敵1体ごとに付与するか、Encounter完了報酬とするか
- Bossからも強化素材を付与するか
- 固定量 / ランダム量
- Reward Definitionのデータ構造と付与タイミング

### 1.7 カメラ操作 `FR-PLAYER-021`

- Mouse / Gamepadの感度値と設定場所
- Pitch Clamp
- Y軸反転設定を初期Vertical Sliceに含めるか
- LockOn中の手動入力と自動補正の優先順位
- Camera Collision / SpringArmの最終調整値

### 1.8 Combat Input Componentの粒度

`IPlayerInputComponent`を入力基盤の正とすることは確定しています。一方、Combat入力追加時に以下を決定します。

- Light / Heavy / Dodge / Parry等を1Action = 1 ActorComponentとするか
- 複数のCombat InputActionを1つのComponentへ集約するか
- 集約する場合、現在1つの`FTaggedInputAction`を返すInterfaceを拡張するか

入力Component数の増加と責務集約のバランスを比較し、Combat入力の最初のIssue作成前に決定します。

## 2. 数値調整

- 回復アイテム所持数
- 回復量
- 回復時間
- スタミナ最大値
- スタミナ回復開始遅延
- 息切れ解除閾値
- ジャスト回避受付時間
- 反撃受付時間
- パリィ受付時間
- パリィ失敗硬直
- ロックオン最大距離
- 遮蔽による解除時間
- 遠距離攻撃枠の最大数
- 通常敵最大同時出現数
- 体勢値回復速度
- ボス各攻撃の評価値

数値はData Asset等で調整可能にし、設計上必要な範囲・制約のみ実装Issue開始時に決定します。

## 3. Mover

現行実装はCharacterMovementを使用します。Moverは初期Vertical Sliceの必須依存ではありません。

Moverを評価する場合は次を比較します。

```text
入力応答性
Root Motion連携
Motion Warping連携
ジャンプ / 回避
斜面 / 段差
パフォーマンス
デバッグ容易性
Shippingビルド安定性
```

Mover採用の具体的メリットが確認されるまで、`IMovementDriver`や`UMovementAdapterComponent`等の抽象化を先行追加しません。採用する場合もCombat層へMover固有型・APIを直接依存させません。

## 4. 斧 — Post-Vertical Slice

- ガードか受け止めか
- ガード中のスタミナ消費
- ガードブレイク
- スーパーアーマーの対象攻撃
- Heavy Branchの具体コンボ
- 各攻撃の速度・威力・体勢削り

## 5. 弓 — Post-Vertical Slice

- 通常攻撃を3段コンボにするか連続射撃にするか
- ProjectileとLine Traceの最終分担
- 弱点倍率
- 弱点判定の表現
- 肩越し照準時の移動速度
- 弓の距離減衰曲線
- Bow Counterの具体挙動

## 6. アセット依存

- 世界観：現代都市 / 近未来 / ファンタジー
- 最初のボス：人型 / 獣型 / 大型怪物
- 回避モーション
- ボス登場演出

## 7. アニメーション機能

使用候補：

- Animation Blueprint
- Animation Montage
- Motion Warping
- Root Motion
- Control Rig
- IK Retargeter
- Full Body IK
- Pose Warping

各機能について「何の問題を解決するために採用したか」を記録します。

## 8. オンライン / Steam

Vertical Sliceではオンライン、ネットワーク同期、EOS、Steam Cloudを対象外とします。

Steam公開版では次を再評価します。

- ストア価格
- 体験版の範囲
- Steam Cloud方式
- 実績
- 対応言語
- ストア素材

### [戻る](../README.md#ドキュメント一覧)
