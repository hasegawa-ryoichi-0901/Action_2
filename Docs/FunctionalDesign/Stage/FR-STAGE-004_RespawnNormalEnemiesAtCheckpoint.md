# FR-STAGE-004 Checkpoint Rest時に通常EnemyをRespawnする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-004` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#91`, `#93` |
| 関連要件・設計 | `FR-STAGE-003`, `FR-SAVE-002` |

## 2. 目的
Checkpoint Restを通常Enemy再配置の区切りとし、攻略ループを再構築する。

## 3. 確定仕様・スコープ
- CheckpointのRest処理で通常Enemyを初期状態 / 初期配置へ戻す。
- Bossは通常Enemy Respawn対象に含めない。
- Rest確定後のEnemy状態をAuto Save前提のGameplay状態とする。

## 4. 基本フロー
```text
Checkpoint Rest
↓
Normal Enemy一覧 / Spawn定義取得
↓
既存Enemy状態整理
↓
初期位置・初期状態へRespawn / Reset
↓
Rest完了通知
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Checkpoint / Stage | Respawn要求 |
| Enemy Spawn / Reset | 通常Enemy復元 |
| Enemy AI | 初期Stateへ復帰 |

## 6. 状態 / Gameplay Tag
Enemy Defeated / Down / Combat等のRuntime状態を初期状態へ戻す。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Enemy SpawnId | 対象識別 | Level / Master Data |
| Spawn Transform | 初期位置 | Level Data |
| Initial Enemy State | 初期化 | Gameplay Data |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Bossや永続的に消える特殊Actorを誤Respawnしない。
- 重複Actorを生成しない。
- Reset中の古いAI Task / Slotを残さない。

## 10. 受入条件
- [ ] Restで通常Enemyを復活できる。
- [ ] 初期位置・状態へ戻せる。
- [ ] Bossを対象にしない。
- [ ] 重複Spawnしない。

## 11. 依存・Issue反映
### 依存
- `FR-STAGE-003`

### Issue反映
- `#93`へNormal Enemy RespawnをRest処理として反映する。

## 12. 未決事項
なし
