# NFR-MAINT-002 C++とBlueprintの責務を分離する

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-MAINT-002`](../../01_Requirements.md#nfr-maint-002) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#138](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/138) |
| 関連要件・設計 | [Class Design](../../07_ClassDesign.md), 各FR基本設計 |

## 2. 目的
Gameplay RuleとPresentationを分離し、仕様変更・Test・Asset差し替えを行いやすくする。

## 3. 確定仕様・スコープ
- C++はState、実行可否、Lifecycle、Validation、主要Gameplay Ruleを担当する。
- Blueprint / AssetはAnimation、VFX、SE、Widget、Camera演出、Asset割当等を担当する。
- Gameplay上の正本となる永続State / RuleをBlueprintだけに保持しない。
- Blueprint未設定時もC++側で安全に失敗できる設計を優先する。

## 4. 基本フロー
```text
Gameplay Request
↓
C++ Rule / State / Validation
↓
Gameplay Result Event
↓
Blueprint / Asset Presentation
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| C++ | Rule、State、Validation、Lifecycle、System間契約 |
| Blueprint | Presentation、Asset構成、Designer調整 |
| Data | 調整値・差分 |

## 6. 状態 / Gameplay Tag
Gameplay Stateの正本はC++ / GAS / State System側で管理し、Blueprintは表示目的で参照する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Asset References | Montage / VFX / SE / Widget割当 | Asset Data |
| Gameplay Result Events | Presentation通知 | Runtime |
| Responsibility Mapping | Review時の責務確認 | Design |

## 8. UI / HUD / Animation / Feedback
UI / Animation / VFX / SEの具体表現はBlueprint / Asset側へ配置し、Gameplay RuleをPresentationへ埋め込まない。

## 9. 異常系・終了条件
- Asset未設定でGameplay Stateを破損させない。
- Blueprint Event未実装でC++ Lifecycleを停止させない。
- 同じGameplay RuleをC++とBlueprintへ二重実装しない。

## 10. 受入条件
- [ ] Gameplay Ruleの正本をC++ / System側で確認できる。
- [ ] Presentation Assetを差し替えてもGameplay Ruleを変更しない。
- [ ] Blueprint未設定時に安全に検出・終了できる。
- [ ] 同じ責務の二重実装がない。

## 11. 依存・Issue反映
### 依存
- 各FRの責務定義

### Issue反映
- [#138](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/138)で主要SystemのC++ / Blueprint責務を監査する。

## 12. 未決事項
なし
