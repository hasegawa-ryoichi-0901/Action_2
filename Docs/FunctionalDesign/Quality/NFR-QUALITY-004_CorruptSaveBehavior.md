# NFR-QUALITY-004 Save破損時の挙動を確認する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-QUALITY-004`](../../01_Requirements.md#nfr-quality-004) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#144](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/144), [#154](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154) |
| 関連要件・設計 | [`FR-SAVE-001`](../../01_Requirements.md#fr-save-001)～[`006`](../../01_Requirements.md#fr-save-006), [Save JSON Architecture](../../18_SaveJsonArchitecture.md) |

## 2. 目的
読込不能・不正形式のSave Dataを正常進行Dataとして適用せず、Crashや部分的なRuntime破損を防ぐ。

## 3. 確定仕様・スコープ
- Save読込時に形式・Version・必須Data等を検証可能にする。
- 破損または読込失敗したDataをRuntimeへ部分適用しない。
- Save破損を検出した場合は破損Saveを削除し、New Gameを開始できる状態へ戻す。
- 破損SaveからのBackup復旧は初期プレイアブル版では行わない。
- Load失敗をUI / 呼出元へ通知可能にする。

## 4. 基本フロー
```text
Save Load Request
↓
Data読込
↓
Validation
├ Valid → Runtimeへ復元
└ Invalid / Corrupt
   ↓
Runtimeへ適用しない
   ↓
破損Saveを削除
   ↓
Failure / Recovery通知
   ↓
New Game開始可能状態へ戻る
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Save Reader / Validator | 破損検出 |
| Save System | 破損Save削除と状態初期化 |
| Gameplay Restore | Valid Dataのみ適用 |
| UI | Load失敗通知とNew Game導線 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Save Version | Compatibility確認 | Save Metadata |
| Validation Result | Load可否 | Runtime |
| Failure Reason | UI / Log | Runtime |
| Save Slot Identifier | 破損Save削除対象 | Save Metadata |

## 8. UI / HUD / Animation / Feedback
- 破損 / Load失敗を成功として表示しない。
- Saveが破損していることを通知し、破損Save削除後にNew Gameを開始できる導線へ戻す。

## 9. 異常系・終了条件
- Invalid SaveをRuntimeへ部分適用しない。
- Load失敗でCrashしない。
- 正常Saveを破損Saveと誤判定して削除しない。
- 削除後に旧SaveのRuntime値を残さない。

## 10. 受入条件
- [ ] 破損Saveを検出できる。
- [ ] Invalid DataをGameplayへ部分適用しない。
- [ ] 破損Saveだけを削除できる。
- [ ] 削除後にNew Gameを開始できる状態へ戻れる。
- [ ] Backup復旧を行わない。
- [ ] Corrupt SaveからCrashしない。

## 11. 依存・Issue反映
### 依存
- [#154 Save JSON Architecture](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)
- [#150 Title / Start Flow](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/150)

### Issue反映
- [#144](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/144)へ破損検出、非適用、破損Save削除、New Game復帰を反映する。
- [#154](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)でValidation / Storage側Architectureを確定する。

## 12. 未決事項
なし
