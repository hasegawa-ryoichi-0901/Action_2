# [FR-PLAYER-010] 弱攻撃・強攻撃・連続攻撃

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-010`](../../01_Requirements.md#fr-player-010) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#58](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58), [#67](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/67), [#71](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/71) |
| 関連要件・設計 | [`FR-PLAYER-011`](../../01_Requirements.md#fr-player-011), [`FR-PLAYER-012`](../../01_Requirements.md#fr-player-012), [Combat System](../../03_CombatSystem.md), [GAS Design](../../05_GASDesign.md) |

## 2. 目的

Sword基本AttackとしてLight / Heavyを独立Actionで成立させ、受付Window内InputによりCombo Branchへ接続する。

## 3. 確定仕様・スコープ

- Light Attack、Heavy Attack、Combo Attackはそれぞれ親Issueで管理する。
- Light / Heavyは`Startup → Commitment → Active → Recovery`を持つ。
- Commitment中は許可されていないCancelを拒否する。
- 定義されたCancel Window内のみCancelを許可する。
- Active Window内だけHitを有効化する。
- Combo受付Window内の次InputをInput Bufferへ保存し後続Attackを選択する。

## 4. 基本フロー

```text
Light / Heavy Input
↓
実行条件 / Stamina確認
↓
Startup
↓
Commitment
↓
Active + Hit Window
↓
Recovery
├ Combo Window Inputあり → 次Attack
└ なし → Neutral
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input層 | Light / Heavy要求配送 |
| GAS / Attack Ability | Phase、Cost、Cancel、Montage制御 |
| Input Buffer | Combo Input保存・有効期限・消費 |
| Animation | Hit / Combo / Cancel Window通知 |
| Damage基盤 | Health / Posture Damage反映 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Action.Attacking` | Attack実行中 |
| `Window.Hitbox.Active` | Hit有効期間 |
| `Window.Combo.AcceptInput` | Combo Input受付 |
| `Window.Cancel.Dodge` | Dodge Cancel可能期間の例 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| AttackId | Attack識別 | Master Data |
| Montage / Section | Attack Animation | Asset |
| Startup / Commitment / Active / Recovery | Phase Timing | 調整値 |
| Cancel Window | Cancel可否 | 調整値 |
| Combo Window / Branch | 後続Attack | Gameplay Data |
| Stamina Cost | Cost | 調整値 |
| Health / Posture Damage | Damage | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| Animation | Light / Heavy Montage、Hit / Combo Window Notify |
| VFX / SE | Hit結果に応じたFeedback |
| Camera | 必要なHit Stop / Camera ShakeのみAttack Dataから適用可能 |

## 9. 異常系・終了条件

- Stamina不足時は開始しない。
- Commitment中の未許可Cancelを拒否する。
- Death / Cancel / Montage中断でHitbox、Window、Tag、Buffered Inputを残さない。
- 同一Hit Windowで同じTargetへ意図しない多重Damageを与えない。

## 10. 受入条件

- [ ] Light / Heavyを独立してInputからDamageまで実行できる。
- [ ] 4 Phaseを区別できる。
- [ ] Commitment中の禁止Cancelを拒否できる。
- [ ] Active Window外でHitしない。
- [ ] Combo Window内Inputから定義済みBranchへ遷移できる。
- [ ] Cancel / Death後に一時状態が残らない。

## 11. 依存・Issue反映

### 依存
- [#59 ASC](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/59)
- [#60 GameplayTag](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/60)
- [#61 Stamina](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/61)
- [#62 Damage](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/62)
- [#63 Hit Collision](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/63)
- [#64 Montage Event](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/64)

### Issue反映
- [#58](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/58) Light、[#67](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/67) Heavy、[#71](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/71) Comboを親Issueとして実装単位を分離する。

## 12. 未決事項

なし
