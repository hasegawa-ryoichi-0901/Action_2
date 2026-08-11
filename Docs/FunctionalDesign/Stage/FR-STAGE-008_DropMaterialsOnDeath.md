# FR-STAGE-008 死亡時にInventory ResourceをDeathDropへ移す

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-008` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#82`, `#84` |
| 関連設計 | `FR-STAGE-009`, `FR-STAGE-010`, `FR-SAVE-005`, `FR-STAGE-012` |

## 2. 目的

死亡時にPlayer Inventoryが所持する回収対象Resourceを全量DeathDropへ移し、回収前の再死亡にリスクを持たせる。

## 3. 確定仕様・基本フロー

```text
[Death Animation完了]
      ↓
[旧DeathDropあり？]
      +-- Yes --> [旧DeathDrop本体・格納Resourceを完全消失]
      ↓
[Player Inventory取得]
      +--> Upgrade Material 100%
      +--> Gold 100%
      ↓
[死亡座標へ新DeathDrop生成]
      ↓
[死亡座標・格納内容確定]
      ↓
[Auto Save]
      ↓
[Camera確認]
```

- Gold / Upgrade Materialの正本はPlayer Inventory。
- Goldの割合消失は行わない。
- DeathDrop確定後、Camera確認・Respawnより前にAuto Saveする。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Player Inventory | Gold / Upgrade Materialの正本 |
| DeathDrop処理 | Resource全量移動、旧Drop消失、新Drop生成 |
| Save System | DeathDrop座標・内容確定後にAuto Save |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。Death処理の多重実行を防止できる状態を持つこと。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| UpgradeMaterialAmount | DeathDrop格納量 | Player Inventory Runtime |
| GoldAmount | DeathDrop格納量 | Player Inventory Runtime |
| DeathDropTransform | 復元位置 | Save対象 |
| DeathDropContent | 格納Resource | Save対象 |

## 7. UI / Animation / Feedback

- Death Animation完了後に生成する。
- CameraからDeathDropを確認できるフローへ接続する。

## 8. 異常系・終了条件

- Resource移動前後で複製・負値を発生させない。
- 旧DeathDropがある場合は新Drop生成前に旧内容を完全消失させる。
- 同一Deathで新DeathDropを複数生成しない。

## 9. 受入条件

- [ ] Death Animation完了後に処理を開始する。
- [ ] Upgrade Material 100%をInventoryからDeathDropへ移せる。
- [ ] Gold 100%をInventoryからDeathDropへ移せる。
- [ ] 旧未回収DeathDropがあれば本体・内容を完全消失させる。
- [ ] 死亡地点に新DeathDropを1つだけ生成する。
- [ ] DeathDrop座標・内容確定後にAuto Save要求を1回発行する。
- [ ] Resource複製・負値が発生しない。

## 10. 依存・Issue反映

- `#82`, `#84`, `#90`
- `FR-SAVE-005`

## 11. 未決事項

なし。DeathDrop表示Assetは調整項目とする。
