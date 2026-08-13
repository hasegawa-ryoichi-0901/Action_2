# FR-PLAYER-002 GamepadとKeyboard-Mouseで同等に操作できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-002`](../../01_Requirements.md#fr-player-002) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111) |
| 関連要件・設計 | [`NFR-QUALITY-003`](../../01_Requirements.md#nfr-quality-003), [`NFR-MAINT-003`](../../01_Requirements.md#nfr-maint-003), [GAS Design](../../05_GASDesign.md) |

## 2. 目的

初期プレイアブル版の主要操作をGamepadとKeyboard-Mouseのどちらでも同じGameplay Ruleで実行できるようにする。

## 3. 確定仕様・スコープ

- Move / Look / Jump / Light / Heavy / Dodge / Parry / Heal / LockOn / Target Switch等を両Deviceへ割り当てる。
- Device差でGameplay Ruleを分岐しない。
- Enhanced Inputと`IPlayerInputComponent`のSetup / Teardown契約を共通利用する。
- `1 Action = 1 Component`は前提にしない。

## 4. 基本フロー

```text
Gamepad or Keyboard-Mouse Input
↓
Enhanced Input Mapping
↓
IPlayerInputComponent
↓
同一Gameplay Action / Request
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Enhanced Input設定 | DeviceごとのInput割当 |
| IPlayerInputComponent | Input Lifecycleと共通配送契約 |
| Gameplay側 | Device非依存のRule実行 |

## 6. 状態 / Gameplay Tag

Input TagはAction識別に利用する。Component粒度はTag粒度と固定しない。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Input Action | Action識別 | Asset |
| Mapping Context | 各Device割当 | Asset |
| Input Gameplay Tag | Gameplay要求識別 | Config / Runtime |
| Sensitivity | Look調整 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | 必要に応じて操作表記を現在Deviceへ合わせる。Gameplay Ruleは変更しない |

## 9. 異常系・終了条件

- Mapping Contextを重複登録しない。
- Input Component再構築時に古いBindingをTeardownする。
- 同一Input Tag重複を設定不備として検知する。

## 10. 受入条件

- [ ] 初期プレイアブル版の主要Actionを両Deviceで実行できる。
- [ ] Device差でGameplay結果が変わらない。
- [ ] Mapping / Bindingが重複しない。
- [ ] 両DeviceでTitleからStage Clearまで通し操作できる。

## 11. 依存・Issue反映

### 依存
- 各Player Action要件
- [`NFR-QUALITY-003`](../../01_Requirements.md#nfr-quality-003)

### Issue反映
- [#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111)へ全主要Actionの両Device確認を反映する。

## 12. 未決事項

なし
