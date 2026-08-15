# [FR-BOSS-001] ボスとの一対一戦闘

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-001` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#125`, `#126` |
| 関連要件・設計 | `FR-BOSS-002`, `BOSS-AI-COMMON` |

## 2. 目的
Initial VSの主要戦闘として、1人のPlayerと1体のBossによる1対1 Encounterを成立させる。

## 3. 確定仕様・スコープ
- Boss Encounter中に対象Playerを1人として管理する。
- BossはCombat開始後、Current PlayerをContext評価とAttack対象に使用する。
- DefeatedでEncounterを終了する。

## 4. 基本フロー
```text
Boss Encounter開始
↓
Player Target確定
↓
Boss Combat開始
↓
AI評価 / Attack
↓
Boss Defeated
↓
Encounter終了
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Encounter / Boss State | Combat開始・終了 |
| Boss AI | Target Player評価・Attack |
| Player | Boss Combat対象 |

## 6. 状態 / Gameplay Tag
Boss Combat / Defeated状態を大状態として管理する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Target Player | 戦闘対象 | Runtime |
| Boss Combat Area | Encounter範囲 | Level Data |
| Boss Definition | HP / Attack等 | Master Data |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| UI / HUD | Encounter開始中はBoss HPを表示する |

## 9. 異常系・終了条件
- Player無効化 / Level遷移時はAI評価を安全に停止する。
- Defeated後にEncounterを再開始しない。

## 10. 受入条件
- [ ] Bossが1人のPlayerをTargetとして戦闘できる。
- [ ] Player無効時に安全停止できる。
- [ ] DefeatedでEncounterを終了できる。

## 11. 依存・Issue反映
### 依存
- `BOSS-AI-COMMON`

### Issue反映
- `#126`へ1対1 Target / Encounter状態を反映する。

## 12. 未決事項
なし
