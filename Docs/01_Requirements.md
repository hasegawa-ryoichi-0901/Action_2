# 01. 要件定義

本ドキュメントは、Action_2で実装する機能要件・非機能要件と、初期Vertical Slice以降に追加するFuture Featureを定義します。

初期Vertical Sliceは**剣のみ**を使用して、移動・戦闘・通常敵・ボス・チェックポイント・死亡・セーブ・ステージクリアまでの一連のゲームループを完成させます。斧と弓は4～6カ月目の追加目標とします。

## 1. 機能要件

### 1.1 プレイヤー

- `FR-PLAYER-001` 三人称視点で移動できる
- `FR-PLAYER-002` ゲームパッドとキーボード・マウスで同等に操作できる
- `FR-PLAYER-003` ジャンプできる
- `FR-PLAYER-004` 空中攻撃を実行できる
- `FR-PLAYER-005` ソフトロックを使用できる
- `FR-PLAYER-006` 手動ロックオンを使用できる
- `FR-PLAYER-007` ロックオン対象を切り替えられる
- `FR-PLAYER-008` 剣、斧、弓をチェックポイントで変更できる `[Post-Vertical Slice]`
- `FR-PLAYER-009` 戦闘中は武器を変更できない `[Post-Vertical Slice]`
- `FR-PLAYER-010` 通常攻撃と強攻撃を組み合わせられる
- `FR-PLAYER-011` 攻撃と回避でスタミナを消費する
- `FR-PLAYER-012` スタミナ不足時は対象行動を実行できない
- `FR-PLAYER-013` スタミナ枯渇時に息切れ状態となる
- `FR-PLAYER-014` ジャスト回避を実行できる
- `FR-PLAYER-015` ジャスト回避後に武器固有反撃を実行できる
- `FR-PLAYER-016` 剣でパリィできる
- `FR-PLAYER-017` 斧でガードまたは受け止めを実行できる `[Post-Vertical Slice]`
- `FR-PLAYER-018` 回数制限付き回復アイテムを使用できる
- `FR-PLAYER-019` 通常回避を実行できる
- `FR-PLAYER-020` プレイヤーはHPを持ち、HPが0以下になると死亡する
- `FR-PLAYER-021` 三人称カメラを操作できる

### 1.2 敵

- `FR-ENEMY-001` 近接通常敵を実装する
- `FR-ENEMY-002` 遠距離通常敵を実装する
- `FR-ENEMY-003` 通常戦で複数の敵が同時に行動する
- `FR-ENEMY-004` 同時に近接攻撃する敵を最大2体に制限する
- `FR-ENEMY-005` 近接攻撃枠と遠距離攻撃枠を分離する
- `FR-ENEMY-006` HPと体勢値を持つ
- `FR-ENEMY-007` 体勢値が0になるとダウンする
- `FR-ENEMY-008` ダウン時に専用致命攻撃を受ける
- `FR-ENEMY-009` 敵ごとに体勢値の回復設定を変更できる
- `FR-ENEMY-010` HPが0以下になると撃破状態へ遷移する

### 1.3 ボス

- `FR-BOSS-001` 1対1で戦う
- `FR-BOSS-002` HP50%以下で第2フェーズへ移行する
- `FR-BOSS-003` プレイヤーとの距離を評価する
- `FR-BOSS-004` プレイヤーの装備武器を評価する `[Post-Vertical Slice]`
- `FR-BOSS-005` プレイヤーの回復状態を評価する
- `FR-BOSS-006` プレイヤーの残りスタミナを評価する
- `FR-BOSS-007` 直近数秒の行動と戦闘全体の傾向を評価する
- `FR-BOSS-008` 状況に応じて攻撃候補の評価値を変更する
- `FR-BOSS-009` 状況に応じて接近・離脱頻度を変更する
- `FR-BOSS-010` 状況に応じて遠距離攻撃頻度を変更する
- `FR-BOSS-011` 攻撃コンボを分岐できる
- `FR-BOSS-012` 特定攻撃後に大きな隙を持つ
- `FR-BOSS-013` ジャスト回避またはパリィ成功時に反撃可能な隙を作る
- `FR-BOSS-014` 弓で距離を取られた場合に専用接近行動を選択できる `[Post-Vertical Slice]`
- `FR-BOSS-015` HPが0以下になると撃破状態へ遷移する

### 1.4 ステージ・進行

- `FR-STAGE-001` 導入テキストを表示する
- `FR-STAGE-002` チュートリアルを実施する
- `FR-STAGE-003` チェックポイントを使用できる
- `FR-STAGE-004` チェックポイント使用時に通常敵が復活する
- `FR-STAGE-005` チェックポイントで回復アイテムを補充する
- `FR-STAGE-006` チェックポイントで武器を変更する `[Post-Vertical Slice]`
- `FR-STAGE-007` チェックポイントで武器を強化する
- `FR-STAGE-008` 死亡時に強化素材を落とす
- `FR-STAGE-009` 落とした素材を回収できる
- `FR-STAGE-010` 回収前に再死亡すると以前の素材が消滅する
- `FR-STAGE-011` ボス登場演出は工数に余裕がある場合に実装する `[Could]`
- `FR-STAGE-012` 死亡後、最後に有効化したチェックポイントから再開する
- `FR-STAGE-013` ボス撃破後にステージクリア状態へ遷移する
- `FR-STAGE-014` 戦闘報酬として武器強化に使用する強化素材を獲得できる

### 1.5 セーブ

- `FR-SAVE-001` セーブスロットは1つ
- `FR-SAVE-002` チェックポイント使用時にオートセーブする
- `FR-SAVE-003` 武器強化時にオートセーブする
- `FR-SAVE-004` ボス撃破時にオートセーブする
- `FR-SAVE-005` ステージクリア時にオートセーブする
- `FR-SAVE-006` 設定変更時に設定データを保存する
- `FR-SAVE-007` Steam CloudはSteam公開版の追加要件とする `[Post-Vertical Slice]`

## 2. 非機能要件

### 2.1 パフォーマンス

- `NFR-PERF-001` 1920x1080を基準解像度候補とする
- `NFR-PERF-002` 60fpsを最低保証目標とする
- `NFR-PERF-003` 120fpsを挑戦目標とする
- `NFR-PERF-004` RTX 3060搭載開発環境で継続的に計測する
- `NFR-PERF-005` 平均fpsだけでなくフレーム時間を確認する
- `NFR-PERF-006` Game Thread、Render Thread、GPUのボトルネックを分離する

### 2.2 保守性

- `NFR-MAINT-001` 武器、攻撃、敵、Abilityをデータ駆動で追加できる
- `NFR-MAINT-002` C++とBlueprintの責務を分離する
- `NFR-MAINT-003` プレイヤー入力コンポーネントを`IPlayerInputComponent`で抽象化し、`ABasePlayer`が個別入力コンポーネントへ直接依存しない
- `NFR-MAINT-004` Moverを検証・採用する場合でも、戦闘システムへMover固有型・固有APIの直接依存を持ち込まない
- `NFR-MAINT-005` Gameplay Tagで状態を一元管理する
- `NFR-MAINT-006` Tickの使用を必要なクラスに限定する

### 2.3 品質

- `NFR-QUALITY-001` 進行不能バグを0件にする
- `NFR-QUALITY-002` 既知のクラッシュを0件にする
- `NFR-QUALITY-003` ゲームパッドとキーボード・マウスの両方でクリア確認を行う
- `NFR-QUALITY-004` セーブ破損時の挙動を確認する
- `NFR-QUALITY-005` 長時間プレイでメモリ増加を確認する
- `NFR-QUALITY-006` Shippingビルドで最終確認を行う

## 3. Future Feature要件

初期Vertical Sliceでは実装せず、剣によるVertical Slice完成後の4～6カ月目を目安に追加します。

### 3.1 斧

既存の`FR-PLAYER-008`、`FR-PLAYER-009`、`FR-PLAYER-017`をPost-Vertical Sliceで有効化します。加えて次をFuture Feature候補とします。

- `FEATURE-AXE-001` 斧で3段の通常攻撃コンボを実行できる
- `FEATURE-AXE-002` 斧でチャージ攻撃を実行できる
- `FEATURE-AXE-003` 斧で回避攻撃を実行できる
- `FEATURE-AXE-004` 斧の指定攻撃にスーパーアーマー特性を設定できる
- `FEATURE-AXE-005` 斧のジャスト回避後に高威力の武器固有反撃を実行できる

ガード方式を「ガード」または「受け止め」のどちらにするか、ガードブレイク、ガード中のスタミナ消費仕様は`Docs/15_OpenQuestions.md`で確定します。

### 3.2 弓

既存の`FR-PLAYER-008`、`FR-PLAYER-009`、`FR-BOSS-004`、`FR-BOSS-014`をPost-Vertical Sliceで有効化します。加えて次をFuture Feature候補とします。

- `FEATURE-BOW-001` 弓で遠距離射撃を実行できる
- `FEATURE-BOW-002` 弓を構えて肩越し照準を使用できる
- `FEATURE-BOW-003` 通常射撃は弾数を消費せず、射撃ごとにスタミナを消費する
- `FEATURE-BOW-004` 射撃距離に応じてダメージを減衰できる
- `FEATURE-BOW-005` 敵の弱点部位へ命中した場合に追加ダメージを与えられる
- `FEATURE-BOW-006` 弓のジャスト回避後に武器固有反撃を実行できる

通常射撃をProjectileとするか、特殊高速射撃へLine Traceを採用するかなどの実装方式は`Docs/15_OpenQuestions.md`のプロトタイプで決定します。

## 4. 初期Vertical Slice対象外

初期Vertical Sliceでは次を対象外とします。

- 斧の実装
- 弓の実装
- 複数武器の切り替え
- オンラインマルチプレイ
- ネットワーク同期
- Epic Online Services連携
- Steam Cloud
- 複数ロックオン部位
- リアルタイム武器切り替え
- 空中コンボ
- 大規模なストーリー
- フルボイス

### [戻る](../README.md#ドキュメント一覧)
