# FR-STAGE-014 戦闘報酬として武器強化に使用する強化素材を獲得できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-014` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-ENEMY-010`, `FR-STAGE-007`, `FR-STAGE-008` |

## 2. 目的

通常戦闘を武器強化ループへ接続する報酬を提供する。

## 3. 基本フロー

```text
[Enemy / Encounter Defeat]
      ↓
[Reward Definition取得]
      ↓
[Reward条件Validation]
      ↓
[UpgradeMaterial加算]
      ↓
[UI通知]
      ↓
[Checkpoint Weapon Upgradeで利用]
```

死亡時に落とす素材と通常の戦闘報酬は取得経路を分け、最終的な所持値は同じUpgradeMaterialへ集約する。

## 4. データ

既存の`FEnemyDefinition::RewardDefinition`等を報酬定義の候補とする。報酬量、対象、確率等はコードへ固定せずデータ駆動にする。

## 5. 責務

| 対象 | 責務 |
|---|---|
| Enemy / Encounter | Reward発生条件の通知 |
| Reward System | Reward Definition評価、重複付与防止 |
| Player Attribute / Inventory | UpgradeMaterial所持値更新 |
| UI | 獲得通知 |
| Weapon Upgrade | 所持素材消費 |

## 6. 受入条件

- [ ] 仕様で定義した戦闘終了条件から強化素材を獲得できる。
- [ ] 同一撃破 / Encounterから報酬を重複付与しない。
- [ ] 獲得した素材を武器強化で参照・消費できる。
- [ ] Player死亡時に現在所持素材をDeathDrop処理へ渡せる。
- [ ] Reward Definition未設定時にクラッシュしない。
- [ ] 報酬量をデータから変更できる。

## 7. テスト観点

- 通常獲得
- 連続敵撃破
- 同Frame重複Defeat通知
- Reward Definitionなし
- 素材獲得後のDeath
- DeathDrop回収後の合算
- Weapon Upgrade消費

## 8. 未決事項

- 敵1体単位 / Encounter単位のどちらを主要報酬源にするか
- Boss報酬の有無
- 固定量 / ランダム量
- Reward付与タイミング

詳細は`Docs/15_OpenQuestions.md`で確定する。
