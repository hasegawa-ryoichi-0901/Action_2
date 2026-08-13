# 12. 開発スケジュール

## 1. 前提

- 週25～30時間
- 6カ月～1年
- 転職活動と並行
- 最初の企業提出は開発開始から3カ月後
- 途中状態でも提出可能にする
- 3カ月時点ではゲーム全体より、剣とボス1体による戦闘品質を優先する
- **初期プレイアブル版は剣のみで完成させる**
- 斧・弓は初期プレイアブル版完成に必須とせず、4～6カ月目のPost-VS Featureとする
- Issue番号順ではなく、`Docs/ImplementationRoadmap.md`の依存関係順で実装する
- Gameplay Action / Systemの親IssueはTracking用途とし、実装Issueは原則`1 Issue = 1 PR`とする

## 2. 0～1カ月 — Foundation / Sword Core

### 目的

Player操作、GAS共有基盤、Inventory / Save / Data境界、Sword Combatの成立を確認する。

### 依存順

1. Player Move / Look / Camera / Jump
2. Player ASC / GameplayTag / Stamina / Damage共有基盤
3. `#152` Exhausted State
4. `#153` Player Inventory基盤
5. `#154` JSON Save Architecture
6. `#155` CSV / Master Data読込Architecture
7. Light Attack
8. Heavy Attack
9. Combo Attack
10. Dodge / Perfect Dodge
11. Sword Counter / Parry / Air Attack
12. Manual LockOn / Target Switch / Soft Lock
13. Performance計測環境を準備

### 完了条件

- SwordでEnemy DummyをAttackできる
- Light / Heavy / Comboが成立する
- Normal DodgeとPerfect Dodgeを1つのDodge Actionとして実行できる
- AttackとDodgeでStaminaを消費する
- Stamina枯渇時にExhaustedへ遷移・解除できる
- Player InventoryをReward / DeathDrop / Upgradeから共通利用できる
- Gameplay SystemがJSON / CSVの具体実装へ直接依存しない
- LockOn / Target Switch / Soft Lockが動作する
- GamepadとKeyboard / Mouseで移動・Camera・Combat操作できる
- 入力再Setup時にBindingが重複しない

## 3. 2カ月目 — Normal Battle / Progression

### 依存順

1. Enemy Attack Coordinator / Health / Posture
2. Melee / Ranged Enemy
3. Down / Fatal Attack / Posture Recovery
4. Enemy Defeat / Material + Gold Reward
5. Player Health / Hit / Stagger / Down / Death
6. Checkpoint / ActiveCheckpoint / Menu / Save
7. Healing Item
8. DeathDrop / Auto Save / Respawn
9. Gold + MaterialによるWeapon Upgrade

### 完了条件

- Normal Battleの基本Loopが成立する
- Player Death → DeathDrop → Checkpoint Respawnが成立する
- DeathDropにUpgrade Material 100% / Gold 100%が格納される
- 再死亡時に未回収DeathDrop本体と中身が消滅する
- Enemy撃破からMaterial / GoldをPlayer Inventoryへ取得できる
- CheckpointでGold + Materialを消費してWeapon Upgradeできる
- Melee Attack Slot最大2体が機能する
- Healing ItemはHeal Animation開始直後に消費され、その後の被弾中断では返却されない

## 4. 3カ月目 — Boss / Stage Clear / 初期プレイアブル版完成

### 依存順

1. Boss 1対1 / Phase2
2. Combat Context収集
3. Attack Candidate Score
4. Approach / Retreat / Ranged Attack Frequency適応
5. Boss Combo Branch
6. Recovery / Counter Window
7. Boss Defeat
8. Gold + 初回固有収集Item Reward
9. Boss Reward後Auto Save
10. Tutorial Text / Tutorial
11. Clear Trigger
12. Skippable Ending / Title遷移
13. Corrupt Save / Performance / Stability / Shipping確認

### 提出版完了条件

- TitleからSwordでBoss撃破・Stage Clearまで進行可能
- DeathしてもActiveCheckpointから再攻略可能
- Boss1体と高品質な1対1Combatができる
- Boss撃破後はReward / Auto Saveまで完了してからClear Areaへ進行できる
- Clear Trigger → Ending → Titleまで完走できる
- Corrupt Saveを削除してNew Game可能状態へ戻れる
- 60fps最低保証目標を確認できる
- 実行Buildを提出できる
- READMEと主要設計資料が完成している

## 5. 4～6カ月 — Post-VS Feature

- Axe
- Bow
- CheckpointでのWeapon Change
- Axe Guard / Receive
- Axe Super Armor候補
- Bow肩越しAim
- Bow Shooting / Distance Falloff / Weak Point
- Bow Gap Closerを含むBoss Weapon Adaptation
- 3武器でBoss攻略
- Enemy / Stage追加
- VFX / SE調整
- Animation改善
- Control Rig / IK / Pose Warping等の必要箇所への導入
- 最適化
- Test拡充

## 6. 7～12カ月

- 最大3Stage
- 最大3Boss
- Steam Demo
- Steam Cloud
- Store動画
- Screenshot
- Localization
- 第三者Test
- Shipping Build

## 7. Issue単位の実装順

GitHub Projectへ配置するIssueの具体的な依存順・Tracking Parent・Phase / Milestone割当は次を正とする。

- [ImplementationRoadmap.md](ImplementationRoadmap.md)

### [戻る](../README.md#ドキュメント一覧)
