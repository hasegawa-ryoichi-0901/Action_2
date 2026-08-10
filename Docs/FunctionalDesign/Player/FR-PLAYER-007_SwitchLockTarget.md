# FR-PLAYER-007 ロックオン対象を切り替えられる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-007` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-PLAYER-006`, `FR-PLAYER-021` |

## 2. 目的

Manual LockOn中にCamera Lookと競合しない専用入力で左右の有効Targetへ切り替える。

## 3. 基本フロー

```text
[State.Targeting.Locked]
      ↓
[Target Switch Left / Right専用入力]
      ↓
[方向に対応する有効候補検索]
      +-- 候補なし --> [現在Target維持]
      ↓
[Current Target更新]
      ↓
[Camera / Marker追従先更新]
```

## 4. Target無効化

```text
[Current Target死亡 / 無効化]
      ↓
[LockOn解除]
      ↓
[State.Targeting.Locked解除]
      ↓
[通常Camera Lookへ復帰]
```

対象死亡時に別Targetへ自動切替は行わず、LockOn自体を解除します。

## 5. 確定仕様

- Target SwitchはCamera Lookとは別の左右専用キー / ボタンを使用する。
- LockOn中は通常Camera Lookを無効にする。
- Target死亡・無効化時は自動Lock解除する。
- Target候補選定の距離・画面位置等のScore詳細は実装時に調整可能とする。

## 6. 受入条件

- [ ] LockOn中のみTarget Switchを受け付ける。
- [ ] Left / Right入力で対応方向の有効Targetへ変更できる。
- [ ] 候補がない場合に不正参照へ切り替えない。
- [ ] Target死亡時にLockOnを解除する。
- [ ] 解除後に通常Camera Lookが復帰する。
