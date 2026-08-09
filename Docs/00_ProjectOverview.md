# 00. プロジェクト概要

## 1. 目的

本作の最優先目的は転職用ポートフォリオです。

Steamでの公開と販売も想定しますが、売上を優先して仕様を拡大するのではなく、応募企業が次の点を評価できる状態を成功条件とします。

- Unreal Engineによるゲーム開発フローを理解している
- C++を中心に実装できる
- 3Dアクションゲームの操作、戦闘、AI、UI、セーブを一連で構築できる
- 設計理由とトレードオフを説明できる
- 実行可能ビルドと技術ドキュメントを提出できる

## 2. 初期Vertical Slice成功条件

初期Vertical Sliceは**剣のみ**で完成させます。斧・弓は完成条件に含めません。

### 必須

- 応募企業へ実行可能ビルドを提出できる
- 3～5分のプレイ動画を用意できる
- 技術資料が完成している
- C++コードの主要部分を限定公開できる
- 剣でボス1体との高品質な戦闘が完成している
- Player Death → DeathDrop → Checkpoint Respawnが成立する
- Enemy Defeat → Upgrade Material → Weapon Upgradeが成立する
- Boss Defeat → Stage Clearが成立する
- Gamepad / Keyboard-Mouseの両方で操作できる
- 60fpsを安定して維持できる

### Post-Vertical Slice追加目標

- 斧を実装する
- 弓を実装する
- Checkpointで武器変更できる
- Steam体験版を公開する
- 最大3ステージを実装する
- 最大3体のボスを実装する
- Steam Cloudへ対応する
- 120fpsを達成する

## 3. 初期Vertical Sliceフロー

```text
[Title]
    ↓
[Intro Text]
    ↓
[Tutorial]
    ↓
[近接敵]
    ↓
[Upgrade Material]
    ↓
[Checkpoint]
    ↓
[近接 + 遠距離の集団戦]
    ↓
[Weapon Upgrade]
    ↓
[Boss前Checkpoint]
    ↓
[Boss Phase1 / Phase2]
    ↓
[Boss Defeat]
    ↓
[Stage Clear]
```

プレイヤー死亡時は最後に有効化したCheckpointから再開し、通常敵を復活させます。

## 4. Post-Vertical Slice候補

- 武器：斧、弓
- ステージ：最大3
- 通常敵：ステージの役割に応じて追加
- ボス：各ステージ1体を上限候補
- 想定プレイ時間：30分～1時間

## 5. スコープ削減方針

開発が遅延した場合、システムの中核を削除せずコンテンツ量を減らします。

```text
ステージ3
  ↓
ステージ2
  ↓
通常敵の派生種類
  ↓
追加ボス
  ↓
斧・弓の追加Feature
```

次はポートフォリオの中心であるため原則として削除しません。

- C++中心の戦闘基盤
- `IPlayerInputComponent`を中心とした入力基盤
- GAS
- 通常回避 / ジャスト回避
- 体勢値
- Boss AI
- 集団戦管理
- Debug表示
- Player Death / Respawn
- Save / Stage Clear
- 技術資料

### [戻る](../README.md#ドキュメント一覧)
