# FR-PLAYER-008 Checkpointで武器を変更できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-008` |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | `FR-PLAYER-009`, `FR-STAGE-006`, `Docs/04_WeaponSystem.md` |

## 2. 目的

Axe / Bow追加後、Checkpointを武器Loadout変更地点として利用できるようにする。

## 3. 確定仕様・スコープ

- Initial Vertical SliceはSword固定のため対象外。
- Post-VSでSword / Axe / BowをCheckpoint Menuから変更する。
- 戦闘中の変更は禁止し`FR-PLAYER-009`へ従う。

## 4. 基本フロー

```text
Checkpoint Menu
↓
Weapon Menu
↓
所持 / 利用可能武器を選択
↓
現在武器を解除
↓
選択武器を装備
↓
Ability / Animation / HUD更新
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Checkpoint Menu | 武器選択UI |
| Weapon System | 現在武器とAbility Set更新 |
| Player | 装備状態反映 |

## 6. 状態 / Gameplay Tag

武器種別はWeapon Data / Equipped Weapon状態を正とし、必要なGameplay Tagへ同期する。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| WeaponId / Type | 武器識別 | Master Data |
| Ability Set | 武器Ability | Gameplay Data |
| Animation Set | 武器Animation | Asset |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Checkpoint Weapon Menu、現在装備表示 |
| Animation | 武器種別に応じたAnimation Setへ更新 |

## 9. 異常系・終了条件

- Combat中は変更要求を拒否する。
- 無効WeaponIdや未実装武器へ変更しない。
- 変更途中で古いAbilityと新Abilityを同時有効化しない。

## 10. 受入条件

- [ ] Post-VSでCheckpointから利用可能武器を選択できる。
- [ ] 選択後にAbility / Animationが新武器へ同期する。
- [ ] Combat中の変更を拒否できる。

## 11. 依存・Issue反映

### 依存
- Axe / Bow Future Feature
- `FR-STAGE-006`

### Issue反映
- Post-VS Roadmap作成時に実装Issueへ展開する。

## 12. 未決事項

なし
