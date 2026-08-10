# 09. セーブ・チェックポイント・死亡

## 1. セーブ方針

- 進行データは1スロット。
- 設定データは進行データとは別の保存契機を持つ。
- 保存媒体、JSON構造、Steam Cloud同期などの永続化アーキテクチャは別設計で定義し、本ドキュメントではゲーム上の保存契機と復元要件を定義する。

## 2. 進行データのAuto Save契機

Auto Saveは次のタイミングに限定します。

1. Checkpointで操作し、Checkpoint Menuを開いた時点。
2. Player死亡時、新しいDeathDropの位置と格納内容が確定した直後。
3. DeathDropの回収が完了した直後。
4. Boss撃破時、Goldと初回固有収集Itemを含む報酬付与が完了した直後。

次はAuto Save契機にしません。

- 武器強化完了時
- Stage Clear時
- Clear Trigger進入時

設定データは別系統として設定変更時に保存します。

## 3. Manual Save

Checkpoint MenuからManual Saveを実行できます。Checkpoint以外からのManual Saveは初期Vertical Sliceでは提供しません。

## 4. Checkpoint

Checkpointへ接近しただけではSaveしません。PlayerがCheckpointを操作してMenuを開いた時点でActive Checkpointを更新し、Auto Save要求を発行します。

```text
[Checkpoint Interaction]
      ↓
[Checkpoint Menu Open]
      +--> ActiveCheckpoint更新
      +--> HP回復
      +--> Stamina回復
      +--> Healing Item補充
      +--> 通常敵復活
      +--> Weapon Upgrade Menu
      +--> Auto Save
```

初期Vertical Sliceの武器は剣のみです。斧・弓追加後に武器変更機能を有効化します。

## 5. Weapon Upgrade

武器強化はCheckpoint Menuでのみ実行します。

```text
[Weapon Upgrade Request]
      ↓
[Gold Cost確認]
      ↓
[Upgrade Material Cost確認]
      +-- どちらか不足 --> [Reject / 消費なし]
      ↓
[Gold + Upgrade Material消費]
      ↓
[Weapon Upgrade反映]
```

強化完了そのものではAuto Saveしません。必要であればPlayerがCheckpoint MenuからManual Saveできます。

## 6. Player Death / DeathDrop

### 6.1 死亡フロー

```text
[Player Health <= 0]
      ↓
[State.Dead確定]
      +--> 実行中Combat処理終了
      +--> 通常Gameplay入力停止
      +--> Camera Lookは許可
      ↓
[Death Animation]
      ↓
[以前のDeathDropが存在する？]
      +-- Yes --> [以前のDeathDrop本体・格納Resourceを全消失]
      ↓
[現在所持Resourceを計算]
      +--> Upgrade Material : 100%を新DeathDropへ
      +--> Gold             : 70%を新DeathDropへ
      +--> Gold             : 30%を永久消失
      ↓
[死亡座標に新DeathDrop生成]
      ↓
[位置・格納内容を確定]
      ↓
[Auto Save]
      ↓
[CameraでDeathDropを確認]
      ↓
[Fade Out]
      ↓
[Respawn]
```

Goldの70%算出時に端数が発生する場合の丸め規則は実装時に一貫した整数規則として定義します。

### 6.2 Respawn

```text
[Active Checkpointあり？]
   ├─ Yes → Active Checkpoint
   └─ No  → PlayerStart
      ↓
[Player復帰]
   +--> HP Full
   +--> Stamina Full
   +--> Healing Item Full
   +--> Normal Enemy Respawn
      ↓
[Fade In / Gameplay再開]
```

### 6.3 DeathDrop回収

```text
[Player enters DeathDrop recovery range]
      ↓
[格納Upgrade Materialを全量返却]
[格納Goldを全量返却]
      ↓
[DeathDropを消去]
      ↓
[Auto Save]
```

未回収DeathDropはSave/Load後も位置・格納内容をゲーム上復元できることを要求します。保存形式は別Architecture Designで定義します。

## 7. Enemy Reward

通常敵は1体撃破ごとに次を直接Player所持値へ付与します。

- Upgrade Material
- Gold

World上のReward Actorを生成して拾わせる方式にはしません。数量のデータ取得方式は別のMaster Data設計で扱います。

## 8. Boss Reward / Save

```text
[Boss Health <= 0]
      ↓
[Boss Defeated]
      +--> AI / Ability停止
      ↓
[Gold付与]
      ↓
[初回討伐報酬判定]
      +-- 未取得 --> [固有収集ItemをInventoryへ直接付与]
      ↓
[報酬状態確定]
      ↓
[Auto Save]
```

初期Vertical SliceではBoss再戦を実装しません。初回討伐状態をどのデータ形式で永続化するかは別Architecture Designで扱います。

## 9. Stage Clear

Boss撃破はClear条件の前提ですが、Boss撃破直後にはEndingへ遷移しません。

```text
[Boss Defeated + Reward Save完了]
      ↓
[PlayerがClear Areaへ移動]
      ↓
[Clear Trigger Collision]
      ↓
[Ending Sequence]
      +--> Skip可能
      ↓
[Titleへ戻る]
```

Stage Clear時には追加Auto Saveを行いません。Clear Triggerの具体的な場所・外観・演出内容はMap制作時に決定します。

## 10. Settings Save

設定変更時は進行データのAuto Saveとは独立して設定データを保存します。

## 11. Steam Cloud

Steam CloudはPost-Vertical Sliceの追加要件です。ローカルの保存・復元仕様を安定させた後、別Architecture Designで同期方式を定義します。

### [戻る](../README.md#ドキュメント一覧)
