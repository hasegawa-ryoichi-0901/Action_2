# NFR-QUALITY-004 Save破損時の挙動を確認する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-QUALITY-004` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#144` |
| 関連要件・設計 | `FR-SAVE-001`～`006`, `Docs/18_SaveJsonArchitecture.md` |

## 2. 目的
読込不能・不正形式のSave Dataを正常進行データとして適用せず、Crashや部分的なRuntime破損を防ぐ。

## 3. 確定仕様・スコープ
- Save読込時に形式・Version・必須Data等を検証可能にする。
- 破損または読込失敗したDataをRuntimeへ部分適用しない。
- Load失敗をUI / 呼出元へ通知可能にする。
- 破損時の具体的なRecovery PolicyはSave Architectureで確定する。

## 4. 基本フロー
```text
Save Load Request
↓
Data読込
↓
Validation
├ Valid → Runtimeへ復元
└ Invalid → 適用しない → Failure通知 → Recovery導線
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Save Reader / Validator | 破損検出 |
| Gameplay Restore | Valid Dataのみ適用 |
| UI | Load失敗通知・Recovery導線 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Save Version | Compatibility確認 | Save Metadata |
| Validation Result | Load可否 | Runtime |
| Failure Reason | UI / Log | Runtime |
| Recovery Policy | 破損時対応 | Architecture |

## 8. UI / HUD / Animation / Feedback
破損 / Load失敗を成功として表示せず、Title / Load UIからRecovery可能な通知を行う。

## 9. 異常系・終了条件
- Invalid SaveをRuntimeへ部分適用しない。
- Load失敗でCrashしない。
- 元Saveを自動上書きする場合はRecovery Policy確定前に実装しない。

## 10. 受入条件
- [ ] 破損Saveを検出できる。
- [ ] Invalid DataをGameplayへ部分適用しない。
- [ ] CrashせずLoad Failureを通知できる。
- [ ] 確定したRecovery Policyをテストできる。

## 11. 依存・Issue反映
### 依存
- Save JSON Architecture

### Issue反映
- `#144`へ破損検出・非適用・Failure通知を反映し、Recovery Policy確定後に最終受入条件を確定する。

## 12. 未決事項
| 未決事項 | Issue作成前に確定必須 | 理由 |
|---|---|---|
| 破損Save検出後にBackup復旧、新規開始、削除確認等のどのRecoveryを採用するか | Yes | Player Dataの扱いとUI導線が変わるため |
