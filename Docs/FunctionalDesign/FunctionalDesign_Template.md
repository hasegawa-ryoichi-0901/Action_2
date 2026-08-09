# 基本設計テンプレート

> `Docs/01_Requirements.md`の1要件を、実装・レビュー・テスト可能な基本設計へ具体化するためのテンプレートです。
> 基本設計では責務、状態、処理フロー、データ、受入条件、依存関係を定義し、private関数や最終アルゴリズムは原則として実装Issueへ残します。
> **存在しないClass / Interface / Adapterをテンプレート都合で確定設計として追加しないでください。既存実装がある場合は、その採用理由と現行Architectureを確認して記載します。**

# [要件ID] [要件名]

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `[FR-PLAYER-001]` |
| 要件名 | `[名称]` |
| 要件種別 | `機能要件 / 非機能要件 / 制約` |
| 要件カテゴリ | `[Player / Enemy / Boss / Stage / Save / ...]` |
| 元要件 | `[Docs/01_Requirements.mdの該当項目]` |
| 優先度 | `Must / Should / Could` |
| 対応範囲 | `Initial Vertical Slice / Post-Vertical Slice / Architecture Rule` |
| 設計状態 | `Draft / Review / Approved / Implemented` |
| 関連Issue | `未割当 / #xxx` |
| 関連PR | `未割当 / #xxx` |
| 関連設計 | `[相対リンク]` |

## 2. 目的

- この要件が必要なゲームデザイン上・システム上の理由。

## 3. スコープ

### 3.1 対象

- 本要件が責任を持つ処理・状態・データ。

### 3.2 対象外

- 別要件が担当する内容。
- Post-Vertical Slice項目。
- 最終調整値・Asset選定等。

## 4. 現行Architecture / 前提

既存実装がある場合は、実在するClass / Interface / Dataの呼び出し方向を記載します。

```text
[Input / Event]
      ↓
[Existing Interface / Component]
      ↓
[Gameplay System]
```

- 実装されていない抽象化を「将来必要かもしれない」という理由だけで必須化しない。
- 将来差し替え候補がある場合は未決事項またはADRで追跡する。

## 5. アクター・責務

| Class / System | 責務 | 実装区分 |
|---|---|---|
| `[ClassA]` | `[責務]` | `C++` |
| `[ClassB]` | `[責務]` | `Blueprint / Asset` |
| `[Data]` | `[調整値]` | `Data Asset / Config` |

## 6. 事前条件

- 必須参照が有効。
- 実行禁止状態ではない。
- 依存Systemが初期化済み。
- 多重実行を識別できる。

## 7. 事後条件

### 7.1 成功時

- 変更されるState / Attribute / Data。
- 発生するEvent・Presentation。

### 7.2 失敗時

- 部分更新を残さない。
- 必要に応じてLog / UIへ理由を通知する。

### 7.3 中断時

- Tag / Timer / Delegate / Binding / 一時参照を解除する。

## 8. 基本フロー

```text
[開始]
   ↓
[入力 / Event受付]
   ↓
[Validation]
   +-- NG --> [Reject]
   ↓
[主要処理]
   ↓
[State / Data反映]
   ↓
[通知]
   ↓
[終了]
```

## 9. 代替フロー・異常系

- 参照無効。
- Owner破棄。
- Death / Level Transition。
- 多重入力 / 重複Event。
- Cancel / Interrupt。
- Save / Async失敗。

要件に存在しない異常系を機械的に追加せず、現実に起こり得る失敗条件だけを具体化します。

## 10. 状態遷移

```text
[State A]
   ↓ Condition
[State B]
   +-- Cancel --> [State A / Cancelled]
   +-- Complete -> [State C]
```

### Gameplay Tag

| Tag | 用途 | 付与 | 解除 |
|---|---|---|---|
| `[State.*]` | `[意味]` | `[時点]` | `[時点]` |

## 11. 入出力

### 入力

| 項目 | 型候補 | 必須 | 説明 |
|---|---|---:|---|
| `[Input]` | `[type]` | Yes | `[説明]` |

### 出力

| 項目 | 型候補 | 説明 |
|---|---|---|
| `[Result]` | `[type]` | `[説明]` |

## 12. Interface / 公開契約

既存Interfaceを利用する場合は実際の契約を記載します。新規Interfaceは複数実装・差し替え・依存逆転等の具体的必要性がある場合だけ提案します。

```cpp
// Concept level only when not implemented.
bool CanExecute() const;
void RequestExecute();
```

## 13. データ設計

| データ | 型候補 | 初期値 | 設定場所 | 説明 |
|---|---|---:|---|---|
| `[Value]` | `[type]` | `TBD` | `[DataAsset / Config]` | `[説明]` |

- 調整値を不要にHard Codeしない。
- 必須参照・値域・重複ID等をValidationする。

## 14. UI・Animation・Feedback

| 種別 | 内容 |
|---|---|
| UI | `[内容]` |
| Animation | `[内容]` |
| VFX / SE | `[内容]` |
| Camera | `[内容]` |

## 15. 非機能要件

### Performance

- 不要なTick / Actor全検索 / Allocationを避ける。
- 必要な場合はUnreal Insights等で計測する。

### Maintainability

- 既存Architectureと依存方向を守る。
- Player Inputでは`IPlayerInputComponent`を共通契約として扱い、`ABasePlayer`へ入力具体型の個別依存を増やさない。
- 将来Moverを評価する場合も、必要性が確認されるまでMovement Adapter等を先行追加しない。
- C++ / Blueprint / Dataの責務を分離する。

### Lifecycle / Safety

- UObject lifetime、GC、Delegate、Timerを考慮する。
- Setup / Possess / UnPossessed / EndPlay等の再実行を考慮する。
- 重複Binding / 重複Eventを防止する。

## 16. 受入条件

第三者がYes / Noで判定できる表現にします。

- [ ] `[正常条件]`
- [ ] `[異常条件]`
- [ ] `[Lifecycle条件]`
- [ ] Gamepad / Keyboard-Mouse対象なら両方で確認する。

## 17. テスト観点

| ID | 分類 | 前提 | 操作 | 期待結果 |
|---|---|---|---|---|
| `TC-001` | 正常 | `[前提]` | `[操作]` | `[期待]` |
| `TC-002` | 境界 | `[前提]` | `[操作]` | `[期待]` |
| `TC-003` | 異常 | `[前提]` | `[操作]` | `[期待]` |

## 18. 依存関係

### 前提要件

- `[Requirement ID]`

### 後続要件

- `[Requirement ID]`

## 19. 未決事項

| ID | 内容 | Blocker | 決定期限 |
|---|---|---|---|
| `Q-001` | `[内容]` | `Yes / No` | `Issue開始前 / Release前` |

**実装Issueを開始できない未決事項と、調整段階までTBDでよい項目を分離します。**

## 20. 設計判断

| ADR | 判断 | 採用 | 不採用 | 理由 |
|---|---|---|---|---|
| `ADR-001` | `[判断]` | `[採用案]` | `[不採用案]` | `[根拠]` |

## 21. Issue・PR分割案

Issueは設計書の章ではなく、**単独で実装・テスト・レビュー・Rollback可能な変更単位**で切ります。

| 順序 | Issue案 | 完了条件 | 依存 |
|---:|---|---|---|
| 1 | `[実装単位]` | `[Acceptance Criteria]` | `なし` |

原則`1 Issue = 1 PR`とします。1基本設計が複数Issueへ分割されることを許容します。

## 22. 変更履歴

| 日付 | 変更者 | 内容 |
|---|---|---|
| `YYYY-MM-DD` | `[name]` | `初版` |
