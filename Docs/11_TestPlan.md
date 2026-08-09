# 11. テスト計画

## 1. テストレベル

### 単体・機能テスト

- `IPlayerInputComponent`のSetup / Teardown
- Input Tag重複検出
- 入力押下状態のStarted / Completed / Canceled同期
- 通常移動
- カメラYaw / Pitch操作
- 通常回避
- スタミナ消費・回復・息切れ遷移
- Ability発動条件
- Gameplay Tag付与・解除
- Player Health / Death
- Enemy / Boss Health / Defeat
- 体勢ダメージ・ダウン・致命攻撃
- 強化素材付与
- 武器強化
- セーブ・ロード
- AI攻撃評価

### 結合テスト

- `ABasePlayer::SetupPlayerInputComponent`と各`IPlayerInputComponent`
- UnPossessed / EndPlay / InputComponent再構築とBinding解除
- 入力バッファとGAS
- Montageと攻撃判定
- Motion Warpingとロックオン
- 通常回避とジャスト回避
- パリィと体勢値
- Player DeathとDeathDrop
- RespawnとActiveCheckpoint
- チェックポイントと敵復活
- Enemy DefeatとReward
- Boss DefeatとStage Clear
- Boss Defeat SaveとStage Clear Save

### 初期Vertical Slice通しテスト

- 新規開始から剣でボス撃破・ステージクリアまで進行できる
- 死亡を含む再攻略ができる
- Gamepadでクリアできる
- Keyboard / Mouseでクリアできる

### Post-Vertical Slice通しテスト

- 斧でクリア
- 弓でクリア
- 3武器のチェックポイント切り替え

## 2. 入力テスト

```text
TC-INPUT-001
前提 : Move / Look Input ComponentがPlayerへアタッチ済み
操作 : SetupPlayerInputComponentを実行
期待 : 各IPlayerInputComponent::Setupが1回有効化され、InputTagごとに登録される

TC-INPUT-002
前提 : 同一InputTagを持つComponentが2つ存在
操作 : SetupPlayerInputComponentを実行
期待 : 重複Componentを登録せず設定不備をLogへ記録する

TC-INPUT-003
前提 : Inputがセットアップ済み
操作 : UnPossessed後に再Possess / Setupする
期待 : 古いBindingが残らず入力が重複発火しない
```

## 3. 戦闘テスト

```text
TC-COMBAT-001
目的 : スタミナ不足時に攻撃できない
前提 : Stamina < AttackCost
操作 : 通常攻撃入力
期待 : Abilityが発動せず誤ったコスト消費もない

TC-COMBAT-002
目的 : 通常回避できる
前提 : Dodge可能状態、Perfect Dodge条件なし
操作 : 回避入力
期待 : 通常回避が実行され、Dodge Costだけ消費する

TC-COMBAT-003
目的 : ジャスト回避成功後に反撃可能
前提 : PerfectDodge Window内
操作 : 回避成功後に攻撃入力
期待 : 剣のCounter Abilityが発動する

TC-COMBAT-004
目的 : Player死亡
前提 : Healthが残りDamage以下
操作 : Damageを受ける
期待 : Health<=0でState.Deadへ1回だけ遷移し、戦闘処理を継続しない
```

## 4. 敵・ボステスト

- Enemy HP0でDefeatedへ1回だけ遷移する
- Enemy Defeat時にAIと攻撃枠を終了する
- Enemy Rewardが定義どおり付与される
- Boss HP0でAI / Abilityを停止する
- Boss Defeated EventからStage Clearへ遷移する
- 同一攻撃の過剰連続を避ける
- 距離に合わない攻撃を選択しない
- 回復中のプレイヤーを評価する
- 未反映入力を参照しない
- Phase2で攻撃候補が変化する
- AIデバッグ値と実際の選択が一致する
- 弓固有Gap CloserはPost-Vertical Sliceで確認する

## 5. Respawn・進行テスト

- Death時に現在の強化素材がDeathDropへ移る
- ActiveCheckpointからRespawnする
- Respawn時にHPと回復アイテムが仕様どおり復元される
- Respawnで通常敵が復活する
- 回収前再死亡で以前のDeathDropが消える
- Boss Defeat後にStage Clearとなる
- Boss Defeat Save / Stage Clear Saveが破損・競合しない
- ActiveCheckpoint未設定時のFallbackは仕様確定後に追加する

## 6. カメラテスト

- MouseでYaw / Pitch操作できる
- GamepadでYaw / Pitch操作できる
- 移動入力中もカメラを独立操作できる
- Input無効化時にLook Inputが意図どおり停止する
- ロックオン導入後、自由視点とTarget補正が競合しない

## 7. セーブテスト

- チェックポイント保存
- 武器強化保存
- ボス撃破保存
- ステージクリア保存
- 設定保存
- 古いSaveVersionの移行
- 保存中断時の破損対策
- 不正値の検出

## 8. 性能テスト

- 各計測地点で60fpsを確認
- ボスPhase2でフレーム時間を確認
- 長時間プレイでメモリ増加を確認
- Shippingビルドで計測
- デバッグ表示無効時の負荷を確認

### [戻る](../README.md#ドキュメント一覧)
