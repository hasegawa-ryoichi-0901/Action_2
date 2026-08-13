# FR-STAGE-011 Boss Intro演出を追加できる

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-011` |
| 優先度 | `Could` |
| 対応範囲 | `Initial Vertical Slice Optional` |
| 設計状態 | `Draft` |
| 関連Issue | `#147` |
| 関連要件・設計 | `FR-BOSS-001`, `FR-BOSS-015` |

## 2. 目的
Core Gameplay完成後に工数余裕がある場合、Boss Encounter開始前のPresentationを追加する。

## 3. 確定仕様・スコープ
- Initial VS完成に必須ではない。
- Boss Encounter開始前に1回だけIntro演出を開始できる。
- 演出中はPlayer / Bossの入力・AIを必要範囲で停止する。
- 演出終了後に通常Boss Combatへ遷移する。
- Intro Asset未設定でもBoss戦を開始できるFallbackを持つ。

## 4. 基本フロー
```text
Boss Encounter Trigger
↓
Intro Assetあり?
├ No → Boss Combat開始
└ Yes → Input / AI制御 → Intro → 復帰 → Boss Combat開始
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Stage / Encounter | Intro開始判定 |
| Sequence / Presentation | 演出再生 |
| Player / Boss | 演出中の行動停止・復帰 |

## 6. 状態 / Gameplay Tag
Intro中をEncounter Stateとして管理し、Combat開始前であることを保証する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Intro Sequence | 演出 | Asset |
| Boss Encounter Trigger | 開始地点 | Level Data |

## 8. UI / HUD / Animation / Feedback
Sequence、Camera、必要なUI非表示を演出Asset側で調整する。

## 9. 異常系・終了条件
- Asset未設定でも進行不能にしない。
- Skip / 中断対応を追加する場合もCombat開始を1回だけ行う。
- Stage Clear / Boss Defeated状態と競合しない。

## 10. 受入条件
- [ ] Introを1回だけ再生できる。
- [ ] 演出中にPlayer / Bossを安全に制御できる。
- [ ] 終了後にBoss Combatへ遷移できる。
- [ ] Assetなしでも戦闘開始できる。

## 11. 依存・Issue反映
### 依存
- Boss Encounter基盤

### Issue反映
- `#147`はOptionalとしてCore完成後に着手する。

## 12. 未決事項
なし
