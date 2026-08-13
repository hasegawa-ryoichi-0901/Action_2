# FR-BOSS-013 Perfect Dodge / Parry成功時に反撃可能な隙を作る

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-013` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#131` |
| 関連要件・設計 | `FR-PLAYER-014`～`016`, `FR-BOSS-012` |

## 2. 目的
PlayerのPerfect Dodge / Parry成功をBoss側の反撃可能Windowへ接続し、防御成功に明確な攻撃機会を与える。

## 3. 確定仕様・スコープ
- Perfect DodgeまたはParry成功EventをBoss側で受け付ける。
- 対象Attack / 状態がCounter Windowを許可する場合に反撃可能な隙を開始する。
- Window中はBossの新規Attackを抑制できる。
- Window時間はデータ調整可能とする。

## 4. 基本フロー
```text
Perfect Dodge / Parry Success Event
↓
Boss / AttackがCounter許可?
├ No → 通常継続
└ Yes → Counter Window開始
          ↓
       Boss新規Attack抑止
          ↓
       Window終了
          ↓
       通常評価へ復帰
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Player Defense | Success Event通知 |
| Boss Combat | Counter Window開始・終了 |
| Evaluator | Window中Attack抑止 |

## 6. 状態 / Gameplay Tag
| State / Gameplay Tag | 用途 |
|---|---|
| `Window.Counter.Available` | Player反撃可能期間として共有可能 |

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Counter Window Duration | 隙時間 | 調整値 |
| Attack Counter Policy | 対象Attack可否 | Gameplay Data |
| Defense Result Event | Perfect / Parry識別 | Runtime |

## 8. UI / HUD / Animation / Feedback
Boss Reaction Animation / VFX / SEを必要に応じ設定し、反撃機会を視覚的に識別可能にする。

## 9. 異常系・終了条件
- 同一Defense SuccessでWindowを重複開始しない。
- Defeated / Phase Transitionで上位状態を優先する。
- Window終了後にAttack禁止を残さない。

## 10. 受入条件
- [ ] Perfect Dodge / Parry Successを受信できる。
- [ ] 許可AttackだけCounter Windowを開始できる。
- [ ] Window中にBossの新規Attackを抑制できる。
- [ ] 終了後に通常評価へ戻れる。

## 11. 依存・Issue反映
### 依存
- `FR-PLAYER-014`, `FR-PLAYER-016`

### Issue反映
- `#131`へDefense Event、Counter Window、Recovery優先順位を反映する。

## 12. 未決事項
なし
