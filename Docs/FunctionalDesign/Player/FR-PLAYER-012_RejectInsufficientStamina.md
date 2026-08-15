# FR-PLAYER-012 Stamina不足時は対象Actionを実行できない

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-012`](../../01_Requirements.md#fr-player-012) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#61](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61) |
| 関連要件・設計 | [`FR-PLAYER-011`](../../01_Requirements.md#fr-player-011), [`FR-PLAYER-013`](../../01_Requirements.md#fr-player-013) |

## 2. 目的

必要Staminaを満たさないActionを開始させず、Cost適用とAction状態の不整合を防ぐ。

## 3. 確定仕様・スコープ

- ActionごとのRequired StaminaとCurrent Staminaを開始前に比較する。
- 不足時はCost・Montage・Gameplay Tag・Hitboxを変更せずRejectする。
- Input Bufferへ保存するかどうかはCombo / Action側の受付Window Ruleへ従う。

## 4. 基本フロー

```text
Action Request
↓
Required Cost取得
↓
Current >= Required?
├ Yes → Action開始
└ No → Reject / 状態変更なし
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Ability / Action | 実行前Cost確認 |
| Attribute | Current Stamina提供 |
| HUD / Feedback | 必要に応じ不足を視覚的に示す |

## 6. 状態 / Gameplay Tag

不足Reject専用の継続Tagは不要。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| CurrentStamina | Current値 | Runtime |
| Required Stamina Cost | 実行条件 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Stamina Gaugeで不足を認識できる。Reject専用Popupは必須としない |

## 9. 異常系・終了条件

- Cost取得失敗時に0 Costとして誤実行しない。
- Reject時にMontage / Tag / Costの部分適用を残さない。

## 10. 受入条件

- [ ] Current StaminaがCost未満ならActionを開始しない。
- [ ] Reject時にStaminaを消費しない。
- [ ] Reject時にAttack / Dodge状態を開始しない。

## 11. 依存・Issue反映

### 依存
- [`FR-PLAYER-011`](../../01_Requirements.md#fr-player-011)

### Issue反映
- [#61](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61)の共通Cost契約としてAttack / Dodge各Issueから利用する。

## 12. 未決事項

なし
