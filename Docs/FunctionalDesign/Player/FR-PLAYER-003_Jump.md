# FR-PLAYER-003 ジャンプできる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-003` |
| 要件名 | ジャンプできる |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |

## 2. 目的

地形の高低差を越える基本移動を提供する。

## 3. 設計方針

Jump入力は`IPlayerInputComponent`を実装する入力Componentからゲームプレイ処理へ配送する。現時点では存在しない`IMovementDriver` / `UMovementAdapterComponent`を前提にしない。

```text
[Enhanced Input / Jump]
      ↓
[IPlayerInputComponent実装]
      ↓
[Jump Request]
      ↓
[死亡 / 息切れ / 接地等の実行可否]
      +-- NG --> [Reject / Buffer]
      ↓
[Character Jump または UGA_Jump]
      ↓
[State.Action.Jumping]
      ↓
[Landing]
```

GASでJumpを管理する場合でも、Input BindingのSetup / Teardownは入力Component側の責務とする。

## 4. 事前条件

- Jump入力Componentが正しくSetupされている。
- Player / Controller参照が有効。
- 接地している。
- `State.Dead`、`State.Action.Exhausted`、Down等の禁止状態ではない。

## 5. 成功・失敗

成功時：
- Characterが離地する。
- `State.Action.Jumping`等、戦闘側が必要とする状態を更新する。
- 着地時にJump状態を解除する。

失敗時：
- 状態やコストを部分変更しない。
- 連続入力で多重Jumpを発生させない。

## 6. 責務分割

| 対象 | 責務 |
|---|---|
| `IPlayerInputComponent`実装 | Jump入力受付とゲームプレイ要求への配送 |
| Character / Jump Ability | 実行可否、Jump開始・終了 |
| CharacterMovement | 実際の鉛直移動・接地判定 |
| Animation | Jump / Fall / Land表示 |

## 7. 受入条件

- [ ] GamepadとKeyboard / Mouseの両方でJumpできる。
- [ ] 空中で通常のJump入力を再実行して二段Jumpしない。
- [ ] 息切れ・死亡等の禁止状態ではJumpできない。
- [ ] 着地後にJump状態が残らない。
- [ ] Setup再実行でJump入力が重複発火しない。

## 8. 未決事項

Jumpを最終的にGAS Abilityとして扱うかCharacterのMovement APIとして扱うかは、戦闘状態Tag・空中攻撃・キャンセル制御との整合を確認して実装Issue開始前に確定する。ただしInput Bindingは`IPlayerInputComponent`方針を維持する。
