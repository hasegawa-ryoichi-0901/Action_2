# FR-STAGE-013 Boss撃破後にClear Areaへ到達するとStage Clearする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-013` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-BOSS-015`, `FR-BOSS-016`, `FR-SAVE-004` |

## 2. 目的

Boss撃破とEnding開始を分離し、撃破後にPlayer自身が奥のClear Areaへ進む余韻と進行を作る。

## 3. 基本フロー

```text
[Boss Defeated]
      ↓
[Reward Grant]
      ↓
[Auto Save]
      ↓
[PlayerがClear Areaへ移動]
      ↓
[Clear Trigger Collision進入]
      ↓
[Ending Sequence開始]
      +--> Skip可能
      ↓
[Ending終了 / Skip]
      ↓
[Titleへ戻る]
```

## 4. 確定仕様

- Boss撃破だけではEndingを開始しない。
- Boss撃破報酬のSave後、Clear Areaへの進行を許可する。
- Clear Areaは城・洞窟・祠等のMap表現から後で決定する。
- Clear Triggerへの進入でEnding Sequenceを開始する。
- Ending SequenceはSkip可能。
- 終了後はTitleへ戻る。
- Stage Clear自体では追加Auto Saveしない。

## 5. 受入条件

- [ ] Boss生存中にClear TriggerでEndingを開始できない。
- [ ] Boss撃破直後に自動Endingへ入らない。
- [ ] Boss Reward / Auto Save完了後にClear Triggerを有効化できる。
- [ ] Trigger進入でEndingが1回だけ開始する。
- [ ] EndingをSkipできる。
- [ ] Ending終了またはSkip後にTitleへ戻る。
