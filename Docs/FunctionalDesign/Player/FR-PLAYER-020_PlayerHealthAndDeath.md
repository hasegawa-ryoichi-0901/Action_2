# FR-PLAYER-020 プレイヤーはHPを持ち、HPが0以下になると死亡する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-020` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#82`, `#83` |
| 関連要件 | `FR-STAGE-008`, `FR-STAGE-012` |

## 2. データ・状態

- `Health`
- `MaxHealth`
- `State.Dead`

HealthはGAS Attributeとして管理する方針です。

## 3. 基本フロー

```text
[Damage]
      ↓
[Health更新]
      +-- Health > 0 --> [Combat継続]
      ↓
[Health <= 0]
      ↓
[Death Transition Guard]
      +-- Already Dead --> [Ignore]
      ↓
[State.Dead]
      +--> Combat Action終了 / Cancel
      +--> 通常Gameplay入力停止
      +--> Camera Lookは許可
      ↓
[Death Animation]
      ↓
[DeathDrop Systemへ通知]
```

Death Animation完了後のDeathDrop、Auto Save、Camera確認、Fade Out、Respawnは`FR-STAGE-008`～`012`および`Docs/09_SaveCheckpointDeath.md`へ委譲します。

## 4. 受入条件

- [ ] Health <= 0でDeathへ1回だけ遷移する。
- [ ] 同Frame複数Hit / OverkillでDeath処理を重複しない。
- [ ] Attack / Dodge / Heal等を終了・Cancelできる。
- [ ] Death中は通常Gameplay Actionを開始できない。
- [ ] Death中もCamera Lookできる。
- [ ] Death Animation完了EventからDeathDrop処理へ1回だけ接続する。
