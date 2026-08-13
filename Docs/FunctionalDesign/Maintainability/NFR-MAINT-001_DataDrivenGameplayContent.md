# NFR-MAINT-001 Gameplay ContentをData Drivenで追加できる

## 1. 基本情報
| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-MAINT-001` |
| 優先度 | `Must` |
| 対応範囲 | `Initial Vertical Slice` |
| 設計状態 | `Draft` |
| 関連Issue | `#137` |
| 関連要件・設計 | `Docs/08_DataDesign.md`, `Docs/17_MasterDataCsvArchitecture.md` |

## 2. 目的
Weapon、Attack、Enemy、Ability、Reward等の差分・調整値をGameplay Codeの分岐へ固定せず、データ追加・変更で拡張できる構造を維持する。

## 3. 確定仕様・スコープ
- 各FRはGameplay上必要なデータを`必要データ`欄へ明示する。
- Gameplay Systemは必要データをProvider / Definition等の契約から取得し、具体的なCSV ReaderやDB Schemaへ直接依存しない。
- ID、必須参照、値域、重複等を検証可能にする。
- Master Dataの具体SchemaとCSV読込Architectureは別ドキュメントで定義する。

## 4. 基本フロー
```text
Gameplay System
↓
必要なData Id / Definitionを要求
↓
Game Data Provider / Definition契約
↓
検証済みGameplay Data
↓
Gameplay処理へ利用
```

## 5. 責務
| 対象 | 責務 |
|---|---|
| 各FR基本設計 | 必要データを定義する |
| Gameplay System | Data契約を利用して処理する |
| Data Provider / Definition | Data取得境界を提供する |
| Validation | 欠損・重複・不正値を検知する |
| Master Data Architecture | CSV / DB等の具体読込方式を定義する |

## 6. 状態 / Gameplay Tag
本要件固有の状態はなし。Gameplay Tag自体もGameplay Dataの一部として参照可能にする。

## 7. 必要データ
| データ | 用途 | 備考 |
|---|---|---|
| Gameplay Data Id | Data識別 | Master Data |
| Gameplay Definitions | Weapon / Attack / Enemy / Reward等 | Master Data |
| Validation Result | 設定不備検出 | Development Runtime / Editor |
| Data Provider Contract | Gameplayと読込方式の境界 | Architecture |

## 8. UI / HUD / Animation / Feedback
Gameplay UIは各FRが担当する。開発時はData Validation Errorを確認可能にする。

## 9. 異常系・終了条件
- 必須ID / Data欠損時にCrashせず開発時に検出できる。
- 重複IDを正しいDataとして扱わない。
- Gameplay SystemからCSV Parse等の具体実装を直接呼び出さない。

## 10. 受入条件
- [ ] Weapon / Attack / Enemy / Reward等の調整値をGameplay Code変更なしで変更できる。
- [ ] 各FRが必要データを明示している。
- [ ] Gameplay側が具体的なCSV Readerへ直接依存しない。
- [ ] 必須Data欠損・重複・不正値を検出できる。

## 11. 依存・Issue反映
### 依存
- 各Gameplay FRの`必要データ`
- `Docs/17_MasterDataCsvArchitecture.md`

### Issue反映
- `#137`へData契約、Validation、読込方式非依存を反映する。

## 12. 未決事項
なし
