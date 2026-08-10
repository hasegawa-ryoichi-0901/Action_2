# 04. 武器システム

## 1. 開発スコープ

### 初期Vertical Slice

初期Vertical Sliceでは**剣のみ**を実装します。複数武器切り替え、斧、弓は完成条件に含めません。

### Post-Vertical Slice

Vertical Slice完成後の4～6カ月目を目安に斧と弓を追加し、チェックポイントで武器変更可能にします。

## 2. 共通仕様

- 最終的な武器構成は剣、斧、弓の3種類。
- 初期Vertical Sliceは剣のみ。
- 複数武器実装後はチェックポイントで変更可能。
- 戦闘中は変更不可。
- 各武器は共通の武器定義・攻撃定義・Ability連携を利用する。
- 攻撃力、体勢削り、スタミナコスト、怯み耐性をデータ化する。
- 強化は3段階候補。
- 武器強化には**強化素材とGoldの両方**を使用する。
- Goldの用途は武器強化のみ。
- 武器強化はCheckpoint Menuからのみ実行できる。
- 強化素材・Goldの必要量はゲームデータで管理する。

## 3. 共通アクション構成

初期Vertical Sliceでは剣で戦闘基盤を成立させ、斧・弓は同じ基盤を利用して追加します。

- Light Attack
- Heavy Attack
- Combo Attack
- Dodge Attack候補
- Perfect Dodge Counter
- Air Attack
- Fatal Attack

Light Attack、Heavy Attack、Combo AttackはIssue管理上それぞれ別Action / Featureとして扱います。ActionとActorComponentの数を一致させることは前提としません。

## 4. 剣 — Vertical Slice対象

### 役割

- 標準的な速度
- 高い対応力
- パリィ可能
- 比較的短い硬直
- ジャスト回避後の高速接近反撃

### コンボ

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

## 5. 斧 — Post-Vertical Slice Feature

関連要件：`FR-PLAYER-017`、`FEATURE-AXE-001`～`FEATURE-AXE-005`。

- 低速・高威力・高い体勢削り・高い怯み耐性。
- Guard / Receive。
- 一部攻撃にSuper Armor候補。
- 3段Light Combo、Charge Attack、Dodge Attack、Perfect Dodge Counterを追加候補とする。

## 6. 弓 — Post-Vertical Slice Feature

関連要件：`FEATURE-BOW-001`～`FEATURE-BOW-006`、`FR-BOSS-014`。

- 遠距離攻撃。
- 通常時はSoft Lock。
- 構え時は肩越し照準。
- 通常射撃は弾数無制限候補で、射撃ごとにStaminaを消費。
- Weak Point、距離減衰を持つ。
- 遠距離維持に対してBossは専用Gap Closerを使用する。

Projectile / Line Trace等の最終方式はPost-Vertical Sliceのプロトタイプで決定します。

## 7. 武器強化

```text
Level 1
  +--> 初期性能

Level 2
  +--> 攻撃力上昇
  +--> 体勢削り性能上昇

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
[両Resourceを消費]
      ↓
[Weapon Level / Parameter更新]
```

武器強化そのものをAuto Save契機にはしません。進行Saveは`Docs/09_SaveCheckpointDeath.md`で定義した契機に従います。

### [戻る](../README.md#ドキュメント一覧)
