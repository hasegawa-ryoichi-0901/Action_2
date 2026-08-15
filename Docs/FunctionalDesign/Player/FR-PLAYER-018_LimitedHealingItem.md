# [FR-PLAYER-018] 使用回数制限付き回復アイテム

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-018`](../../01_Requirements.md#fr-player-018) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#116](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/116) |
| 関連要件・設計 | [`FR-STAGE-005`](../../01_Requirements.md#fr-stage-005), [`FR-PLAYER-020`](../../01_Requirements.md#fr-player-020), [`FR-BOSS-005`](../../01_Requirements.md#fr-boss-005) |

## 2. 目的

回数制限付きHealをCombat Resourceとして提供し、Checkpoint / Respawn補充とBoss AIのHealing State評価へ接続する。

## 3. 確定仕様・スコープ

- Healing Item残数が1以上の場合のみHealを開始する。
- Heal Input成立後、PlayerがHeal Animationへ遷移した直後にHealing Itemを1個消費する。
- Item消費後に被弾してHealが中断された場合も、消費したHealing Itemは返却しない。
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
Heal Animation開始
  ↓
Healing Itemを1個消費
  ↓
Animation継続
├ 被弾 → Cancel / Itemは返却しない
└ 完了 → Health回復
  ↓
終了
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Heal Ability | 実行可否、Healing State、Animation開始後のItem消費、Heal適用 |
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
| Heal Montage / Duration | Action Timing | Asset / 調整値 |
| Item Consumption Timing | Animation開始直後に1個消費 | 確定仕様 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Animation開始直後のItem消費をHealing Item残数へ反映し、Heal完了時はHP変化を反映する |
| Animation | Heal Montage |
| VFX / SE | Heal成功 / 中断を識別可能にする |

## 9. 異常系・終了条件

- Item 0で開始しない。
- Heal Animation開始前に中断された場合はItemを消費しない。
- Heal Animation開始直後にItemを1個消費した後は、被弾・CancelでもItemを返却しない。
- 同一Heal ActionでItemを2回以上消費しない。
- Death / CancelでHealing StateとMontageを残さない。
- MaxHealthを超えて回復しない。

## 10. 受入条件

- [ ] Item残数1以上でHealを開始できる。
- [ ] Heal Animation開始直後にItemを1個だけ消費できる。
- [ ] Item消費後に被弾でHealが中断されてもItemを返却しない。
- [ ] Heal完了時にHPを回復できる。
- [ ] Checkpoint / RespawnでItemをFull補充できる。
- [ ] Boss AIからHealing中状態を参照できる。

## 11. 依存・Issue反映

### 依存
- [#59 Player ASC](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/59)
- [#91 Checkpoint](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/91)

### Issue反映
- [#116](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/116)へAnimation開始直後のItem消費、中断時非返却、補充、Boss AI参照を反映する。

## 12. 未決事項

なし
