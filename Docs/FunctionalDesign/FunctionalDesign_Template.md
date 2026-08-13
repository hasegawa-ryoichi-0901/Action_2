# 基本設計テンプレート

> `Docs/01_Requirements.md` の1要件を、他の開発者が内容整理済みであれば約1時間以内に記述・レビューできる粒度へ具体化する。
>
> 本テンプレートでは、以下の12章のみを基本設計の標準構成とする。詳細設計レベルのprivate関数、内部アルゴリズム、最終調整値、アセット最終選定は記載しない。
>
> 実装方式が未確定の場合、存在しないClass / Interface / Component / Adapterをテンプレート都合で確定実装として記載しない。
>
> 本プロジェクトでは、従来の`Initial Vertical Slice`を日本語で**「初期プレイアブル版」**と表記する。

# [要件ID] [要件名]

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `[FR-...]` |
| 優先度 | `Must / Should / Could` |
| 対応範囲 | `初期プレイアブル版 / Post-VS` |
| 設計状態 | `Draft / Review / Approved / Implemented` |
| 関連Issue | `未割当 / #xxx` |
| 関連要件・設計 | `[Requirement ID / 相対リンク]` |

## 2. 目的

- この要件を実装する目的を1～3文で記載する。

## 3. 確定仕様・スコープ

- 確定しているゲーム上の挙動を記載する。
- 本要件で扱う範囲を記載する。
- 明確な対象外がある場合のみ記載する。
- 開発中に調整する数値は、値を固定せず「調整可能」と記載してよい。

## 4. 基本フロー

主要な正常系の処理順を記載する。

```text
[開始]
  ↓
[条件確認]
  ↓
[主要処理]
  ↓
[結果 / 通知]
```

必要な場合だけ分岐、Cancel、Failureを追加する。

## 5. 責務

| 対象 | 責務 |
|---|---|
| `[既存Class / System / Concept]` | `[担当する責務]` |

- ゲームルール、入力、Animation、UI、保存などの責務境界を明確にする。
- 実在しないClass名を確定実装として書かない。
- `IPlayerInputComponent`を使用する場合も、`1 Action = 1 Component`を前提にしない。

## 6. 状態 / Gameplay Tag

状態管理が必要な場合のみ記載する。

| State / Gameplay Tag | 用途 |
|---|---|
| `[State.* / Window.* / Event.*]` | `[意味]` |

状態管理が不要な場合は「なし」と記載する。

## 7. 必要データ

> 全FRで必須。DB / CSV / JSON / Data Asset等の保存・読込方式ではなく、この要件がGameplay上必要とするデータを記載する。

| データ | 用途 | 備考 |
|---|---|---|
| `[DataName]` | `[用途]` | `調整値 / Master Data / Runtime` |

- Master Data Schema、CSV Reader、JSON Schema等のArchitectureは別ドキュメントで定義する。
- Gameplay実装を具体的な読込方式へ直接依存させない。

## 8. UI / HUD / Animation / Feedback

本要件で必要なものだけ記載する。

| 種別 | 内容 |
|---|---|
| UI / HUD | `[表示・操作]` |
| Animation | `[Animation / Montage]` |
| VFX / SE | `[必要Feedback]` |
| Camera | `[必要Camera挙動]` |

不要な項目は削除するか「なし」と記載する。

## 9. 異常系・終了条件

この要件で実際に考慮が必要なものだけ記載する。

例：

- 多重実行
- Death / Defeat
- Cancel / Montage中断
- Owner / Target破棄
- 無効参照
- Input再Setup
- Collision / Gameplay Tag / Timer / Delegateの解除漏れ

終了時に解除・復元が必要な状態があれば明記する。

## 10. 受入条件

第三者がYes / Noで判定できる条件を記載する。

- [ ] `[正常系]`
- [ ] `[境界・異常系]`
- [ ] `[依存Systemとの接続]`

## 11. 依存・Issue反映

### 依存

- 前提となる要件・基本設計・既存実装を記載する。
- 後続機能へ提供する契約がある場合は記載する。

### Issue反映

- 基本設計で確定した実装範囲、必要データ、UI / Animation、異常系、受入条件を関連Issueへ反映する。
- 基本設計全文をIssueへ複製しない。
- 原則 `1実装Issue = 1PR` とする。
- Gameplay Actionは親Issueで管理してよいが、ActorComponent粒度とは一致させない。

## 12. 未決事項

Issue作成・実装開始前に確定しないと、ゲーム上の挙動またはIssue境界が変わる事項だけ記載する。

未決事項がない場合：

```text
なし
```

未決事項がある場合：

| 未決事項 | Issue作成前に確定必須 | 理由 |
|---|---|---|
| `[内容]` | `Yes / No` | `[影響]` |

数値調整、アセット最終選定など、実装中に安全に変更できる事項は原則としてここへ記載しない。
