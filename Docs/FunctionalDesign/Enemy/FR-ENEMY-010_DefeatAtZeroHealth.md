# FR-ENEMY-010 HPが0以下になると撃破状態へ遷移する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-010` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-ENEMY-006`, `FR-STAGE-014` |

## 2. 目的

通常敵の戦闘終了条件を定義し、AI停止・攻撃枠解放・報酬付与へ安全に接続する。

## 3. 基本フロー

```text
[Damage]
   ↓
[Enemy Health更新]
   +-- Health > 0 --> [Combat継続]
   ↓
[Health <= 0]
   ↓
[Defeat Guard]
   +-- 既にDefeated --> [Ignore]
   ↓
[Defeated]
   +--> Attack Ability終了
   +--> AI移動 / 判断停止
   +--> Melee / Ranged Slot解放
   +--> Targeting対象から除外
   ↓
[Reward Grant]
```

## 4. 優先順位

HP0によるDefeatedはPosture Down / Stagger等の一時状態より優先する。Defeated後にDownやFatal Attack受付へ戻さない。

## 5. 責務

| 対象 | 責務 |
|---|---|
| Enemy Attribute / Damage | Health更新 |
| Enemy Combat / Death処理 | Defeated確定、Ability停止 |
| AI Controller | Behavior停止 |
| Attack Coordinator | 攻撃枠解放 |
| Reward System | Reward Definitionに基づく報酬付与 |
| Targeting | 撃破敵を候補から除外 |

## 6. 受入条件

- [ ] Health>0ではDefeatedへ遷移しない。
- [ ] Health<=0で1回だけDefeatedへ遷移する。
- [ ] 撃破後に攻撃・移動・攻撃枠占有を継続しない。
- [ ] 撃破後にLockOn候補として残らない。
- [ ] 同Frame複数HitでもRewardを重複付与しない。
- [ ] Posture Down中にHP0になってもDefeatedを優先する。

## 7. 未決事項

- ActorのDestroy / Disableタイミング
- Death AnimationとCollision解除のタイミング
- Reward付与をDefeat確定時に行うかAnimation完了後に行うか

詳細は`Docs/15_OpenQuestions.md`で確定する。
