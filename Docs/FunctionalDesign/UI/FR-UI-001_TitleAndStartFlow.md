# FR-UI-001 Title / Start Flowを実装する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-UI-001` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | 未割当 |
| 関連設計 | `FR-STAGE-001`, `FR-STAGE-002`, `FR-SAVE-001-006`, `FR-STAGE-013` |

## 2. 目的

ゲーム起動からTitle、New Game / Continue / Load Game、Ending後のTitle復帰までの入口と出口を一意にする。

## 3. 確定仕様・スコープ

ゲーム起動時は次の順で遷移する。

```text
[Game Boot]
  ↓
[Intro]
  ↓
[Title]
```

Titleには次を表示する。

- Continue
- Load Game
- New Game
- Config
- Exit

各導線は次で確定する。

- `New Game` → Tutorial Text → Tutorial → Play Start
- `Continue` → 現在の進行Save DataからPlay Start
- `Load Game` → Save Data選択 → Play Start
- `Config` → Config画面
- `Exit` → Game終了
- `Ending`終了 / Skip → Titleへ復帰

Initial Vertical Sliceの進行Saveは1スロットであるため、Load Game画面の選択対象は現在存在するSave Dataとする。将来複数スロット化してもTitle Flow自体は変更しない。

## 4. 基本フロー

```text
[Game Boot]
  ↓
[Intro]
  ↓
[Title]
  ├─ Continue → [Load Current Save] → [Play Start]
  ├─ Load Game → [Save Data Select] → [Load] → [Play Start]
  ├─ New Game → [Tutorial Text] → [Tutorial] → [Play Start]
  ├─ Config → [Config]
  └─ Exit → [Quit]

[Ending Complete / Skip]
  ↓
[Title]
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Title UI | Menu表示、選択入力、各Flowへの要求 |
| Game Flow / GameMode相当 | Boot / Intro / Title / Gameplay / Endingの遷移管理 |
| Save System | Continue / Load Game用Save存在確認とLoad |
| Config System | Config画面と設定反映 |

## 6. 状態・Gameplay Tag

Gameplay Tagでの管理は必須にしない。Game Flow Stateとして`Intro / Title / Loading / Gameplay / Ending`を識別できること。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Intro Content | Boot後Intro表示 | UI / Asset |
| Title Menu Definition | Menu項目 | UI Data |
| Save Summary | Continue / Load Game表示 | Save Runtime Data |
| New Game Initial State | New Game開始状態 | Gameplay / Save Data |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI | Continue / Load Game / New Game / Config / Exit |
| Feedback | 選択、決定、戻る、Load失敗等の最低限Feedback |
| Camera / Animation | Intro / Title演出はAsset調整可能 |

## 9. 異常系・終了条件

- Save Dataが存在しない場合はContinueを実行しない。
- Load失敗時はTitle / Load Game画面へ安全に戻れる。
- New Game開始を多重実行しない。
- EndingからTitleへ戻る際にGameplay入力・残存Widget・一時Stateを残さない。

## 10. 受入条件

- [ ] Boot → Intro → Titleの順で遷移する。
- [ ] Titleに5項目を表示できる。
- [ ] New GameからTutorial Text / Tutorialへ遷移できる。
- [ ] Continueから現在のSave Dataを読みPlay Startできる。
- [ ] Load GameからSave Dataを選択してPlay Startできる。
- [ ] Configを開ける。
- [ ] Exitでゲームを終了できる。
- [ ] Ending終了 / Skip後にTitleへ戻れる。
- [ ] Saveなし / Load失敗で進行不能にならない。

## 11. 依存・Issue反映

- Save System
- Tutorial
- Stage Clear / Ending
- Config

## 12. 未決事項

なし。TitleのVisual、Intro尺、Transition Animationは調整項目とする。
