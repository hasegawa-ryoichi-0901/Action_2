# FR-SAVE-005 DeathDrop生成・回収後にAuto Saveする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-005` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#90`, `#82`, `#86` |
| 関連設計 | `FR-STAGE-008`, `FR-STAGE-009`, `FR-STAGE-010`, `FR-STAGE-012` |

## 2. 目的

DeathDropとPlayer Inventoryの状態を同一保存時点で確定し、終了・再起動後のResource複製、二重回収、旧Drop復活を防ぐ。

## 3. 確定仕様・基本フロー

### Death時

```text
[Death Animation完了]
      ↓
[旧DeathDropがあれば本体・内容を完全消失]
      ↓
[Player Inventoryから新DeathDropへ移動]
      +--> Upgrade Material 100%
      +--> Gold 100%
      ↓
[死亡座標・格納内容確定]
      ↓
[Auto Save]
      ↓
[Camera確認 → Fade Out → Respawn]
```

### 回収時

```text
[DeathDrop回収成立]
      ↓
[Upgrade Material / GoldをInventoryへ全量返却]
      ↓
[DeathDrop回収済み・消去を確定]
      ↓
[Auto Save]
```

- Death時SaveはDeathDrop確定後、Camera確認・Respawnより前。
- Goldの割合消失は行わない。
- 未回収DeathDropはSave / Load後も復元する。

## 4. 責務

| 対象 | 責務 |
|---|---|
| DeathDrop System | Active Drop位置・内容・回収状態を提供する |
| Player Inventory | Gold / Upgrade Materialの正本 |
| Save System | Snapshot作成、保存、多重要求制御、Load復元 |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。Save中状態とActive DeathDropを一意に識別できること。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| DeathDrop Transform | World復元 | JSON Save対象 |
| Stored Upgrade Material | 格納量復元 | JSON Save対象 |
| Stored Gold | 格納量復元 | JSON Save対象 |
| Unrecovered / Active State | Drop復元可否 | JSON Save対象 |
| Active Checkpoint | Load後Player再開地点 | Progress Save |

JSON Schema、Versioning、Reader / Writerは別Architecture Designで定義する。

## 7. UI / Animation / Feedback

- Auto Save中 / 成功 / 失敗状態をHUDへ通知可能にする。
- Save表示方法は`FR-UI-002`へ委譲する。

## 8. 異常系・終了条件

- DeathDrop内容確定前にDeath時Saveを発行しない。
- 同一Death / 回収でSave要求を重複発行しない。
- Load後に同一DeathDropを二重生成しない。
- Save失敗でInventoryとDeathDropのRuntime状態を巻き戻す要件は設けないが、失敗を検知・通知できること。

## 9. 受入条件

- [ ] 新DeathDropの位置・Material100%・Gold100%確定後にAuto Saveできる。
- [ ] Camera確認 / Respawnより前にDeath時Saveを要求できる。
- [ ] 回収完了後にAuto Saveできる。
- [ ] 再死亡時は旧DeathDropの消失状態も含めて保存できる。
- [ ] Save / Load後に未回収DeathDropの位置と内容を1つだけ復元できる。
- [ ] Load後にPlayerをActive Checkpoint、未設定時PlayerStartから再開できる。
- [ ] Resourceを二重取得・二重生成しない。

## 10. 依存・Issue反映

- `#90`, `#82`, `#84`, `#86`

## 11. 未決事項

なし。JSON具体構造は別Architecture Designの対象。
