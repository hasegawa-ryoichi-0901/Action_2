# FR-BOSS-015 HP0以下でBossをDefeatする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-015` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#100`, `#101` |
| 関連要件・設計 | `FR-BOSS-016`, `FR-SAVE-004`, `FR-STAGE-013` |

## 2. 目的
Boss戦終了条件を一意に確定し、Reward、Auto Save、Clear Area、Ending、Titleへ正しい順序で接続する。

## 3. 確定仕様・スコープ
- Health<=0でBoss Defeatedを1回だけ確定する。
- DefeatedはPhase Transition / Down / Recoveryより優先する。
- AI評価・Attack Abilityを停止する。
- `Defeated → Gold → 初回固有Item → Reward確定 → Auto Save → Clear Area → Clear Trigger → Ending → Title`を確定順序とする。
- Boss撃破直後にEndingへ自動遷移しない。

## 4. 基本フロー
```text
Boss Health <= 0
↓
Defeated
↓
AI / Ability停止
↓
FR-BOSS-016 Reward
↓
FR-SAVE-004 Auto Save
↓
FR-STAGE-013 Clear Area / Ending / Title
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Boss Combat | Defeated一意確定 |
| AI / Ability | 行動停止 |
| Reward | Gold / Unique Item付与 |
| Save | Reward確定後保存 |
| Stage Progression | Clear Trigger以降 |

## 6. 状態 / Gameplay Tag
DefeatedをBoss終端状態として扱う。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Health | Defeat判定 | Runtime |
| BossId / RewardId | Reward接続 | Master Data |
| Clear Progress State | 後続解放 | Runtime |

## 8. UI / HUD / Animation / Feedback
Boss HP表示を終了し、Defeat Animation / Feedbackを設定可能にする。EndingはStage側が担当する。

## 9. 異常系・終了条件
- 同Frame複数HitでDefeatedを重複確定しない。
- Defeated後にPhase2 / Attack評価を開始しない。
- Reward / Save完了前にClear Triggerを有効化しない。

## 10. 受入条件
- [ ] Health0でDefeatedを1回だけ確定できる。
- [ ] AI / Abilityを停止できる。
- [ ] Reward → Save → Stage Progressionの順序を維持できる。
- [ ] Boss撃破直後にEndingへ入らない。

## 11. 依存・Issue反映
### 依存
- `#102` Reward
- `#103` Auto Save
- `#105` Stage Clear

### Issue反映
- `#101`へDefeated状態と停止処理、親`#100`へ後続順序を反映する。

## 12. 未決事項
なし
