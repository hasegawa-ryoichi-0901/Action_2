# FR-PLAYER-014 Dodge結果としてPerfect Dodgeが成立する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-014`](../../01_Requirements.md#fr-player-014) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#52](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52), [#56](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/56), [#57](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/57) |
| 関連要件・設計 | [`FR-PLAYER-019`](../../01_Requirements.md#fr-player-019), [`FR-PLAYER-015`](../../01_Requirements.md#fr-player-015), [Combat System](../../03_CombatSystem.md) |

## 2. 目的

1つのDodge Actionの中で、Enemy AttackとのTimingに応じてPerfect Dodge結果を成立させる。

## 3. 確定仕様・スコープ

- Input TagはDodgeのみで、Perfect Dodge専用Inputを持たない。
- Invincible WindowとPerfect Dodge Windowは別調整値とする。
- Enemy Attack判定がPerfect Dodge Windowと重なった場合にPerfect Resultを通知する。
- Invincible Windowのみと重なった場合はDamageを受けないがPerfect Resultにはしない。
- Result通知は状況に応じ複数Gameplay Event / Tagへ分岐可能とする。

## 4. 基本フロー

```text
Dodge中
↓
Enemy Attack判定
↓
Perfect Window内?
├ Yes → Perfect Dodge Result
└ No
  ↓
Invincible Window内?
├ Yes → Normal Avoid / No Damage
└ No → Hit
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Dodge Ability | Dodge Window状態管理 |
| Enemy Attack / Hit判定 | Windowとの交差評価 |
| Gameplay Event | Perfect Result通知 |
| HUD / Combat | Feedback / Counter受付へ接続 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Dodging` | Dodge実行中 |
| `Window.PerfectDodge` | Perfect判定可能期間 |
| Result / Event Tag | Perfect成立Result通知。具体階層はGameplay Tag設計に従う |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Perfect Dodge Window | Perfect判定時間 | 調整値 |
| Invincible Window | Damage無効時間 | 調整値 |
| Attack Source | Counter対象保持 | Runtime |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Perfect成立時のみFeedbackを表示する |
| VFX / SE | Normal Dodgeと区別できる成功Feedback |

## 9. 異常系・終了条件

- 同一AttackでPerfect Resultを重複通知しない。
- Dodge終了 / Cancel / DeathでWindowとAttack Source参照を解除する。
- Air Dodgeは`FR-PLAYER-019`により開始しない。

## 10. 受入条件

- [ ] Dodge Inputは1つのままNormal / Perfect Resultを分岐できる。
- [ ] Perfect WindowとInvincible Windowを独立調整できる。
- [ ] Perfect Window内のEnemy AttackでPerfect Resultを1回通知できる。
- [ ] Perfect外かつInvincible内ではDamageを受けずPerfect扱いしない。

## 11. 依存・Issue反映

### 依存
- [#52 Dodge Action](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/52)
- [#56 Window判定](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/56)

### Issue反映
- [#57](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/57)へResult通知、Feedback、Counter連携を反映する。

## 12. 未決事項

なし
