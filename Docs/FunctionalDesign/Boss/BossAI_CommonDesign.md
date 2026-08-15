# BOSS-AI-COMMON Boss AI共通設計

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `BOSS-AI-COMMON` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#125`～`#131` |
| 関連要件・設計 | `FR-BOSS-001`～`013`, `Docs/06_EnemyAI.md` |

## 2. 目的
Boss AIのState、Combat Context、Attack Score、行動適応、Combo、Recovery / Counter Windowを同一の判断パイプラインで扱い、選択理由をDebugで追跡可能にする。

## 3. 確定仕様・スコープ
- StateTreeで大状態とPhaseを管理する。
- C++評価ロジックでAttack候補をScore計算する。
- Gameplay Abilityで選択Attackを実行する。
- Initial VSではSword Playerを前提とし、Weapon別評価はPost-VS。
- 未反映Inputや将来入力をAI判断に使用しない。
- Debug表示はBoss AI検証責務に含め、Gameplay結果へ影響させない。

## 4. 基本フロー
```text
Boss Combat State
↓
Combat Context収集
↓
Attack候補生成
↓
候補ごとScore計算
↓
Cooldown / Repetition / Phase等を反映
↓
Attack選択
↓
Ability実行
↓
結果を履歴へ記録
↓
次回評価
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| StateTree | Intro / Combat / Phase / Down / Defeated等の大状態 |
| Combat Context | Player・Stageの確定済み状態収集 |
| Attack Evaluator | Candidate Score計算・選択 |
| Action History | 直近行動・戦闘傾向記録 |
| Gameplay Ability | 選択Attack実行 |
| Debug Presenter | State / Candidate / Score内訳表示 |

## 6. 状態 / Gameplay Tag
Boss StateはStateTreeを正とし、Ability / Reactionに必要なGameplay Tagへ同期する。Defeatedは他状態より優先する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Boss Phase | 候補切替 | Runtime |
| Attack Candidate Definitions | Attack候補 | Master Data |
| Base Score / Modifiers | Score計算 | 調整値 |
| Cooldown / Repetition Penalty | 連続使用抑制 | 調整値 |
| Player Distance / Stamina / Healing | Context | Runtime |
| Recent History / Battle Trend | 適応 | Runtime |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| UI / HUD | Boss HPはGameplay HUDへ表示する |
| Debug | State、Phase、Candidate、Base / Final Score、Modifier内訳、Selected Attackを確認可能にする |
| Animation | 選択Ability側でAttack Montageを再生する |

## 9. 異常系・終了条件
- Player参照無効時はAttack評価 / 実行を停止する。
- Boss Defeated後に新しいCandidateを評価しない。
- Debug ON/OFFでAI判断結果を変えない。
- 無効Data / CandidateをScore対象から除外しCrashしない。

## 10. 受入条件
- [ ] Combat Contextから複数Attack候補を評価できる。
- [ ] Score内訳から選択理由を追跡できる。
- [ ] Cooldown / Repetition / PhaseをScoreへ反映できる。
- [ ] Defeated後にAI判断を停止できる。
- [ ] Debug表示がGameplay結果へ影響しない。

## 11. 依存・Issue反映
### 依存
- `FR-BOSS-001`～`013`
- Player Combat / Attribute / History情報

### Issue反映
- `#125`を親Issueとし、Context、Score、Adaptation、Combo、Windowへ分割する。

## 12. 未決事項
なし
