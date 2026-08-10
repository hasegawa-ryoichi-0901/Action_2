# FR-PLAYER-006 手動ロックオンを使用できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-006` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-PLAYER-007`, `FR-PLAYER-021` |

## 2. 基本フロー

```text
[LockOn Input]
      ↓
[現在Locked？]
   ├─ Yes → [Lock解除]
   └─ No  → [有効Target候補検索]
              +-- なし --> [解除状態維持]
              ↓
           [Target固定]
           [State.Targeting.Locked]
           [Camera Target追従]
```

## 3. 確定仕様

- 同じLockOnキー / ボタンの再入力で解除する。
- LockOn中は通常Camera Lookを無効化する。
- Target Switchは別の左右専用入力で行う。
- Current Targetが死亡・無効化した場合は自動的にLockOnを解除する。
- Target死亡時の自動別Target選択は行わない。

## 4. 受入条件

- [ ] 有効Targetが存在する時にLockOnできる。
- [ ] 同じLockOn入力でもう一度押すと解除できる。
- [ ] LockOn中にCameraがCurrent Targetへ追従する。
- [ ] LockOn中に通常Camera Lookを受け付けない。
- [ ] Target死亡時に安全に解除される。
