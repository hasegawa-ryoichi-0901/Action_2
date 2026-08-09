# FR-BOSS-014 弓で距離を取られた場合に専用接近行動を選択できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-014` |
| 優先度 | `Should` |
| 対応範囲 | `Post-Vertical Slice / Bow Feature` |
| 設計状態 | `Draft` |

## 2. 目的

Bowによる遠距離維持だけでBossを一方的に攻略できないよう、遠距離Contextに対応する専用Gap Closerを攻撃評価へ追加する。

## 3. 前提

- Bow Featureが実装済み。
- Bossの基礎Attack Evaluatorが初期Vertical Sliceで成立済み。
- `FR-BOSS-004`の装備武器評価が利用可能。

## 4. 基本フロー

```text
[Boss Attack Evaluation]
      ↓
[Player Weapon == Bow?]
      +-- No --> [通常評価]
      ↓
[Long Range / Line of Sight / Cooldown / Reachability]
      +-- NG --> [通常評価]
      ↓
[Gap Closer Score補正]
      ↓
[Select / Execute]
```

## 5. 公平性

- 現在確定済みのWeapon、位置、距離、Range Trendのみを参照する。
- 未反映入力、次の射撃予定、入力Bufferを参照しない。
- Gap Closerには認識可能な予備動作を持たせる。

## 6. 受入条件

- [ ] Bowかつ長距離ContextでGap Closer候補の評価を変更できる。
- [ ] Sword / AxeではBow専用補正を適用しない。
- [ ] Cooldown / Reachability不成立時に無理なGap Closerを選択しない。
- [ ] 初期Vertical SliceのSword Bossには本要件が依存しない。

## 7. 依存

- `FEATURE-BOW-001`～`FEATURE-BOW-005`
- `FR-BOSS-004`
- `FR-BOSS-008`
