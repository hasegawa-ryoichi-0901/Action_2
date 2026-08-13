# Implementation Roadmap

本ドキュメントは、GitHub IssueをIssue番号順ではなく**実装依存関係順**で進めるためのロードマップです。

## 1. 運用ルール

- Gameplay Action / Systemの親Issueは進捗集約用とし、原則PRを作成しない。
- 実装Issueは原則 `1 Issue = 1 PR` とする。
- 依存先Issueが未完了の場合、依存元Issueを先に実装しない。
- 共有基盤は後続Actionで重複実装せず、既存Issueを依存先として参照する。
- 横断的なMaintainability / Quality Issueは、単独機能の完成ではなく各PhaseのReview Gateとして扱う。
- `Post-VS`のAxe / Bow / 複数武器関連は初期プレイアブル版完了後に着手する。

## 2. GitHub Project Field方針

| Field | 値 |
|---|---|
| Status | Todo / In Progress / Review / Done |
| Priority | P0 / P1 / P2 / P3 |
| Phase | P0 Foundation / P1 Sword Core / P2 Normal Enemy / P3 Progression / P4 Boss / P5 Stage Clear / P6 Quality |
| Milestone / Roadmap | M0 Core Foundation / M1 Combat Core / M2 Normal Battle Loop / M3 Death & Progression / M4 Boss / M5 Release Gate |
| Start date / End date | 実着手時に設定し、依存Issueの完了状況に合わせて更新する |

親IssueはTracking用View、実装IssueはRoadmap / Board用Viewで管理する。

---

# 3. P0 Foundation

## 3.1 Player / Combat Base

1. [#110 Third Person Movement](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/110)
2. [#117 Third Person Camera Control](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/117)
3. [#109 Jump Input / Grounded](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/109) — Parent [#108](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/108)
4. [#59 Player ASC](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/59)
5. [#60 GameplayTag基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/60)
6. [#61 Stamina Attribute](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61)
7. [#152 Exhausted State](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/152)
8. [#62 Damage / Hit Result](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/62)
9. [#153 Player Inventory](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)

## 3.2 Save / Data Architecture

10. [#154 JSON Save Architecture](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)
11. [#88 1 Slot Progress Save Request](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/88)
12. [#155 CSV / Master Data Architecture](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/155)

### 横断確認

- [#139 Input抽象化 / Movement依存境界](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139)
- [#134 1080p / RTX3060計測環境](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/134)

### 完了条件

- PlayerがMove / Look / Jump可能。
- GAS / GameplayTag / Stamina / Exhausted / Damageの共有基盤が利用可能。
- Gold / Material / Boss Unique ItemをPlayer Inventoryで一元管理可能。
- Gameplay側をJSON / CSVの具体実装へ直接依存させないSave / Master Data境界が定義されている。

---

# 4. P1 Sword Core

## 4.1 Light Attack

Tracking Parent: [#58](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58)

1. [#63 Weapon Hit Collision / Attack Window](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/63)
2. [#64 Attack Montage / Gameplay Event](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/64)
3. [#65 Light Attack Input → Ability](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/65)
4. [#66 Light Attack統合](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/66)

## 4.2 Heavy Attack

Tracking Parent: [#67](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/67)

5. [#68 Heavy Attack Input / Ability](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/68)
6. [#69 Heavy Montage / Hit Window / Damage](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/69)
7. [#70 Heavy Attack統合](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/70)

## 4.3 Combo Attack

Tracking Parent: [#71](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/71)

8. [#72 Input Buffer基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/72)
9. [#73 Combo受付Window / 次Attack選択](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/73)
10. [#74 Light / Heavy Combo統合](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/74)

## 4.4 Dodge

Tracking Parent: [#52](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52)

11. [#53 Dodge Input / GameplayTag経路](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/53)
12. [#54 Dodge Ability / Stamina / State](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/54)
13. [#55 Roll / Back Step / Animation](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/55)
14. [#56 Invincible / Perfect Window](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/56)
15. [#57 Dodge Result / Feedback](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/57)
16. [#114 Perfect Dodge後Sword Counter](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/114)

## 4.5 Sword Defense / Additional Action

17. [#115 Sword Parry](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/115)
18. [#112 Air Attack](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/112)
19. [#148 Fatal Attack](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/148)
20. [#149 Player Hit / Stagger / Down](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/149)

## 4.6 Targeting

Tracking Parents: [#75](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/75), [#79](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/79)

21. [#76 LockOn Target候補 / Lock状態](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/76)
22. [#77 LockOn Camera / Look抑止](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/77)
23. [#78 Target死亡時Unlock](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/78)
24. [#80 Target Switch左右Input](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/80)
25. [#81 Target Switch候補 / Current Target更新](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/81)
26. [#113 Soft Lock](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/113)

### 横断確認

- [#140 Gameplay Tag状態管理統一](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/140)

### 完了条件

- Sword Light / Heavy / Combo / Air / Fatal Attackが成立。
- Dodge / Perfect Dodge / Counter / Parryが成立。
- Hit / Stagger / DownとDeath優先順位が成立。
- Manual LockOn / Target Switch / Soft Lockが成立。

---

# 5. P2 Normal Enemy

Tracking Parent: [#118](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/118)

1. [#121 Multi Enemy Attack Coordinator](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/121)
2. [#122 Enemy Health / Posture](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/122)
3. [#119 Melee Normal Enemy](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/119)
4. [#120 Ranged Normal Enemy](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/120)
5. [#123 Posture Break / Down / Fatal受付](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/123)
6. [#124 Posture Recovery](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/124)
7. [#98 Enemy HP0 Defeat](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/98)
8. [#99 Material / Gold Reward](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/99) — Parent [#97](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/97)

### 完了条件

- Melee / Ranged Enemyとの複数戦闘が成立。
- Melee Attack Slot最大2体が機能。
- Health / Posture / Down / Fatal Attack / Defeat / Rewardが一連で成立。
- RewardはPlayer Inventoryへ直接加算される。

---

# 6. P3 Progression / Death / Checkpoint

## 6.1 Player Death

1. [#83 Player Health0 / Death State](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/83) — Parent [#82](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/82)

## 6.2 Checkpoint

2. [#92 Checkpoint Interaction / ActiveCheckpoint / Menu](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/92)
3. [#93 Rest / HP / Stamina / Heal補充 / Enemy復活](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/93)
4. [#89 Rest確定後Auto Save / Manual Save](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89)

Tracking Parent: [#91](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/91)

## 6.3 Healing

5. [#116 Limited Healing Item](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/116)

## 6.4 DeathDrop / Respawn

6. [#84 Death Animation完了 → DeathDrop生成](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/84)
7. [#86 DeathDrop回収 / 旧Drop消失 / 復元契約](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/86)
8. [#90 DeathDrop生成・回収後Auto Save](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/90)
9. [#85 DeathDrop確認 / Fade / Respawn](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/85)

## 6.5 Weapon Upgrade

Tracking Parent: [#94](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/94)

10. [#95 Gold / Material Cost判定](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/95)
11. [#96 Resource消費 / Weapon Level更新](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/96)

## 6.6 Settings Save

12. [#104 Settings変更時Save](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/104)

### 完了条件

- Checkpointを攻略拠点として利用可能。
- `Interaction → ActiveCheckpoint → Menu → Rest → Auto Save`の順序が成立。
- Death → DeathDrop → Save → Camera確認 → Fade → Respawnが成立。
- Upgrade Material 100% / Gold 100%をDeathDropへ移動できる。
- 未回収で再死亡した場合は旧DeathDrop本体と全内容を消失させる。
- Gold + MaterialでCheckpoint Weapon Upgrade可能。
- Heal Animation開始直後にItemを消費し、その後の被弾中断では返却しない。

---

# 7. P4 Boss

Tracking Parent: [#125](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/125)

1. [#126 Boss 1対1 / Phase2](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/126)
2. [#127 Combat Context](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/127)
3. [#128 Attack Candidate Score](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/128)
4. [#129 Approach / Retreat / Ranged Frequency](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/129)
5. [#130 Boss Combo Branch](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/130)
6. [#131 Recovery / Counter Window](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/131)
7. [#101 Boss HP0 Defeat](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/101)
8. [#102 Boss Gold / 初回Unique Item Reward](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/102) — Parent [#100](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/100)
9. [#103 Boss Reward確定後Auto Save](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/103)

### 完了条件

- BossがPlayer状態を評価してAttackを選択する。
- Phase2 / Combo / Recovery / Counter Windowが成立。
- Defeat → Reward → Auto Saveが一連で成立。
- Debug表示でState / Context / Candidate / Score内訳 / Selected Attackを確認できる。

---

# 8. P5 Stage Clear / Frontend

1. [#150 Title / Start Flow](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/150)
2. [#132 Tutorial Text](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/132)
3. [#133 Tutorial Flow](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/133)
4. [#151 Gameplay HUD](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/151)
5. [#106 Boss撃破後Clear Trigger有効化](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/106)
6. [#107 Skippable Ending / Title遷移](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/107) — Parent [#105](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/105)

### Optional

- [#147 Boss Intro演出](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/147)

### 完了条件

- Boot → Intro → Title → New Game → Tutorial → Normal Battle → Checkpoint → Boss → Clear Area → Ending → Titleまで通しPlay可能。

---

# 9. P6 Quality / Release Gate

## 9.1 入力・設計品質

1. [#111 Gamepad / Keyboard-Mouse同等性](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111)
2. [#137 Gameplay Content Data Driven](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/137)
3. [#138 C++ / Blueprint責務分離](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/138)
4. [#141 Tick監査](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/141)

## 9.2 Save品質

5. [#144 Corrupt Save](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/144)

## 9.3 Performance

6. [#136 Frame Time / Bottleneck](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136)
7. [#135 60fps最低保証 / 120fps挑戦](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/135)

## 9.4 Stability / Final Gate

8. [#145 Long Play Memory Growth](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/145)
9. [#142 進行不能Bug 0件](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/142)
10. [#143 Known Crash 0件](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/143)
11. [#146 Shipping Build Final Verification](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/146)

### 完了条件

- Gamepad / Keyboard-Mouse双方でClear可能。
- Known Crash / 進行不能Bugが0件。
- 1080p基準で60fps最低保証目標を確認。
- Corrupt Saveを削除しNew Game可能状態へ安全に戻れる。
- Shipping BuildでNew GameからTitle帰還まで完走可能。

---

# 10. Tracking Parent一覧

- [#52 Dodge](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52)
- [#58 Light Attack](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58)
- [#67 Heavy Attack](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/67)
- [#71 Combo Attack](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/71)
- [#75 Manual LockOn](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/75)
- [#79 Target Switch](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/79)
- [#82 Player Death / DeathDrop / Respawn](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/82)
- [#87 Save](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/87)
- [#91 Checkpoint](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/91)
- [#94 Weapon Upgrade](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/94)
- [#97 Normal Enemy Defeat / Reward](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/97)
- [#100 Boss Defeat / Reward](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/100)
- [#105 Stage Clear](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/105)
- [#108 Jump](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/108)
- [#118 Normal Enemy Combat](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/118)
- [#125 Boss Combat AI](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/125)

# 11. Post-VS

初期プレイアブル版完了後に、Requirementsの`Post-VS` / `Future Feature`を別Roadmapとして作成する。

対象例：Axe、Bow、Checkpoint Weapon Change、Axe Guard / Receive、Axe Super Armor、Bow Shooting / Shoulder Aim / Distance Falloff / Weak Point、Boss Weapon Adaptation / Bow Gap Closer、Steam Cloud。

### [戻る](../README.md#ドキュメント一覧)
