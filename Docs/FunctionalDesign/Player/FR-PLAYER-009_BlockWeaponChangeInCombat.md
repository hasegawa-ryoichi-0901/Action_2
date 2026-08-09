# FR-PLAYER-009 戦闘中は武器を変更できない

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-009` |
| 優先度 | `Should` |
| 対応範囲 | `Post-Vertical Slice / 複数武器実装後` |
| 設計状態 | `Draft` |

## 2. 目的

複数武器導入後に、戦闘途中の装備切替によるAbility・Animation・状態不整合を防ぐ。

## 3. 方針

初期Vertical Sliceは剣のみのため武器変更自体を提供せず、本要件は実質的に成立する。Axe / Bow追加後、Checkpoint Weapon Menuからのみ武器変更を許可する。

## 4. 実行可否

武器変更要求時に少なくとも以下を確認する。

- Checkpoint Menu内であること
- Attack / Dodge / Parry / Heal等の戦闘Ability実行中でないこと
- Combat状態として定義した禁止Tagが存在しないこと
- Death / Down等の不正状態でないこと

## 5. 受入条件

- [ ] 通常戦闘中に武器変更できない。
- [ ] Boss戦闘中に武器変更できない。
- [ ] Checkpointの許可状態では変更できる。
- [ ] 拒否された変更でAbilityや武器Dataが部分更新されない。
- [ ] 初期Vertical Sliceでは複数武器機能がなくても影響しない。

## 6. 依存

- `FR-PLAYER-008`
- `FR-STAGE-006`
- Axe / Bow Future Feature
