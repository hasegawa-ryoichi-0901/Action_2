# FR-PLAYER-017 斧でガードまたは受け止めを実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-017` |
| 優先度 | `Should` |
| 対応範囲 | `Post-Vertical Slice / Axe Feature` |
| 設計状態 | `Draft` |

## 2. 目的

斧に高いStagger Resistanceを活かした武器固有防御を提供する。

## 3. スコープ

初期Vertical Sliceは剣のみのため、本要件は実装Blockerにしない。Axe Feature開始時にGuard / Receive方式を確定して実装する。

## 4. 基本フロー候補

```text
[Guard Input]
      ↓
[IPlayerInputComponent実装]
      ↓
[斧装備 / Stamina / GuardPolicy確認]
      +-- NG --> [Reject]
      ↓
[UGA_Guard候補]
      ↓
[被攻撃]
      +--> Guardable : Damage / Stamina / Reaction適用
      +--> GuardBreak: Break Reaction
      +--> Unguardable: Hit
```

## 5. 受入条件候補

- [ ] 斧装備時のみ武器固有防御を開始できる。
- [ ] GuardPolicyにより防御可能 / 不可能を判定できる。
- [ ] Stamina消費をデータから調整できる。
- [ ] Guard終了 / Cancel時に`State.Action.Guarding`が残らない。
- [ ] 剣のみの初期Vertical Sliceには影響しない。

## 6. 未決事項

- Guard / Receiveの最終方式
- Guard中Stamina消費
- Guard Break
- Super Armor対象攻撃

`Docs/15_OpenQuestions.md`でAxe実装前に確定する。
