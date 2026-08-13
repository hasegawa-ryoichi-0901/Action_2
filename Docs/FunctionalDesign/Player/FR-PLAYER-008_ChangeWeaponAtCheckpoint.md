# FR-PLAYER-008 CheckpointでWeaponを変更できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-008`](../../01_Requirements.md#fr-player-008) |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | [`FR-PLAYER-009`](../../01_Requirements.md#fr-player-009), [`FR-STAGE-006`](../../01_Requirements.md#fr-stage-006), [Weapon System](../../04_WeaponSystem.md) |

## 2. 目的

Axe / Bow追加後、CheckpointをWeapon Loadout変更地点として利用できるようにする。

## 3. 確定仕様・スコープ

- 初期プレイアブル版はSword固定のため対象外。
- Post-VSでSword / Axe / BowをCheckpoint Menuから変更する。
- Combat中の変更は禁止し`FR-PLAYER-009`へ従う。

## 4. 基本フロー

```text
Checkpoint Menu
↓
Weapon Menu
↓
所持 / 利用可能Weaponを選択
↓
現在Weaponを解除
↓
選択Weaponを装備
↓
Ability / Animation / HUD更新
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Checkpoint Menu | Weapon選択UI |
| Weapon System | Current WeaponとAbility Set更新 |
| Player | 装備状態反映 |

## 6. 状態 / Gameplay Tag

Weapon種別はWeapon Data / Equipped Weapon状態を正とし、必要なGameplay Tagへ同期する。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| WeaponId / Type | Weapon識別 | Master Data |
| Ability Set | Weapon Ability | Gameplay Data |
| Animation Set | Weapon Animation | Asset |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Checkpoint Weapon Menu、Current Weapon表示 |
| Animation | Weapon種別に応じたAnimation Setへ更新 |

## 9. 異常系・終了条件

- Combat中は変更要求を拒否する。
- 無効WeaponIdや未実装Weaponへ変更しない。
- 変更途中で旧Abilityと新Abilityを同時有効化しない。

## 10. 受入条件

- [ ] Post-VSでCheckpointから利用可能Weaponを選択できる。
- [ ] 選択後にAbility / Animationが新Weaponへ同期する。
- [ ] Combat中の変更を拒否できる。

## 11. 依存・Issue反映

### 依存
- Axe / Bow Future Feature
- [`FR-STAGE-006`](../../01_Requirements.md#fr-stage-006)

### Issue反映
- Post-VS Roadmap作成時に実装Issueへ展開する。

## 12. 未決事項

なし
