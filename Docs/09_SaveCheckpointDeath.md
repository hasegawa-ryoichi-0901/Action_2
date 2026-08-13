# 09. セーブ・チェックポイント・死亡

## 1. セーブ方針

- Progress Saveは1 Slot。
- Settings DataはProgress Saveとは別のSave契機を持つ。
- 保存媒体、JSON Schema、Steam Cloud同期などの永続化Architectureは別設計で定義する。
- 本ドキュメントではゲーム上のSave契機とRestore要件を確定する。
- JSON永続化Architectureは[#154](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)で確定する。

## 2. Progress Auto Save契機

Auto Saveは次のタイミングに限定する。

1. Checkpointで`Interaction → ActiveCheckpoint更新 → Menu Open → Rest処理確定`まで完了した直後。
2. Player死亡時、新しいDeathDropの死亡座標と格納内容が確定した直後。
3. DeathDropの回収が完了した直後。
4. Boss撃破時、Goldと初回固有Itemを含むReward付与が確定した直後。

Weapon Upgrade完了、Stage Clear、Clear Trigger進入自体はAuto Save契機にしない。

## 3. Checkpoint

確定順序は次とする。

```text
[Interaction]
      ↓
[ActiveCheckpoint更新]
      ↓
[Menu Open]
      ↓
[Rest処理確定]
      +--> HP Full
      +--> Stamina Full
      +--> Healing Item補充
      +--> Normal Enemy Respawn
      ↓
[Auto Save]
```

Checkpointへ接近しただけではSaveしない。Manual SaveはCheckpoint Menuからのみ実行できる。

## 4. Weapon Upgrade

Weapon UpgradeはCheckpoint Menuでのみ実行する。GoldとUpgrade MaterialはPlayer Inventoryから消費する。Upgrade完了自体はAuto Save契機にしない。

## 5. Player Death / DeathDrop

```text
[Player Health <= 0]
      ↓
[State.Dead]
      ↓
[Death Animation]
      ↓
[旧DeathDropあり？]
      +-- Yes --> [旧DeathDrop本体・格納Resourceを完全消失]
      ↓
[Player Inventoryから現在所持Resourceを取得]
      +--> Upgrade Material 100%
      +--> Gold 100%
      ↓
[死亡地点に新DeathDrop生成]
      ↓
[死亡座標・格納内容確定]
      ↓
[Auto Save]
      ↓
[CameraでDeathDrop確認]
      ↓
[Fade Out]
      ↓
[ActiveCheckpoint / 未設定時PlayerStartへRespawn]
      ↓
[HP / Stamina Full + Healing Item補充 + Normal Enemy Respawn]
      ↓
[Fade In / Gameplay再開]
```

DeathDropは死亡時点のUpgrade MaterialとGoldを全量回収対象へ移す。割合消失は行わない。

## 6. DeathDrop回収

```text
[PlayerがDeathDrop回収条件を満たす]
      ↓
[格納Upgrade Material全量をInventoryへ返却]
[格納Gold全量をInventoryへ返却]
      ↓
[DeathDrop消去]
      ↓
[Auto Save]
```

同一DeathDropを二重回収しない。

## 7. Save / Load後のDeathDrop

未回収DeathDropはSave / Load後も次を復元する。

- 死亡座標
- Upgrade Material格納量
- Gold格納量
- 未回収状態

Playerは最後のActiveCheckpoint、未設定時はPlayerStartから再開する。DeathDrop座標・内容はJSONへ保存する方針だが、JSON構造・Versioning・Reader / Writerは[`Docs/18_SaveJsonArchitecture.md`](18_SaveJsonArchitecture.md)で定義する。

## 8. Player Inventory

次の所持DataはPlayer Inventoryを正本とする。

- Gold
- Upgrade Material
- Boss Unique Item
- Inventory系所持Item

Enemy Reward、Boss Reward、Weapon Upgrade、DeathDrop、HUD、Saveは同じInventory状態を参照・更新する。共通実装は[#153](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)で管理する。

## 9. Enemy Reward

Normal Enemy1体のDefeatごとにReward Masterから0..N件のReward Entryを取得し、Player Inventoryへ直接付与する。World Drop Actorは生成しない。

## 10. Boss Reward / Save

```text
[Boss HP <= 0]
      ↓
[Boss Defeated]
      ↓
[Gold付与]
      ↓
[初回固有Item付与]
      ↓
[Reward確定]
      ↓
[Auto Save]
      ↓
[Clear Areaへ進行可能]
```

初期プレイアブル版ではBoss Replayを実装しない。

## 11. Stage Clear

```text
[Boss Reward Auto Save完了]
      ↓
[PlayerがClear Areaへ移動]
      ↓
[Clear Trigger]
      ↓
[Skippable Ending]
      ↓
[Title]
```

Stage Clear自体では追加Auto Saveを行わない。

## 12. TitleからのLoad / Corrupt Save

- Continue: 現在のProgress Saveを読みPlay Startする。
- Load Game: Save Data選択画面を経由してLoadする。
- 初期プレイアブル版は1 Slotのため、選択可能なProgress Saveは現在存在する1件を基本とする。
- Corrupt / Invalid SaveはRuntimeへ部分適用しない。
- Corrupt Saveを削除し、New Gameを開始できる状態へ戻す。
- 初期プレイアブル版ではBackupからの自動復旧を行わない。

## 13. Settings / Steam Cloud

Settings変更時はProgress Saveとは独立してSettings Dataを保存する。Steam CloudはPost-VSで追加する。

### [戻る](../README.md#ドキュメント一覧)
