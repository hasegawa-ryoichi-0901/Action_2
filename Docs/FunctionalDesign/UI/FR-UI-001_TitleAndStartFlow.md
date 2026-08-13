# FR-UI-001 Title / Start Flowを提供する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-UI-001` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#150` |
| 関連要件・設計 | `FR-STAGE-001`, `FR-STAGE-013`, `FR-SAVE-001`, `FR-SAVE-006` |

## 2. 目的
Game BootからTitle、New Game / Continue / Load / Config / Exit、およびEnding後のTitle復帰までを一貫したStart Flowとして提供する。

## 3. 確定仕様・スコープ
- `Game Boot → Intro → Title`とする。
- Title項目はContinue / Load Game / New Game / Config / Exit。
- New Gameは`Tutorial Text → Tutorial → Play Start`へ進む。
- Continueは現在の進行SaveをLoadしてPlay Startする。
- Load GameはSave Data選択画面を開き選択後にLoadする。
- Configは設定画面、ExitはGame終了。
- Ending終了 / Skip後はTitleへ戻る。

## 4. 基本フロー
```text
Game Boot → Intro → Title

Title
├ Continue → Save Load → Play Start
├ Load Game → Save選択 → Load → Play Start
├ New Game → Tutorial Text → Tutorial
├ Config → Config UI
└ Exit → Game終了

Ending Complete / Skip → Title
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Boot / Frontend Flow | Intro / Title状態管理 |
| Title UI | 5項目操作 |
| Save System | Continue / Load |
| Config | 設定画面 |
| Stage / Ending | Title復帰通知 |

## 6. 状態 / Gameplay Tag
Frontend / Gameplay状態はFlow Stateとして管理する。Gameplay Tagは必須としない。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Intro Content | 起動Intro | Asset |
| Title Menu Definition | Menu項目 | UI Data |
| Save Summary | Continue / Load表示 | Runtime / Save |
| New Game Initial State | 初期進行 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
Title Menu、Load Data選択、Config画面、Introを提供する。Gameplay HUDはTitle表示中に残さない。

## 9. 異常系・終了条件
- SaveなしではContinueを実行不可にする。
- Load失敗時にTitle / Load UIへ戻れる。
- New Game / Loadを多重開始しない。
- Ending→TitleでGameplay HUD / Input /一時Stateを残さない。

## 10. 受入条件
- [ ] Boot→Intro→Titleへ遷移できる。
- [ ] Titleの5項目を選択できる。
- [ ] New Game→Tutorialへ進める。
- [ ] Continue / LoadからPlay Startできる。
- [ ] Ending後Titleへ戻れる。
- [ ] Saveなし / Load失敗で進行不能にならない。

## 11. 依存・Issue反映
### 依存
- `#87` Save
- `#132`, `#133`
- `#107` Ending

### Issue反映
- `#150`へFrontend Flow全体を反映する。

## 12. 未決事項
なし
