# FR-UI-002 初期プレイアブル版のGameplay HUDを提供する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-UI-002`](../../01_Requirements.md#fr-ui-002) |
| 優先度 | `Must` |
| 対応範囲 | `初期プレイアブル版` |
| 設計状態 | `Draft` |
| 関連Issue | [#151](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/151) |
| 関連要件・設計 | Player / Boss / Save / Tutorial各要件 |

## 2. 目的
戦闘・Resource・Targeting・Save・TutorialでPlayerが判断に必要な状態を表示する。

## 3. 確定仕様・スコープ
- Player HP、Stamina、Healing Item残数、Gold、Upgrade Materialを表示する。
- LockOn Marker、Boss HP、Perfect Dodge Feedbackを表示する。
- Save中 / 成功 / 失敗、Tutorial Text / Stepを表示する。
- Player Hit / Stagger / Downの内部蓄積値は表示しない。
- HUDはGameplay Ruleを所有しない。

## 4. 基本フロー
```text
Gameplay System State / Event
↓
HUD ViewModel / 表示更新
↓
各Widgetへ反映

Title / Ending遷移
↓
Gameplay HUD終了
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Gameplay Systems | 状態 / Event提供 |
| HUD | 表示変換 |
| Widgets | 視覚表現 |

## 6. 状態 / Gameplay Tag
Perfect Dodge、LockOn等のGameplay状態 / Eventを表示条件として参照するがHUD自身は正本にしない。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Health / Stamina | Gauge | Runtime |
| Healing Count | 残数 | Runtime |
| Gold / Material | Inventory表示 | Runtime |
| Current Lock Target | Marker | Runtime |
| Boss Health | Boss Gauge | Runtime |
| Perfect Dodge Event | Feedback | Runtime Event |
| Save State | Save表示 | Runtime |
| Tutorial Step / Text | Tutorial表示 | Runtime / Data |

## 8. UI / HUD / Animation / Feedback
本要件自体がHUD仕様。Event駆動更新を優先し、毎Frameの全Actor検索を前提にしない。

## 9. 異常系・終了条件
- Target無効化時にLockOn Markerを残さない。
- Boss Encounter終了時にBoss HPを残さない。
- Title / Ending遷移時にGameplay HUDを残さない。
- Save失敗時に成功表示を出さない。

## 10. 受入条件
- [ ] 確定HUD要素を表示できる。
- [ ] Gameplay State変化を反映できる。
- [ ] Lock解除 / Boss終了で対応UIを消せる。
- [ ] Perfect Dodge成功時だけFeedbackできる。
- [ ] Reaction内部蓄積値を表示しない。

## 11. 依存・Issue反映
### 依存
- 各Gameplay Systemの通知契約
- [#153 Player Inventory](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)

### Issue反映
- [#151](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/151)へ全表示項目、Event更新、Cleanupを反映する。

## 12. 未決事項
なし
