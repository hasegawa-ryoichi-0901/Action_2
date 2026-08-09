# FR-BOSS-015 HPが0以下になると撃破状態へ遷移する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-015` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-BOSS-002`, `FR-STAGE-013`, `FR-SAVE-004` |

## 2. 目的

ボス戦の終了条件を一意に定義し、AI停止・撃破保存・Stage Clearへ安全に接続する。

## 3. 基本フロー

```text
[Damage]
   ↓
[Boss Health更新]
   +-- Health > 0 --> [Combat継続]
   ↓
[Health <= 0]
   ↓
[Defeat Guard]
   +-- 既にDefeated --> [Ignore]
   ↓
[Boss Defeated]
   +--> Attack Ability終了
   +--> StateTree / Evaluator停止
   +--> Targeting / Collision調整
   +--> BossDefeated Event発行
   ↓
[FR-SAVE-004]
   ↓
[FR-STAGE-013]
```

## 4. 状態優先順位

- DefeatedはPhase Transition、Posture Down、Recovery等より優先する。
- Health<=0後にPhase2へ新規遷移しない。
- Defeated後に新しい攻撃候補を評価・実行しない。

## 5. 責務

| 対象 | 責務 |
|---|---|
| Boss Attribute / Damage | Health更新 |
| Boss Combat / Death処理 | Defeated確定、Ability停止 |
| StateTree / Attack Evaluator | Defeated時の評価停止 |
| Stage Progression | BossDefeated EventからStage Clearへ遷移 |
| Save System | Boss Defeat時のAutoSave Request |

## 6. 受入条件

- [ ] Health>0ではDefeatedへ遷移しない。
- [ ] Health<=0で1回だけDefeatedへ遷移する。
- [ ] Defeated後に攻撃AbilityやAI評価を実行しない。
- [ ] Phase Transition中にHP0になってもDefeatedを優先する。
- [ ] BossDefeated EventをStage Progressionへ1回だけ通知する。
- [ ] Boss Defeat Saveを重複要求しない。

## 7. 未決事項

- 撃破Animation完了をStage Clear開始条件とするか
- Boss Collision / Targeting解除タイミング
- Boss Defeat SaveとStage Clear Saveの連続Request制御

詳細は`Docs/15_OpenQuestions.md`で確定する。
