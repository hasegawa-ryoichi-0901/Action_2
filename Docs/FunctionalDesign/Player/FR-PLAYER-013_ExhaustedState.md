# FR-PLAYER-013 Stamina枯渇時にExhaustedになる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-013` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#61` |
| 関連要件・設計 | `FR-PLAYER-011`, `FR-PLAYER-012`, `Docs/03_CombatSystem.md` |

## 2. 目的

Staminaを使い切ることに追加リスクを設け、無計画なAction連打を抑制する。

## 3. 確定仕様・スコープ

- Staminaが0以下になった場合にExhaustedへ遷移する。
- Exhausted中はAttack / Jump / Dodge等の対象Actionを禁止する。
- 通常移動は可能とする。
- 回復が設定閾値へ達したらExhaustedを解除する。
- 回復開始遅延・回復速度・解除閾値は調整可能とする。

## 4. 基本フロー

```text
Stamina更新
↓
Current <= 0?
├ No → 通常
└ Yes → Exhausted
          ↓
      対象Action禁止
          ↓
      Stamina回復
          ↓
      Recovery Threshold到達
          ↓
      Exhausted解除
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Attribute / Stamina System | 枯渇・回復値管理 |
| Gameplay State | Exhausted状態管理 |
| Action | Exhausted中の開始拒否 |
| Animation | 息切れ表現 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Exhausted` | 枯渇中の禁止条件 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Recovery Delay | 回復開始 | 調整値 |
| Recovery Rate | 回復速度 | 調整値 |
| Exhausted Recovery Threshold | 解除値 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Stamina Gaugeへ枯渇と回復を反映する |
| Animation | Exhausted / 息切れ状態を表現する |
| VFX / SE | 必要に応じ息切れ音を付与可能 |

## 9. 異常系・終了条件

- Exhaustedを重複付与しない。
- Death時はExhaustedよりDeathを優先する。
- RespawnでStamina Fullへ戻しExhaustedを解除する。

## 10. 受入条件

- [ ] Stamina 0以下でExhaustedへ1回遷移する。
- [ ] Exhausted中に禁止Actionを開始できない。
- [ ] 通常移動は継続できる。
- [ ] Threshold到達後に解除できる。

## 11. 依存・Issue反映

### 依存
- `FR-PLAYER-011`, `FR-PLAYER-012`

### Issue反映
- `#61`へExhausted Tag、回復契約、Action禁止条件を反映する。

## 12. 未決事項

なし
