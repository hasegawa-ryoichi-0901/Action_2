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

Save破損を検出した場合は、破損SaveをGameplayへ適用せず削除し、New Gameを開始できる状態へ戻す。初期プレイアブル版ではBackupからの自動復旧は行わない。

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

## 5. 確定している破損Saveの扱い

```text
Save Load
↓
Validation
├ Valid → Runtimeへ復元
└ Corrupt / Invalid
   ↓
Runtimeへ適用しない
   ↓
破損Saveを削除
   ↓
Title / Load側へ失敗通知
   ↓
New Game開始可能状態
```

- 正常Saveを誤って削除しない。
- 破損Saveの一部だけをRuntimeへ適用しない。
- 削除後は旧Save由来のRuntime状態を残さない。
- 初期プレイアブル版ではBackup復旧を行わない。

## 6. 後続Architecture設計事項

以下は具体実装時に本Architectureで決定する。

- JSON Schema
- Version field
- Migration方式
- Atomic Write方式
- Corrupt Save検出方式
- Serializer / Deserializer実装
- File Path / Slot Nameの物理表現
- Steam Cloud連携

これらの具体実装方式は、Gameplay基本設計で確定済みのSave挙動を変更しない範囲で決定する。
