# 04. 武器システム

## 1. 開発スコープ

### 初期プレイアブル版

初期プレイアブル版では**Swordのみ**を実装します。複数Weapon切替、Axe、Bowは完成条件に含めません。

### Post-VS

初期プレイアブル版完成後の4～6カ月目を目安にAxeとBowを追加し、CheckpointでWeapon Change可能にします。

## 2. 共通仕様

- 最終的なWeapon構成はSword、Axe、Bowの3種類。
- 初期プレイアブル版はSwordのみ。
- 複数Weapon実装後はCheckpointで変更可能。
- Combat中は変更不可。
- 各Weaponは共通のWeapon Definition・Attack Definition・Ability連携を利用する。
- Attack Power、Posture Damage、Stamina Cost、Stagger Resistance等をData化する。
- Upgradeは3段階候補。
- Weapon Upgradeには**Upgrade MaterialとGoldの両方**を使用する。
- Goldの用途はWeapon Upgradeのみ。
- Weapon UpgradeはCheckpoint Menuからのみ実行できる。
- Upgrade Material / Goldの必要量はGameplay Dataで管理する。
- Gold / Upgrade Materialの正本はPlayer Inventoryとする。

## 3. 共通Action構成

初期プレイアブル版ではSwordでCombat基盤を成立させ、Axe / Bowは同じ基盤を利用して追加します。

- Light Attack
- Heavy Attack
- Combo Attack
- Dodge Attack候補
- Perfect Dodge Counter
- Air Attack
- Fatal Attack

Light Attack、Heavy Attack、Combo AttackはIssue管理上それぞれ別Action / Featureとして扱います。ActionとActorComponentの数を一致させることは前提としません。

## 4. Sword — 初期プレイアブル版対象

### 役割

- 標準的な速度
- 高い対応力
- Parry可能
- 比較的短いRecovery
- Perfect Dodge後の高速接近Counter

### Combo

```text
Light 1
  +--> Light 2
  |      +--> Light 3
  |              +--> Light 4
  +--> Heavy Branch

Light 2
  +--> Heavy Branch

Charge Heavy候補
Dodge Attack候補
Air Attack
Perfect Dodge Counter
Fatal Attack
```

## 5. Axe — Post-VS Feature

関連要件：`FR-PLAYER-017`、`FEATURE-AXE-001`～`FEATURE-AXE-005`。

- 低速・高威力・高Posture Damage・高Stagger Resistance。
- Guard / Receive。
- 一部AttackにSuper Armor候補。
- 3段Light Combo、Charge Attack、Dodge Attack、Perfect Dodge Counterを追加候補とする。

## 6. Bow — Post-VS Feature

関連要件：`FEATURE-BOW-001`～`FEATURE-BOW-006`、`FR-BOSS-014`。

- Ranged Attack。
- 通常時はSoft Lock。
- Aim時はShoulder Camera。
- 通常射撃は弾数無制限候補で、射撃ごとにStaminaを消費。
- Weak Point、Distance Falloffを持つ。
- 遠距離維持に対してBossは専用Gap Closerを使用する。

Projectile / Line Trace等の最終方式はPost-VS Prototypeで決定します。

## 7. Weapon Upgrade

```text
Level 1
  +--> 初期性能

Level 2
  +--> Attack Power上昇
  +--> Posture Damage上昇

Level 3
  +--> 固有Skill解放候補
```

```text
[Checkpoint Menu]
      ↓
[Upgrade対象選択]
      ↓
[Gold Cost確認]
      +-- 不足 --> [Reject]
      ↓
[Upgrade Material Cost確認]
      +-- 不足 --> [Reject]
      ↓
[両ResourceをPlayer Inventoryから消費]
      ↓
[Weapon Level / Parameter更新]
```

Weapon UpgradeそのものをAuto Save契機にはしません。進行Saveは`Docs/09_SaveCheckpointDeath.md`で定義した契機に従います。

関連Inventory基盤: [#153](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)

### [戻る](../README.md#ドキュメント一覧)
