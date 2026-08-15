# [NFR-QUALITY-006] 出荷用ビルドの最終確認

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-QUALITY-006`](../../01_Requirements.md#nfr-quality-006) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#146](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/146) |
| 関連要件・設計 | [`NFR-QUALITY-001`](../../01_Requirements.md#nfr-quality-001)～[`005`](../../01_Requirements.md#nfr-quality-005), Performance要件 |

## 2. 目的
Editor / Development環境だけでなく、実際に提出するShipping Buildでα版全体が成立することを最終確認する。

## 3. 確定仕様・スコープ
- Shipping Buildを生成して実機環境で通しPlayする。
- Title / New Game / Continue / Load / Gameplay / Save / Death / Boss / Ending / Title復帰を確認する。
- Gamepad / Keyboard-Mouse双方を確認する。
- Known Crash、進行不能Bug、Performance最低目標を最終Gateとして確認する。

## 4. 基本フロー
```text
Shipping Build生成
↓
起動 / Title確認
↓
両Input Deviceで通しPlay
↓
Save / Load / Death / Boss / Ending確認
↓
Performance / Crash / 進行確認
↓
提出可否判定
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| Build | Shipping Package生成 |
| Final Verification | 通しScenario実施 |
| Quality / Performance | Release Gate確認 |

## 6. 状態 / Gameplay Tag
なし。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Shipping Build Id | 検証対象 | Test Evidence |
| Test Results | 各Gate結果 | Test Evidence |
| Performance Metrics | 60fps等 | Measurement |
| Known Issue List | 提出判断 | Test Evidence |

## 8. UI / HUD / Animation / Feedback
Shipping BuildでDebug専用表示に依存せず、必要UI / HUD / Endingが正常表示されることを確認する。

## 9. 異常系・終了条件
- Development Buildだけ成功してShipping未確認の状態を完了としない。
- Shippingで欠落Asset / Config / Input Mappingがある場合は修正後に再検証する。

## 10. 受入条件
- [ ] Shipping Buildを生成・起動できる。
- [ ] New GameからEnding後Titleまで完走できる。
- [ ] 両Input Deviceで主要操作できる。
- [ ] 既知Crash / 進行不能Bugが0件である。
- [ ] Performance最低目標を確認できる。

## 11. 依存・Issue反映
### 依存
- [#111](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/111), [#135](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/135), [#136](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/136), [#142](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/142), [#143](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/143), [#144](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/144), [#145](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/145)

### Issue反映
- [#146](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/146)をα版最終Release Gateとする。

## 12. 未決事項
なし
