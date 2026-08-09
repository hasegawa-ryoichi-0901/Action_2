# NFR-MAINT-004 Moverを検証・採用しても戦闘システムへ固有依存を持ち込まない

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-MAINT-004` |
| 要件種別 | 非機能要件 / 保守性 |
| 優先度 | `Must` |
| 対応範囲 | Architecture Rule |
| 設計状態 | `Draft` |

## 2. 目的

初期Vertical SliceのCharacterMovement実装を不要な抽象化で複雑化せず、将来Moverを採用した場合にもCombat / Ability / InputへMover固有型やAPIを拡散させない。

## 3. 現在の方針

```text
Move Input
    ↓
UPlayerMoveInputComponent
    ↓
APawn::AddMovementInput
    ↓
CharacterMovement
```

現時点では`IMovementDriver`、`UMovementAdapterComponent`、`UMoverDriver`等を実装前提としない。

## 4. Mover評価時の規則

Moverを評価する場合、まず実際に解決したい問題を明示する。

- Root Motion / Motion Warping連携
- Dodge / Jumpの表現
- 入力応答性
- 斜面・段差
- 性能
- Debug / Shipping安定性

採用メリットが確認された場合のみ、必要最小限のMovement境界を設計する。

## 5. 禁止する依存

Mover採用時も以下をCombat / Ability / Inputの公開契約へ直接持ち込まない。

- Mover固有ClassをCombat APIの引数・戻り値へ露出する
- Mover固有Headerを多数のCombat Classからincludeする
- Mover固有状態をCombat Gameplay Tagの代替にする
- Moverの採否によってAttack / Dodge / Targetingの呼び出し側を全面修正する

## 6. 受入条件

### 現在

- [ ] CharacterMovementでVertical Sliceの移動・Jump・Dodgeを成立させられる。
- [ ] 未実装のMovement abstractionを必須依存にしない。

### Mover採用時

- [ ] Combat / Ability側へMover固有型が拡散しない。
- [ ] Mover不採用へ戻す場合の変更箇所をMovement境界付近へ限定できる。
- [ ] Mover導入理由と比較結果を設計判断として記録する。

## 7. 未決事項

Moverを実際に評価する時期と採否。初期Vertical SliceのIssue作成・実装を停止するBlockerにはしない。
