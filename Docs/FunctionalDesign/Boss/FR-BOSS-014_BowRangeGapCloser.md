# [FR-BOSS-014] 弓で距離を取られた場合の専用接近行動

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-014` |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | `FR-BOSS-004`, `FEATURE-BOW-*`, `BOSS-AI-COMMON` |

## 2. 目的
Bow Playerが長距離を維持した場合にBossが専用Gap Closer候補を高く評価できるようにする。

## 3. 確定仕様・スコープ
- Bow実装後のPost-VS対象。
- Equipped WeaponがBowかつRange Trendが長距離の場合にGap Closer候補へ補正を加える。
- Initial VSのSword Bossを本要件へ依存させない。

## 4. 基本フロー
```text
Weapon = Bow
+ Long Range Trend
↓
Gap Closer Modifier適用
↓
通常CandidateとScore比較
↓
選択時に専用接近Ability実行
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Weapon Context | Bow判定 |
| Range Trend | 長距離傾向判定 |
| Evaluator | Gap Closer補正 |
| Ability | 専用接近行動 |

## 6. 状態 / Gameplay Tag
Bow装備状態とBoss Phase / Cooldownを利用する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Bow Weapon Type | 条件 | Runtime / Master Data |
| Long Range Threshold | Trend判定 | 調整値 |
| Gap Closer Definition | 行動 | Master Data |
| Gap Closer Modifier | Score補正 | 調整値 |

## 8. UI / HUD / Animation / Feedback
専用Gap Closer Animation / VFX / SEをAttack Dataから設定する。DebugでBow補正を表示可能にする。

## 9. 異常系・終了条件
- Bow未実装 / 無効Data時にCandidateへ追加しない。
- 距離条件解消後に補正を残さない。

## 10. 受入条件
- [ ] Bow + Long Range時にGap Closer Scoreを補正できる。
- [ ] Sword / Axe時にBow専用補正を適用しない。
- [ ] Debugで補正理由を確認できる。

## 11. 依存・Issue反映
### 依存
- Bow Feature
- `FR-BOSS-004`

### Issue反映
- Bow Post-VS RoadmapでIssue化する。

## 12. 未決事項
なし
