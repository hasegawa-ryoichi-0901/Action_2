# 08. データ設計

## 1. データ駆動方針

各FR基本設計には、その機能がGameplay上必要とする`必要データ`を記載します。

DB Schema、CSV形式、CSV Reader、Primary Data Asset / Data Table等の具体的な読込・保存方式は別Architecture Designで定義し、本ドキュメントでは固定しません。

```text
[Gameplay System]
      ↓
[Gameplay Data Contract / Definition]
      ↓
[具体的なMaster Data Reader / CSV / DBは別Architecture]
```

Gameplay実装は特定CSV ReaderやDB実装へ直接依存させません。

## 2. 武器に必要なデータ

- WeaponId / WeaponType
- DisplayName
- Ability Set
- Light / Heavy / Air / Counter / Fatal Attack Definition
- Stamina Cost
- Stagger Resistance
- Posture Damage係数
- Upgrade Definition

## 3. Attackに必要なデータ

- AttackId
- Ability / Montage
- Stamina Cost
- Health Damage
- Posture Damage
- **Player Reaction Accumulation**
- Attack Tag / Parry Policy / Guard Policy
- Hit Stop
- Combo Branch
- Cooldown
- VFX / SFX

通常敵・BossのAttack DataはPlayer Reaction用の累積値を持ちます。Player側では内部値として計算し、HUDへ表示しません。

## 4. Enemyに必要なデータ

- EnemyId
- Max Health / Max Posture
- Posture Recovery設定
- Attack Definition参照
- Behavior Profile
- Melee / Ranged Slot Policy
- RewardId
- Down Animation
- Fatal Attack受付Collision設定
- Fatal Attack基準Transform

## 5. Bossに必要なデータ

- Boss / Attack ID
- Phase条件
- Range条件
- Base Score
- Score Modifier
- Cooldown / Repetition Penalty
- Player Stamina / Healing / History Modifier
- Combo Branch
- Recovery / Counter Window
- RewardId

Boss AI基本設計では、該当DataがDebug表示で確認可能であることも受入対象とします。

## 6. Weapon Upgradeに必要なデータ

- WeaponId
- Upgrade Level
- Required Material Type
- Required Material Amount
- **Required Gold Amount**
- Attack Power変更値
- Posture Damage変更値
- Granted / Removed Ability

GoldとUpgrade Materialの両方をPlayer Inventoryから消費します。

## 7. Reward Masterの確定方針

Reward件数に依存しないMaster構造とします。

概念関係：

```text
EnemyID(PK) -> RewardID
RewardID -> ItemID / Amount ... (0..N)
```

例：

```text
EnemyID = 1 -> RewardID = 1
RewardID = 1 -> ItemID = 1
RewardID = 1 -> ItemID = 2
```

Gameplay側は「RewardIDから0..N件のReward Entryを取得する」という契約だけに依存します。Rewardが1個・2個・将来それ以上になってもGameplayロジックの構造を変更しません。

具体的なPK / FK / Table構成、CSV列、Reader実装はDB / Master Data Architecture文書で定義します。

## 8. Inventory

次の所持データはPlayer Inventoryを正本とします。

- Gold
- Upgrade Material
- Boss Unique Item
- その他Inventory Item

Reward、DeathDrop、Weapon Upgrade、HUD、Saveは同一Inventory状態を参照します。

## 9. Save Data

未回収DeathDropについて、少なくとも次をSave / Load対象とします。

- DeathDrop位置
- Upgrade Material格納量
- Gold格納量
- 未回収状態

JSONで保存する方針ですが、JSON Schema / Versioning / Reader / Writerは別Architecture Designで定義します。

## 10. Validation

必要データについて次を検証可能にします。

- 必須ID / 参照先が存在する
- Damage / Cost / Amount等が不正な負値でない
- Combo Branch先が存在する
- Range Min <= Max
- RewardIdが解決できる
- Reward EntryのItemIdが解決できる
- Upgrade Levelが不正な重複を持たない
- Fatal Attack用Transform / Montage等の必須参照が設定されている

### [戻る](../README.md#ドキュメント一覧)
