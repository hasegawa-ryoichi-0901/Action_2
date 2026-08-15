# FR-STAGE-003 Checkpointを使用してMenuを開く

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-003` |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | `#91`, `#92` |
| 関連要件・設計 | `FR-STAGE-004`, `FR-STAGE-005`, `FR-SAVE-002`, `FR-STAGE-007` |

## 2. 目的
CheckpointをRespawn地点・Rest・強化・Saveの拠点として利用する。

## 3. 確定仕様・スコープ
- CheckpointへのInteractionで処理を開始する。
- `Interaction → ActiveCheckpoint更新 → Menu Open → Rest処理確定 → Auto Save`の順序を正とする。
- Checkpointへ接近しただけではSave / Restしない。

## 4. 基本フロー
```text
Interaction
↓
ActiveCheckpoint更新
↓
Menu Open
↓
Rest処理
├ HP / Stamina Full
├ Healing Item補充
└ Normal Enemy Respawn
↓
Auto Save
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Checkpoint | Interaction受付・Active更新 |
| Menu | Checkpoint機能表示 |
| Rest | 回復・Enemy Respawn |
| Save | Rest確定後Snapshot保存 |

## 6. 状態 / Gameplay Tag
ActiveCheckpointIdを進行状態として保持する。専用Gameplay Tagは必須ではない。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| CheckpointId | Active地点識別 | Level / Master Data |
| Respawn Transform | Respawn位置 | Level Data |
| Interaction State | 多重実行防止 | Runtime |

## 8. UI / HUD / Animation / Feedback
Checkpoint Menuを表示し、Rest / Weapon Upgrade / Manual Save等の利用可能機能を提示する。

## 9. 異常系・終了条件
- 同一InteractionでMenu / Rest / Saveを重複実行しない。
- 無効CheckpointをActiveにしない。
- Menu終了時に入力Mode等を正しく復帰する。

## 10. 受入条件
- [ ] InteractionでActiveCheckpointを更新できる。
- [ ] 更新後にMenuを開ける。
- [ ] Rest処理確定後にAuto Saveへ接続できる。
- [ ] 接近だけでは処理しない。

## 11. 依存・Issue反映
### 依存
- `#89` Checkpoint Save
- `#93` Rest

### Issue反映
- `#91`を親Issue、`#92`をInteraction / Active / Menuとして扱う。

## 12. 未決事項
なし
