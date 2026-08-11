# FR-STAGE-009 DeathDropからResourceを回収する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-009` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#82`, `#86` |
| 関連設計 | `FR-STAGE-008`, `FR-STAGE-010`, `FR-SAVE-005` |

## 2. 目的

未回収DeathDropに格納されたUpgrade MaterialとGoldをPlayer Inventoryへ安全に全量返却する。

## 3. 確定仕様・基本フロー

```text
[PlayerがDeathDrop回収条件を満たす]
      ↓
[DeathDrop内容取得]
      ↓
[Upgrade Material全量をPlayer Inventoryへ返却]
[Gold全量をPlayer Inventoryへ返却]
      ↓
[DeathDropを回収済みに確定]
      ↓
[World上のDeathDrop消去]
      ↓
[Auto Save]
```

- 回収は1回だけ成立する。
- Gold / Upgrade Materialの正本はPlayer Inventory。
- 回収完了直後にAuto Saveする。

## 4. 責務

| 対象 | 責務 |
|---|---|
| DeathDrop | 格納Resourceと回収済み状態を保持する |
| Player Inventory | Gold / Upgrade Materialを受け取る |
| Save System | 回収完了状態をAuto Saveする |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。二重回収を防止できる回収状態を持つこと。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| StoredUpgradeMaterial | 回収量 | DeathDrop Runtime / Save |
| StoredGold | 回収量 | DeathDrop Runtime / Save |
| IsRecovered相当の状態 | 二重回収防止 | Runtime / Save |

## 7. UI / Animation / Feedback

- 回収成功時にMaterial / Gold取得Feedbackを表示可能にする。
- 表示方法・演出は調整項目とする。

## 8. 異常系・終了条件

- 同一DeathDropを二重回収しない。
- Inventory加算途中でWorld Dropだけ消さない。
- 無効参照・再入EventでResourceを重複付与しない。

## 9. 受入条件

- [ ] 格納Upgrade Materialを全量Inventoryへ返却できる。
- [ ] 格納Goldを全量Inventoryへ返却できる。
- [ ] 同一DeathDropを二重回収できない。
- [ ] 回収完了後にWorldからDeathDropを消去できる。
- [ ] 回収完了後にAuto Save要求を1回発行できる。

## 10. 依存・Issue反映

- `#86`, `#90`
- `FR-SAVE-005`

## 11. 未決事項

なし。回収FeedbackのVisualは調整項目とする。
