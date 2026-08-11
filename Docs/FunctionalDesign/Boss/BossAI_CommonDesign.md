# Boss AI 共通基本設計

> `FR-BOSS-001`～`FR-BOSS-013`のInitial Vertical Slice Boss AI基本設計に共通する責務・Data・Debug契約を定義する。各FR固有の挙動は個別基本設計を正とし、本書は重複記述を避けるための共通契約とする。

## 1. 目的

Boss AIがPlayerの確定済みCombat Contextを評価し、Attack候補をScore化して行動を選択できること、およびその判断根拠を開発時に確認できることを保証する。

## 2. 確定仕様・基本フロー

```text
[Combat Context収集]
      ↓
[現在Phase / State確認]
      ↓
[Attack Candidate列挙]
      ↓
[各Candidate Score計算]
      ↓
[実行可能Candidateから選択]
      ↓
[Gameplay Ability実行]
      ↓
[結果 / Action History記録]
```

参照可能：Player位置、HP / Stamina、Healing状態、実行済みAction History、現在Phase、確定済みGameplay State。

参照しない：未反映Input、Input Buffer内容、次の予定Ability、将来入力予測。

## 3. 責務

| 対象 | 責務 |
|---|---|
| StateTree | Boss大状態・Phase遷移 |
| Combat Context | Player / Stageの確定情報収集 |
| Attack Evaluator | Candidate Score計算・選択 |
| Gameplay Ability | 選択Attack実行 |
| Action History | 実行済み行動・傾向の記録 |
| Debug Presentation | Context、Score、選択理由の可視化 |

## 4. 状態・Gameplay Tag

各Boss FRで必要なState / Windowを定義する。DefeatedはPhase Transition、Posture Down、Recovery等より優先する。

## 5. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| AttackId | Candidate識別 | Master Data |
| RequiredPhase | Phase制約 | Master Data |
| Range条件 | Attack実行範囲 | Master Data |
| BaseScore | 基本評価値 | Master Data |
| Context Modifier | Distance / Stamina / Healing / History等の補正 | Master Data |
| Cooldown | 再使用制約 | Master Data |
| RepetitionPenalty | 同一行動連続抑制 | Master Data |
| ComboBranch | 後続Attack候補 | Master Data |
| Recovery / Counter Window | 反撃可能な隙 | Master Data / Runtime |

DB / CSV SchemaとReaderは別Architecture Designで定義する。

## 6. Debug — Boss AI基本設計の必須契約

Debugは別Gameplay Featureではなく、Boss AI基本設計の検証責務とする。各FR実装時、そのFRに関連する項目を確認可能にする。

| 項目 | 主な対象要件 |
|---|---|
| Boss State / Current Phase | `FR-BOSS-001/002` |
| Distance / Distance Score | `FR-BOSS-003` |
| Healing State / Modifier | `FR-BOSS-005` |
| Player Stamina / Modifier | `FR-BOSS-006` |
| Recent Action History / Battle Trend | `FR-BOSS-007` |
| Candidate List / Base Score / Final Score / Selected Attack | `FR-BOSS-008` |
| Approach / Retreat / Ranged Frequency補正 | `FR-BOSS-009/010` |
| Combo Branch条件 / 選択結果 | `FR-BOSS-011` |
| Recovery / Counter Window State | `FR-BOSS-012/013` |

Debug要件：

- 最終選択結果だけでなくScore内訳を確認できる。
- Debug ON/OFFでAI判断結果を変えない。
- Shipping Gameplay仕様をDebug表示へ依存させない。
- Invalid Player / DataでもDebug処理からCrashしない。

## 7. UI / Animation / Feedback

Boss HP HUDはGameplay HUDへ通知する。AI Debugは開発用表示としてGameplay HUDとは分離する。

## 8. 異常系・終了条件

- Invalid Target時は新規Attack評価・実行を安全に停止する。
- Defeated後にCandidate評価・Ability実行を行わない。
- Cooldown / Candidate不成立時に無効Attackを強制実行しない。
- Debug参照切れでGameplay本体を停止させない。

## 9. 受入条件

- [ ] Combat Contextから確定済み情報だけを収集できる。
- [ ] 複数Attack Candidateを評価できる。
- [ ] Scoreに基づき有効Candidateを選択できる。
- [ ] 各FRに関連するDebug値とScore内訳を確認できる。
- [ ] Debug ON/OFFで選択結果が変わらない。
- [ ] Defeated後にAI評価を停止できる。

## 10. 依存・Issue反映

Boss AI親Issue `#125`および実装Issue `#126`～`#131`は、本共通設計のうち各Issueに関連するDebug・Data・異常系・受入条件を含める。

## 11. 未決事項

なし。Debug表示Layout、表示方式、具体Score値は調整項目とする。
