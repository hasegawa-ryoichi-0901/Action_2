# FR-ENEMY-007 体勢値が0になるとDownする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-007` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#123` |
| 関連設計 | `FR-ENEMY-008`, `FR-PLAYER-022` |

## 2. 目的

EnemyのPosture BreakをDown状態へ接続し、Fatal Attack可能時間を作る。

## 3. 確定仕様・基本フロー

```text
[Posture <= 0]
  ↓
[State.Reaction.Downed]
  ↓
[通常AI / Attack停止・Attack Slot解放]
  ↓
[Down Animation]
  ↓
[FR-ENEMY-008 Fatal Attack受付開始]
  ↓
[Down終了 / Defeat / Fatal成立]
  ↓
[Down終了処理]
```

- Down中は通常AI / Attackを実行しない。
- Down中Animationを再生する。
- DefeatedはDownより優先する。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Posture / Combat処理 | Posture<=0判定、Down状態開始・終了 |
| Enemy AI / Attack Coordinator | AI停止、Attack Slot解放 |
| Animation | Down中Animation |
| `FR-ENEMY-008` | Fatal Attack受付State / Collision |

## 5. 状態・Gameplay Tag

| State / Tag | 用途 |
|---|---|
| `State.Reaction.Downed` | Enemy Down状態 |

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| DownDuration / RecoveryRule | Down終了条件 | Gameplay Data |
| DownAnimation | Down中表示 | Asset参照 |
| PostureResetRule | Down終了後のPosture | Gameplay Data |

## 7. UI / Animation / Feedback

- Down Animationを必須とする。
- Fatal Attack可能状態のUI表示は`FR-ENEMY-008 / FR-PLAYER-022`側で必要性を扱う。

## 8. 異常系・終了条件

- Defeat時はDownを終了する。
- Owner破棄時にAI Slot / Tag / Timerを残さない。
- Posture<=0通知の多重発火でDownを二重開始しない。

## 9. 受入条件

- [ ] 生存中にPosture<=0でDownへ1回だけ遷移する。
- [ ] Down中Animationを再生する。
- [ ] Down中に通常AI / Attackを停止する。
- [ ] Attack Slotを解放する。
- [ ] Fatal Attack受付へ接続できる。
- [ ] Defeat時はDownを終了する。

## 10. 依存・Issue反映

`#123`へDown Animation、受付開始条件、終了条件を反映する。

## 11. 未決事項

なし。Down時間・Animation Assetは調整項目とする。
