# FR-STAGE-006 チェックポイントで武器を変更する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-006` |
| 優先度 | `Should` |
| 対応範囲 | `Post-Vertical Slice / 複数武器実装後` |
| 設計状態 | `Draft` |

## 2. 目的

Axe / Bow追加後、Checkpointを安全な武器変更地点として提供する。

## 3. 初期Vertical Slice

Swordのみを使用するためWeapon Change Menuを必須としない。CheckpointではHeal Refill、Weapon Upgrade、Enemy Respawn、Auto Saveを優先する。

## 4. 基本フロー

```text
[Checkpoint Rest]
      ↓
[Weapon Menu]
      ↓
[利用可能武器一覧]
      ↓
[Weapon選択]
      ↓
[FR-PLAYER-009 Combat Block確認]
      ↓
[FR-PLAYER-008 Weapon Change]
```

## 5. 受入条件

- [ ] 複数武器実装後にCheckpointからWeapon Menuを開ける。
- [ ] 利用できない武器を選択できない。
- [ ] 戦闘中の変更要求を通さない。
- [ ] 初期Vertical Sliceでは本UIがなくてもCheckpoint機能が成立する。

## 6. 依存

- `FR-PLAYER-008`
- `FR-PLAYER-009`
- Axe / Bow Future Feature
