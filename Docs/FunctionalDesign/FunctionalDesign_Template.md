# 基本設計テンプレート

> 目的：`Docs/01_Requirements.md`の1要件を、他の開発者が**約1時間以内で記述・レビュー可能**な粒度へ具体化する。
> private関数、詳細アルゴリズム、最終数値、アセット最終選定は実装Issueまたは実装中の調整へ残す。
> 存在しないClass / Interface / Adapterをテンプレート都合で確定設計として追加しない。

# [要件ID] [要件名]

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `[FR-...]` |
| 優先度 | `Must / Should / Could` |
| 対応範囲 | `Initial Vertical Slice / Post-VS` |
| 設計状態 | `Draft / Review / Approved / Implemented` |
| 関連Issue | `未割当 / #xxx` |
| 関連設計 | `[Requirement ID / 相対リンク]` |

## 2. 目的

- この要件が必要な理由を1～3文で記載する。

## 3. 確定仕様・スコープ

- 本要件で実現するゲーム上の挙動。
- 明確に対象外となる内容があれば併記する。
- 調整値やアセット選定は必要な場合だけ「調整可能」と記載する。

## 4. 基本フロー

```text
[開始]
  ↓
[条件確認]
  ↓
[主要処理]
  ↓
[結果 / 通知]
```

必要な場合だけ分岐・Cancel・Failureを追記する。

## 5. 責務

| 対象 | 責務 |
|---|---|
| `[既存Class / System / Concept]` | `[担当する責務]` |

- 実在しないClass名は確定実装として書かない。
- `IPlayerInputComponent`を使う場合も、`1 Action = 1 Component`を前提にしない。

## 6. 状態・Gameplay Tag

要件に状態管理が必要な場合のみ記載する。

| State / Tag | 用途 |
|---|---|
| `[State.* / Window.*]` | `[意味]` |

不要な場合は「なし」とする。

## 7. 必要データ

> **全FRで必須欄。** DB / CSV / Data Asset等の保存方式はここでは決めず、この要件がGameplay上必要とするデータだけを列挙する。

| データ | 用途 | 備考 |
|---|---|---|
| `[DataName]` | `[何に使うか]` | `調整値 / Master Data / Runtime` |

- Master Dataの具体SchemaやCSV Readerは別Architecture Designで定義する。
- Gameplay側は具体的なCSV読込実装へ直接依存しない。

## 8. UI / HUD / Animation / Feedback

必要なものだけ記載する。

| 種別 | 内容 |
|---|---|
| UI / HUD | `[表示・操作]` |
| Animation | `[必要Animation / Montage]` |
| VFX / SE | `[必要Feedback]` |
| Camera | `[必要Camera挙動]` |

不要な項目は削除または「なし」とする。

## 9. 異常系・終了条件

- 多重実行、Owner破棄、Death、Cancel、Target無効化等のうち、この要件で実際に問題になるものだけ記載する。
- 終了時に解除が必要なTag / Timer / Binding / Collision / 参照があれば記載する。

## 10. 受入条件

第三者がYes / Noで判定できる条件だけを書く。

- [ ] `[正常系]`
- [ ] `[境界・異常系]`
- [ ] `[他Systemとの接続]`

## 11. 依存・Issue反映

- 前提要件・後続要件を列挙する。
- 基本設計で確定している内容は、関連Issueの目的・実装範囲・受入条件へ反映する。
- 原則`1実装Issue = 1 PR`。
- Gameplay Actionは親Issue単位で管理してよいが、ActorComponentの粒度とは一致させない。

## 12. 未決事項

**Issue境界や挙動を変える未決事項だけ**を記載する。

- なし

または

| 内容 | Blocker |
|---|---|
| `[未決事項]` | `Yes / No` |

数値調整・アセット最終選定は原則Blockerにしない。
