# FR-PLAYER-004 Air Attackを実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-004`](../../01_Requirements.md#fr-player-004) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#112](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/112) |
| 関連要件・設計 | [`FR-PLAYER-003`](../../01_Requirements.md#fr-player-003), [`FR-PLAYER-010`](../../01_Requirements.md#fr-player-010), [`FR-PLAYER-011`](../../01_Requirements.md#fr-player-011), [Combat System](../../03_CombatSystem.md) |

## 2. 目的

Jump後のAirborne状態からAttackへ派生できるようにし、三次元的なCombat選択肢を提供する。

## 3. 確定仕様・スコープ

- Airborne中のみSwordのAir Attackを開始できる。
- Stamina Costを適用する。
- Attack Montage、Hit Window、Damageは既存Combat共有基盤へ接続する。
- Grounded時は通常のLight / Heavyへ混入させない。

## 4. 基本フロー

```text
Attack Input
↓
Airborne確認
├ No → Ground Attack側へ
└ Yes
  ↓
Stamina確認
  ↓
Air Attack Ability
  ↓
Montage / Hit Window
  ↓
Damage
  ↓
Landing or Ability End
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input / Combat | Airborne時のAction選択 |
| GAS / Ability | Cost、状態、Attack実行 |
| Animation | Air Attack MontageとHit Window通知 |
| Damage基盤 | Hit結果反映 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Attacking` | Air Attack実行中 |
| `Window.Hitbox.Active` | Damage判定有効期間 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| AirAttackDefinition | Attack定義 | Master Data / Gameplay Data |
| Montage / Section | Animation | Asset |
| Stamina Cost | Cost | 調整値 |
| Health / Posture Damage | Damage | 調整値 |
| Hit Window | Hit判定期間 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Air Attack Montage |
| VFX / SE | Hit成功時の通常Attack Feedbackを共用可能 |

## 9. 異常系・終了条件

- Grounded時はAir Attackを開始しない。
- Stamina不足時は開始しない。
- Landing / Death / Cancel時にHitbox、Tag、Montage状態を残さない。

## 10. 受入条件

- [ ] Airborne中のみAir Attackを開始できる。
- [ ] Stamina Costを適用できる。
- [ ] Active Window内だけHitする。
- [ ] Landing / Cancel後に一時状態を解除できる。

## 11. 依存・Issue反映

### 依存
- [#58 Light Attack共有基盤](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58)
- [#108 Jump](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/108)

### Issue反映
- [#112](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/112)へAirborne判定、Cost、Montage、Hit Window、Cleanupを反映する。

## 12. 未決事項

なし
