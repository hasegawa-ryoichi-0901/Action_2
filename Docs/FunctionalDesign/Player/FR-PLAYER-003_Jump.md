# FR-PLAYER-003 Jumpできる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-003`](../../01_Requirements.md#fr-player-003) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#108](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/108), [#109](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/109) |
| 関連要件・設計 | [`FR-PLAYER-004`](../../01_Requirements.md#fr-player-004), [`NFR-MAINT-003`](../../01_Requirements.md#nfr-maint-003) |

## 2. 目的

GroundedからAirborneへ移行する基本Actionを提供し、Air Attackへ接続する。

## 3. 確定仕様・スコープ

- Grounded時のみJumpを開始する。
- Airborne中の再Jumpはα版では行わない。
- Inputは`IPlayerInputComponent`契約からGameplayへ配送する。

## 4. 基本フロー

```text
Jump Input
↓
Grounded確認
├ No → Reject
└ Yes
  ↓
Jump開始
  ↓
Airborne
  ↓
Landing
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input層 | Jump Input配送 |
| Player / Movement | Grounded判定とJump実行 |
| Animation | Jump / Fall / Land表示 |

## 6. 状態 / Gameplay Tag

Jump専用Tagを必須とはしない。Airborne / GroundedはMovement状態を正とする。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Jump Input | Jump要求 | Runtime |
| Grounded State | 実行可否 | Runtime |
| Jump Parameters | Jump高さ等 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Jump開始、Fall、Landingを表現する |

## 9. 異常系・終了条件

- Airborne中の再Inputを拒否する。
- Death等の禁止状態では開始しない。
- Landing後にAirborne固有状態を残さない。

## 10. 受入条件

- [ ] Grounded時にJumpできる。
- [ ] Airborne中の再Jumpを拒否できる。
- [ ] Landing後に通常移動へ戻れる。
- [ ] `FR-PLAYER-004`のAir Attack判定へAirborne状態を提供できる。

## 11. 依存・Issue反映

### 依存
- [`FR-PLAYER-001`](../../01_Requirements.md#fr-player-001)
- [`FR-PLAYER-004`](../../01_Requirements.md#fr-player-004)

### Issue反映
- [#108](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/108)をTracking Parent、[#109](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/109)をInput / Grounded実装Issueとして扱う。

## 12. 未決事項

なし
