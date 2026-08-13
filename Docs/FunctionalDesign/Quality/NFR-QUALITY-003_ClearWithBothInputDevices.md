# NFR-QUALITY-003 GamepadとKeyboard-Mouseの両方でClear確認する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-QUALITY-003`](../../01_Requirements.md#nfr-quality-003) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111) |
| 関連要件・設計 | [`FR-PLAYER-002`](../../01_Requirements.md#fr-player-002), [`FR-UI-001`](../../01_Requirements.md#fr-ui-001), [`FR-STAGE-013`](../../01_Requirements.md#fr-stage-013) |

## 2. 目的
Input Deviceの違いで操作不能・進行不能になる機能がないことを、通しClearで確認する。

## 3. 確定仕様・スコープ
- GamepadだけでTitleからStage Clear / Title復帰まで操作確認する。
- Keyboard-Mouseだけでも同じ通し確認を行う。
- Move / Look / Jump / Combat / LockOn / Target Switch / Heal / Checkpoint / UI操作を含める。
- Device差でGameplay Ruleを変更しない。

## 4. 基本フロー
```text
Gamepadで通しPlay
↓
Clear確認
↓
Keyboard-Mouseで通しPlay
↓
Clear確認
↓
差分Issue確認
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Input Mapping | 両Device割当 |
| Gameplay | Device非依存Rule |
| Test | 両Device通し検証 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Input Mapping | 操作割当 | Asset |
| Test Scenario | 通し検証 | Test Data |
| Device Result | 結果記録 | Test Evidence |

## 8. UI / HUD / Animation / Feedback
Title / Checkpoint / Config等のUIを両Deviceで操作可能にする。操作表示を切り替える場合もGameplay Ruleは変更しない。

## 9. 異常系・終了条件
- Device変更後にMapping / Bindingを重複させない。
- 一方のDeviceでしか実行できない必須Actionを残さない。

## 10. 受入条件
- [ ] Gamepadのみで初期プレイアブル版をClearできる。
- [ ] Keyboard-Mouseのみで初期プレイアブル版をClearできる。
- [ ] 両方で必須UIを操作できる。
- [ ] Device差によるGameplay Rule分岐がない。

## 11. 依存・Issue反映
### 依存
- [`FR-PLAYER-002`](../../01_Requirements.md#fr-player-002)
- 初期プレイアブル版全操作

### Issue反映
- 重複Issueを作らず[#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111)で機能要件と品質確認を統合する。

## 12. 未決事項
なし
