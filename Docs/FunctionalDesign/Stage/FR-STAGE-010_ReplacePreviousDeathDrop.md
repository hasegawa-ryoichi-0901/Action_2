# FR-STAGE-010 未回収DeathDropを残して再死亡した場合に置き換える

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-010` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#82`, `#86` |
| 関連要件・設計 | `FR-STAGE-008`, `FR-STAGE-009` |

## 2. 目的
未回収DeathDropを複数残さず、再死亡時に以前のResourceを永久消失させるDark Souls型ループを成立させる。

## 3. 確定仕様・スコープ
- 未回収DeathDropが存在する状態で再死亡した場合、旧DeathDrop本体と格納内容をすべて消失させる。
- 旧内容を新Dropへ引き継がない。
- 再死亡時点のPlayer InventoryからMaterial100% / Gold100%だけを新Dropへ移す。
- 常に未回収DeathDropは最大1つとする。

## 4. 基本フロー
```text
Player再死亡
↓
旧Active DeathDropあり?
├ No → 通常DeathDrop生成
└ Yes → 旧本体 / 内容を完全消失
          ↓
現在Inventoryから新Drop生成
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| DeathDrop Manager / Flow | 旧Drop識別・消失 |
| Player Inventory | 新Drop移動元 |
| Save | 旧Drop消失と新Drop状態保存 |

## 6. 状態 / Gameplay Tag
Active DeathDropを1件だけ進行状態として保持する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Active DeathDrop Reference / Id | 旧Drop識別 | Runtime / Save |
| Stored Resource | 消失対象 | Runtime / Save |
| New Death Transform | 新Drop位置 | Runtime |

## 8. UI / HUD / Animation / Feedback
旧Drop消失の専用UIは必須としない。新Dropは死亡フローでCamera確認する。

## 9. 異常系・終了条件
- 旧Drop内容をInventoryへ返却しない。
- 旧Dropと新Dropを同時Activeにしない。
- Save / Load後もActive Dropを1つだけ復元する。

## 10. 受入条件
- [ ] 再死亡時に旧Drop本体 / 内容を完全消失できる。
- [ ] 旧内容を新Dropへ合算しない。
- [ ] 新Dropは現在Inventory分だけで生成できる。
- [ ] Active Dropが最大1つに保たれる。

## 11. 依存・Issue反映
### 依存
- `FR-STAGE-008`, `FR-SAVE-005`

### Issue反映
- `#86`へ旧Drop消失 / 一意性 / Save復元を反映する。

## 12. 未決事項
なし
