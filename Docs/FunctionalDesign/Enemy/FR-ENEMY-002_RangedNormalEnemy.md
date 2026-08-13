# FR-ENEMY-002 遠距離通常Enemyを実装する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-002` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#120` |
| 関連要件・設計 | `FR-ENEMY-003`, `FR-ENEMY-005`, `Docs/06_EnemyAI.md` |

## 2. 目的
距離を維持しながら射撃する通常Enemyを追加し、近接Enemyと異なる圧力を作る。

## 3. 確定仕様・スコープ
- Playerとの距離を評価して射撃可能距離を維持する。
- Ranged Attack Slot取得後のみ射撃を開始する。
- Playerが近すぎる場合は離脱 / Repositionする。
- Down / Defeated中はAIとAttackを停止する。

## 4. 基本フロー
```text
Player認識
↓
距離評価
├ 近すぎる → Reposition
├ 遠すぎる → 接近
└ 射撃範囲
   ↓
Ranged Slot取得
├ 失敗 → Wait / Reposition
└ 成功 → Ranged Attack → Slot解放
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Enemy AI | 距離維持・射撃要求 |
| Attack Coordinator | Ranged Slot管理 |
| Combat / Projectile | 射撃とDamage |

## 6. 状態 / Gameplay Tag
Down / DefeatedをAI停止条件として扱う。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Preferred Range | 距離維持 | 調整値 |
| Ranged Attack Definitions | 射撃候補 | Master Data |
| Fire Interval / Cooldown | 射撃頻度 | 調整値 |
| Projectile Data | Projectile / Damage | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| Animation | 射撃、Reposition、Hit / Down / Death |
| VFX / SE | Projectileと射撃予兆 |

## 9. 異常系・終了条件
- Target無効化、Down、Defeat時に射撃TaskとSlotを終了する。
- Projectile Owner無効時にCrashしない。

## 10. 受入条件
- [ ] Playerとの距離を評価できる。
- [ ] Ranged Slot取得後だけ射撃できる。
- [ ] 近すぎる場合に距離を取り直せる。
- [ ] Down / Defeated時に行動停止できる。

## 11. 依存・Issue反映
### 依存
- `#121` Attack Coordinator
- `#122` Health / Posture

### Issue反映
- `#120`へ距離維持、Ranged Slot、Projectile、Cleanupを反映する。

## 12. 未決事項
なし
