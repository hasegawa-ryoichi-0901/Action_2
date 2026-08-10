# FR-PLAYER-019 通常回避を実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-019` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-PLAYER-011`, `FR-PLAYER-012`, `FR-PLAYER-014` |

## 2. 目的

1つのDodge Actionで通常回避とPerfect Dodge Resultを扱い、入力・Ability・結果判定を重複させない。

## 3. Action境界

- Input Gameplay TagはDodgeの1つ。
- Normal DodgeとPerfect Dodgeは別Actionではない。
- Perfect Dodgeは敵Attackとの関係で決まるDodge Actionの結果。
- 結果通知には用途別のGameplay Tag / Gameplay Eventを使用できる。
- `1 Action = 1 ActorComponent`は前提としない。

## 4. 基本フロー

```text
[Dodge Input]
      ↓
[IPlayerInputComponent]
      ↓
[状態 / Stamina確認]
      +-- NG --> [Reject / Buffer]
      ↓
[Dodge Action開始]
      +--> State.Action.Dodging
      +--> Stamina Cost
      ↓
[移動入力あり？]
   ├─ Yes → 入力方向へRoll
   └─ No  → キャラクター後方へBack Step
      ↓
[Invincible Window]
[Perfect Dodge Window]
      ↓
[Enemy Attack判定]
   ├─ Perfect Window成立 → Perfect Dodge Result
   ├─ Invincibleのみ成立 → Normal Dodge / No Damage
   └─ 無敵外             → Hit可能
      ↓
[Recovery / Neutral]
```

## 5. 確定仕様

- Roll方向は移動入力基準。
- 無入力時はBack Step。
- Invincible Windowを持つ。
- Perfect Dodge WindowはInvincible Windowと別の調整値。
- 具体的な時間・距離は開発中に調整可能。
- 空中Dodge不可。
- 敵Collisionをすり抜けない。

## 6. 責務

| 対象 | 責務 |
|---|---|
| `IPlayerInputComponent`実装 | Dodge入力受付とGameplay要求配送 |
| Dodge Ability / Gameplay処理 | 実行条件、Stamina Cost、Dodge状態、Window管理、終了・Cancel |
| CharacterMovement / Animation | Roll / Back Step移動と表示 |
| Combat判定 | Enemy AttackとのWindow評価と結果通知 |

## 7. 受入条件

- [ ] Gamepad / Keyboard-Mouseから同じDodge Actionを開始できる。
- [ ] 移動入力中は入力方向へRollする。
- [ ] 無入力時は後方へBack Stepする。
- [ ] 空中ではDodgeを開始できない。
- [ ] Dodge中も敵Collisionを通過しない。
- [ ] Invincible WindowとPerfect Dodge Windowを独立して調整できる。
- [ ] Perfect条件不成立でも通常回避として成立できる。
- [ ] Perfect条件成立時は結果通知Tag / Eventを発行できる。
- [ ] Stamina不足・死亡・Down・Exhausted等の禁止状態で開始しない。
- [ ] Setup再実行でDodge入力が重複発火しない。

## 8. Issue構造

Dodgeは1つの親Action Issueとし、Input、Gameplay Tag / GAS、Stamina、Movement / Animation、Invincible / Perfect判定、統合テスト等を独立検証可能な実装Issueへ分割する。
