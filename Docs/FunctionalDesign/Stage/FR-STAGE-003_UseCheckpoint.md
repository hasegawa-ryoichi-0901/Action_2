# FR-STAGE-003 チェックポイントを使用できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-003` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |

## 2. 目的

回復・強化・敵復活・保存・死亡後の再開地点をまとめた攻略拠点を提供する。

## 3. 初期Vertical Sliceフロー

```text
[Interact Input]
      ↓
[Checkpoint有効性 / Player生存確認]
      ↓
[Rest]
      +--> ActiveCheckpoint更新
      +--> HP回復
      +--> Stamina回復
      +--> Healing Item補充
      +--> Normal Enemy Respawn
      +--> Weapon Upgrade
      +--> Auto Save
```

初期Vertical SliceはSwordのみのためWeapon Change Menuを必須としない。複数武器追加後に`FR-STAGE-006`を接続する。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Checkpoint Actor / Checkpoint管理 | Checkpoint ID、Interaction、ActiveCheckpoint更新 |
| Player | HP / Stamina等の復元 |
| Enemy Respawn | 通常敵復活 |
| Weapon Upgrade | Sword強化、Post-VSでは他武器も対象 |
| Save System | Checkpoint AutoSave |
| Respawn System | `FR-STAGE-012`でActiveCheckpointを再開地点として参照 |

## 5. 受入条件

- [ ] 有効なCheckpointを1回の操作で使用できる。
- [ ] ActiveCheckpointが現在地点へ更新される。
- [ ] HP / Stamina / Healing Itemが仕様どおり復元される。
- [ ] 通常敵が復活する。
- [ ] AutoSaveを1回要求する。
- [ ] 多重InteractionでRest処理を重複実行しない。
- [ ] 死亡時に最後に有効化したCheckpointを`FR-STAGE-012`から参照できる。
- [ ] 初期Vertical SliceではWeapon Change UIがなくても成立する。

## 6. Post-Vertical Slice

Axe / Bow実装後に`FR-STAGE-006`のWeapon Change Menuを追加する。Checkpoint本体のRest責務は武器追加によって変更しない。
