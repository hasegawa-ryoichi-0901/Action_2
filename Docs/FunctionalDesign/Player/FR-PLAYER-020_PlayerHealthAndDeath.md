# FR-PLAYER-020 プレイヤーはHPを持ち、HPが0以下になると死亡する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-020` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連要件 | `FR-STAGE-008`, `FR-STAGE-012` |

## 2. 目的

被ダメージから死亡、DeathDrop、Checkpoint Respawnへ一貫して遷移できるプレイヤー生存状態を定義する。

## 3. データ

- `Health`
- `MaxHealth`
- `State.Dead`

HealthはGASの`CharacterAttributeSet`で管理する方針とする。

## 4. 基本フロー

```text
[Damage確定]
      ↓
[Health更新]
      +-- Health > 0 --> [Combat継続]
      ↓
[Health <= 0]
      ↓
[Death Transition Guard]
      +-- 既にDead --> [Ignore]
      ↓
[State.Dead]
      +--> 実行中Abilityを終了 / Cancel
      +--> 戦闘入力・Interaction停止
      +--> Target / 一時状態解除
      ↓
[DeathDrop / Respawnへ通知]
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| AttributeSet / Damage System | Health更新 |
| Player Death処理 | Health<=0検出、Dead遷移の一意性、戦闘停止 |
| Gameplay Ability | Death時のCancel / Endに対応 |
| Stage / Death System | DeathDrop生成、Respawn |
| UI | HP表示、死亡演出 |

## 6. 受入条件

- [ ] HealthがDamageによって減少する。
- [ ] Health>0では死亡しない。
- [ ] Health<=0で`State.Dead`へ1回だけ遷移する。
- [ ] Dead後に攻撃・回避・回復等を継続しない。
- [ ] Dead遷移中の追加Damageで死亡処理を重複実行しない。
- [ ] DeathDrop / Respawn処理へ1回だけ通知する。
- [ ] Respawn後に新しいPlayer状態として戦闘を再開できる。

## 7. テスト観点

- Health境界値 1→0
- Overkill Damage
- 同Frame複数Hit
- Attack / Dodge / Heal中の死亡
- Death状態中の追撃
- Respawn後のHealth / Tag整合性

## 8. 未決事項

- Death Animation完了待ちか固定時間Respawnか
- Death中のCamera操作可否
- Death時に一律Cancelする処理の共通ルール

詳細は`Docs/15_OpenQuestions.md`で確定する。
