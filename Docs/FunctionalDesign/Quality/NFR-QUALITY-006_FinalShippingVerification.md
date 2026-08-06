# NFR-QUALITY-006 Shippingビルドで最終確認を行う

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-QUALITY-006` |
| 要件名 | Shippingビルドで最終確認を行う |
| 要件種別 | 非機能要件 |
| 要件カテゴリ | 品質 |
| 元要件 | [Docs/01_Requirements.md](../../01_Requirements.md)「Shippingビルドで最終確認を行う」 |
| 優先度 | `Must` |
| 設計状態 | `Draft` |
| 関連Issue | 未割当 |
| 関連PR | 未割当 |
| 関連設計書 | [Docs/09_SaveCheckpointDeath.md](../../09_SaveCheckpointDeath.md)<br>[Docs/10_PerformanceRequirements.md](../../10_PerformanceRequirements.md)<br>[Docs/11_TestPlan.md](../../11_TestPlan.md) |

---

## 2. 目的

Editor・Development専用機能に依存しない製品相当動作を確認する。

---

## 3. スコープ

### 3.1 対象

- 元要件「Shippingビルドで最終確認を行う」の判定基準、検証条件、証跡を定義する。
- 新規開始・戦闘・死亡・Save/Load・Boss撃破・Stage Clearと性能要点をShippingで実行する。
- Release判断で第三者が合否を再確認できる記録を残す。

### 3.2 対象外

- 要件に直接関係しない演出の最終調整と詳細アルゴリズム。
- 個別機能のprivate実装と、根拠のない環境・閾値の追加。

---

## 4. アクター

| アクター | 役割 |
|---|---|
| `QA / 開発者` | 条件を固定し検証を実施する |
| `Quality Verification` | 計測・レビュー・テスト結果を収集して合否を判定する |
| `ゲーム全体 / 保存データ / ビルド` | 要件を満たす対象と証跡の生成元 |

---

## 5. 事前条件

- Build ID、実行環境、品質・入力・テスト設定が記録されている。
- Shipping構成、Cook済みAsset、設定、デバッグ機能無効化を確認する。
- Warmup、試験開始点、操作手順、計測区間を再現できる。
- デバッグ機能の有効・無効とShipping差分を識別できる。

---

## 6. 事後条件

### 6.1 成功時

- 最終確認Checklistと証跡が保存される。
- 受入条件に対するPass根拠をBuild・環境・日時と関連付ける。
- 退行比較に利用できる形式で証跡を保持する。

### 6.2 失敗時

- Failを隠さず、再現条件、期待値、実測値、影響範囲をIssueへ記録する。
- 測定不能と要件未達を区別する。
- Release blockerか挑戦目標かを優先度に従って分類する。

### 6.3 中断時

- 不完全な計測を合格証跡として使用しない。
- 中断理由と取得済みLog・Captureを残し、条件を初期化して再実施する。

---

## 7. 基本フロー

```text
[基準Build・環境を固定]
      |
      v
[Shipping Buildを準備]
      |
      v
[Shipping構成、Cook済みAsset、設定、デバッグ機能無効化を確認する]
      |
      +-- 不備 --> [測定不能として条件を修正]
      |
      v
[新規開始・戦闘・死亡・Save/Load・Boss撃破・Stage Clearと性能要点をShippingで実行する]
      |
      v
[最終確認Checklistと証跡を記録]
      |
      v
[基準と比較してPass / Fail判定]
```

### 7.1 処理手順

1. Build、Hardware、解像度、品質、入力、試験データを固定する。
2. 前回結果または受入閾値を確認する。
3. 同じ手順で必要回数の計測・レビュー・通し試験を実行する。
4. 新規開始・戦闘・死亡・Save/Load・Boss撃破・Stage Clearと性能要点をShippingで実行する。
5. 最終確認Checklistと証跡を証跡とともに記録する。
6. Pass / Fail / 測定不能を分類し、FailはIssueへ関連付ける。

---

## 8. 代替フロー・異常系

### 8.1 検証条件を満たさない場合

- 条件不足の結果を合否判定へ使用しない。
- 不足する環境・Asset・Build・手順を記録して再検証する。

### 8.2 検証中に中断された場合

- CaptureとLogを保存し、中断理由を記録する。
- 再実施時は初期状態、Warmup、操作順を揃える。

### 8.3 計測対象または証跡が無効な場合

- 欠落・破損したCaptureを根拠にしない。
- 別Profilerや再現Logで相互確認する。

### 8.4 複数回の結果が乖離する場合

- 外れ値を無断で除外せず、Background Process・Shader Compile・温度・乱数を調査する。
- 代表値と最悪値の採用ルールを記録する。

---

## 9. 状態遷移

```text
[Not Verified]
      |
      v
[Verifying] ----条件不備----> [Blocked]
      |
      +----基準達成---------> [Passed]
      |
      +----基準未達---------> [Failed]
```

### 9.1 使用するGameplay Tag

| Gameplay Tag | 用途 | 付与タイミング | 解除タイミング |
|---|---|---|---|
| 該当なし | 検証状態はテスト記録またはIssue Statusで管理する | - | - |

---

## 10. 入出力

### 10.1 入力

| 入力項目 | 型・形式 | 必須 | 説明 |
|---|---|---:|---|
| 検証対象 | Build / Source / Asset / Save Fixture | Yes | Shipping Build |
| 実行条件 | Hardware Profile / Test Matrix / Checklist | Yes | Shipping構成、Cook済みAsset、設定、デバッグ機能無効化を確認する |
| 比較基準 | 数値閾値 / 0件条件 / Architecture Rule | Yes | Shipping Verification Checklist |

### 10.2 出力

| 出力項目 | 型・形式 | 説明 |
|---|---|---|
| 判定 | Pass / Fail / Blocked | 要件単位の最終結果 |
| 証跡 | Report / Log / Trace / Screenshot / Checklist | 最終確認Checklistと証跡 |
| Issue | Defect / Improvement | 失敗条件、再現手順、影響、優先度 |

---

## 11. 責務分割

| クラス・システム | 責務 | 実装区分 |
|---|---|---|
| `Quality Verification` | 条件固定、収集、比較、判定 | `Tool / C++ / Test` |
| `テスト計画 / 不具合管理` | 閾値、環境、履歴、証跡 | `Config / Document` |
| `QA / Reviewer` | 再現性確認、結果承認、Issue分類 | `Process` |

### 11.1 C++の責務

- 必要な計測点、Validation、Automation Hookを製品挙動へ影響しない形で提供する。
- Shippingで無効となるデバッグ依存を必須フローに持ち込まない。

### 11.2 Blueprintの責務

- テストMap、Fixture、表示確認用Assetを設定する。
- 合否ロジックや品質基準の正本をBlueprintだけに保持しない。

### 11.3 DataAsset・テストデータの責務

- 再現可能な入力値、環境条件、期待値を保持する。
- 変更履歴とBuild IDを結果へ関連付ける。

---

## 12. インターフェース

### 12.1 公開操作

```cpp
// 概念レベル。実際のAutomation/Test APIは実装時に選定する。
FVerificationResult VerifyVerifyShippingBuild(const FVerificationContext& Context);
bool MeetsVerifyShippingBuildRequirement(const FVerificationResult& Result);
```

### 12.2 通知イベント

```cpp
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVerificationCompleted, const FVerificationResult&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVerificationFailed, const FVerificationFailure&);
```

### 12.3 呼び出し方向

```text
[Test Plan / Reviewer]
          |
          v
[Quality Verification]
   |             |
   v             v
[Build / Runtime] [Profiler / Log / Checklist]
          |
          v
[Report / Issue / Release Decision]
```

---

## 13. データ設計

| データ項目 | 型候補 | 初期値 | 設定場所 | 説明 |
|---|---|---:|---|---|
| Shipping Verification Checklist | Test Config / Number / Rule | Data Asset定義値 | テスト計画 / 不具合管理 | 合否基準または検証条件 |
| Build情報 | String / Changelist / Configuration | 計測対象 | Test Report | 再現対象の識別 |
| 証跡参照 | Path / URL / Attachment ID | None | Test Report / Issue | Log・Trace・画像・Checklist |

### 13.1 データ駆動対象

- 閾値、計測地点、試験時間、Hardware Profile、品質Preset、Fixture。
- Build間比較に必要な結果と環境Metadata。

### 13.2 ハードコードを許可する内容

- 要件で明示された不変基準と安全上の上限。
- 調整・Release判断対象の閾値はConfigまたは文書で追跡する。

### 13.3 バリデーション

- Build ID、環境、手順、期待値、実測値、判定が欠落していない。
- 単位と測定方法が一致し、前回結果と比較可能である。

---

## 14. UI・フィードバック

| 種別 | 内容 |
|---|---|
| 開発UI | 製品向けUIのみ表示され、開発用Overlayは無効である |
| Report | 条件、結果、閾値、合否、証跡、Issueを同じ要件IDへ関連付ける |
| Shipping | 開発用Overlay・Profiler・個人情報を無効にする |

---

## 15. 非機能要件

### 15.1 パフォーマンス

- 計測自体のObserver Effectを記録し、Profiler無効時とも比較する。
- 平均値だけでなくFrame Time、Spike、Memoryまたは所要時間を要件に応じて確認する。

### 15.2 保守性

- 要件IDをTest、Report、Issue、変更履歴で共通利用する。
- 閾値と環境をデータ化し、手順を別担当者が再現できるようにする。

### 15.3 安全性

- 破損Fixtureや異常系試験は本番データと隔離する。
- Test完了・中断後に状態、File、Delegate、Processを片付ける。

### 15.4 品質

- Pass / FailをYes / Noで判定できる条件にする。
- Developmentだけでなく必要な最終確認をShipping Buildで実施する。

---

## 16. 受入条件

### 16.1 正常系

- [ ] Shipping Buildで必須通しテストが完了し、進行不能・既知Crashが0件である。
- [ ] Build、環境、手順、期待値、実測値、証跡が要件IDへ関連付けられる。
- [ ] 別担当者が記録された条件で結果を再現できる。

### 16.2 異常系

- [ ] 条件不足・中断・証跡破損をPassとして扱わない。
- [ ] Fail時に再現条件、影響範囲、優先度を持つIssueを作成できる。

### 16.3 入力・ビルド

- [ ] 対象がPlayer操作ならゲームパッドとキーボード・マウスの条件を区別して記録する。
- [ ] Release判断に必要な項目をShipping Buildで確認する。

---

## 17. テスト観点

| ID | 分類 | 条件 | 操作 | 期待結果 |
|---|---|---|---|---|
| `TC-NFR-QUALITY-006-001` | 基準確認 | すべての前提条件が固定済み | Shipping Buildで検証する | Shipping Buildで必須通しテストが完了し、進行不能・既知Crashが0件である |
| `TC-NFR-QUALITY-006-002` | 再現性 | 同じBuild・環境・手順 | 別担当者が再実施する | 許容差内で同じ判定となる |
| `TC-NFR-QUALITY-006-003` | 条件不備 | 必須Metadataまたは証跡なし | 判定を要求する | PassにせずBlockedまたは測定不能となる |

---

## 18. 依存関係

### 18.1 前提となる要件

- `NFR-QUALITY-001`
- `NFR-QUALITY-002`
- `NFR-QUALITY-003`
- `NFR-QUALITY-004`
- `NFR-QUALITY-005`

### 18.2 この要件に依存する要件

- なし

### 18.3 関連システム

- Automation Test
- Gauntlet候補
- Crash Reporter
- Memory Insights

---

## 19. 未決事項

| ID | 内容 | 影響範囲 | 決定期限 | 状態 |
|---|---|---|---|---|
| - | 現行資料から追加の未決事項なし | - | - | Closed |

### 19.1 未決事項の運用

- Open項目はRelease判定前に決定し、TBDのままPass判定しない。
- 仮条件の結果は参考値と明記し、正式条件で再検証する。

---

## 20. 設計判断

| 判断ID | 判断事項 | 採用案 | 不採用案 | 理由 |
|---|---|---|---|---|
| `ADR-NFR-QUALITY-006-001` | 検証方式 | C++で状態と判定を管理し、調整値とアセット参照はデータへ分離する | 担当者の主観だけで合否を決める | 再現性、比較可能性、Release判断の追跡性を保つため |

---

## 21. Issue・PR分割案

| 実装順 | Issue案 | 完了条件 | 依存Issue |
|---:|---|---|---|
| 1 | `NFR-QUALITY-006: 検証条件・Fixture整備` | 環境、手順、期待値、証跡形式が確定する | なし |
| 2 | `NFR-QUALITY-006: 計測・レビュー・試験` | 基準Buildの結果と証跡が揃う | #1 |
| 3 | `NFR-QUALITY-006: 未達修正と再確認` | Must/Should基準がPassまたは承認済み判断となる | #2 |

---

## 22. 変更履歴

| 日付 | 変更者 | 内容 |
|---|---|---|
| `2026-08-07` | `Codex` | 要件定義と既存設計書から初版作成 |
