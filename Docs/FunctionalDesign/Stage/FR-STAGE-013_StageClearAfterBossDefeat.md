# FR-STAGE-013 Boss撃破後にClear TriggerからEndingへ進む

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-013` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#105`, `#106`, `#107` |
| 関連要件・設計 | `FR-BOSS-015`, `FR-BOSS-016`, `FR-SAVE-004`, `FR-UI-001` |

## 2. 目的
Boss Defeat後に即Endingへ遷移せず、Playerが奥のClear Areaへ進むことでEndingを開始するStage Clear Flowを実現する。

## 3. 確定仕様・スコープ
- Boss Reward確定とAuto Save完了後にClear Triggerを有効化する。
- Boss生存中 / Reward Save未完了ではEndingを開始しない。
- PlayerがClear Trigger Collisionへ進入した時にEnding Sequenceを1回開始する。
- EndingはSkip可能。
- Ending終了 / Skip後にTitleへ戻る。
- Stage Clear自体では追加Auto Saveしない。
- Clear Areaの見た目は城 / 洞窟 / 祠等、Map制作時に決定可能。

## 4. 基本フロー
```text
Boss Defeated
↓
Reward確定
↓
Auto Save完了
↓
Clear Trigger有効化
↓
Player進入
↓
Ending Sequence
├ Skip
└ Complete
↓
Title
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Boss Progress | Defeat / Reward Save完了通知 |
| Stage Progression | Trigger有効化・一意開始 |
| Ending Sequence | Ending / Skip |
| Title Flow | 終了後Title遷移 |

## 6. 状態 / Gameplay Tag
Clear Trigger Enabled / Ending StartedをStage Runtime Stateとして管理する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Boss Defeated / Reward Save State | Trigger条件 | Runtime |
| Clear Trigger | Collision | Level Data |
| Ending Sequence | Ending | Asset |
| Title Destination | 遷移先 | Config |

## 8. UI / HUD / Animation / Feedback
Ending開始時にGameplay HUDを終了 / 非表示にし、Sequenceへ移行する。Ending Skip操作を提供する。

## 9. 異常系・終了条件
- Boss生存中にTriggerを開始しない。
- Trigger多重OverlapでEndingを重複開始しない。
- Skip / Completeの両方からTitle遷移を1回だけ行う。

## 10. 受入条件
- [ ] Reward Auto Save完了後だけTriggerを有効化できる。
- [ ] Player進入時だけEndingを開始できる。
- [ ] EndingをSkipできる。
- [ ] Ending終了 / Skip後Titleへ戻れる。
- [ ] Stage Clearで追加Saveしない。

## 11. 依存・Issue反映
### 依存
- `#100`, `#103`, `#150`

### Issue反映
- `#105`親、`#106`Trigger、`#107`Ending / Titleとして扱う。

## 12. 未決事項
なし
