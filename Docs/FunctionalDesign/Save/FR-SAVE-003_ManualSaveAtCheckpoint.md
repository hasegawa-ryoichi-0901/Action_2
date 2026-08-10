# FR-SAVE-003 CheckpointでManual Saveできる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-003` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 目的

Auto Saveとは別に、PlayerがCheckpoint Menuから任意のタイミングで進行保存を要求できるようにする。

## 3. 基本フロー

```text
[Checkpoint Menu Open]
      ↓
[Manual Save選択]
      ↓
[保存可能状態確認]
      +-- NG --> [理由を通知 / 状態変更なし]
      ↓
[Save Request]
      ↓
[Save完了通知]
```

## 4. 制約

- 初期Vertical SliceではCheckpoint Menu以外からManual Saveできない。
- Weapon Upgrade完了自体はAuto Save契機ではない。
- Manual Save実行時は現在の確定済み進行状態を保存対象にする。
- 保存形式・JSON・Steam Cloud方式は別Architecture Designで扱う。

## 5. 受入条件

- [ ] Checkpoint MenuからManual Saveを要求できる。
- [ ] Checkpoint外ではManual Saveできない。
- [ ] 保存中の重複要求を安全に処理できる。
- [ ] 成功・失敗をPlayerへ通知できる。
