# FR-SAVE-001 Save Slotを1つにする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-001` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#87`, `#88` |
| 関連要件・設計 | `FR-SAVE-002`～`006`, `Docs/09_SaveCheckpointDeath.md`, `Docs/18_SaveJsonArchitecture.md` |

## 2. 目的
Initial VSの進行Saveを単一の論理Slotへ集約し、Save / Load契約を単純化する。

## 3. 確定仕様・スコープ
- 進行Saveは1 Slotとする。
- Checkpoint Auto Save、Manual Save、DeathDrop Save、Boss Reward Saveは同じ進行Slotを更新する。
- Settings Saveは進行Saveとは別契機として扱う。
- JSON SchemaやSteam Cloud同期方式は別Architectureで扱う。

## 4. 基本フロー
```text
Save Request
↓
唯一のProgress Slotを解決
↓
Current Progress Snapshot作成
↓
Save

Load Request
↓
同一Progress Slotを読込
↓
Gameplay State復元
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Save Request基盤 | Save / Load要求集約 |
| Progress Snapshot | 現在進行状態表現 |
| Storage Adapter | 実際の永続化。別Architecture |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Logical Slot Id | Save識別 | Config |
| Progress Snapshot | 保存対象 | Runtime |
| Save Result State | UI通知 | Runtime |

## 8. UI / HUD / Animation / Feedback
Save中 / 成功 / 失敗状態をGameplay HUD / Title Load UIへ通知可能にする。

## 9. 異常系・終了条件
- Save中に同一Requestを重複実行しない。
- Load失敗時に現在Runtimeを部分的に上書きしない。
- 保存媒体詳細をGameplay側へ漏らさない。

## 10. 受入条件
- [ ] 全進行Save契機を同一論理Slotへ集約できる。
- [ ] Save / Load結果を呼出元へ通知できる。
- [ ] Settings Saveと進行Saveを分離できる。

## 11. 依存・Issue反映
### 依存
- `Docs/18_SaveJsonArchitecture.md`

### Issue反映
- `#88`を進行Save Request基盤として扱う。

## 12. 未決事項
なし
