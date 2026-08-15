# 三人称視点で移動

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-001`](../../01_Requirements.md#fr-player-001) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#110](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/110) |
| 関連要件・設計 | [`FR-PLAYER-002`](../../01_Requirements.md#fr-player-002), [`FR-PLAYER-021`](../../01_Requirements.md#fr-player-021), [`NFR-MAINT-003`](../../01_Requirements.md#nfr-maint-003), [Class Design](../../07_ClassDesign.md) |

## 2. 目的

三人称Actionの基礎として、Camera方向を基準にPlayerを安定して移動できるようにする。

## 3. 確定仕様・スコープ

- Camera Yawを基準に前後左右の移動方向を算出する。
- 現行実装では`ABasePlayer`とCharacterMovementを利用する。
- Input受付は`IPlayerInputComponent`契約を経由する。
- Moverや未実装Movement Adapterを前提にしない。

## 4. 基本フロー

```text
Move Input
↓
IPlayerInputComponent経由で受付
↓
Controller / Camera Yawから方向算出
↓
AddMovementInput
↓
CharacterMovementで移動
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input層 | 移動Inputの受付・配送 |
| Player | 移動方向の算出と移動要求 |
| CharacterMovement | 実際の移動処理 |

## 6. 状態 / Gameplay Tag

なし。通常移動そのものはGAS状態として管理しない。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Move Input Vector | 前後左右Input | Runtime |
| Controller Yaw | Camera基準方向 | Runtime |
| Movement Parameters | 移動速度等 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | 移動速度・方向をAnim側へ渡してLocomotionへ反映する |
| Camera | `FR-PLAYER-021`の三人称Cameraを基準にする |

## 9. 異常系・終了条件

- Controller無効時は移動方向計算を行わず安全に終了する。
- Input再SetupでBindingを重複させない。
- Death等のInput禁止状態では上位のInput制御に従う。

## 10. 受入条件

- [ ] Camera向きを基準に前後左右へ移動できる。
- [ ] Gamepad / Keyboard-Mouseで同等に移動できる。
- [ ] Input再Setup後も1 Input 1回の移動要求になる。
- [ ] Controller無効時にCrashしない。

## 11. 依存・Issue反映

### 依存
- [`FR-PLAYER-002`](../../01_Requirements.md#fr-player-002)
- [`FR-PLAYER-021`](../../01_Requirements.md#fr-player-021)
- [`NFR-MAINT-003`](../../01_Requirements.md#nfr-maint-003)

### Issue反映
- [#110](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/110)へ移動方向、Input Lifecycle、CharacterMovement利用方針を反映する。

## 12. 未決事項

なし
