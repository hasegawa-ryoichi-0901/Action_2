# [NFR-MAINT-004] Mover固有依存の戦闘機能からの分離

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-MAINT-004`](../../01_Requirements.md#nfr-maint-004) |
| 優先度 | `Must` |
| 対応範囲 | `α版 / 将来Mover検証` |
| 設計状態 | `Draft` |
| 関連Issue | [#139](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139) |
| 関連要件・設計 | [`FR-PLAYER-001`](../../01_Requirements.md#fr-player-001), [Class Design](../../07_ClassDesign.md) |

## 2. 目的
現在のCharacterMovement利用を維持しつつ、将来Moverを検証する場合にもCombat SystemをMover固有APIへ結合させない。

## 3. 確定仕様・スコープ
- α版ではCharacterMovementを現行Movement実装として利用する。
- 未使用の`IMovementDriver`、`UMovementAdapterComponent`等を先行導入しない。
- Combat / Abilityは「移動要求」というGameplay上の責務を持ち、Mover固有型・固有APIを直接参照しない。
- Mover採用の必要性が確認された時点でのみ境界を追加設計する。

## 4. 基本フロー
```text
Combat / Abilityが移動補正を要求
↓
現在のPlayer Movement契約へ要求
↓
CharacterMovementで実行

将来Mover採用時
↓
Gameplay契約を維持
↓
Movement実装側だけ差し替え可能にする
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Combat / Ability | Gameplay上の移動要求 |
| Player Movement | 具体Movement実行 |
| 将来Adapter | 必要性確定後のみ実装差分吸収 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Movement Request Parameters | Dodge / Attack移動補正 | Runtime / 調整値 |
| Current Movement Backend | 実装確認 | Architecture |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- α版のためだけに未使用抽象層を追加しない。
- Combat ClassのPublic APIにMover固有型を露出しない。
- 将来Mover検証で既存Combat Ruleを書き換える前提にしない。

## 10. 受入条件
- [ ] α版をCharacterMovementで成立させられる。
- [ ] Combat / AbilityがMover固有APIへ直接依存しない。
- [ ] 不要なMovement Adapterを先行実装しない。
- [ ] 将来差し替える境界を説明できる。

## 11. 依存・Issue反映
### 依存
- [`FR-PLAYER-001`](../../01_Requirements.md#fr-player-001)

### Issue反映
- [#139](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139)へInput抽象化とは別観点としてMovement依存境界を反映する。

## 12. 未決事項
なし
