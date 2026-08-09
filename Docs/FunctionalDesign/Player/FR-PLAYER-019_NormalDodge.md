# FR-PLAYER-019 通常回避を実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-019` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-PLAYER-011`, `FR-PLAYER-012`, `FR-PLAYER-014` |

## 2. 目的

敵攻撃を避けながら位置を調整する基本防御行動を提供し、同じ回避行動からジャスト回避判定へ接続する。

## 3. 基本フロー

```text
[Dodge Input]
      ↓
[IPlayerInputComponent実装]
      ↓
[状態 / Stamina確認]
      +-- NG --> [Reject / Buffer]
      ↓
[UGA_Dodge候補]
      +--> Dodge Cost適用
      +--> State.Action.Dodging
      +--> Dodge Movement / Animation
      ↓
[敵攻撃とのWindow判定]
      +-- Perfect条件成立 --> [FR-PLAYER-014]
      +-- 不成立 -----------> [Normal Dodge]
      ↓
[Recovery / Neutral]
```

## 4. 事前条件

- Playerが死亡・ダウン・息切れ中でない。
- 必要Staminaを満たす。
- Dodge入力ComponentがSetup済み。
- 同一Dodgeが多重開始されていない。

## 5. 責務

| 対象 | 責務 |
|---|---|
| `IPlayerInputComponent`実装 | 回避入力受付とAbility / gameplay request配送 |
| `UGA_Dodge`候補 | 実行可否、Cost、Dodge状態、終了 / Cancel |
| CharacterMovement / Animation | 回避移動と表示 |
| Perfect Dodge判定 | 回避中の敵攻撃Window評価 |

## 6. 状態

- `State.Action.Dodging`
- `Window.PerfectDodge`
- 必要に応じて`Window.Cancel.Dodge`

## 7. 受入条件

- [ ] GamepadとKeyboard / Mouseから通常回避できる。
- [ ] Dodge開始時にStaminaを仕様どおり消費する。
- [ ] Stamina不足時は回避を開始しない。
- [ ] Perfect Dodge条件を満たさない場合でも通常回避として成立する。
- [ ] 死亡・息切れ等の禁止状態で開始しない。
- [ ] Cancel / End後にDodge Tagや受付Windowが残らない。
- [ ] 入力再Setupで回避が重複発火しない。

## 8. テスト観点

- 正常回避
- Stamina境界値
- 連続入力
- Perfect Dodge成功 / 失敗
- Attack Cancel Windowからの回避
- Death / Exhausted / Down中
- Owner破棄・Ability Cancel

## 9. 未決事項

- 回避方向と無入力時方向
- 通常回避の無敵時間
- 回避移動距離 / 時間
- 空中回避可否
- 敵Collisionすり抜け可否
- Step / Roll等のAnimation

未決事項は`Docs/15_OpenQuestions.md`で確定してから実装Issue化する。
