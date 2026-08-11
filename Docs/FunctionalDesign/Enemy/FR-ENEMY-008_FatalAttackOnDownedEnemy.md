# FR-ENEMY-008 Down中にFatal Attackを受け付ける

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-008` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#123` |
| 関連設計 | `FR-ENEMY-007`, `FR-PLAYER-022` |

## 2. 目的

Enemy Down中だけPlayer Fatal Attackを受け付ける範囲と受付状態を提供する。

## 3. 確定仕様・基本フロー

```text
[Enemy Down開始]
  ↓
[Window.FatalAttack.Available ON]
  ↓
[Fatal Attack受付Collision ON]
  ↓
[Playerが受付範囲内へ]
  ↓
[FR-PLAYER-022がAttack Inputを評価]
  ↓
[Down終了 / Defeat / Fatal成立]
  ↓
[受付Window / Collision OFF]
```

- Fatal Attack受付はEnemyがDown中の間だけ有効。
- 受付範囲は専用Collisionで判定する。
- Player側の入力、位置合わせ、`UGA_FatalAttack`、Montage、Fatal Damageは`FR-PLAYER-022`が担当する。

## 4. 責務

| 対象 | 責務 |
|---|---|
| Enemy Down処理 | 受付開始・終了Eventを発行する |
| Fatal Attack受付Collision | Playerが実行可能範囲内かを判定する |
| Gameplay State | `Window.FatalAttack.Available`を管理する |
| Player Fatal Attack | `FR-PLAYER-022`へ委譲 |

## 5. 状態・Gameplay Tag

| State / Tag | 用途 |
|---|---|
| `State.Reaction.Downed` | Enemy Down中 |
| `Window.FatalAttack.Available` | Fatal Attack受付可能 |

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| FatalAttackCollision Shape / Size | 受付範囲 | Enemy / Runtime設定 |
| FatalAttackPosition / Transform | Player位置合わせ先 | Enemy / Fatal定義 |
| DownState | 受付開始・終了判定 | Runtime State |

## 7. UI / Animation / Feedback

- Down中Animationは`FR-ENEMY-007`で必須。
- Fatal Attack専用Promptを表示するかはVisual調整可能だが、受付状態をGameplay側から取得可能にする。

## 8. 異常系・終了条件

- Down終了、Defeat、Fatal Attack成立時にCollisionと受付Stateを必ず無効化する。
- Enemy破棄時にCollision / Tag / Target参照を残さない。
- 同一Enemyで受付状態を二重開始しない。

## 9. 受入条件

- [ ] Down開始時にFatal Attack受付状態になる。
- [ ] Down中だけ受付Collisionを有効にする。
- [ ] Playerが受付範囲内か判定できる。
- [ ] Down終了時に受付を無効化する。
- [ ] Defeat / Fatal成立時にも受付を無効化する。
- [ ] Player Fatal Attack実行へ必要なTarget / Transformを提供できる。

## 10. 依存・Issue反映

`#123`はEnemy側Down / Fatal Attack受付までを担当し、Player Actionは独立Issueへ分離する。

## 11. 未決事項

なし。Collisionサイズ、Prompt表示方法は調整項目とする。
