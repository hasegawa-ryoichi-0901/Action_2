# 12. 開発スケジュール

## 1. 前提

- 週25～30時間
- 6カ月～1年
- 転職活動と並行
- 最初の企業提出は開発開始から3カ月後
- 途中状態でも提出可能にする
- 3カ月時点ではゲーム全体より、剣とボス1体による戦闘品質を優先する
- **初期Vertical Sliceは剣のみで完成させる**
- 斧・弓は初期Vertical SliceのBlockerにせず、4～6カ月目のPost-Vertical Slice Featureとする

## 2. 0～1カ月

### 目的

プレイヤー操作と戦闘基盤の成立を確認する。

### 作業

- プロジェクト初期設定
- Git / Git LFS
- コーディング規約
- Enhanced Input
- `IPlayerInputComponent`入力基盤
- Move / Look / Camera
- PlayerState ASC
- AttributeSet
- Gameplay Tag
- 剣通常攻撃
- 通常回避
- スタミナ
- 入力バッファ
- ロックオン
- テストマップ
- Moverは必要性を検証する候補とし、初期開発を停止させない

### 完了条件

- 剣で敵ダミーを攻撃できる
- 通常回避できる
- 攻撃と回避でスタミナを消費する
- GamepadとKeyboard / Mouseで移動・カメラ・戦闘操作できる
- 入力再セットアップ時にBindingが重複しない

## 3. 2カ月目

### 作業

- 剣4段コンボ
- 強攻撃分岐
- 空中攻撃
- ジャスト回避
- パリィ
- Player HP / Death
- 敵HP / Defeat
- 体勢値
- ダウン
- 致命攻撃
- 近接敵
- 遠距離敵
- Behavior Tree
- 集団戦管理
- チェックポイント
- ActiveCheckpoint Respawn
- DeathDrop
- 強化素材報酬
- 回復アイテム

### 完了条件

- 通常戦の基本ループが成立する
- Player Death → DeathDrop → Checkpoint Respawnが成立する
- 敵撃破から強化素材を獲得できる
- ジャスト回避とパリィから反撃できる
- 近接2体の攻撃枠が機能する

## 4. 3カ月目 — 初期Vertical Slice

### 作業

- ボス1体
- Boss HP / Defeat
- StateTree
- C++攻撃評価
- Phase1 / Phase2
- 行動履歴
- AIデバッグ表示
- Boss Defeat → Stage Clear
- 導入テキスト
- チュートリアル
- セーブ
- 基本UI
- パフォーマンス初回計測
- 技術資料初版
- プレイ動画

### 提出版完了条件

- タイトルから剣でボス撃破・ステージクリアまで進行可能
- 死亡してもActiveCheckpointから再攻略可能
- ボス1体と高品質な1対1戦闘ができる
- 60fps目標を確認できる
- 実行ビルドを提出できる
- READMEと主要設計資料が完成している

## 5. 4～6カ月 — Post-Vertical Slice Feature

- 斧
- 弓
- チェックポイントでの武器変更
- 斧Guard / Receive
- 斧Super Armor候補
- 弓肩越し照準
- 弓射撃 / 距離減衰 / 弱点
- Bow Gap Closerを含むBoss武器適応
- 3武器でボス攻略
- 敵・ステージ追加
- VFX・SE調整
- アニメーション改善
- Control Rig / IK / Pose Warping等の必要箇所への導入
- 最適化
- テスト拡充

## 6. 7～12カ月

- 最大3ステージ
- 最大3ボス
- Steam体験版
- Steam Cloud
- ストア用動画
- スクリーンショット
- ローカライズ
- 第三者テスト
- Shippingビルド

### [戻る](../README.md#ドキュメント一覧)
