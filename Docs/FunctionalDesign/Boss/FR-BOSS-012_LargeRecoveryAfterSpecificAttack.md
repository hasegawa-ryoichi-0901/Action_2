# FR-BOSS-012 特定Attack後に大きなRecoveryを持つ

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-012` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#131` |
| 関連要件・設計 | `FR-BOSS-013`, `BOSS-AI-COMMON` |

## 2. 目的
高威力・高圧力Attack後にPlayerが反撃できる明確な隙を設け、Boss戦の攻守交代を作る。

## 3. 確定仕様・スコープ
- Attack DefinitionごとにRecovery Windowを設定可能にする。
- Recovery中は新規Attack開始を制限する。
- 特定Attackほど長いRecoveryを設定可能とする。
- Recovery時間はデータ調整可能とする。

## 4. 基本フロー
```text
特定Boss Attack完了
↓
Recovery Window開始
↓
新規Attack選択停止
↓
Recovery終了
↓
通常Attack評価へ復帰
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Attack Definition | Recovery時間提供 |
| Boss State / Ability | Recovery状態管理 |
| Evaluator | Recovery中の新規Attack抑止 |

## 6. 状態 / Gameplay Tag
Recovery状態をBoss Action StateまたはWindowとして管理する。具体Tagは共通Combat Tag設計に従う。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Recovery Window | 隙時間 | 調整値 |
| AttackId | 対象Attack識別 | Master Data |

## 8. UI / HUD / Animation / Feedback
AnimationのRecovery Pose / EndをAttack Montageで表現する。DebugでRecovery中か確認可能にする。

## 9. 異常系・終了条件
- Defeated / Phase Transition等の上位状態でRecoveryを中断できる。
- Recovery終了後にAttack禁止状態を残さない。

## 10. 受入条件
- [ ] AttackごとにRecoveryを設定できる。
- [ ] Recovery中は新規Attackを開始しない。
- [ ] 終了後に通常評価へ戻れる。

## 11. 依存・Issue反映
### 依存
- Boss Attack Ability基盤

### Issue反映
- `#131`へRecovery State、Attack Data、Cleanupを反映する。

## 12. 未決事項
なし
