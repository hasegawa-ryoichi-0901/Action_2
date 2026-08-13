# FR-BOSS-004 Player装備Weaponを評価する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `FR-BOSS-004` |
| 優先度 | `Should` |
| 対応範囲 | `Post-VS` |
| 設計状態 | `Draft` |
| 関連Issue | `未割当` |
| 関連要件・設計 | `FR-PLAYER-008`, `FR-BOSS-014`, `BOSS-AI-COMMON` |

## 2. 目的
Axe / Bow追加後にPlayer装備WeaponをBoss Attack評価へ反映し、武器ごとに異なる対処を選択可能にする。

## 3. 確定仕様・スコープ
- Initial VSではSword固定のため評価対象外。
- Post-VSで確定済みEquipped Weapon TypeだけをContextへ使用する。
- 未反映Weapon Change Inputは参照しない。

## 4. 基本フロー
```text
Combat Context更新
↓
Equipped Weapon取得
↓
Weapon Modifier取得
↓
Attack Candidate Scoreへ反映
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Player Weapon System | 現在装備を公開 |
| Boss Context | Weapon Type取得 |
| Evaluator | Weapon Modifier適用 |

## 6. 状態 / Gameplay Tag
Weapon状態はEquipped Weaponを正とし、必要なWeapon Tagへ同期する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Equipped Weapon Type | Context | Runtime |
| Weapon Modifier | Score補正 | Master Data |

## 8. UI / HUD / Animation / Feedback
Gameplay表示は不要。DebugでWeapon TypeとModifierを表示可能にする。

## 9. 異常系・終了条件
- 未実装Weapon Typeは中立Modifierとして安全に扱う。
- Weapon参照無効でCrashしない。

## 10. 受入条件
- [ ] Post-VSで装備Weaponを取得できる。
- [ ] Weapon ModifierをAttack Scoreへ反映できる。
- [ ] Debugで評価内容を確認できる。

## 11. 依存・Issue反映
### 依存
- Axe / Bow実装
- `FR-PLAYER-008`

### Issue反映
- Post-VS RoadmapでIssue化する。

## 12. 未決事項
なし
