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
- 最終的にはすべてのボスをすべての武器で撃破可能にする。
- 各武器は共通の武器定義・攻撃定義・Ability連携を利用する。
- 攻撃力、体勢削り、スタミナコスト、怯み耐性をデータ化する。
- 強化は3段階候補。
- 強化素材は初期仕様では共通。
- 素材種別はマスターデータで変更可能。
- 強化素材の振り直しはPost-Vertical Slice候補とする。

## 3. 共通アクション構成

最終目標は次のとおりです。初期Vertical Sliceでは剣で戦闘基盤を成立させ、斧・弓は同じ基盤を利用して追加します。

- 通常攻撃コンボ：1系統
- 強攻撃：1種類
- チャージ攻撃：1種類
- 回避攻撃：1種類
- ジャスト回避反撃：1種類
- 固有スキル：2種類候補
- 空中攻撃：1種類
- 致命攻撃：1種類

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

Charge Heavy
Dodge Attack
Air Attack
Perfect Dodge Counter
Fatal Attack
```

通常攻撃は4段を目標とします。

## 5. 斧 — Post-Vertical Slice Feature

関連要件：`FR-PLAYER-017`、`FEATURE-AXE-001`～`FEATURE-AXE-005`。

### 役割

- 低速
- 高威力
- 高い体勢削り
- 高い怯み耐性
- ガードまたは受け止め
- 一部攻撃にスーパーアーマー候補
- ジャスト回避後に高威力の叩きつけ

### アクション候補

```text
Light 1
  +--> Light 2
  |      +--> Light 3
  +--> Heavy Branch

Charge Heavy
Guard / Receive
Dodge Attack
Air Attack
Perfect Dodge Counter
Fatal Attack
```

ガード / 受け止め方式、ガード中スタミナ、ガードブレイク、スーパーアーマー対象は`15_OpenQuestions.md`で確定します。

## 6. 弓 — Post-Vertical Slice Feature

関連要件：`FEATURE-BOW-001`～`FEATURE-BOW-006`、`FR-BOSS-014`。

### 役割

- 遠距離攻撃
- 通常時はソフトロック
- 構え時は肩越し照準
- 通常射撃の弾数は無制限候補
- 射撃ごとにスタミナを消費
- 敵の弱点部位を攻撃可能
- 弱点はUIへ明示しない
- 距離が長くなるほどダメージが減少
- 遠距離維持に対し、ボスは専用接近行動を使用する

### 射撃方式

```text
通常矢
  +--> Projectile候補
  +--> 飛翔時間あり
  +--> 距離減衰あり

特殊高速射撃
  +--> Line Trace候補
  +--> 即着弾
  +--> Ability / Skill候補
```

通常攻撃を3段コンボとするか連続射撃とするか、Projectile / Line Traceの最終分担はプロトタイプで決定します。

## 7. 武器強化

```text
Level 1
  +--> 初期性能

Level 2
  +--> 攻撃力上昇
  +--> 体勢削り性能上昇

Level 3
  +--> 固有スキル解放候補
```

```text
[Checkpoint]
      ↓
[Weapon Upgrade Menu]
      +--> 素材確認
      +--> 強化実行
      +--> Gameplay Ability付与
      +--> パラメータ更新
      +--> オートセーブ
```

### [戻る](../README.md#ドキュメント一覧)
