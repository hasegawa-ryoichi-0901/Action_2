# FR-PLAYER-023 PlayerはHit / Stagger / Down Reactionを持つ

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-023` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#149` |
| 関連要件・設計 | `FR-PLAYER-020`, Enemy / Boss Attack Data, `Docs/03_CombatSystem.md` |

## 2. 目的

Enemy / Boss Attackの重さをPlayer Reactionへ反映し、軽いHitからDownまで段階的な被弾結果を実現する。

## 3. 確定仕様・スコープ

- Player ReactionはHit / Stagger / Downの3段階とする。
- 通常Enemy / Bossの各Attack DataにPlayer Reaction用蓄積値を持たせる。
- 被弾ごとに内部蓄積値へ加算してReactionを判定する。
- 蓄積値はPlayer HUDへ表示しない。
- DeathはすべてのReactionより優先する。
- Threshold、減衰 / Reset RuleはGameplay Dataとして調整可能にする。

## 4. 基本フロー

```text
Enemy / Boss Attack Hit
↓
Health Damage + Reaction Accumulation取得
↓
Health <= 0?
├ Yes → Death
└ No
  ↓
内部Reaction値加算
↓
Threshold評価
├ Down
├ Stagger
└ Hit
↓
対応Reaction
↓
Recovery / Reset Rule
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Attack Data | Reaction蓄積値提供 |
| Player Reaction | 内部値蓄積・Threshold判定 |
| Animation | Hit / Stagger / Down表現 |
| Death処理 | Reactionより優先して死亡確定 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Reaction.Hit` | 軽被弾 |
| `State.Reaction.Staggered` | 大きな硬直 |
| `State.Reaction.Downed` | Down状態 |
| `State.Dead` | Reactionより優先 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| PlayerReactionAccumulation | Attackごとの蓄積量 | Master Data |
| Hit / Stagger / Down Threshold | Reaction判定 | 調整値 |
| Recovery / Reset Rule | 蓄積回復 | Gameplay Data |
| Hit / Stagger / Down Animation | Reaction表現 | Asset |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | 内部Reaction蓄積値は表示しない |
| Animation | Hit / Stagger / Downを識別可能にする |
| VFX / SE | Reaction強度を必要に応じ区別する |

## 9. 異常系・終了条件

- 同Frame複数HitでもState Eventを不正に重複させない。
- Health<=0ならReaction開始よりDeathを優先する。
- Reaction終了 / DeathでTag、Montage、一時値状態を矛盾させない。

## 10. 受入条件

- [ ] Attack Dataから蓄積値を取得し内部値へ加算できる。
- [ ] Hit / Stagger / DownをThresholdで区別できる。
- [ ] 内部蓄積値をHUDへ表示しない。
- [ ] DeathをReactionより優先できる。
- [ ] Reaction終了後に一時状態が残らない。

## 11. 依存・Issue反映

### 依存
- `#62` Damage / Hit Result
- `#83` Player Death

### Issue反映
- `#149`へAttack Data、内部蓄積、3 Reaction、Death優先を反映する。

## 12. 未決事項

なし
