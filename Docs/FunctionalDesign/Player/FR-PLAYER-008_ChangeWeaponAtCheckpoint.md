# FR-PLAYER-008 剣、斧、弓をチェックポイントで変更できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-008` |
| 優先度 | `Should` |
| 対応範囲 | `Post-Vertical Slice / 4～6カ月目` |
| 設計状態 | `Draft` |

## 2. 目的

斧・弓追加後に、戦闘外の明確な地点で装備武器を変更し、武器ごとのAbility・データ・戦闘スタイルを切り替える。

## 3. 前提

初期Vertical Sliceは剣のみのため、本要件を完成条件・依存Blockerに含めない。斧・弓Featureが利用可能になった後に有効化する。

## 4. 基本フロー

```text
[Checkpoint]
      ↓
[Weapon Menu]
      ↓
[武器選択]
      ↓
[戦闘中でないことを確認]
      ↓
[Weapon Definition切替]
      +--> Weapon Actor / Mesh
      +--> Ability Set
      +--> Attack / Dodge / Counter Data
      +--> Stagger Resistance
      ↓
[装備状態更新]
```

## 5. 受入条件

- [ ] Sword / Axe / Bowから利用可能な武器を選択できる。
- [ ] 戦闘中には変更できない。
- [ ] 武器変更後に古い武器固有Ability・状態が残らない。
- [ ] 新武器のAbility / Data / Presentationへ一貫して切り替わる。
- [ ] 初期Vertical Sliceの剣のみビルドでは本要件が未実装でも進行できる。

## 6. 依存

- `FR-PLAYER-009`
- `FR-STAGE-006`
- Axe / Bow Future Feature
- Weapon Definition / Ability Set
