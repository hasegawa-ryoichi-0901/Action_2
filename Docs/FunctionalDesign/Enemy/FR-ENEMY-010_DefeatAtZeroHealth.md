# FR-ENEMY-010 HP0以下でEnemyをDefeatする

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-ENEMY-010`](../../01_Requirements.md#fr-enemy-010) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#97](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/97), [#98](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/98) |
| 関連要件・設計 | [`FR-ENEMY-006`](../../01_Requirements.md#fr-enemy-006), [`FR-STAGE-014`](../../01_Requirements.md#fr-stage-014) |

## 2. 目的
Enemy戦の終了条件を一意に定義し、AI停止・Slot解放・Targeting解除・Reward付与へ接続する。

## 3. 確定仕様・スコープ
- Health<=0でDefeatedを1回だけ確定する。
- DefeatedはDown / Stagger等より優先する。
- Attack Ability、AI移動・判断を停止する。
- 所有Attack Slotを解放しTarget候補から除外する。
- Reward付与はDefeated確定後に1回だけ行う。

## 4. 基本フロー
```text
Damage
↓
Health <= 0
↓
Defeat Guard
↓
Defeated
├ Ability / AI停止
├ Slot解放
├ Targeting除外
└ Reward通知
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Health / Combat | Defeated一意確定 |
| AI / Ability | 行動停止 |
| Coordinator | Slot解放 |
| Targeting | 候補除外 |
| Reward System | `FR-STAGE-014`実行 |

## 6. 状態 / Gameplay Tag
Defeated状態を死亡終端として管理する。具体Tag名は共通Tag設計に従う。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Health | Defeat判定 | Runtime |
| RewardId | Reward解決 | Master Data |
| Death Animation / Cleanup Rule | 撃破表現 | Asset / Gameplay Data |

## 8. UI / HUD / Animation / Feedback
| 種別 | 内容 |
|---|---|
| Animation | Enemy Death / Defeat Animation |
| VFX / SE | 撃破Feedback |

## 9. 異常系・終了条件
- 同Frame複数HitでDefeat / Rewardを重複実行しない。
- Down中Health0でもDefeatedを優先する。
- Defeated後にLockOn候補へ戻さない。

## 10. 受入条件
- [ ] Health0でDefeatedへ1回遷移する。
- [ ] AI / Attack / Slotを終了できる。
- [ ] Targeting候補から除外できる。
- [ ] Rewardを1回だけ後続へ通知できる。

## 11. 依存・Issue反映
### 依存
- [#122 Health](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/122)
- [#99 Reward付与](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/99)

### Issue反映
- [#97](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/97)をDefeat / Reward親Issue、[#98](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/98)をDefeat実装Issueとして扱う。

## 12. 未決事項
なし
