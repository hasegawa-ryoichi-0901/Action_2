# FR-STAGE-006 CheckpointでWeapon Menuを利用する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-006` |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | `FR-PLAYER-008`, `FR-PLAYER-009`, `FR-STAGE-003` |

## 2. 目的
Axe / Bow追加後にCheckpoint Menuから装備Weaponを変更する導線を提供する。

## 3. 確定仕様・スコープ
- Initial VSはSword固定のため対象外。
- Post-VSでCheckpoint MenuにWeapon Change項目を追加する。
- 実際の装備変更は`FR-PLAYER-008`が担当する。

## 4. 基本フロー
```text
Checkpoint Menu
↓
Weapon Menu
↓
Weapon選択
↓
FR-PLAYER-008へChange Request
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Checkpoint UI | Weapon Menu表示 |
| Weapon System | 選択結果の装備反映 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Available Weapons | 選択肢 | Runtime / Master Data |
| Current Weapon | 現在装備表示 | Runtime |

## 8. UI / HUD / Animation / Feedback
Checkpoint Weapon Menuと現在装備表示を追加する。

## 9. 異常系・終了条件
- 未実装Weaponを選択可能にしない。
- Menu閉鎖時に選択途中状態を残さない。

## 10. 受入条件
- [ ] Post-VSでWeapon Menuを開ける。
- [ ] 利用可能Weaponを表示できる。
- [ ] 選択を`FR-PLAYER-008`へ渡せる。

## 11. 依存・Issue反映
### 依存
- Axe / Bow実装

### Issue反映
- Post-VS Roadmap作成時にIssue化する。

## 12. 未決事項
なし
