# FR-PLAYER-006 Manual LockOnを使用できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-006`](../../01_Requirements.md#fr-player-006) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#75](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/75), [#76](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/76), [#77](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/77), [#78](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/78) |
| 関連要件・設計 | [`FR-PLAYER-007`](../../01_Requirements.md#fr-player-007), [`FR-PLAYER-021`](../../01_Requirements.md#fr-player-021) |

## 2. 目的

Playerが明示的にEnemyをTargetとして固定し、CameraとCombatが同じCurrent Targetを利用できるようにする。

## 3. 確定仕様・スコープ

- LockOn Inputで有効Targetを選択してLockする。
- LockOn中に同じLockOn Inputを再度押すと解除する。
- LockOn中のみCameraがTargetへ追従し、通常Camera Lookを無効化する。
- Current Targetが死亡 / 無効化した場合は自動でLockを解除し、別Targetへ自動切替しない。

## 4. 基本フロー

```text
LockOn Input
↓
Lock中?
├ Yes → Unlock
└ No
  ↓
Target候補選択
  ├ なし → 終了
  └ あり → Current Target設定 → Camera追従

Target死亡 / 無効化
↓
Unlock
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Targeting | Current Target選択・保持・解除 |
| Camera | Lock中のTarget追従 |
| HUD | LockOn Marker表示 |
| Enemy | Target有効性通知 |

## 6. 状態 / Gameplay Tag

LockOn状態はTargeting SystemのCurrent Target有無を正とする。必要ならState Tagへ同期する。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Lock Search Range / Angle | 初期Target候補 | 調整値 |
| Current Target | Lock対象 | Runtime |
| Target Point | Camera注視点 | Runtime / Asset |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | Current TargetへLockOn Markerを表示する |
| Camera | Lock中のみTarget追従し通常Lookを抑止する |

## 9. 異常系・終了条件

- Current Target死亡 / Destroy / 無効化時はLockを解除する。
- Unlock時にCamera LookとMarkerを確実に復帰 / 消去する。
- Target参照を無効なWeak Referenceとして保持し続けない。

## 10. 受入条件

- [ ] LockOn Inputで有効TargetをLockできる。
- [ ] 同じInputでUnlockできる。
- [ ] Lock中はCamera Lookを無効化してTarget追従できる。
- [ ] Target死亡時に自動Unlockできる。
- [ ] Unlock後にCamera Lookが復帰する。

## 11. 依存・Issue反映

### 依存
- [`FR-PLAYER-007`](../../01_Requirements.md#fr-player-007)
- [`FR-PLAYER-021`](../../01_Requirements.md#fr-player-021)

### Issue反映
- [#75](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/75)を親Issueとして[#76](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/76)～[#78](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/78)へ候補選択、Camera、死亡解除を分割する。

## 12. 未決事項

なし
