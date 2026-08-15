# FR-SAVE-003 Checkpoint MenuからManual Saveできる

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-SAVE-003`](../../01_Requirements.md#fr-save-003) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#87](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/87), [#89](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89) |
| 関連要件・設計 | [`FR-STAGE-003`](../../01_Requirements.md#fr-stage-003), [`FR-SAVE-001`](../../01_Requirements.md#fr-save-001), [`FR-SAVE-002`](../../01_Requirements.md#fr-save-002) |

## 2. 目的
PlayerがCheckpoint Menu滞在中に任意のタイミングで現在進行状態を保存できるようにする。

## 3. 確定仕様・スコープ
- Manual SaveはCheckpoint Menuからのみ実行可能。
- Checkpoint外からManual Saveは提供しない。
- Progress Slotは`FR-SAVE-001`と同じ1 Slotを使用する。
- Weapon Upgrade完了自体はAuto Saveしないため、必要ならManual Saveできる。

## 4. 基本フロー
```text
Checkpoint Menu
↓
Manual Save選択
↓
Current Progress Snapshot
↓
Save Request
↓
Result表示
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Checkpoint Menu | Manual Save操作 |
| Save基盤 | Snapshot保存・結果通知 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Checkpoint Menu Active | 実行可否 | Runtime |
| Progress Snapshot | 保存対象 | Runtime |

## 8. UI / HUD / Animation / Feedback
Manual Save項目、Save中 / 成功 / 失敗Feedbackを表示する。

## 9. 異常系・終了条件
- Checkpoint Menu外ではRequestを拒否する。
- Save中に連打して重複Saveしない。

## 10. 受入条件
- [ ] Checkpoint MenuからManual Saveできる。
- [ ] Checkpoint外では実行できない。
- [ ] Save結果をUIへ表示できる。

## 11. 依存・Issue反映
### 依存
- [#88 Save基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/88)
- [#91 Checkpoint](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/91)

### Issue反映
- [#89](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/89)へManual Save導線も含める。

## 12. 未決事項
なし
