# FR-ENEMY-007 Posture0でDownする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-007` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#123` |
| 関連要件・設計 | `FR-ENEMY-006`, `FR-ENEMY-008`, `FR-PLAYER-022` |

## 2. 目的
Posture BreakをEnemyの行動停止とFatal Attack機会へ接続する。

## 3. 確定仕様・スコープ
- 生存中にPosture<=0でDownへ1回遷移する。
- Down中は通常AI / Attackを停止しAttack Slotを解放する。
- Down Animationを再生する。
- Down開始時に`FR-ENEMY-008`のFatal Attack受付を有効化する。

## 4. 基本フロー
```text
Posture <= 0 + Alive
↓
State.Reaction.Downed
↓
AI / Attack停止 + Slot解放
↓
Down Animation
↓
Fatal Attack受付ON
↓
Down終了 / Fatal / Defeat
↓
受付OFF → Posture Reset / 次状態
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Enemy Combat | Down状態開始・終了 |
| AI / Coordinator | 行動停止・Slot解放 |
| Animation | Down Animation |
| Fatal受付 | Window / Collision有効化 |

## 6. 状態 / Gameplay Tag
| State / Gameplay Tag | 用途 |
|---|---|
| `State.Reaction.Downed` | Down中 |
| `Window.FatalAttack.Available` | Fatal受付。詳細はFR-ENEMY-008 |

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Down Duration | Down継続 | 調整値 |
| Down Animation | 表現 | Asset |
| Posture Reset Rule | Down終了後 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| Animation | Down Animation |
| VFX / SE | Posture Breakを識別できるFeedback |

## 9. 異常系・終了条件
- DefeatedをDownより優先する。
- 多重Posture BreakでDownを重複開始しない。
- 終了時にAI停止状態とFatal受付を残さない。

## 10. 受入条件
- [ ] Posture0でDownへ1回遷移する。
- [ ] Down中にAI / Attackを停止できる。
- [ ] Down Animationを再生できる。
- [ ] Down開始 / 終了をFatal受付へ通知できる。

## 11. 依存・Issue反映
### 依存
- `#122` Health / Posture

### Issue反映
- `#123`へDown、Animation、Slot、Fatal受付接続を反映する。

## 12. 未決事項
なし
