# FR-PLAYER-009 Combat中はWeaponを変更できない

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-009`](../../01_Requirements.md#fr-player-009) |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | [`FR-PLAYER-008`](../../01_Requirements.md#fr-player-008), [Weapon System](../../04_WeaponSystem.md) |

## 2. 目的

WeaponごとのCombat特性を維持し、Combat途中の即時切替によるAbility / Animation / Balance不整合を防ぐ。

## 3. 確定仕様・スコープ

- Weapon変更はCheckpoint Menuからのみ行う。
- Combat状態中の変更要求は拒否する。
- α版はSword固定のため実質的な変更処理はPost-VS。

## 4. 基本フロー

```text
Weapon Change Request
↓
Checkpoint Menuからの要求?
├ No → Reject
└ Yes
  ↓
Combat中?
├ Yes → Reject
└ No → FR-PLAYER-008へ
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Weapon System | Weapon変更可否判定 |
| Combat State | Combat中かを提供 |
| Checkpoint | 正規変更導線を提供 |

## 6. 状態 / Gameplay Tag

Combat中を識別する既存Gameplay Stateを利用する。専用Tagの新設は必須としない。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Combat State | 変更禁止判定 | Runtime |
| Current WeaponId | Current Weapon | Runtime |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Combat中はWeapon Change項目を無効化または拒否表示する |

## 9. 異常系・終了条件

- Combat状態解除前に変更を開始しない。
- Weapon Change中にCombatへ入る競合を発生させない。

## 10. 受入条件

- [ ] Combat中のWeapon変更を拒否できる。
- [ ] Checkpointかつ非Combat時のみ変更処理へ進める。
- [ ] Rejectで装備状態が部分変更されない。

## 11. 依存・Issue反映

### 依存
- [`FR-PLAYER-008`](../../01_Requirements.md#fr-player-008)
- [`FR-STAGE-006`](../../01_Requirements.md#fr-stage-006)

### Issue反映
- Post-VS Roadmap作成時に`FR-PLAYER-008`と依存関係を持つ実装Issueへ展開する。

## 12. 未決事項

なし
