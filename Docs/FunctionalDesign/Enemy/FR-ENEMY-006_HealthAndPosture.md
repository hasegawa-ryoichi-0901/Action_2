# FR-ENEMY-006 EnemyはHPとPostureを持つ

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-006` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#122` |
| 関連要件・設計 | `FR-ENEMY-007`, `FR-ENEMY-009`, `FR-ENEMY-010`, `Docs/05_GASDesign.md` |

## 2. 目的
Enemyの生存判定とPosture Break判定を独立Resourceとして管理する。

## 3. 確定仕様・スコープ
- Health / MaxHealthとPosture / MaxPostureを持つ。
- Health<=0はDefeatedへ接続する。
- Posture<=0かつ生存中はDownへ接続する。
- Health DefeatはPosture Downより優先する。

## 4. 基本フロー
```text
Attack Hit
↓
Health Damage / Posture Damage適用
↓
Health <= 0?
├ Yes → Defeated
└ No
  ↓
Posture <= 0?
├ Yes → Down
└ No → Combat継続
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Attribute / Combat | Health / Posture保持と更新 |
| Defeat処理 | Health0終端 |
| Down処理 | Posture0終端 |

## 6. 状態 / Gameplay Tag
`State.Reaction.Downed`、Defeated状態へResource閾値から遷移する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| MaxHealth | HP最大 | Master Data |
| MaxPosture | Posture最大 | Master Data |
| Health / Posture Damage | 被Damage | Attack Data |

## 8. UI / HUD / Animation / Feedback
通常EnemyのHP / Posture常時HUD表示は必須としない。Hit / Down Animationで結果を表現する。

## 9. 異常系・終了条件
- Health / Postureの多重終端通知を防ぐ。
- Health0時に新規Downへ遷移しない。
- Defeated後にResource回復でCombatへ戻らない。

## 10. 受入条件
- [ ] Health / Postureを独立更新できる。
- [ ] Health0でDefeatedへ遷移できる。
- [ ] 生存中Posture0でDownへ遷移できる。
- [ ] Health0をDownより優先できる。

## 11. 依存・Issue反映
### 依存
- `#62` Damage基盤

### Issue反映
- `#122`へHealth / Posture Attributeと優先順位を反映する。

## 12. 未決事項
なし
