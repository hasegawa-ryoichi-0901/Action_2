# FR-PLAYER-020 PlayerはHPを持ちHP0以下で死亡する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-020` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#82`, `#83` |
| 関連要件・設計 | `FR-STAGE-008`～`012`, `FR-SAVE-005`, `Docs/09_SaveCheckpointDeath.md` |

## 2. 目的

Player Damageの終端としてDeath Stateを一意に確定し、Death Animation / DeathDrop / Save / Respawnへ接続する。

## 3. 確定仕様・スコープ

- Healthが0以下になった時点でDeathを1回だけ確定する。
- DeathはHit / Stagger / Down等のReactionより優先する。
- 実行中Combat Actionを終了し通常Gameplay Inputを停止する。
- Death中もCamera Lookは許可する。
- Death Animation完了後にDeathDrop処理へ進む。

## 4. 基本フロー

```text
Damage
↓
Health更新
↓
Health <= 0?
├ No → Gameplay継続
└ Yes
  ↓
Death Guard
  ↓
State.Dead
  ↓
Combat / Gameplay Input停止
  ↓
Death Animation
  ↓
FR-STAGE-008 / FR-SAVE-005
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Player Attribute | Health更新 |
| Death処理 | Death一意確定・優先順位 |
| Combat / Input | Action終了・通常Input停止 |
| Animation | Death Animation完了通知 |
| DeathDrop / Save | 後続死亡処理 |

## 6. 状態 / Gameplay Tag

| State / Gameplay Tag | 用途 |
|---|---|
| `State.Dead` | Player死亡状態 |

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Health / MaxHealth | 生存判定 | Runtime / 調整値 |
| Death Animation / Montage | 死亡表現 | Asset |
| Death Location | DeathDrop位置 | Runtime |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | HPを0へ反映し通常Gameplay HUDの操作要素を停止する |
| Animation | Death Animation |
| Camera | Death中もCamera Look可能 |

## 9. 異常系・終了条件

- 同Frame複数DamageでもDeathを重複開始しない。
- Death後にHeal / Attack / Dodgeを開始しない。
- Death Animation完了Eventを複数処理しない。

## 10. 受入条件

- [ ] Health>0ではDeathへ遷移しない。
- [ ] Health<=0でDeathを1回だけ確定する。
- [ ] DeathがReactionより優先される。
- [ ] Death中に通常Gameplay Actionを開始できない。
- [ ] Camera Lookを継続できる。
- [ ] Death Animation完了からDeathDrop処理へ1回接続できる。

## 11. 依存・Issue反映

### 依存
- `#62` Damage
- `#84` DeathDrop生成

### Issue反映
- `#82`を死亡Loop親Issue、`#83`をHealth0 / Death Stateとして扱う。

## 12. 未決事項

なし
