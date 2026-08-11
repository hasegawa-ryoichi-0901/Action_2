# FR-PLAYER-010 Light / Heavy AttackとComboを実装する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-010` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#58`, `#67`, `#71` |

## 2. 目的

Light / Heavyを独立したGameplay Actionとして成立させ、その上で入力受付WindowからCombo Branchへ接続する。攻撃の重量感は入力遅延ではなくCommitmentとCancel制約で表現する。

## 3. 確定仕様・スコープ

### Light Attack

```text
Input
↓
Startup
↓
Commitment
↓
Active
↓
Recovery
↓
Neutral / Combo
```

- Light Attackは独立Action Issue `#58`。
- 各Phaseを区別できる。
- Cancelは定義されたCancel Window内だけ許可する。
- Combo InputはCombo受付Window内だけ後続候補として受理する。

### Heavy Attack

```text
Input
↓
Startup
↓
Commitment
↓
Active
↓
Recovery
↓
Neutral / Combo
```

- Heavy AttackはLightとは独立Action Issue `#67`。
- Lightと同様にCommitment / Cancel Windowを持つが、時間・Damage・Stamina Cost等は別データで定義可能。

### Combo

- Combo統合は`#71`で扱う。
- Light / Heavyの単体Action実装をCombo都合で重複実装しない。
- Input BufferとComboDefinitionから有効な次Attackを選択する。

## 4. 基本フロー

```text
[Light / Heavy Input]
↓
[状態 / Stamina / Weapon確認]
+-- NG --> Reject / Buffer方針に従う
↓
[Attack Start]
↓
[Startup → Commitment → Active → Recovery]
↓
[Combo Window内Input?]
├─ Yes → 次Attack候補へ
└─ No  → Neutral
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input層 | Light / Heavy InputをGameplay要求へ配送 |
| Attack Ability | 実行条件、Phase、Cost、Cancel、終了 |
| Animation | MontageとHit / Combo / Cancel Window通知 |
| Combat | Hit判定、Damage、Posture Damage |
| Input Buffer / Combo | Window内入力と次Attack選択 |

## 6. 状態・Gameplay Tag

| State / Tag | 用途 |
|---|---|
| `State.Action.Attacking` | Attack実行中 |
| `Window.Hitbox.Active` | Hit判定有効 |
| `Window.Combo.AcceptInput` | Combo Input受付 |
| `Window.Cancel.Dodge` | Dodge Cancel可能例 |

Phase表現をGameplay Tag / Montage Section / Ability内部Stateのどれで保持するかは実装詳細とするが、外部から必要なCancel / Hit / Combo Windowは契約として取得可能にする。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| AttackId | Attack識別 | Master Data |
| Montage / Section | Animation | Asset / Data |
| Startup / Commitment / Active / Recovery | Phase timing | Gameplay Data |
| Cancel Window | 許可Cancel | Gameplay Data |
| Combo Window | 次入力受付 | Gameplay Data |
| Stamina Cost | Cost | Gameplay Data |
| Health Damage | Damage | Gameplay Data |
| Posture Damage | Posture Damage | Gameplay Data |
| Player Reaction Accumulation | 対Player攻撃時のReaction値 | Enemy / Boss Attack Dataで使用 |
| Combo Branch | 次Attack候補 | Gameplay Data |

## 8. UI / Animation / Feedback

- Light / HeavyそれぞれのMontageを使用する。
- Hit VFX / SE / Hit StopはAttack Dataに従う。
- Combo受付そのものをHUDへ常時表示する必要はない。

## 9. 異常系・終了条件

- Death /強制Reaction / Montage中断時にHitbox、Combo Window、Cancel Window、Tagを解除する。
- Stamina不足時にAttackを開始しない。
- 同一InputでAbilityを二重開始しない。
- Commitment中は許可されていないCancelを受け付けない。

## 10. 受入条件

- [ ] Light / Heavyを別ActionとしてInputから開始できる。
- [ ] 各ActionでStartup / Commitment / Active / Recoveryを区別できる。
- [ ] Commitment中の禁止Cancelを拒否できる。
- [ ] 許可されたCancel Window内だけCancelできる。
- [ ] Active Window内だけHit判定できる。
- [ ] Combo Window内入力だけ次Attackへ接続できる。
- [ ] Stamina不足 / Death /禁止状態で開始しない。
- [ ] Cancel / Death後にWindow / Hitbox / Tagが残らない。

## 11. 依存・Issue反映

- `#58` Light Attack
- `#67` Heavy Attack
- `#71` Combo
- `#61` Stamina
- `#62` Damage
- `#63` Hit Collision

## 12. 未決事項

なし。各Phase時間、Cancel可能Action、Damage / Cost値、Montage Assetは調整項目とする。
