# FR-PLAYER-021 三人称カメラを操作できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-021` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-PLAYER-006`, `FR-PLAYER-007` |

## 2. 基本フロー

### 非LockOn時

```text
[Look Input]
      ↓
[IPlayerInputComponent実装]
      ↓
[Controller Yaw / Pitch]
      ↓
[CameraBoom / FollowCamera]
```

### LockOn時

```text
[State.Targeting.Locked]
      ↓
[通常Camera Look無効]
      ↓
[Current TargetへCamera追従]
```

## 3. 確定仕様

- 非LockOn時はPlayer Look InputでYaw / Pitch操作可能。
- LockOn中のみTarget追従を行う。
- LockOn中は通常Camera Lookを無効化する。
- Target Switchは別専用入力へ委譲する。
- Current Target死亡・無効化でLockOn解除後、通常Camera Lookへ戻る。
- Player死亡中はCamera Lookを許可する。

## 4. 調整可能項目

- Mouse / Gamepad感度
- Pitch Clamp
- Camera Collision
- SpringArm長
- Y軸反転設定

## 5. 受入条件

- [ ] 非LockOn時にYaw / Pitch操作できる。
- [ ] LockOn時に通常Look入力でCameraを自由回転できない。
- [ ] LockOn時にCurrent Targetへ追従する。
- [ ] Lock解除後に自由Cameraへ復帰する。
- [ ] Death状態中もCameraを操作できる。
