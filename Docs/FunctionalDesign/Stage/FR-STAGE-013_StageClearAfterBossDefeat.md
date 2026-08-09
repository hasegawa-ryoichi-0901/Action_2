# FR-STAGE-013 ボス撃破後にステージクリア状態へ遷移する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-013` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-BOSS-015`, `FR-SAVE-004`, `FR-SAVE-005` |

## 2. 目的

Boss Defeatをゲーム進行上の明確な完了条件へ変換し、クリア演出・進行保存へ接続する。

## 3. 基本フロー

```text
[BossDefeated Event]
      ↓
[Stage Clear Guard]
      +-- 既にClear --> [Ignore]
      ↓
[Stage Clear]
      +--> Progress更新
      +--> Player操作制御
      +--> Clear UI / Presentation
      +--> AutoSave Request
```

Boss Defeat処理そのものは`FR-BOSS-015`が担当し、本要件は進行状態への変換を担当する。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Boss System | BossDefeated Event発行 |
| Stage / GameMode | Stage Clear状態の一意な確定 |
| Save System | Stage Clear進行データ保存 |
| UI / Presentation | Clear表示・入力制御 |

## 5. 受入条件

- [ ] BossがDefeatedになるまでStage Clearへ遷移しない。
- [ ] BossDefeated EventからStage Clearへ1回だけ遷移する。
- [ ] Stage Clear後の進行状態を保存できる。
- [ ] 重複EventでClear演出や保存を多重実行しない。
- [ ] Stage Clear中にBoss Combatへ戻らない。

## 6. テスト観点

- Boss通常撃破
- Phase Transition中の撃破
- BossDefeated Event重複
- Save失敗時
- Clear後のPlayer入力
- Clear後の再Load

## 7. 未決事項

- Boss撃破Animation完了を待つか
- Stage Clear時のPlayer入力ロック範囲
- Clear UIから次に遷移する画面 / 状態
- Boss Defeat SaveとStage Clear Saveの集約方式

詳細は`Docs/15_OpenQuestions.md`で確定する。
