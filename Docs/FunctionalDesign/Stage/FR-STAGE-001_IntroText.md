# FR-STAGE-001 New Game時にTutorial Textを表示する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-001` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#132` |
| 関連要件・設計 | `FR-UI-001`, `FR-STAGE-002` |

## 2. 目的
New Game開始直後にTutorial導入Textを提示し、Tutorial Flowへ接続する。

## 3. 確定仕様・スコープ
- Game Boot時のIntroは`FR-UI-001`が担当する。
- 本要件は`New Game → Tutorial Text → Tutorial`のText部分を担当する。
- Continue / Load Gameでは強制表示しない。
- Text内容・ページ構成はData / Assetで変更可能とする。

## 4. 基本フロー
```text
TitleでNew Game
↓
Tutorial Text表示
↓
表示完了
↓
FR-STAGE-002 Tutorial開始
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Title Flow | New Game開始通知 |
| Tutorial Text UI | Text表示・ページ進行 |
| Tutorial Flow | 完了後の次状態 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Tutorial Intro Text | 表示内容 | Master Data / Asset |
| Page Order | 複数ページ順序 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| UI / HUD | Tutorial Text画面 |

## 9. 異常系・終了条件
- 多重New Game開始でTextを重複表示しない。
- Level再入場で意図せず再表示しない。
- UI終了時に入力制御を復元する。

## 10. 受入条件
- [ ] New Game時だけTutorial Textを表示できる。
- [ ] Continue / Loadで強制表示しない。
- [ ] 表示完了後にTutorialへ1回遷移できる。

## 11. 依存・Issue反映
### 依存
- `#150` Title / Start Flow
- `#133` Tutorial

### Issue反映
- `#132`へNew Game条件、Text、Tutorial遷移を反映する。

## 12. 未決事項
なし
