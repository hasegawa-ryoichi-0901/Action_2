# FR-STAGE-007 CheckpointでWeaponをUpgradeする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-007` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#94`, `#95`, `#96` |
| 関連要件・設計 | `FR-STAGE-003`, Player Inventory, `Docs/17_MasterDataCsvArchitecture.md` |

## 2. 目的
CheckpointをWeapon強化地点とし、GoldとUpgrade Materialを消費してWeapon Levelを上げる。

## 3. 確定仕様・スコープ
- Weapon UpgradeはCheckpoint Menuでのみ実行する。
- GoldとUpgrade Materialの両方をCostとして使用する。
- Goldの用途はWeapon Upgradeのみ。
- Resourceの正本はPlayer Inventory。
- Upgrade完了自体はAuto Save契機ではない。

## 4. 基本フロー
```text
Checkpoint Weapon Upgrade Request
↓
Upgrade Cost取得
↓
Gold / Material所持確認
├ 不足 → Reject / 消費なし
└ 足りる
  ↓
両Resource消費
↓
Weapon Level更新
↓
結果表示
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Checkpoint Menu | Upgrade選択UI |
| Upgrade System | Cost判定・Level更新 |
| Player Inventory | Gold / Material保持・消費 |
| Game Data Provider | Upgrade Cost提供 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| WeaponId / UpgradeLevel | 対象識別 | Runtime / Master Data |
| RequiredGoldAmount | Gold Cost | Master Data |
| RequiredMaterialId / Amount | Material Cost | Master Data |
| Upgrade Result Parameters | 強化結果 | Master Data |

## 8. UI / HUD / Animation / Feedback
Checkpoint Upgrade UIで現在Level、Cost、所持Gold / Material、成功 / 不足を表示する。

## 9. 異常系・終了条件
- 片方不足時にResourceを部分消費しない。
- 最大Level超過を拒否する。
- 多重Requestで二重消費しない。

## 10. 受入条件
- [ ] CheckpointでのみUpgradeできる。
- [ ] Gold / Material両方の所持を判定できる。
- [ ] 成功時だけ両Resourceを消費しLevelを更新できる。
- [ ] UpgradeだけではAuto Saveしない。

## 11. 依存・Issue反映
### 依存
- `#91` Checkpoint
- Player Inventory

### Issue反映
- `#94`を親Issue、`#95` Cost、`#96` 消費 / Level更新として扱う。

## 12. 未決事項
なし
