# FR-SAVE-007 Steam CloudへSave Dataを同期する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-SAVE-007`](../../01_Requirements.md#fr-save-007) |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | [`FR-SAVE-001`](../../01_Requirements.md#fr-save-001)～[`006`](../../01_Requirements.md#fr-save-006), [Save JSON Architecture](../../18_SaveJsonArchitecture.md) |

## 2. 目的
Local Save仕様が安定した後、Steam公開版でProgress / Settings SaveをCloud同期可能にする。

## 3. 確定仕様・スコープ
- α版対象外。
- Local Save / Load契約を正とし、その上にSteam Cloud同期を追加する。
- Cloud固有APIをGameplay Systemへ直接依存させない。

## 4. 基本フロー
```text
Local Save成功
↓
Cloud Sync Adapter
↓
Steam Cloud更新

Load時
Local / Cloud状態取得
↓
Post-VSで確定するConflict Policy
↓
Local Save契約へ復元
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Local Save | Gameplay上の正本契約 |
| Cloud Adapter | Steam API境界 |
| Conflict Resolver | 競合解決 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Local Save File / Logical Id | 同期対象 | Save Data |
| Timestamp / Version | 競合判定 | Save Metadata |
| Cloud Result | 同期結果 | Runtime |

## 8. UI / HUD / Animation / Feedback
同期失敗 / 競合時に必要なFeedbackをTitle / Save UIへ表示可能にする。

## 9. 異常系・終了条件
- Network / Steam未利用時もLocal Saveを失敗させない。
- Cloud失敗でLocal Saveを破損させない。

## 10. 受入条件
- [ ] Local Save契約を変更せずCloud同期を追加できる。
- [ ] Steam未接続でもLocal Saveを利用できる。
- [ ] 同期結果をUIへ通知できる。

## 11. 依存・Issue反映
### 依存
- Local Save Architecture完成後

### Issue反映
- Post-VS RoadmapでIssue化する。

## 12. 未決事項
| 未決事項 | Issue作成前に確定必須 | 理由 |
|---|---|---|
| Local / Cloud競合時の採用Policy | Yes | Player Data損失Riskがあるため |
