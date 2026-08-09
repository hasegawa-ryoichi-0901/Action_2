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
- Data Assetで攻撃を追加・調整

初期Vertical SliceではPlayer WeaponはSword固定とし、Axe / Bowによる武器別Score補正はPost-Vertical Sliceで追加します。

## 2. 通常敵Behavior Tree

```text
[Root]
   ↓
[Is Defeated?] --Yes--> [Stop]
   ↓ No
[Has Target?] --No--> [Patrol / Idle]
   ↓ Yes
[In Attack Range?]
   +-- No --> [Move / Reposition]
   ↓
[Has Attack Slot?]
   +-- No --> [Circle / Threaten / Wait]
   ↓
[Select Attack]
   ↓
[Execute Ability]
   ↓
[Release Attack Slot]
```

Health<=0でDefeatedになった場合、現在のTask / Abilityを停止し攻撃枠を即時解放します。

## 3. 集団戦管理

```text
UEnemyAttackCoordinatorSubsystem
    +-- RegisterEnemy
    +-- UnregisterEnemy
    +-- RequestMeleeSlot
    +-- ReleaseMeleeSlot
    +-- RequestRangedSlot
    +-- ReleaseRangedSlot
    +-- ApplyWaitingPriority
```

- Melee Active Max = 2
- Ranged Active Max = TBD
- Defeated / Down / Cancel / Owner破棄時のSlot解放を保証する

攻撃権を持たない敵は位置調整、威嚇、待機、視界内への移動、攻撃予約等を行います。

## 4. ボスStateTree

```text
[Root]
   +--> [Intro]
   +--> [Combat]
   |       +--> [Phase 1]
   |       +--> [Phase Transition]
   |       +--> [Phase 2]
   +--> [Posture Down]
   +--> [Fatal Reaction]
   +--> [Defeated]
```

```text
Boss HP > 50%  -> Phase 1
Boss HP <= 50% -> Phase Transition -> Phase 2
Boss HP <= 0   -> Defeated
```

DefeatedはPhase Transition、Posture Down、Attack Recoveryより優先します。

## 5. 初期Vertical Sliceの攻撃評価

評価対象：

- プレイヤーとの距離
- プレイヤーの回復状態
- プレイヤーの残りスタミナ
- 直近数秒の行動履歴
- 戦闘開始からの行動傾向
- 攻撃Cooldown
- 直前に使用した攻撃
- 同一攻撃の連続使用回数
- 現在Phase
- 壁際やStage端の位置関係

```text
FinalScore =
    BaseScore
  + DistanceScore
  + PlayerStateScore
  + RecentHistoryScore
  + BattleTrendScore
  + PhaseScore
  + PositionScore
  - CooldownPenalty
  - RepetitionPenalty
```

## 6. Post-Vertical Sliceの武器評価

Axe / Bow実装後にPlayer Weapon Modifierを追加します。

- Axe：高Stagger Resistance / Guard系行動を考慮した候補補正
- Bow：Range TrendとWeapon Typeを組み合わせた遠距離対応
- Bowで長距離維持された場合：`FR-BOSS-014`のGap Closer候補を補正

初期Vertical SliceのSword BossをこれらのFeatureへ依存させません。

## 7. 公平性

参照してよい：

- 現在位置
- 確定済み装備武器（Post-VS）
- 現在HP / Stamina
- 回復Abilityの確定済み発動状態
- 実行済み回避・攻撃履歴
- 確定済みGameplay Tag

参照しない：

- 未反映の入力
- 入力Bufferの中身
- 次に発動予定のAbility
- 将来入力の予測を確定情報として扱う処理

## 8. AIデバッグ表示

```text
Boss State       : Phase2
Selected Attack  : DashSlash
Final Score      : 82.5
Distance         : 620
Player Stamina   : 18%
Recent DodgeRate : High
Battle RangeBias : Long
Cooldown         : Ready
```

Post-VSではPlayer Weapon等の武器評価内訳を追加します。最終結果だけでなくScore内訳を確認可能にします。

### [戻る](../README.md#ドキュメント一覧)
