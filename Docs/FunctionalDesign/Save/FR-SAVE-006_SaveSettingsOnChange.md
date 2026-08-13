# FR-SAVE-006 Settings変更時に設定データを保存する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-SAVE-006`](../../01_Requirements.md#fr-save-006) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#87](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/87), [#104](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/104) |
| 関連要件・設計 | [`FR-UI-001`](../../01_Requirements.md#fr-ui-001), [`FR-SAVE-001`](../../01_Requirements.md#fr-save-001) |

## 2. 目的
Config変更をProgress Saveとは独立して保存し、次回起動時にも設定を維持する。

## 3. 確定仕様・スコープ
- Settings変更時に設定Saveを行う。
- Progress Auto Save契機とは分離する。
- Title Config等から変更された設定を保存対象とする。

## 4. 基本フロー
```text
Config変更
↓
値Validation / 適用
↓
Settings Snapshot
↓
Settings Save
↓
Result通知
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Config UI | 設定変更操作 |
| Settings System | 値Validation / Runtime適用 |
| Settings Save | 設定永続化 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Audio / Camera / Input Settings | 設定内容 | Runtime / Save |
| Settings Version | 将来互換 | Save Data |

## 8. UI / HUD / Animation / Feedback
Config UIへ保存結果を必要に応じ表示する。

## 9. 異常系・終了条件
- 不正値を保存前にClamp / Rejectする。
- Progress Save失敗とSettings Save結果を混同しない。

## 10. 受入条件
- [ ] 設定変更時にSettings Saveできる。
- [ ] 再起動後に設定を復元できる。
- [ ] Progress Save契機と独立して動作できる。

## 11. 依存・Issue反映
### 依存
- Config UI

### Issue反映
- [#104](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/104)へSettings Snapshot / Save / Loadを反映する。

## 12. 未決事項
なし
