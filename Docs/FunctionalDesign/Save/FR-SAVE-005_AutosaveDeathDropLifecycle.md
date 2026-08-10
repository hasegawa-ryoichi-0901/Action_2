# FR-SAVE-005 DeathDrop生成・回収後にAuto Saveする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-SAVE-005` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-STAGE-008`, `FR-STAGE-009`, `FR-STAGE-010`, `FR-STAGE-012` |

## 2. 目的

DeathDropの生成・消失・回収状態とPlayer所持Resourceの状態を同じ保存時点で確定し、終了・再起動後のResource二重取得や消失矛盾を防ぐ。

## 3. Death時Auto Save

```text
[Death Animation完了]
      ↓
[旧DeathDropがあれば完全消失]
      ↓
[新DeathDrop生成]
   +--> Upgrade Material 100%
   +--> Gold 70%
   +--> Gold 30%永久消失
      ↓
[死亡座標・格納内容確定]
      ↓
[Auto Save]
      ↓
[Camera確認 → Fade Out → Respawn]
```

## 4. 回収時Auto Save

```text
[DeathDrop回収]
      ↓
[Upgrade Material全量返却]
[Gold全量返却]
      ↓
[DeathDrop消去]
      ↓
[Auto Save]
```

## 5. 復元要件

- 未回収DeathDropの位置と格納内容をSave/Load後に復元できる。
- Playerは最後のActive Checkpoint、未設定時はPlayerStartから再開する。
- 保存媒体・JSON構造は別Architecture Designで扱う。

## 6. 受入条件

- [ ] DeathDrop内容確定前に死亡Saveを発行しない。
- [ ] 旧DeathDropがある再死亡では旧Dropと格納Resourceを先に失う。
- [ ] 新DeathDropはMaterial 100%、Gold 70%を保持する。
- [ ] Gold 30%はDeath時に回収不能となる。
- [ ] DeathDrop回収完了後に1回Auto Saveする。
- [ ] Save/Load後に未回収DeathDropを二重生成しない。
