# FR-PLAYER-021 三人称Cameraを操作できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-021`](../../01_Requirements.md#fr-player-021) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#117](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/117), [#77](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/77) |
| 関連要件・設計 | [`FR-PLAYER-006`](../../01_Requirements.md#fr-player-006), [`FR-PLAYER-007`](../../01_Requirements.md#fr-player-007), [Class Design](../../07_ClassDesign.md) |

## 2. 目的

非LockOn時のFree Camera操作と、LockOn時のTarget追従を両立する。

## 3. 確定仕様・スコープ

- Mouse / GamepadからYaw / Pitchを操作できる。
- SensitivityとPitch Clampを調整可能とする。
- 非LockOn時はFree Camera Lookを使用する。
- LockOn中のみCameraがCurrent Targetを追従し、通常Camera Lookを無効化する。
- Death中はCamera Lookを許可する。

## 4. 基本フロー

```text
Look Input
↓
LockOn中?
├ Yes → 通常Lookを無効化 → Current Target追従
└ No → Yaw / Pitch Input → SpringArm / FollowCamera

Death中 + 非LockOn
→ Camera Look許可
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Look Input | Yaw / Pitch配送 |
| Player / Controller | Free Look処理 |
| SpringArm / Camera | 三人称Camera位置 |
| Targeting / LockOn Camera | Lock中の追従 |

## 6. 状態 / Gameplay Tag

LockOn状態はCurrent Target有無を正とする。Camera専用Gameplay Tagは必須としない。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Mouse / Gamepad Sensitivity | Look速度 | 調整値 |
| Pitch Min / Max | 上下制限 | 調整値 |
| SpringArm Length / Offset | Camera位置 | 調整値 |
| Current Target | Lock追従 | Runtime |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Camera | Free Look / LockOn Followを切り替える |
| UI / HUD | LockOn Markerは`FR-PLAYER-006`側で表示する |

## 9. 異常系・終了条件

- Controller / Camera参照無効時にCrashしない。
- Lock解除時に通常Camera Lookを復帰する。
- Target死亡時は`FR-PLAYER-006`によりLock解除する。

## 10. 受入条件

- [ ] Mouse / GamepadでYaw / Pitchを操作できる。
- [ ] Pitch Clampを超えない。
- [ ] LockOn中は通常Lookを無効化してTarget追従できる。
- [ ] Lock解除後にFree Cameraへ戻る。
- [ ] Death中もCamera Lookできる。

## 11. 依存・Issue反映

### 依存
- [`FR-PLAYER-006`](../../01_Requirements.md#fr-player-006), [`FR-PLAYER-007`](../../01_Requirements.md#fr-player-007)

### Issue反映
- [#117](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/117)へFree Camera、[#77](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/77)へLockOn追従を反映する。

## 12. 未決事項

なし
