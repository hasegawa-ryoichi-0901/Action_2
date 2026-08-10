# FR-BOSS-016 Boss撃破時にGoldと初回固有収集Itemを獲得する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-016` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-BOSS-015`, `FR-SAVE-004`, `FR-STAGE-013` |

## 2. 目的

Boss撃破に通常敵とは異なる明確な報酬を与え、初回討伐の証明となる収集Itemを保持できるようにする。

## 3. 基本フロー

```text
[Boss Defeated]
      ↓
[Gold Reward取得]
      ↓
[Goldを直接Player所持値へ加算]
      ↓
[初回固有Item取得済み？]
   ├─ Yes → [追加付与なし]
   └─ No  → [固有収集ItemをInventoryへ直接付与]
      ↓
[Reward状態確定]
      ↓
[FR-SAVE-004 Auto Save]
```

## 4. 確定仕様

- BossはGoldを付与する。
- Bossは通常のUpgrade Materialを付与しない。
- 初回討伐時のみ固有収集Itemを付与する。
- 固有Itemは現時点では消費せず、収集・討伐証明用途とする。
- World Dropは生成せずInventoryへ直接付与する。
- 初期Vertical SliceではBoss再戦を実装しない。
- 初回取得状態の永続化方式は別Architecture Designで定義する。

## 5. 受入条件

- [ ] Boss Defeated確定前にRewardを付与しない。
- [ ] Goldを1回だけ付与する。
- [ ] 初回固有ItemをInventoryへ直接付与できる。
- [ ] Reward付与完了後にAuto Saveへ接続する。
- [ ] 通常のUpgrade MaterialをBoss Rewardとして付与しない。
