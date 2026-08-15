# 00. プロジェクト概要

## 1. 目的

本作の最優先目的は転職用ポートフォリオです。

Steamでの公開と販売も想定しますが、売上を優先して仕様を拡大するのではなく、応募企業が次の点を評価できる状態を成功条件とします。

- Unreal Engineによるゲーム開発フローを理解している
- C++を中心に実装できる
- 3Dアクションゲームの操作、戦闘、AI、UI、セーブを一連で構築できる
- 設計理由とトレードオフを説明できる
- 実行可能ビルドと技術ドキュメントを提出できる

## 2. α版の成功条件

α版は**Swordのみ**で完成させます。Axe / Bowは完成条件に含めません。

### 必須

- 応募企業へ実行可能Buildを提出できる
- 3～5分のPlay動画を用意できる
- 技術資料が完成している
- C++ Codeの主要部分を限定公開できる
- SwordでBoss1体との高品質なCombatが完成している
- Player Death → DeathDrop → Auto Save → Checkpoint Respawnが成立する
- Normal Enemy Defeat → Upgrade Material + Gold → Player Inventory → Weapon Upgradeが成立する
- Boss Defeat → Gold + 初回Unique Item → Auto Save → Clear Area → Ending → Titleが成立する
- Gamepad / Keyboard-Mouseの両方で操作できる
- 60fps最低保証目標を確認できる

### Post-VS追加目標

- Axeを実装する
- Bowを実装する
- CheckpointでWeapon Changeできる
- Steam Demoを公開する
- 最大3Stageを実装する
- 最大3体のBossを実装する
- Steam Cloudへ対応する
- 120fpsを達成する

## 3. α版フロー

```text
[Game Boot]
    ↓
[Intro]
    ↓
[Title]
    ↓ New Game
[Tutorial Text]
    ↓
[Tutorial]
    ↓
[Melee Enemy]
    ↓
[Upgrade Material + Gold]
    ↓
[Checkpoint]
    ↓
[Melee + Ranged Group Battle]
    ↓
[Gold + MaterialによるWeapon Upgrade]
    ↓
[Boss前Checkpoint]
    ↓
[Boss Phase1 / Phase2]
    ↓
[Boss Defeat]
    ↓
[Gold + 初回Unique Item]
    ↓
[Auto Save]
    ↓
[Clear Area]
    ↓
[Clear Trigger]
    ↓
[Skippable Ending]
    ↓
[Title]
```

Player Death時はDeath Animation後にUpgrade Material 100% + Gold 100%をDeathDropへ移し、DeathDrop確定後Auto Saveを行います。その後Camera確認・Fade Outを経て最後のActiveCheckpoint、未設定時はPlayerStartから再開し、Normal Enemyを復活させます。

## 4. Post-VS候補

- Weapon：Axe、Bow
- Stage：最大3
- Normal Enemy：Stageの役割に応じて追加
- Boss：各Stage1体を上限候補
- 想定Play時間：30分～1時間

## 5. スコープ削減方針

開発が遅延した場合、Systemの中核を削除せずContent量を減らします。

```text
Stage 3
  ↓
Stage 2
  ↓
Normal Enemy派生種類
  ↓
追加Boss
  ↓
Axe / Bow追加Feature
```

次はPortfolioの中心であるため原則として削除しません。

- C++中心のCombat基盤
- `IPlayerInputComponent`を中心としたInput基盤
- GAS
- Normal Dodge / Perfect Dodge
- Posture
- Boss AI / Debug
- Group Battle管理
- Player Death / DeathDrop / Respawn
- Player Inventory / Reward / Weapon Upgrade
- Save / Stage Clear
- 技術資料

### [戻る](../README.md#主要ドキュメント)
