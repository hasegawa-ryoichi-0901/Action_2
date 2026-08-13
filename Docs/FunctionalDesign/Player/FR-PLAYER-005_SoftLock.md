# FR-PLAYER-005 ソフトロックを使用できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-005` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#113` |
| 関連要件・設計 | `FR-PLAYER-006`, `FR-PLAYER-010`, `Docs/03_CombatSystem.md` |

## 2. 目的

Manual LockOnを使用していない通常戦闘でも、近傍の有効Enemyへ攻撃方向を補正して操作負荷を下げる。

## 3. 確定仕様・スコープ

- Attack開始時に近傍の有効Target候補からSoft Lock対象を選ぶ。
- Manual LockOn中はManual Targetを優先する。
- Targetが存在しない場合はPlayer入力 / 向きを維持する。
- Defeated / 無効Targetを候補にしない。
- 補正距離・角度は調整可能とする。

## 4. 基本フロー

```text
Attack開始
↓
Manual LockOn中?
├ Yes → Manual Targetを使用
└ No
  ↓
Soft Lock候補検索
  ├ なし → 現在方向を維持
  └ あり → 最適候補へ攻撃方向補正
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Targeting | 候補収集・有効性判定・候補選択 |
| Combat | 選択TargetをAttack方向補正へ利用 |
| Enemy | Target可能 / Defeated状態を公開 |

## 6. 状態 / Gameplay Tag

Soft Lock専用の常駐状態Tagは必須としない。Target有効性はEnemy状態を参照する。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Search Distance | 候補範囲 | 調整値 |
| Search Angle | 候補角度 | 調整値 |
| Candidate Target | 補正対象 | Runtime |

## 8. UI / HUD / Animation / Feedback

なし。Manual LockOn Markerは表示しない。

## 9. 異常系・終了条件

- TargetがAttack開始前後で無効化された場合は補正を破棄する。
- Actor全件検索を毎Frame行う前提にしない。
- Manual LockOnと競合した場合はManual Targetを優先する。

## 10. 受入条件

- [ ] Manual LockOnなしで有効Targetへ攻撃方向を補正できる。
- [ ] 候補なしではPlayer方向を維持する。
- [ ] Defeated / Invalid Targetを選択しない。
- [ ] Manual LockOn中はManual Targetを優先する。

## 11. 依存・Issue反映

### 依存
- `FR-PLAYER-006`
- `FR-PLAYER-010`

### Issue反映
- `#113`へ候補条件、Manual Lock優先、補正調整値を反映する。

## 12. 未決事項

なし
