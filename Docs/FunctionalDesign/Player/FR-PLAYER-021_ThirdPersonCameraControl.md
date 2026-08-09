# FR-PLAYER-021 三人称カメラを操作できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-021` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-PLAYER-001`, `FR-PLAYER-002`, `FR-PLAYER-005`, `FR-PLAYER-006` |

## 2. 目的

探索・戦闘中に高い入力応答性で周囲を確認できる三人称カメラ操作を提供する。

## 3. 現行構成

```text
[Enhanced Input / Look]
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent]
      ↓
[UPlayerLookInputComponent]
      ↓
[AddControllerYawInput / AddControllerPitchInput]
      ↓
[CameraBoom]
      ↓
[FollowCamera]
```

`ABasePlayer`がSpringArmとFollowCameraを保持し、Look入力ComponentがControllerへYaw / Pitch入力を渡す現行実装を正とする。

## 4. 基本フロー

1. Look Input ComponentをInterface経由でSetupする。
2. Vector2DのLook入力を受け取る。
3. Owner PawnとControllerを検証する。
4. Yaw / Pitch入力をControllerへ渡す。
5. CameraBoom / FollowCameraが視点結果を反映する。

## 5. 責務

| 対象 | 責務 |
|---|---|
| `ABasePlayer` | CameraBoom / FollowCamera保持、入力Lifecycle |
| `UPlayerLookInputComponent` | Look軸解釈、Controller入力 |
| `IPlayerInputComponent` | Setup / Teardown等の共通契約 |
| Targeting System | LockOn時の対象追従・補正 |
| Settings / Config | 感度、反転等の調整値候補 |

## 6. 受入条件

- [ ] MouseでYaw / Pitch操作できる。
- [ ] Gamepad右Stick等でYaw / Pitch操作できる。
- [ ] 移動入力と同時にカメラを操作できる。
- [ ] Owner / Controller無効時にクラッシュしない。
- [ ] Input Disable時にLook操作が仕様どおり停止する。
- [ ] Setup再実行でLook入力が重複発火しない。
- [ ] LockOn導入後に自由視点入力と自動補正の優先順位を一意にできる。

## 7. テスト観点

- Mouse / Gamepad
- Move+Look同時入力
- Pitch上限 / 下限
- Possess / UnPossessed
- Input Disable / Enable
- Camera Collision
- LockOn開始 / 解除 / Target Switch

## 8. 未決事項

- Mouse / Gamepad感度と設定場所
- Pitch Clamp
- Y軸反転を初期VSに含めるか
- LockOn中の手動入力と自動補正の優先順位
- SpringArm長、Camera Collision等の最終調整値

`Docs/15_OpenQuestions.md`で確定する。
