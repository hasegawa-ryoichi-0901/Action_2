# 06. 敵AI設計

## 1. AI構成方針

### 通常敵

- Behavior Tree
- Blackboard
- AI Perception
- C++ Task / Service
- 集団戦管理Subsystem

### ボス

- StateTreeで大状態とフェーズを管理
- C++評価システムで攻撃候補をスコアリング
- Gameplay Abilityで攻撃を実行
- データアセットで攻撃を追加・調整

```text
通常敵
  |
  +--> Behavior Tree
  +--> Blackboard
  +--> Attack Coordinator

ボス
  |
  +--> StateTree
  +--> C++ Attack Evaluator
  +--> Attack Definition Data
  +--> GAS Ability
```

## 2. 通常敵Behavior Tree

```text
[Root]
   |
   v
[Is Dead?] --------Yes------> [Stop]
   |
   No
   v
[Has Target?] -----No-------> [Patrol / Idle]
   |
   Yes
   v
[In Attack Range?]
   |
   +-- No --> [Move / Reposition]
   |
   v
[Has Attack Slot?]
   |
   +-- No --> [Circle / Threaten / Wait]
   |
   v
[Select Attack]
   |
   v
[Execute Ability]
   |
   v
[Release Attack Slot]
```

## 3. 集団戦管理

```text
+--------------------------------------------------+
| UEnemyAttackCoordinatorSubsystem                 |
|--------------------------------------------------|
| RegisterEnemy                                    |
| UnregisterEnemy                                  |
| RequestMeleeSlot                                 |
| ReleaseMeleeSlot                                 |
| RequestRangedSlot                                |
| ReleaseRangedSlot                                |
| ApplyWaitingPriority                             |
+-------------------------+------------------------+
                          |
             +------------+------------+
             |                         |
             v                         v
+------------------------+  +------------------------+
| Melee Attack Slots     |  | Ranged Attack Slots    |
| Max Active: 2          |  | Max Active: 未確定     |
+------------------------+  +------------------------+
```

攻撃権を持たない敵は次の行動を行います。

- プレイヤー周囲で位置調整
- 威嚇
- 待機
- 視界内への移動
- 攻撃予約
- 長時間待機による優先度上昇

## 4. ボスStateTree

```text
[Root]
   |
   +--> [Intro]
   |
   +--> [Combat]
   |       |
   |       +--> [Phase 1]
   |       |
   |       +--> [Phase Transition]
   |       |
   |       +--> [Phase 2]
   |
   +--> [Posture Down]
   |
   +--> [Fatal Reaction]
   |
   +--> [Dead]
```

### フェーズ移行

```text
Boss HP > 50%
    |
    v
[Phase 1]

Boss HP <= 50%
    |
    v
[Phase Transition]
    |
    v
[Phase 2]
```

## 5. 攻撃評価

### 評価対象

- プレイヤーとの距離
- プレイヤーの装備武器
- プレイヤーの回復状態
- プレイヤーの残りスタミナ
- 直近数秒の行動履歴
- 戦闘開始からの行動傾向
- 攻撃のクールダウン
- 直前に使用した攻撃
- 同一攻撃の連続使用回数
- 現在フェーズ
- 壁際やステージ端の位置関係

### 評価式の概念

```text
FinalScore =
    BaseScore
  + DistanceScore
  + WeaponMatchScore
  + PlayerStateScore
  + RecentHistoryScore
  + BattleTrendScore
  + PhaseScore
  + PositionScore
  - CooldownPenalty
  - RepetitionPenalty
```

## 6. 適応

ボスは直近の行動と戦闘全体の傾向を併用します。

```text
[Player Action History]
      |
      +--> Recent Window
      |       |
      |       +--> 直近数秒
      |       +--> 即時的な対応
      |
      +--> Battle Trend
              |
              +--> 回避頻度
              +--> 遠距離維持傾向
              +--> 回復タイミング傾向
              +--> 武器使用傾向
```

適応によって変更する項目は次のとおりです。

- 攻撃候補の評価値
- 接近頻度
- 離脱頻度
- 遠距離攻撃頻度

## 7. 公平性

### 参照してよい

- 現在位置
- 装備武器
- 現在HP
- 現在スタミナ
- 回復Abilityの確定済み発動状態
- 実行済み回避履歴
- 実行済み攻撃履歴
- 確定済みGameplay Tag

### 参照しない

- 未反映の入力
- 入力バッファの中身
- 次に発動予定のAbility
- プレイヤーだけが知る内部情報
- 将来入力の予測結果を確定情報として使う処理

## 8. AIデバッグ表示

```text
Boss State       : Phase2
Selected Attack  : DashSlash
Final Score      : 82.5
Distance         : 620
Player Weapon    : Bow
Player Stamina   : 18%
Recent DodgeRate : High
Battle RangeBias : Long
Melee Slot       : N/A
Cooldown         : Ready
```

デバッグ表示では、最終結果だけでなく評価項目の内訳を確認できるようにします。
