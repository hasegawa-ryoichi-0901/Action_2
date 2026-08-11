# Implementation Roadmap

本ドキュメントは、GitHub IssueをIssue番号順ではなく**実装依存関係順**で進めるためのロードマップです。

## 1. 運用ルール

- Gameplay Action / Systemの親Issueは進捗集約用とし、原則PRを作成しない。
- 実装Issueは原則 `1 Issue = 1 PR` とする。
- 依存先Issueが未完了の場合、依存元Issueを先に実装しない。
- 共有基盤は後続Actionで重複実装せず、既存Issueを依存先として参照する。
- 横断的なMaintainability / Quality Issueは、単独機能の完成ではなく各PhaseのReview Gateとして扱う。
- `Post-Vertical Slice` の斧・弓・複数武器関連は本ロードマップのInitial Vertical Slice完了後に着手する。

## 2. GitHub Project Field方針

| Field | 値 |
|---|---|
| Status | Todo / In Progress / Review / Done |
| Priority | P0 / P1 / P2 / P3 |
| Phase | P0 Foundation / P1 Sword Core / P2 Normal Enemy / P3 Progression / P4 Boss / P5 Stage Clear / P6 Quality |
| Milestone / Roadmap | M0 Core Foundation / M1 Combat Core / M2 Normal Battle Loop / M3 Death & Progression / M4 Boss Vertical Slice / M5 Release Gate |
| Start date / End date | 実着手時に設定し、依存Issueの完了状況に合わせて更新する |

親IssueはTracking用View、実装IssueはRoadmap / Board用Viewで管理する。

---

# 3. P0 Foundation

## 3.1 Player Base

1. `#110` Third Person Movementを要件へ同期
2. `#117` Third Person Camera Controlを要件へ同期
3. `#109` Jump Input / Grounded判定
   - Tracking Parent: `#108`
4. `#59` Player ASC初期化 / Owner・Avatar
5. `#60` Combat GameplayTag基盤
6. `#61` Stamina Attribute基盤
7. `#62` Damage / Hit Result基盤
8. `#88` 1スロット進行Save Request基盤

### 横断確認

- `#139` Input抽象化 / Movement依存境界
- `#134` 1080p / RTX3060 Performance計測環境

### 完了条件

- PlayerがMove / Look / Jump可能。
- GAS / GameplayTag / Stamina / Damageの共有基盤が利用可能。
- 後続SystemがSave媒体詳細へ直接依存せずSave Request可能。

---

# 4. P1 Sword Core

## 4.1 Light Attack

Tracking Parent: `#58`

1. `#63` Weapon Hit Collision / Attack Window
2. `#64` Attack Montage / Gameplay Event
3. `#65` Light Attack Input → Ability
4. `#66` Light Attack統合

## 4.2 Heavy Attack

Tracking Parent: `#67`

5. `#68` Heavy Attack Input / Ability
6. `#69` Heavy Montage / Hit Window / Damage
7. `#70` Heavy Attack統合

## 4.3 Combo Attack

Tracking Parent: `#71`

8. `#72` Input Buffer基盤
9. `#73` Combo受付Window / 次Attack選択
10. `#74` Light / Heavy Combo統合

## 4.4 Dodge

Tracking Parent: `#52`

11. `#53` Dodge Input / GameplayTag経路
12. `#54` Dodge Ability / Stamina / State
13. `#55` Roll / Back Step / Animation
14. `#56` Invincible Window / Perfect Dodge Window
15. `#57` Dodge Result通知 / Feedback / 統合
16. `#114` Perfect Dodge後Sword Counter

## 4.5 Sword Defense / Additional Action

17. `#115` Sword Parry
18. `#112` Air Attack

## 4.6 Targeting

Tracking Parents: `#75`, `#79`

19. `#76` LockOn Target候補選定 / Lock状態
20. `#77` LockOn Camera追従 / Camera Look抑止
21. `#78` Target死亡 / 無効化時のLock解除
22. `#80` Target Switch左右専用Input
23. `#81` Target Switch候補選定 / Current Target更新
24. `#113` Soft Lock

### 横断確認

- `#140` Gameplay Tag状態管理統一

### 完了条件

- SwordのLight / Heavy / Combo / Air Attackが成立。
- Dodge / Perfect Dodge / Counter / Parryが成立。
- Manual LockOn / Target Switch / Soft Lockが成立。

---

# 5. P2 Normal Enemy

Tracking Parent: `#118`

1. `#121` Multi Enemy Attack Coordinator
2. `#122` Enemy Health / Posture Attribute
3. `#119` Melee Normal Enemy
4. `#120` Ranged Normal Enemy
5. `#123` Posture Break / Down / Fatal Attack
6. `#124` EnemyごとのPosture Recovery
7. `#98` Enemy HP0 Defeat / AI・Attack Slot終了
8. `#99` Upgrade Material / Gold Reward直接付与
   - Tracking Parent: `#97`

### 完了条件

- Melee / Ranged Enemyとの複数戦闘が成立。
- 近接Attack Slot最大2体が機能。
- Health / Posture / Down / Fatal Attack / Defeat / Rewardが一連で成立。

---

# 6. P3 Progression / Death / Checkpoint

## 6.1 Player Death基礎

1. `#83` Player Health0 / Death State
   - Tracking Parent: `#82`

## 6.2 Checkpoint

Tracking Parent: `#91`

2. `#92` Checkpoint Interaction / ActiveCheckpoint / Menu Open
3. `#89` Checkpoint Menu Open Auto Save / Manual Save
4. `#93` Checkpoint休息・Player回復・Healing補充・Enemy復活

## 6.3 Healing

5. `#116` Limited Healing Item

## 6.4 DeathDrop / Respawn

6. `#84` Death Animation完了 → DeathDrop生成
7. `#86` DeathDrop回収 / 旧Drop消失 / Save復元契約
8. `#90` DeathDrop生成・回収後Auto Save
9. `#85` DeathDrop確認 / Fade / Checkpoint Respawn

## 6.5 Weapon Upgrade

Tracking Parent: `#94`

10. `#95` Gold / Material所持値・Cost判定
11. `#96` Resource消費 / Weapon Level更新

## 6.6 Settings Save

12. `#104` Settings変更時の独立Save

### 完了条件

- Checkpointを攻略拠点として利用可能。
- Death → DeathDrop → Save → Fade → Respawnが成立。
- Material 100% / Gold 70% Dropと再死亡時消失が成立。
- Gold + MaterialでCheckpoint Weapon Upgrade可能。

---

# 7. P4 Boss Vertical Slice

Tracking Parent: `#125`

1. `#126` Boss 1対1戦闘 / Phase2
2. `#127` Combat Context収集
3. `#128` Attack Candidate Score評価
4. `#129` 接近・離脱 / 遠距離Attack頻度適応
5. `#130` Boss Attack Combo Branch
6. `#131` Recovery Window / Counter Window
7. `#101` Boss HP0 Defeat / AI・Ability停止
8. `#102` Boss Gold / 初回固有収集Item Reward
   - Tracking Parent: `#100`
9. `#103` Boss Reward付与完了後Auto Save

### 完了条件

- BossがPlayer状態を評価してAttackを選択する。
- Phase2 / Combo / Recovery / Counter Windowが成立。
- Defeat → Reward → Auto Saveが一連で成立。

---

# 8. P5 Stage Clear / Presentation

1. `#132` Intro Text
2. `#133` Tutorial Flow
3. `#106` Boss撃破後Clear Trigger有効化
4. `#107` Skippable Ending Sequence / Title遷移
   - Tracking Parent: `#105`

### Optional

- `#147` Boss Intro演出

### 完了条件

- New Game → Tutorial → Normal Battle → Checkpoint → Boss → Clear Area → Ending → Titleまで通しプレイ可能。

---

# 9. P6 Quality / Release Gate

## 9.1 入力・設計品質

1. `#111` Gamepad / Keyboard-Mouse入力同等性
2. `#137` Gameplay Content Data Driven確認
3. `#138` C++ / Blueprint責務分離
4. `#141` Tick使用箇所監査・削減

## 9.2 Save品質

5. `#144` Corrupt Save挙動

## 9.3 Performance

6. `#136` Frame Time / Thread・GPU Bottleneck分析
7. `#135` 60fps最低保証 / 120fps挑戦目標検証

## 9.4 Stability / Final Gate

8. `#145` Long Play Memory Growth
9. `#142` 進行不能Bug 0件
10. `#143` Known Crash 0件
11. `#146` Shipping Build Final Verification

### 完了条件

- Gamepad / Keyboard-Mouse双方でClear可能。
- Known Crash / Progression Blockerが0件。
- 1080p基準で60fps最低保証目標を確認。
- Shipping BuildでNew GameからTitle帰還まで完走可能。

---

# 10. Tracking Parent一覧

以下は進捗集約用で、実装順序そのものには含めない。

- `#52` Dodge
- `#58` Light Attack
- `#67` Heavy Attack
- `#71` Combo Attack
- `#75` Manual LockOn
- `#79` Target Switch
- `#82` Player Death / DeathDrop / Respawn
- `#87` Save
- `#91` Checkpoint
- `#94` Weapon Upgrade
- `#97` Normal Enemy Defeat / Reward
- `#100` Boss Defeat / Reward
- `#105` Stage Clear
- `#108` Jump
- `#118` Normal Enemy Combat
- `#125` Boss Combat AI

# 11. Post-Vertical Slice

Initial Vertical Slice完了後に、Requirementsの`Post-Vertical Slice` / `Future Feature`を別Roadmapとして作成する。

対象例：

- Axe
- Bow
- Checkpoint Weapon Change
- Axe Guard / Receive
- Axe Super Armor
- Bow Shooting / Shoulder Aim / Distance Falloff / Weak Point
- Boss Weapon Adaptation / Bow Gap Closer
- Steam Cloud

### [戻る](../README.md#ドキュメント一覧)
