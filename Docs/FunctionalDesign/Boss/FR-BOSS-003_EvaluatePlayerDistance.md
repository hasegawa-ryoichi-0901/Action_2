# FR-BOSS-003 Playerとの距離を評価する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-003` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#127` |
| 関連要件・設計 | `FR-BOSS-008`, `FR-BOSS-009`, `FR-BOSS-010`, `BOSS-AI-COMMON` |

## 2. 目的
Attack候補が適正距離に応じて選ばれるよう、BossとPlayerの距離をCombat Contextへ提供する。

## 3. 確定仕様・スコープ
- BossとCurrent Playerの距離を取得する。
- Attack DefinitionのMinimum / Maximum Range等と比較可能にする。
- 距離値とScore内訳をDebug確認可能にする。

## 4. 基本フロー
```text
Combat Context更新
↓
Boss / Player位置取得
↓
Distance算出
↓
Attack Range条件 / Distance Modifierへ提供
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Combat Context | Distance算出・保持 |
| Attack Evaluator | Range条件・Scoreへ利用 |
| Debug | Distance / Modifier表示 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Boss / Player Position | 距離算出 | Runtime |
| Min / Max Range | Attack適正範囲 | Master Data |
| Distance Modifier | Score補正 | 調整値 |

## 8. UI / HUD / Animation / Feedback
Gameplay HUD表示は不要。Debug表示でDistanceとScore内訳を確認可能にする。

## 9. 異常系・終了条件
- Player無効時は距離評価を無効としてAttack選択を安全に停止する。
- NaN / 不正DistanceをScoreへ使用しない。

## 10. 受入条件
- [ ] Current Playerとの距離を取得できる。
- [ ] 距離をAttack候補条件 / Scoreへ利用できる。
- [ ] Debugで距離と補正を確認できる。

## 11. 依存・Issue反映
### 依存
- `FR-BOSS-001`

### Issue反映
- `#127`へDistance Contextを反映する。

## 12. 未決事項
なし
