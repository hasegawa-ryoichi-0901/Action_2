# FR-STAGE-010 DeathDrop回収前に再死亡すると旧DeathDropを消失させる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-010` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#82`, `#86` |
| 関連設計 | `FR-STAGE-008`, `FR-STAGE-009`, `FR-SAVE-005` |

## 2. 目的

未回収DeathDropを最大1つに限定し、回収前の再死亡で旧DeathDropと格納Resourceを永久消失させる。

## 3. 確定仕様・基本フロー

```text
[Player再死亡]
      ↓
[未回収DeathDropあり？]
      +-- Yes --> [旧DeathDrop本体を消去]
                   [旧Drop内Upgrade Material / Goldを永久消失]
      ↓
[現在Player Inventoryの所持量を取得]
      +--> Upgrade Material 100%
      +--> Gold 100%
      ↓
[新DeathDropを今回の死亡地点へ生成]
      ↓
[座標・内容確定]
      ↓
[Auto Save]
```

- 旧DeathDropの内容を新DeathDropへ引き継がない。
- World上の未回収DeathDropは最大1つ。
- Gold / Upgrade Materialの正本はPlayer Inventory。

## 4. 責務

| 対象 | 責務 |
|---|---|
| DeathDrop管理 | 旧Drop検出・完全消失・新Drop登録 |
| Player Inventory | 新Dropへ移す現在所持Resourceを提供する |
| Save System | 新Drop確定状態を保存する |

## 5. 状態・Gameplay Tag

本要件固有Tagは必須にしない。Active DeathDropを一意に識別できること。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| ActiveDeathDrop識別 | 旧Drop検出 | Runtime / Save |
| StoredUpgradeMaterial | 旧Drop消失 / 新Drop格納 | Save対象 |
| StoredGold | 旧Drop消失 / 新Drop格納 | Save対象 |
| DeathDropTransform | 新Drop位置 | Save対象 |

## 7. UI / Animation / Feedback

旧DeathDrop消失の専用UIは必須としない。死亡フローのCamera確認へ接続する。

## 8. 異常系・終了条件

- 旧Drop消失前に旧内容をPlayer Inventoryへ戻さない。
- 新Dropへ旧Drop内容を合算しない。
- 同一死亡Eventで複数の新Dropを生成しない。

## 9. 受入条件

- [ ] World上の未回収DeathDropを最大1つにできる。
- [ ] 再死亡時に旧DeathDrop本体と格納Resourceを完全消失できる。
- [ ] 新DeathDropは再死亡時点のPlayer Inventory所持量だけから生成する。
- [ ] Upgrade Material 100%とGold 100%を新Dropへ移せる。
- [ ] Save / Load後も同じルールを維持できる。

## 10. 依存・Issue反映

- `#82`, `#86`, `#90`
- `FR-SAVE-005`

## 11. 未決事項

なし。
