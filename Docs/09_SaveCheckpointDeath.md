# 09. セーブ・チェックポイント・死亡

## 1. セーブスロット

- 1スロット
- オートセーブ中心
- 設定データは進行データと分離可能な構造にする

## 2. オートセーブ

次のタイミングで保存します。

- チェックポイント使用時
- 武器強化時
- ボス撃破時
- ステージクリア時
- 設定変更時

Boss DefeatedとStage Clearが連続するため、同一進行で2回のSave Requestが発生した場合の集約・直列化方針は実装前に確定します。

## 3. セーブ処理

```text
[Save Request]
      ↓
[Build Save Data]
      +--> SaveVersion
      +--> Checkpoint
      +--> Weapon Upgrade
      +--> Material
      +--> Progress
      ↓
[Validate]
      +-- NG --> [Log / Abort]
      ↓
[Write Temporary File]
      ↓
[Replace Main Save]
      ↓
[Complete]
```

## 4. チェックポイント

チェックポイント使用時に次を行います。

```text
[Rest at Checkpoint]
      +--> ActiveCheckpoint更新
      +--> HP回復
      +--> スタミナ回復
      +--> 回復アイテム補充
      +--> 武器強化UI
      +--> 通常敵復活
      +--> オートセーブ
```

初期Vertical Sliceでは剣のみのため武器変更UIを必須としません。斧・弓追加後に武器変更を有効化します。

## 5. プレイヤー死亡

```text
[Player Health <= 0]
      ↓
[State.Deadを確定]
      +--> 実行中戦闘処理停止
      +--> 入力 / 一時状態解除
      +--> 所持強化素材を記録
      +--> 以前の未回収DeathDropを削除
      +--> 新しいDeathDropを死亡位置に生成
      ↓
[Respawn Request]
      ↓
[Respawn at Active Checkpoint]
      +--> HP回復
      +--> 回復アイテム補充
      +--> 通常敵復活
```

未決事項：
- ActiveCheckpointが存在しない場合のFallback Spawn。
- Death確定からRespawnまでの待機条件（Death Animation完了 / Timer等）。
- Respawn時にStaminaを全回復するか。
- DeathDrop生成・Respawn直後にSaveするか。

## 6. 敵・ボス撃破との連携

### 通常敵

```text
[Enemy Health <= 0]
      ↓
[Defeated]
      +--> AI停止
      +--> 攻撃枠解放
      +--> Combat停止
      ↓
[Reward Grant]
      ↓
[Upgrade Material加算候補]
```

報酬量・付与対象はEnemy Definition / Reward Definition等のデータで設定します。

### ボス

```text
[Boss Health <= 0]
      ↓
[Boss Defeated]
      +--> AI / Ability停止
      +--> Boss Defeat Save Request
      ↓
[Stage Clear]
      +--> Progress更新
      +--> Stage Clear Save Request
      +--> Clear Presentation
```

Boss DefeatとStage Clearのイベント順序は上記を基本とし、Save Request重複時の扱いを確定してから実装します。

## 7. 素材回収

```text
[Player overlaps DeathDrop]
      ↓
[Add Dropped Material]
      ↓
[Destroy DeathDrop]
      ↓
[Auto Save候補]
```

通常の強化素材獲得と死亡素材回収は別経路とし、最終的には同じUpgradeMaterial所持値へ集約します。

## 8. バージョン管理

```text
SaveVersion = 1
```

将来のアップデートを想定し、ロード時にバージョンを確認します。

```text
[Load]
   ↓
[Version Check]
   +-- Current --> [Load Directly]
   +-- Old --> [Migrate]
   +-- Unsupported --> [Backup / New Save / Error]
```

## 9. Steam Cloud

Steam CloudはSteam公開版のPost-Vertical Slice追加要件です。ローカルセーブが安定した後に採用方式を比較します。

### [戻る](../README.md#ドキュメント一覧)
