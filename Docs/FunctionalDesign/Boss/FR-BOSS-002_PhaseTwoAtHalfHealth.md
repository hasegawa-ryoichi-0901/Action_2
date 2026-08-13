# FR-BOSS-002 HP50%以下でPhase2へ移行する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-002` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#126` |
| 関連要件・設計 | `FR-BOSS-001`, `FR-BOSS-008`, `BOSS-AI-COMMON` |

## 2. 目的
戦闘中盤でBossの行動候補・調整値を変化させ、戦闘展開を二段階にする。

## 3. 確定仕様・スコープ
- Boss HPが50%以下になった時にPhase Transitionを1回だけ開始する。
- Phase2へ移行後はPhase1へ戻らない。
- PhaseごとにAttack候補・Parameterを切り替え可能にする。
- Health<=0時はPhase TransitionよりDefeatedを優先する。

## 4. 基本フロー
```text
Boss Health更新
↓
Health <= 0? → Defeated
↓ No
Health <= 50% and Phase1?
├ No → Current Phase継続
└ Yes → Phase Transition → Phase2
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Boss Attribute | HP率提供 |
| StateTree | Phase Transition / Phase2状態 |
| Attack Evaluator | Phase別Candidate / Modifier適用 |

## 6. 状態 / Gameplay Tag
PhaseはStateTreeを正とする。必要なAbility Tagへ同期可能。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Phase Threshold | 移行条件 | 50%確定 |
| Phase1 / Phase2 Attack Set | 候補 | Master Data |
| Phase Transition Animation | 演出 | Asset |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| Animation | Phase Transition Animationを設定可能 |
| UI / HUD | Boss HPは継続表示する |

## 9. 異常系・終了条件
- Phase Transitionを重複開始しない。
- Transition中にHP0ならDefeatedへ遷移する。

## 10. 受入条件
- [ ] HP50%以下でPhase2へ1回だけ移行できる。
- [ ] Phase2からPhase1へ戻らない。
- [ ] Phase別Attack候補を切り替えられる。
- [ ] HP0時にDefeatedを優先できる。

## 11. 依存・Issue反映
### 依存
- `FR-BOSS-001`

### Issue反映
- `#126`へHP閾値、Phase State、Candidate切替を反映する。

## 12. 未決事項
なし
