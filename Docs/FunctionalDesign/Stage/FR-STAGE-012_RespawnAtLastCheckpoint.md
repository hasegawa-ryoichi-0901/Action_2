# FR-STAGE-012 最後のCheckpointからRespawnする

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-012` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 基本フロー

```text
[Player Death]
      ↓
[Death Animation完了]
      ↓
[DeathDrop生成・Auto Save]
      ↓
[CameraでDeathDrop確認]
      ↓
[Fade Out]
      ↓
[Active Checkpointあり？]
   ├─ Yes → Active CheckpointへRespawn
   └─ No  → PlayerStartへRespawn
      ↓
[HP Full / Stamina Full / Healing Item Full]
      ↓
[Normal Enemy Respawn]
      ↓
[Fade In / Gameplay再開]
```

## 3. 確定仕様

- Death状態中もCamera Lookを許可する。
- DeathDrop確認後にFade OutしてからRespawnする。
- Active Checkpoint未設定時はPlayerStartをFallbackとする。
- HP、Stamina、Healing Itemを全回復する。
- 通常敵を復活させる。

## 4. 受入条件

- [ ] Death Animation完了前にRespawnしない。
- [ ] DeathDrop生成・Save確定前にRespawnしない。
- [ ] Active Checkpointがあればその地点へ戻る。
- [ ] 未設定でもPlayerStartへ安全に戻れる。
- [ ] 復帰後のHP / Stamina / Healing Itemが全回復している。
- [ ] 通常敵が復活している。
