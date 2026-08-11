# 18. Save JSON Architecture

## 1. 目的

Gameplay基本設計で確定したSave / Load上の挙動と、JSONの具体Schema・Reader / Writerを分離する。

## 2. Gameplay側で確定している保存要件

未回収DeathDropはSave / Load後も次を復元する。

- DeathDrop死亡座標 / Transform
- Upgrade Material格納量
- Gold格納量
- 未回収 / Active状態

Playerは最後のActiveCheckpoint、未設定時はPlayerStartから再開する。

## 3. 境界

```text
[Gameplay / Save System]
      ↓ Snapshot / Restore Contract
[Save Data Model]
      ↓
[JSON Serializer / Deserializer]
      ↓
[Local Save]
```

Gameplay SystemはJSONキー名・JSON Library・File Layoutへ直接依存しない。

## 4. 確定Save契機

- Checkpoint Rest確定後
- DeathDrop生成位置・内容確定後
- DeathDrop回収完了後
- Boss Reward確定後
- Settings変更時（進行Saveとは別系統）

Weapon Upgrade完了、Stage Clear、Clear Trigger進入自体は進行Auto Save契機にしない。

## 5. 未確定事項

以下は本Architectureで後続決定する。

- JSON Schema
- Version field
- Migration方式
- Atomic Write / Backup方式
- Corrupt Save検出・Fallback
- Serializer / Deserializer実装
- File Path / Slot Nameの物理表現
- Steam Cloud連携

具体実装はGameplay FRの挙動確定Blockerにはしない。
