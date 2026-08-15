# FR-SAVE-002 Checkpoint Rest確定後にAuto Saveする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-SAVE-002`](../../01_Requirements.md#fr-save-002) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#87](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/87), [#89](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89) |
| 関連要件・設計 | [`FR-STAGE-003`](../../01_Requirements.md#fr-stage-003)～[`005`](../../01_Requirements.md#fr-stage-005), [`FR-SAVE-001`](../../01_Requirements.md#fr-save-001) |

## 2. 目的
Checkpoint利用後のActiveCheckpoint・回復・Enemy Respawn状態を一貫したSnapshotとして保存する。

## 3. 確定仕様・スコープ
- `Interaction → ActiveCheckpoint更新 → Menu Open → Rest処理確定 → Auto Save`の順とする。
- Checkpoint接近だけではSaveしない。
- Rest処理はHP / Stamina Full、Healing Item補充、Normal Enemy Respawnを含む。
- 同一InteractionでAuto Saveを重複発行しない。

## 4. 基本フロー
```text
Checkpoint Interaction
↓
ActiveCheckpoint更新
↓
Menu Open
↓
Rest確定
↓
Progress Snapshot
↓
Auto Save
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Checkpoint | 順序管理・Save Request発行 |
| Rest処理 | 保存前の回復 / Respawn状態確定 |
| Save基盤 | Snapshot保存 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| ActiveCheckpointId | Respawn地点 | Runtime / Save |
| Player Rest State | HP / Stamina / Heal | Runtime |
| Enemy Reset State | Respawn結果 | Runtime |

## 8. UI / HUD / Animation / Feedback
Save中 / 成功 / 失敗をHUDへ通知可能にする。

## 9. 異常系・終了条件
- Rest完了前にSnapshotを保存しない。
- 同一Menu Open / Interactionで重複Saveしない。
- Save失敗してもCheckpoint MenuからRecovery可能にする。

## 10. 受入条件
- [ ] Rest確定後だけAuto Saveできる。
- [ ] ActiveCheckpoint更新済み状態を保存できる。
- [ ] 接近だけではSaveしない。
- [ ] 重複Saveを防止できる。

## 11. 依存・Issue反映
### 依存
- [#91 Checkpoint](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/91)
- [#88 Save基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/88)

### Issue反映
- [#89](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89)へ確定順序とSnapshot条件を反映する。

## 12. 未決事項
なし
