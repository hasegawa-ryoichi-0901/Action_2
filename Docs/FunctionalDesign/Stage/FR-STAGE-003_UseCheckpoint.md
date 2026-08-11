# FR-STAGE-003 Checkpointを使用してMenuを開く

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-003` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#91`, `#92`, `#93` |
| 関連設計 | `FR-STAGE-004`, `FR-STAGE-005`, `FR-STAGE-007`, `FR-SAVE-002`, `FR-STAGE-012` |

## 2. 目的

Checkpointを攻略拠点として使用し、再開地点更新、Menu、Rest、Enemy Respawn、Saveを一貫した順序で処理する。

## 3. 確定仕様・基本フロー

```text
[Interaction]
      ↓
[Checkpoint利用条件確認]
      ↓
[ActiveCheckpoint更新]
      ↓
[Menu Open]
      ↓
[Rest処理確定]
      +--> HP Full
      +--> Stamina Full
      +--> Healing Item補充
      +--> Normal Enemy Respawn
      ↓
[FR-SAVE-002 Auto Save]
```

- Checkpointへ接近しただけでは利用成立・Saveしない。
- Initial VSはSwordのみで、Weapon ChangeはPost-VS。
- Weapon UpgradeはMenuから利用可能だが、Upgrade完了自体はAuto Save契機にしない。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Checkpoint | Interaction成立、Checkpoint識別、ActiveCheckpoint更新要求 |
| Menu / UI | Checkpoint Menu表示・操作 |
| Player / ASC | HP / Stamina回復 |
| Inventory / Healing | Healing Item補充 |
| Enemy Respawn | Normal Enemy復活 |
| Save System | Rest確定後Auto Save |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。多重Interaction / Menu Openを防止できる利用状態を持つこと。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| CheckpointId | ActiveCheckpoint識別・Save | Master / Map Data |
| RespawnTransform | Player Respawn位置 | Map Data |
| HealingItemMax | 補充上限 | Gameplay Data |
| Enemy Respawn Group / Identifier | 復活対象 | Stage Data |

## 7. UI / Animation / Feedback

- Checkpoint Menuを表示する。
- MenuからWeapon Upgrade / Manual Save等へ遷移可能にする。
- Interaction / Rest演出はAsset調整可能。

## 8. 異常系・終了条件

- 死亡中はCheckpoint利用を開始しない。
- 多重InteractionでActiveCheckpoint更新、Rest、Auto Saveを重複実行しない。
- Menu Close / Level Transitionで一時UI・入力状態を残さない。

## 9. 受入条件

- [ ] Interaction成立後にActiveCheckpointを更新できる。
- [ ] ActiveCheckpoint更新後にMenuをOpenできる。
- [ ] Menu Open後にHP / Stamina Full、Healing Item補充、Normal Enemy Respawnを確定できる。
- [ ] Rest確定後にAuto Saveへ1回だけ接続できる。
- [ ] Checkpoint接近だけではSaveしない。
- [ ] Respawn時に最後のActiveCheckpointを参照できる。

## 10. 依存・Issue反映

- `#91`, `#92`, `#93`, `#89`

## 11. 未決事項

なし。Checkpoint Visual / Rest演出は調整項目とする。
