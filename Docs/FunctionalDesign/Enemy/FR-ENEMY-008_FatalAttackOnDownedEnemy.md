# FR-ENEMY-008 Down中だけFatal Attackを受け付ける

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-008` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#123`, `#148` |
| 関連要件・設計 | `FR-ENEMY-007`, `FR-PLAYER-022` |

## 2. 目的
Enemy Down中だけPlayer Fatal Attackの対象となる受付状態・Collision・基準Transformを提供する。

## 3. 確定仕様・スコープ
- Down中のみFatal Attack受付Stateと受付Collisionを有効化する。
- Player側Actionは`FR-PLAYER-022`が担当する。
- Fatal Attack基準TransformをPlayer側へ提供する。
- Down終了 / Defeat / Fatal Attack成立時に受付を無効化する。

## 4. 基本フロー
```text
Enemy Down開始
↓
Window.FatalAttack.Available + Collision ON
↓
Playerが受付範囲へ
↓
FR-PLAYER-022がAction開始
↓
Fatal成立 / Down終了 / Defeat
↓
Window + Collision OFF
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Enemy Down / Combat | 受付状態Lifecycle |
| Fatal Collision | Playerが受付範囲内か判定 |
| Enemy | Fatal基準Transform提供 |
| Player Fatal Ability | 実際のAttack実行 |

## 6. 状態 / Gameplay Tag
| State / Gameplay Tag | 用途 |
|---|---|
| `State.Reaction.Downed` | 受付前提 |
| `Window.FatalAttack.Available` | Fatal受付可能 |

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Fatal Collision Shape / Size | 受付範囲 | 調整値 |
| FatalAttack Transform | Player位置合わせ | Runtime / Gameplay Data |
| Down State | 受付Lifecycle | Runtime |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| UI / HUD | 受付状態を参照可能とする。専用Promptは必須ではない |
| Animation | Down AnimationはFR-ENEMY-007 |

## 9. 異常系・終了条件
- Defeated / Down終了後にCollisionを有効のまま残さない。
- Fatal成立を二重通知しない。
- Owner Destroy時にCollision / Windowを解除する。

## 10. 受入条件
- [ ] Down中だけ受付State / Collisionを有効化できる。
- [ ] PlayerへFatal Transformを提供できる。
- [ ] Down終了 / Defeat / Fatal成立で受付を無効化できる。
- [ ] #148と安全に連携できる。

## 11. 依存・Issue反映
### 依存
- `FR-ENEMY-007`
- `FR-PLAYER-022`

### Issue反映
- Enemy側は`#123`、Player Action側は`#148`へ分離する。

## 12. 未決事項
なし
