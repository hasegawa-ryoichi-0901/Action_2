# FR-ENEMY-009 EnemyごとにPosture回復設定を変更できる

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-ENEMY-009`](../../01_Requirements.md#fr-enemy-009) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#118](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/118), [#124](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/124) |
| 関連要件・設計 | [`FR-ENEMY-006`](../../01_Requirements.md#fr-enemy-006), [`FR-ENEMY-007`](../../01_Requirements.md#fr-enemy-007) |

## 2. 目的
Enemy種別ごとにPosture回復有無・Delay・Rateを調整し、Posture Break難度を差別化する。

## 3. 確定仕様・スコープ
- Enemy DataごとにPosture Recovery設定を持つ。
- Recovery Enabled、Delay、Rateを個別調整可能にする。
- Down / Defeated中の回復RuleはDown / Defeat状態を優先する。

## 4. 基本フロー
```text
Posture Damage
↓
Recovery Enabled?
├ No → 維持
└ Yes
  ↓
Recovery Delay
  ↓
Combat状態確認
  ↓
Posture回復
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Enemy Data | 回復Parameter提供 |
| Posture System | Delay / Rate適用 |
| Enemy State | Down / Defeated可否提供 |

## 6. 状態 / Gameplay Tag
Down / Defeated中は回復処理より状態遷移を優先する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| PostureRecoveryEnabled | 回復有無 | Master Data |
| PostureRecoveryDelay | 開始遅延 | 調整値 |
| PostureRecoveryRate | 回復量 | 調整値 |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Defeated後に回復処理を継続しない。
- PostureをMaxPosture超過させない。
- Timer / DelegateをOwner破棄後に残さない。

## 10. 受入条件
- [ ] Enemyごとに回復有無を変えられる。
- [ ] Delay / RateをData変更できる。
- [ ] Down / Defeated中に不正回復しない。

## 11. 依存・Issue反映
### 依存
- [#122](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/122), [#123](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/123)

### Issue反映
- [#124](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/124)へEnemy DataとRecovery Lifecycleを反映する。

## 12. 未決事項
なし
