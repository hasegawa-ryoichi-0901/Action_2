# FR-SAVE-002 Checkpoint Menu Open時にAuto Saveする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-002` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 目的

PlayerがCheckpointを明示的に使用した時点を安全な進行保存点とする。

## 3. 基本フロー

```text
[Player Checkpoint Interaction]
      ↓
[Checkpoint利用条件確認]
      ↓
[ActiveCheckpoint更新]
      ↓
[Checkpoint Menu Open]
      ↓
[Auto Save Request]
      ↓
[Save完了通知 / Indicator]
```

CheckpointのCollisionへ進入しただけではAuto Saveしません。Checkpointを操作してMenuを開いた時点を契機とします。

## 4. 責務

- Checkpoint側は利用成立とMenu Openを通知する。
- Save Systemは進行データのSnapshot作成・保存・多重要求制御を担当する。
- 保存形式・JSON・Steam Cloud方式は別Architecture Designで定義する。

## 5. 受入条件

- [ ] Checkpointへ近づくだけではSaveされない。
- [ ] Checkpoint操作でMenuが開いた時に1回Auto Saveされる。
- [ ] ActiveCheckpoint更新後の状態が保存対象になる。
- [ ] 同一Menu OpenでSave要求が重複発火しない。
- [ ] Save失敗時にCheckpoint Menu自体を不整合状態へしない。
