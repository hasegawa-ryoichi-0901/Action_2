# 12. 開発スケジュール

## 1. 前提

- 週25～30時間
- 6カ月～1年
- 転職活動と並行
- 最初の企業提出は開発開始から3カ月後
- 途中状態でも提出可能にする
- 3カ月時点ではゲーム全体より、剣とボス1体による戦闘品質を優先する
- **初期Vertical Sliceは剣のみで完成させる**
- 斧・弓は初期Vertical Slice完成に必須とせず、4～6カ月目のPost-Vertical Slice Featureとする
- Issue番号順ではなく、`Docs/ImplementationRoadmap.md`の依存関係順で実装する
- Gameplay Action / Systemの親IssueはTracking用途とし、実装Issueは原則`1 Issue = 1 PR`とする

## 2. 0～1カ月 — Foundation / Sword Core

### 目的

プレイヤー操作、GAS共有基盤、剣戦闘の成立を確認する。

### 依存順

1. Player Move / Look / Camera / Jump
2. Player ASC / GameplayTag / Stamina / Damage共有基盤
3. Light Attack
4. Heavy Attack
5. Combo Attack
6. Dodge / Perfect Dodge
7. Sword Counter / Parry / Air Attack
8. Manual LockOn / Target Switch / Soft Lock
9. Performance計測環境を準備

### 完了条件

- 剣で敵ダミーを攻撃できる
- Light / Heavy / Comboが成立する
- 通常回避とPerfect Dodgeを1つのDodge Actionとして実行できる
- 攻撃と回避でスタミナを消費する
- LockOn / Target Switch / Soft Lockが動作する
- GamepadとKeyboard / Mouseで移動・カメラ・戦闘操作できる
- 入力再セットアップ時にBindingが重複しない

## 3. 2カ月目 — Normal Battle / Progression

### 依存順

1. Enemy Attack Coordinator / Health / Posture
2. Melee / Ranged Enemy
3. Down / Fatal Attack / Posture Recovery
4. Enemy Defeat / Material + Gold Reward
5. Player Health / Death State
6. Checkpoint / ActiveCheckpoint / Menu / Save
7. Healing Item
8. DeathDrop / Auto Save / Respawn
9. Gold + MaterialによるWeapon Upgrade

### 完了条件

- 通常戦の基本ループが成立する
- Player Death → DeathDrop → Checkpoint Respawnが成立する
- DeathDropにMaterial 100% / Gold 70%が格納される
- 再死亡時に未回収DeathDrop本体と中身が消滅する
- Enemy撃破からMaterial / Goldを取得できる
- CheckpointでGold + Materialを消費してWeapon Upgradeできる
- 近接2体の攻撃枠が機能する

## 4. 3カ月目 — Boss Vertical Slice / Stage Clear

### 依存順

1. Boss 1対1 / Phase2
2. Combat Context収集
3. Attack Candidate Score
4. 接近・離脱 / 遠距離攻撃頻度適応
5. Boss Combo Branch
6. Recovery / Counter Window
7. Boss Defeat
8. Gold + 初回固有収集Item Reward
9. Boss Reward後Auto Save
10. Intro Text / Tutorial
11. Clear Trigger
12. Skippable Ending / Title遷移
13. Performance / Stability / Shipping確認

### 提出版完了条件

- タイトルから剣でボス撃破・ステージクリアまで進行可能
- 死亡してもActiveCheckpointから再攻略可能
- ボス1体と高品質な1対1戦闘ができる
- Boss撃破後はReward / Auto Saveまで完了してからClear Areaへ進行できる
- Clear Trigger → Ending → Titleまで完走できる
- 60fps最低保証目標を確認できる
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

## 7. Issue単位の実装順

GitHub Projectへ配置するIssueの具体的な依存順・Tracking Parent・Phase / Milestone割当は次を正とする。

- `Docs/ImplementationRoadmap.md`

### [戻る](../README.md#ドキュメント一覧)
