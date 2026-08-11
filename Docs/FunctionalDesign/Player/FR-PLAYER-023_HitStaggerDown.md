# FR-PLAYER-023 PlayerのHit / Stagger / Down Reactionを実装する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-023` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | 未割当 |
| 関連設計 | `FR-PLAYER-020`, Enemy / Boss Attack Data |

## 2. 目的

敵攻撃の重さをPlayer Reactionへ反映し、軽い被弾・大きな怯み・Downを攻撃データから一貫して判定する。

## 3. 確定仕様・スコープ

- Player Reactionは`Hit / Stagger / Down`の3段階とする。
- 通常敵・Bossの各Attack DataにPlayer Reaction用の蓄積値を持たせる。
- Playerは被弾ごとにその値を内部蓄積する。
- 蓄積結果に応じてHit / Stagger / Downへ遷移する。
- Reaction蓄積値はPlayerへ表示しない。HUDゲージは作らない。
- Reaction成立時の閾値・蓄積減衰 / Reset等はGameplay Dataで調整可能にする。
- DeathはReactionより優先し、HP<=0時は`State.Dead`へ遷移する。

## 4. 基本フロー

```text
[Enemy / Boss Attack Hit]
  ↓
[Damage + Reaction Accumulation取得]
  ↓
[Health更新]
  +-- Health <= 0 --> [Death]
  ↓
[内部Reaction値を加算]
  ↓
[閾値判定]
  ├─ Down閾値     → [Down]
  ├─ Stagger閾値  → [Stagger]
  └─ Hit条件      → [Hit]
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Enemy / Boss Attack Data | Reaction蓄積値を定義する |
| Player Combat / Attribute処理 | 内部蓄積、閾値判定、Reaction遷移を管理する |
| Gameplay Ability / Reaction処理 | 実行中ActionのCancel可否とReaction処理を行う |
| Animation | Hit / Stagger / Down Animationを再生する |

## 6. 状態・Gameplay Tag

| State / Tag | 用途 |
|---|---|
| `State.Reaction.Hit` | 軽い被弾Reaction |
| `State.Reaction.Staggered` | 大きな怯みReaction |
| `State.Reaction.Downed` | Down状態 |
| `State.Dead` | Death。Reactionより優先 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| PlayerReactionAccumulation | 各Enemy / Boss AttackがPlayerへ加算する値 | Attack Master Data |
| HitThreshold | Hit判定 | Gameplay Data |
| StaggerThreshold | Stagger判定 | Gameplay Data |
| DownThreshold | Down判定 | Gameplay Data |
| Recovery / Reset Rule | 蓄積値の回復・リセット | Gameplay Data |
| ReactionMontage | Hit / Stagger / Down表示 | Asset参照 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Reaction累積値は表示しない |
| Animation | Hit / Stagger / Down専用Animation / Montage |
| VFX / SE | 攻撃の強さに応じたHit Feedbackを使用可能 |

## 9. 異常系・終了条件

- 同Frame複数Hitでも定義されたAttack Hit単位で蓄積し、不正な多重Eventを防ぐ。
- Death成立時はReaction処理を終了し、Down等へ遷移しない。
- Reaction終了時にTag / Montage /一時参照を残さない。

## 10. 受入条件

- [ ] Enemy / Boss Attack DataからReaction蓄積値を取得できる。
- [ ] 被弾ごとにPlayer内部Reaction値へ加算できる。
- [ ] 条件に応じてHit / Stagger / Downを区別できる。
- [ ] Reaction累積値をHUDへ表示しない。
- [ ] HP<=0時はReactionよりDeathを優先できる。
- [ ] Reaction終了後に一時状態が残らない。

## 11. 依存・Issue反映

- Damage / Hit Result共有基盤
- Enemy / Boss Attack Data
- Player Death

## 12. 未決事項

なし。具体閾値、蓄積減衰速度、各Animation Assetは調整項目とする。
