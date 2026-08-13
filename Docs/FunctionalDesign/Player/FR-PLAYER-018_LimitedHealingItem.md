# FR-PLAYER-018 回数制限付きHealing Itemを使用できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-018` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#116` |
| 関連要件・設計 | `FR-STAGE-005`, `FR-PLAYER-020`, `FR-BOSS-005` |

## 2. 目的

回数制限付き回復を戦闘Resourceとして提供し、Checkpoint / Respawnの補充とBoss AIのHealing State評価へ接続する。

## 3. 確定仕様・スコープ

- Healing Item残数が1以上の場合のみHealを開始する。
- Heal中に被弾した場合は回復を中断する。
- Checkpoint RestとRespawnで最大所持数まで補充する。
- Healing中状態をBoss AIが参照できる。

## 4. 基本フロー

```text
Heal Input
↓
ItemCount > 0?
├ No → Reject
└ Yes
  ↓
Heal開始 / Healing State
  ↓
Animation
├ 被弾 → Cancel
└ 完了 → Health回復
  ↓
終了
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Heal Ability | 実行可否、Healing State、回復適用 |
| Player Resource | Healing Item Count管理 |
| Checkpoint / Respawn | Item補充 |
| Boss AI | Healing State参照 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Healing` | Heal実行中 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| MaxHealingItemCount | 最大所持 | 調整値 |
| CurrentHealingItemCount | 残数 | Runtime |
| Heal Amount | HP回復量 | 調整値 |
| Heal Montage / Duration | Action timing | Asset / 調整値 |
| Item Consumption Timing | 残数減算契約 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Healing Item残数、HP変化を表示する |
| Animation | Heal Montage |
| VFX / SE | Heal成功 / 中断を識別可能にする |

## 9. 異常系・終了条件

- Item 0で開始しない。
- 被弾中断時のItem消費は設定したConsumption Timingへ従う。
- Death / CancelでHealing StateとMontageを残さない。
- MaxHealthを超えて回復しない。

## 10. 受入条件

- [ ] Item残数1以上でHealを開始できる。
- [ ] Heal完了でHPを回復できる。
- [ ] 被弾でHealを中断できる。
- [ ] Checkpoint / RespawnでItemをFull補充できる。
- [ ] Boss AIからHealing中状態を参照できる。

## 11. 依存・Issue反映

### 依存
- `#59` Player ASC
- `#91` Checkpoint

### Issue反映
- `#116`へ中断、補充、Boss AI参照、Item Countを反映する。

## 12. 未決事項

| 未決事項 | Issue作成前に確定必須 | 理由 |
|---|---|---|
| 被弾中断時にHealing Itemを消費済みとするタイミング | Yes | Resource結果が変わるため |
