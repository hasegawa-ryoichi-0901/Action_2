# FR-STAGE-012 最後のActive CheckpointからRespawnする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-012` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#82`, `#85` |
| 関連要件・設計 | `FR-PLAYER-020`, `FR-STAGE-008`, `FR-SAVE-005` |

## 2. 目的
死亡後に最後に利用したCheckpointから再開し、未利用時はPlayerStartへ安全に戻す。

## 3. 確定仕様・スコープ
- `Death Animation → DeathDrop生成 → Auto Save → Camera確認 → Fade Out → Respawn`の順序とする。
- Active CheckpointがあればそのRespawn Transformを使用する。
- 未設定ならPlayerStartをFallbackとする。
- Respawn後はHP / Stamina / Healing ItemをFullにする。
- 通常EnemyをRespawnする。
- Fade In後にGameplay Inputを再開する。

## 4. 基本フロー
```text
DeathDrop Save完了
↓
CameraでDrop確認
↓
Fade Out
↓
Active Checkpointあり?
├ Yes → Checkpoint Transform
└ No → PlayerStart
↓
Player復帰 / Resource Full / Enemy Respawn
↓
Fade In / Input再開
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Death Flow | Camera / Fade / Respawn順序 |
| Checkpoint State | Respawn地点提供 |
| Player | Resource / State復帰 |
| Stage | Normal Enemy Respawn |

## 6. 状態 / Gameplay Tag
Respawn完了時に`State.Dead`を解除し、Gameplay可能状態へ戻す。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| ActiveCheckpointId | Respawn地点識別 | Runtime / Save |
| Checkpoint Transform | Respawn位置 | Level Data |
| PlayerStart Transform | Fallback | Level Data |
| Fade / Camera Timing | Presentation | 調整値 |

## 8. UI / HUD / Animation / Feedback
CameraでDeathDropを確認し、Fade Out / Inを行う。復帰後HUDをFull値へ同期する。

## 9. 異常系・終了条件
- ActiveCheckpoint参照無効ならPlayerStartへFallbackする。
- Respawn中にGameplay Inputを再開しない。
- Fade / Respawnを重複開始しない。

## 10. 受入条件
- [ ] Active CheckpointからRespawnできる。
- [ ] 未設定時PlayerStartへRespawnできる。
- [ ] HP / Stamina / Healing ItemをFullにできる。
- [ ] 通常EnemyをRespawnできる。
- [ ] Fade In後にInputを再開できる。

## 11. 依存・Issue反映
### 依存
- `#84` DeathDrop生成
- `#90` Death Save

### Issue反映
- `#85`へCamera確認、Fade、Fallback、Resource復帰を反映する。

## 12. 未決事項
なし
