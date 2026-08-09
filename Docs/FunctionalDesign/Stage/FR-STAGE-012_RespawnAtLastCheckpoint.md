# FR-STAGE-012 死亡後、最後に有効化したチェックポイントから再開する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-012` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-PLAYER-020`, `FR-STAGE-003`, `FR-STAGE-004`, `FR-STAGE-008` |

## 2. 目的

プレイヤー死亡後にゲーム進行を継続できる再開地点と復帰処理を定義する。

## 3. 基本フロー

```text
[Player Death確定]
      ↓
[DeathDrop生成完了]
      ↓
[Respawn Request]
      ↓
[ActiveCheckpoint取得]
      +-- 無効 --> [Fallback Spawn: TBD]
      ↓
[PlayerをCheckpointへ復帰]
      +--> HP回復
      +--> 回復アイテム補充
      +--> 必要な一時状態解除
      +--> 通常敵復活
      ↓
[入力再有効化]
```

## 4. 責務

| 対象 | 責務 |
|---|---|
| Checkpoint管理 | 最後に有効化したCheckpoint ID / Transform管理 |
| Death System | Respawn Request発行 |
| Player | Respawn後の状態初期化 |
| Enemy Respawn | 通常敵の復活 |
| Input System | 安全なタイミングで入力を再有効化 |

## 5. 受入条件

- [ ] ActiveCheckpointが存在する場合、その地点から再開する。
- [ ] Respawn後にHealthが有効値へ復元される。
- [ ] 回復アイテムが仕様どおり補充される。
- [ ] 通常敵が復活する。
- [ ] `State.Dead`等の死亡用一時状態が残らない。
- [ ] Respawn完了前にPlayer入力が誤って有効にならない。
- [ ] 同一DeathからRespawnを複数回実行しない。

## 6. テスト観点

- Checkpoint A / B切替後のRespawn
- DeathDrop生成との順序
- Enemy Respawn
- Respawn中Level遷移
- Input再セットアップ
- ActiveCheckpoint無効

## 7. 未決事項

- Checkpoint未有効化時のFallback Spawn
- Respawnまでの待機条件
- Stamina全回復の有無
- Death / Respawn時AutoSaveの有無

詳細は`Docs/15_OpenQuestions.md`で確定する。
