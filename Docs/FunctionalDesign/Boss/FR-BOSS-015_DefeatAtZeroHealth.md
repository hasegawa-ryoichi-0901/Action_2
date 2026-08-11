# FR-BOSS-015 HPが0以下になるとBoss Defeatedへ遷移する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-015` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#100`, `#101` |
| 関連設計 | `FR-BOSS-016`, `FR-SAVE-004`, `FR-STAGE-013`, `FR-UI-001` |

## 2. 目的

Boss戦の終了条件を一意にし、Defeat後のReward、Auto Save、Clear Area、Ending、Titleまでを重複なく接続する。

## 3. 確定仕様・基本フロー

```text
[Boss HP <= 0]
      ↓
[Boss Defeated]
      +--> Attack Ability停止
      +--> StateTree / Evaluator停止
      +--> 新規Attack評価停止
      ↓
[Gold付与]
      ↓
[初回固有Item付与]
      ↓
[Reward確定]
      ↓
[Auto Save]
      ↓
[PlayerがClear Areaへ移動]
      ↓
[Clear Trigger]
      ↓
[Skippable Ending]
      ↓
[Title]
```

- DefeatedはPhase Transition、Posture Down、Recoveryより優先する。
- Boss撃破直後にEndingへ自動遷移しない。
- Reward確定前にBoss Reward Saveを発行しない。
- Stage Clear自体では追加Auto Saveを行わない。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Boss Attribute / Combat | HP更新、Defeated確定、Ability停止 |
| Boss AI | StateTree / Evaluator / Attack選択停止 |
| Reward | Gold / 初回固有ItemをPlayer Inventoryへ付与 |
| Save | Reward確定後Auto Save |
| Stage Progression | Save完了後Clear Area / Triggerを進行可能にする |
| UI / Flow | Ending終了 / Skip後にTitleへ戻す |

## 5. 状態・Gameplay Tag

| State / Tag | 用途 |
|---|---|
| Boss Defeated State | Boss戦終了の正本 |

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Boss RewardId | Reward取得 | Master Data |
| First Defeat Item状態 | 初回固有Item重複防止 | Save Data |
| Clear Trigger参照 /状態 | Defeat後のStage進行 | Runtime / Map |

## 7. UI / Animation / Feedback

- Boss HP HUDを終了させる。
- Defeat Animation / VFX / SEはAsset調整可能。
- EndingはClear Trigger進入後に開始しSkip可能とする。

## 8. 異常系・終了条件

- 同Frame複数Hit / OverkillでもDefeatedを1回だけ確定する。
- Defeated後にPhase2 / Attack / AI評価へ戻らない。
- Reward / Save / Clear Trigger要求を重複発行しない。

## 9. 受入条件

- [ ] HP>0ではDefeatedへ遷移しない。
- [ ] HP<=0で1回だけDefeatedへ遷移する。
- [ ] Defeated後にAttack Ability / AI評価を停止する。
- [ ] Gold→初回固有Item→Reward確定の順で処理できる。
- [ ] Reward確定後にAuto Saveする。
- [ ] Auto Save後にClear Areaへ進行できる。
- [ ] Clear TriggerからEndingを開始できる。
- [ ] Ending終了 / Skip後にTitleへ戻る。
- [ ] Stage Clearで追加Auto Saveしない。

## 10. 依存・Issue反映

- `#100` Boss Defeat / Reward
- `#103` Boss Reward Auto Save
- `#105` Stage Clear

## 11. 未決事項

なし。Defeat Animationの具体Asset・尺、Clear Area表現は調整項目とする。
