# 06. 敵AI設計

## 1. AI構成方針

### 通常敵

- Behavior Tree / Blackboard / AI Perception
- C++ Task / Service
- 集団戦管理Subsystem

### Boss

- StateTreeで大状態とPhaseを管理する。
- C++評価SystemでAttack候補をScore化する。
- Gameplay AbilityでAttackを実行する。
- Attack / Score調整値はGameplay Dataから取得する。
- **Boss AIの各基本設計には、その判断根拠を確認できるDebug出力を含める。Debugは別Gameplay FeatureではなくBoss AIの検証責務とする。**

初期プレイアブル版ではPlayer WeaponはSword固定とし、Axe / BowによるWeapon ModifierはPost-VSで追加する。

## 2. 通常敵

```text
[Root]
↓
[Defeated?] --Yes--> Stop
↓ No
[Target?] --No--> Patrol / Idle
↓ Yes
[Attack Range?]
↓
[Attack Slot?]
├─ No → Reposition / Wait
└─ Yes → Select Attack → Execute Ability → Release Slot
```

Defeated / Down / Cancel / Owner破棄時はAttack Slotを必ず解放する。

## 3. 集団戦管理

- Melee Active Max = 2
- Ranged Active Max = 調整Data
- Melee / Ranged Slotを分離する。
- Slot二重取得・解放漏れを防ぐ。

## 4. Enemy Down / Fatal Attack受付

```text
Posture <= 0
↓
Down State
↓
Down Animation
↓
Fatal Attack受付State / Collision ON
↓
Down終了 / Defeat / Fatal成立
↓
受付State / Collision OFF
```

Player側Fatal Attack実行は[`FR-PLAYER-022`](01_Requirements.md#fr-player-022)が担当する。

## 5. Boss StateTree

```text
Root
├─ Intro
├─ Combat
│  ├─ Phase1
│  ├─ PhaseTransition
│  └─ Phase2
├─ Posture Down
├─ Fatal Reaction
└─ Defeated
```

`Boss HP <= 0`によるDefeatedをPhase Transition、Posture Down、Attack Recoveryより優先する。

## 6. Boss Combat Context

初期プレイアブル版で評価する情報：

- PlayerとのDistance
- Healing State
- Remaining Stamina
- 直近数秒のAction History
- Combat全体のRange / Action傾向
- Attack Cooldown
- Previous Attack
- Same Attack Repetition Count
- Current Phase
- Wall / Stage Edge等のPosition関係

参照しない情報：

- 未反映Input
- Input Buffer内容
- 次に発動予定のAbility
- 将来Inputの予測

## 7. Attack Candidate Score

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

Score式の各項目はAttack / Boss Dataから調整可能にする。

## 8. Boss AI Debug — 各基本設計へ組み込む共通要件

Boss AIの設計・Issueでは、該当機能を実装した時点で以下のうち関連する値を確認可能にする。

```text
Boss State
Current Phase
Selected Attack
Attack Candidate List
Base Score
Final Score
Distance / Distance Score
Player HP / Stamina
Healing State
Recent Action History
Battle Range Bias
Cooldown
Repetition Penalty
Position Score
Combo Branch
Recovery / Counter Window State
```

### Debug原則

- 最終選択結果だけでなく、選択理由となるScore内訳を確認できる。
- Shipping BuildのGameplay仕様には依存させない。
- Debug表示を無効化してもAI判断結果が変わらない。
- 無効Targetや未初期化DataでDebug処理からCrashしない。
- Post-VSではPlayer Weapon Modifier等を追加する。

### 各FRへの対応

| 要件 | Debugで確認する主項目 |
|---|---|
| `FR-BOSS-001/002` | State / Phase / HP Threshold |
| `FR-BOSS-003` | Distance / Distance Score |
| `FR-BOSS-005` | Healing State / Modifier |
| `FR-BOSS-006` | Player Stamina / Modifier |
| `FR-BOSS-007` | Recent History / Battle Trend |
| `FR-BOSS-008` | Candidate List / Score内訳 / Selected Attack |
| `FR-BOSS-009/010` | Approach / Retreat / Ranged Frequency補正 |
| `FR-BOSS-011` | Combo Branch条件 / 選択結果 |
| `FR-BOSS-012/013` | Recovery / Counter Window State |

Boss AI実装は親Issue [#125](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/125)および子Issue[#126](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/126)～[#131](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/131)で管理する。

## 9. 必要データ

各Boss FR基本設計に、その評価で必要なData項目を記載する。DB / CSV SchemaやReaderは別Architecture Designで定義し、AI実装は具体Readerへ直接依存しない。

Master Data Architectureは[#155](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/155)で確定する。

## 10. Post-VS

Axe / Bow追加後にPlayer Weapon Modifierを追加する。Bow長距離維持には`FR-BOSS-014` Gap Closerを接続する。

### [戻る](../README.md#ドキュメント一覧)
