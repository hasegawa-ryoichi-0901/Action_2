# FR-SAVE-005 DeathDrop生成・回収後にAuto Saveし未回収Dropを復元する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-005` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#90` |
| 関連要件・設計 | `FR-STAGE-008`～`010`, `FR-STAGE-012`, `Docs/18_SaveJsonArchitecture.md` |

## 2. 目的
DeathDropの位置・格納Resource・回収状態を進行Saveへ含め、再起動後も死亡回収ループを維持する。

## 3. 確定仕様・スコープ
- 新DeathDropの死亡座標・Material100%・Gold100%が確定した直後にAuto Saveする。
- Death時SaveはCamera確認・Fade・Respawnより前に行う。
- DeathDrop回収完了後にもAuto Saveする。
- 再死亡で旧Dropが消失した状態も保存する。
- Save / Load後に未回収DeathDropを1つだけ同じ座標・内容で復元する。
- JSON Schemaは別Architectureで扱う。

## 4. 基本フロー
```text
DeathDrop生成 / 内容確定
↓
Auto Save
↓
Respawn

または

DeathDrop回収 / 消去
↓
Auto Save

Load
↓
未回収Dropあり?
├ Yes → 位置 / 内容を1つ復元
└ No → 生成なし
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| DeathDrop Flow | Save要求タイミング |
| Save Snapshot | Drop状態保持 |
| Load Restore | Active Drop復元 |

## 6. 状態 / Gameplay Tag
DeathDrop Active / Recovered状態をSave Stateとして保持する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| DeathDrop Transform | 復元位置 | Runtime / Save |
| Stored Material / Gold | 復元内容 | Runtime / Save |
| Active / Recovered State | 一意性 | Runtime / Save |
| ActiveCheckpointId | Player再開地点 | Runtime / Save |

## 8. UI / HUD / Animation / Feedback
Save中 / 成功 / 失敗をHUDへ通知する。DeathDrop自体のWorld表示はStage側が担当する。

## 9. 異常系・終了条件
- Drop確定前にSaveしない。
- Save / Load後にDropを二重生成しない。
- 回収済みDropを復元しない。
- 旧Drop消失前のSnapshotへ戻さない。

## 10. 受入条件
- [ ] Drop生成確定後にAuto Saveできる。
- [ ] 回収完了後にAuto Saveできる。
- [ ] Load後に未回収Dropを1つだけ復元できる。
- [ ] 位置 / Material / Goldを復元できる。

## 11. 依存・Issue反映
### 依存
- `#84`, `#86`, `#88`

### Issue反映
- `#90`へ生成 / 回収 / 復元契約を反映する。

## 12. 未決事項
なし
