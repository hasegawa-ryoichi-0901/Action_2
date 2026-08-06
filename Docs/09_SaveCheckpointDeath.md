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

## 3. セーブ処理

```text
[Save Request]
      |
      v
[Build Save Data]
      |
      +--> SaveVersion
      +--> Checkpoint
      +--> Weapon Upgrade
      +--> Material
      +--> Progress
      |
      v
[Validate]
      |
      +-- NG --> [Log / Abort]
      |
      v
[Write Temporary File]
      |
      v
[Replace Main Save]
      |
      v
[Complete]
```

## 4. チェックポイント

チェックポイント使用時に次を行います。

```text
[Rest at Checkpoint]
      |
      +--> ActiveCheckpoint更新
      +--> HP回復
      +--> スタミナ回復
      +--> 回復アイテム補充
      +--> 武器変更UI
      +--> 武器強化UI
      +--> 通常敵復活
      +--> オートセーブ
```

## 5. 死亡

```text
[Player Death]
      |
      +--> 所持強化素材を記録
      +--> 以前の未回収DeathDropを削除
      +--> 新しいDeathDropを死亡位置に生成
      |
      v
[Respawn at Active Checkpoint]
      |
      +--> HP回復
      +--> 回復アイテム補充
      +--> 通常敵復活
```

## 6. 素材回収

```text
[Player overlaps DeathDrop]
      |
      v
[Add Dropped Material]
      |
      v
[Destroy DeathDrop]
      |
      v
[Auto Save候補]
```

## 7. バージョン管理

```text
SaveVersion = 1
```

将来のアップデートを想定し、ロード時にバージョンを確認します。

```text
[Load]
   |
   v
[Version Check]
   |
   +-- Current --> [Load Directly]
   |
   +-- Old --> [Migrate]
   |
   +-- Unsupported --> [Backup / New Save / Error]
```

## 8. Steam Cloud

Steam CloudはSteam公開版の追加要件です。

ローカルセーブが安定した後に、Auto-CloudまたはSteam Remote Storageの採用方式を比較します。


### [戻る](../README.md#ドキュメント一覧)
