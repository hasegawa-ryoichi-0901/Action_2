# FR-PLAYER-011 AttackとDodgeでStaminaを消費する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-011`](../../01_Requirements.md#fr-player-011) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#61](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61) |
| 関連要件・設計 | [`FR-PLAYER-010`](../../01_Requirements.md#fr-player-010), [`FR-PLAYER-012`](../../01_Requirements.md#fr-player-012), [`FR-PLAYER-013`](../../01_Requirements.md#fr-player-013), [`FR-PLAYER-019`](../../01_Requirements.md#fr-player-019), [GAS Design](../../05_GASDesign.md) |

## 2. 目的

Attack / Dodgeの連続使用にResource制約を設け、Action選択へRiskと間隔を与える。

## 3. 確定仕様・スコープ

- Light / Heavy / Dodge等の対象Action開始時に定義されたStamina Costを消費する。
- CostはGameplay Dataから取得しActionごとに調整可能とする。
- Cost不足時は`FR-PLAYER-012`によりAction開始を拒否する。
- Stamina 0以下は`FR-PLAYER-013`のExhaustedへ接続する。

## 4. 基本フロー

```text
Action Request
↓
Required Stamina取得
↓
Current Stamina >= Cost?
├ No → Reject
└ Yes → Cost適用 → Action開始
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Character Attribute | Current / Max Stamina保持 |
| GAS / Ability Cost | Cost判定・適用 |
| Action Data | ActionごとのCost提供 |
| HUD | Current / Max Stamina表示 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Exhausted` | Stamina枯渇状態 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| MaxStamina | 最大値 | 調整値 |
| CurrentStamina | 現在値 | Runtime |
| StaminaCost | Action Cost | Gameplay Data |
| Recovery Rate / Delay | 回復 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Stamina Gaugeを表示し消費・回復を反映する |

## 9. 異常系・終了条件

- Costを二重適用しない。
- Current Staminaを負値としてGameplay判断へ利用しない。
- Cancel時のCost返却はAction側仕様で明示されない限り自動返却しない。

## 10. 受入条件

- [ ] 対象Actionで定義Costを1回だけ消費できる。
- [ ] Cost不足時にActionを開始しない。
- [ ] HUDへStamina変化を反映できる。
- [ ] Stamina 0以下をExhaustedへ接続できる。

## 11. 依存・Issue反映

### 依存
- [#59](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/59), [#60](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/60)

### Issue反映
- [#61](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61)をAttack / Dodgeで共有するStamina基盤として扱う。

## 12. 未決事項

なし
