# [NFR-MAINT-003] IPlayerInputComponentによるプレイヤー入力の抽象化

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | [`NFR-MAINT-003`](../../01_Requirements.md#nfr-maint-003) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#139](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139) |
| 関連要件・設計 | [`FR-PLAYER-002`](../../01_Requirements.md#fr-player-002), [GAS Design](../../05_GASDesign.md), [Class Design](../../07_ClassDesign.md) |

## 2. 目的
`ABasePlayer`を具体Input Component型から分離し、Input Setup / TeardownとGameplay要求配送を共通契約で管理する。

## 3. 確定仕様・スコープ
- `ABasePlayer`はInput Componentを`IPlayerInputComponent`契約で管理する。
- Setup / Teardown / Input Tag / Pressed Stateの共通契約を維持する。
- Duplicate Input Tagを設定不備として検知する。
- Component粒度は固定しない。1 Action 1 Component / 複数Action集約のどちらも仕様・Gameplay Tag・GAS・Lifecycle・Test容易性に応じて選択可能とする。
- Component粒度の決定をAction Issue作成・実装開始の前提条件にしない。

## 4. 基本フロー
```text
SetupPlayerInputComponent
↓
Playerに接続されたInput Component取得
↓
IPlayerInputComponent契約として登録
↓
Input Tag重複検証
↓
Setup / Binding

再Setup / UnPossessed / EndPlay
↓
Teardown
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| ABasePlayer | Interface経由の収集・登録・Lifecycle |
| IPlayerInputComponent | 共通Input契約 |
| Input実装 | 個別入力受付・Gameplay Request変換 |
| Gameplay System | Inputの具体Component型を意識せず要求を処理 |

## 6. 状態 / Gameplay Tag
Input Tagを入力識別へ利用する。Gameplay状態Tagとは用途を分離する。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Input Action | Enhanced Input受付 | Asset |
| Input Tag | 入力識別 | Config |
| Pressed State | 押下状態 | Runtime |
| Binding Handles | Teardown | Runtime |

## 8. UI / HUD / Animation / Feedback
なし。

## 9. 異常系・終了条件
- Duplicate Input Tagを黙って上書きしない。
- Setup再実行前に古いBindingをTeardownする。
- Owner / InputComponent無効時にCrashしない。
- UnPossessed / EndPlay後にBindingを残さない。

## 10. 受入条件
- [ ] ABasePlayerが具体Input Component型へ直接依存しない。
- [ ] Setup / Teardown契約を統一できる。
- [ ] Duplicate Input Tagを検知できる。
- [ ] Component粒度を仕様に応じて変更できる。
- [ ] Input再Setupで重複発火しない。

## 11. 依存・Issue反映
### 依存
- 現行`IPlayerInputComponent` / `UBasePlayerInputComponent`

### Issue反映
- [#139](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/139)へ抽象化、Lifecycle、Component粒度非固定を反映する。

## 12. 未決事項
なし
