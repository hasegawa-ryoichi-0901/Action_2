# FR-BOSS-004 プレイヤーの装備武器を評価する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-004` |
| 優先度 | `Should` |
| 対応範囲 | `Post-Vertical Slice / 複数武器実装後` |
| 設計状態 | `Draft` |

## 2. 目的

Axe / Bow追加後、プレイヤー武器による戦闘距離・防御手段・行動傾向の差をBoss攻撃評価へ反映する。

## 3. 初期Vertical Slice

初期Vertical SliceはSword固定のため、Weapon Modifierによる分岐をBoss完成条件にしない。Boss AIは距離、Player Stamina、Healing State、行動履歴等のSword環境で成立させる。

## 4. Post-Vertical Sliceフロー

```text
[Attack Evaluation Context]
      ↓
[Equipped Weapon Id / Type]
      ↓
[BossAttackDefinition.PlayerWeaponModifiers]
      ↓
[Attack Score補正]
      ↓
[Select Attack]
```

Bow時の専用Gap Closerは`FR-BOSS-014`へ委譲する。

## 5. 受入条件

- [ ] Sword / Axe / Bowを識別してScore Modifierへ反映できる。
- [ ] Weapon情報未取得時に不正なScoreを適用しない。
- [ ] 未反映の入力や将来の武器変更予定を参照しない。
- [ ] Sword固定の初期Vertical Sliceで本要件未実装でもBoss戦が成立する。

## 6. 依存

- Axe / Bow Future Feature
- `FR-BOSS-008`
- `FR-BOSS-014`
- `FBossAttackDefinition.PlayerWeaponModifiers`
