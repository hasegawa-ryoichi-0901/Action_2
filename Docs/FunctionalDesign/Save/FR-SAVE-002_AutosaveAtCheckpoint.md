# FR-SAVE-002 Checkpoint Rest確定後にAuto Saveする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-002` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#89` |
| 関連設計 | `FR-STAGE-003`, `FR-STAGE-004`, `FR-STAGE-005` |

## 2. 目的

Checkpoint利用時の再開地点とRest後状態を同じSnapshotとして保存する。

## 3. 確定仕様・基本フロー

```text
[Interaction]
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
[Auto Save]
```

- Checkpointへ接近しただけではSaveしない。
- Menu Openだけを単独契機とせず、Rest処理まで確定したSnapshotを保存する。
- 同一Checkpoint利用でAuto Save要求を重複発行しない。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Checkpoint / Rest | ActiveCheckpointとRest完了を通知する |
| Save System | Snapshot作成、保存、多重要求制御 |
| UI / HUD | Save状態を表示する |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。Save中 / 完了 / 失敗状態を通知できること。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| ActiveCheckpointId | Load / Respawn地点 | Progress Save |
| Player Rest後状態 | HP / Stamina / Healing等の整合確認 | Runtime / Progress Save |
| Inventory / Progress Data | 現在進行保存 | Player / Stage Data |

## 7. UI / Animation / Feedback

- Save中 / 完了 / 失敗を`FR-UI-002`へ通知可能にする。

## 8. 異常系・終了条件

- Rest確定前にSaveしない。
- 同一Interactionで重複Saveしない。
- Save失敗でもCheckpoint Runtime状態を不整合にしない。

## 9. 受入条件

- [ ] Checkpoint接近だけではSaveしない。
- [ ] ActiveCheckpoint更新後にMenuをOpenできる。
- [ ] Rest処理確定後にAuto Saveを1回要求できる。
- [ ] 保存Snapshotが更新後ActiveCheckpointを含む。
- [ ] Save成功 / 失敗をUIへ通知できる。
- [ ] 同一利用でSaveを重複発火しない。

## 10. 依存・Issue反映

- `#89`, `#91`

## 11. 未決事項

なし。
