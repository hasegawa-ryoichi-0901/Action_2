# 14. Gitリポジトリ運用

## 1. 公開範囲

- リポジトリは応募先企業への提示を想定する。
- 購入Assetの再配布を行わない。
- AssetのLicense条件を別資料で管理する。

## 2. 推奨構成

```text
ProjectRoot/
+-- README.md
+-- Docs/
+-- Config/
+-- Content/
+-- Plugins/
+-- Source/
+-- ProjectName.uproject
```

## 3. Git LFS候補

```text
*.uasset
*.umap
*.fbx
*.wav
*.mp4
*.psd
*.png
*.tga
```

## 4. 除外候補

```text
Binaries/
DerivedDataCache/
Intermediate/
Saved/
.vs/
.idea/
.vscode/
```

## 5. Branch

```text
main
  |
  +-- develop
         |
         +-- feature/...
         +-- fix/...
         +-- docs/...
```

実装Issueごとに差分を独立して確認できるようにします。

## 6. Issue構造

### 6.1 Gameplay Action

Gameplay Actionは**1 Action = 1親Issue**を基本とします。

```text
[Parent] Light Attack
├─ [Implementation] ASC初期化
├─ [Implementation] Gameplay Tag基盤
├─ [Implementation] Stamina Attribute
├─ [Implementation] Damage
├─ [Implementation] Hit Collision
├─ [Implementation] Montage連携
├─ [Implementation] Input
└─ [Implementation] Light Attack統合
```

Light Attack、Heavy Attack、Combo Attack、Dodge等はそれぞれ別の親Issueとして管理します。

### 6.2 ActionとComponentは同義ではない

`1 Action = 1 ActorComponent`はRuleにしません。Gameplay Tag、GAS、責務、Lifecycle、再利用性、Test容易性を考慮してComponent構成を決定します。

Dodgeのように1つのInput / ActionからNormal Dodge / Perfect Dodgeへ結果分岐する場合も、親Issueは1つのDodge Actionとして管理します。

### 6.3 実装Issue

親Issueの下に、独立して実装・Test・Reviewできる実装Issueを配置します。

- 原則として1実装Issue = 1 PR。
- 1つのPRで説明できる責務に絞る。
- 独立して動作確認できる受入条件を持たせる。
- 共有基盤を同じAction内で必要とする場合は実装Issueとして分離できる。
- すでに別Actionで実装済みの共有基盤は重複Issueを作らず、依存先として参照する。
- 親Issue自体は進捗・依存関係を集約するために使用し、必ずしも親Issue単独のPRを作らない。

## 7. 基本設計のTraceability Link

基本設計は要件・設計・Issue間を直接移動できる状態を必須とします。

### 7.1 要件ID

基本設計の`1. 基本情報`に記載する`要件ID`は、必ず[`Docs/01_Requirements.md`](01_Requirements.md)内の該当要件AnchorへのMarkdown Linkにします。

```markdown
| 要件ID | [`FR-PLAYER-001`](../../01_Requirements.md#fr-player-001) |
```

### 7.2 関連Issue

Issueが存在する場合、Issue番号だけをPlain Textで記載せず、必ず該当GitHub Issue URLへのMarkdown Linkにします。

```markdown
| 関連Issue | [#110](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/110) |
```

複数Issueへ対応する基本設計では複数Linkを記載します。Issueがまだ存在しないPost-VS要件のみ`未割当`を許可します。

### 7.3 基本設計一覧

[`Docs/FunctionalDesign/FunctionalDesign_Root.md`](FunctionalDesign/FunctionalDesign_Root.md)から全90要件について次へ直接移動できる状態を維持します。

- 要件定義の該当要件ID
- 基本設計ファイル
- 対応GitHub Issue

## 8. GitHub Project / Roadmap運用

Issue番号順ではなく、[`Docs/ImplementationRoadmap.md`](ImplementationRoadmap.md)で定義した依存関係順を正とします。

### Project Fields

```text
Status
  Todo / In Progress / Review / Done

Priority
  P0 / P1 / P2 / P3

Phase
  P0 Foundation
  P1 Sword Core
  P2 Normal Enemy
  P3 Progression
  P4 Boss
  P5 Stage Clear
  P6 Quality

Milestone / Roadmap
  M0 Core Foundation
  M1 Combat Core
  M2 Normal Battle Loop
  M3 Death & Progression
  M4 Boss
  M5 Release Gate

Start date
End date
```

### View方針

- Tracking View: 親Issueを表示し、Action / System全体の進捗を確認する。
- Implementation Board: 実装IssueのみをStatusで管理する。
- Roadmap View: 実装IssueをPhase / Milestone / Start date / End dateで表示する。
- Priority View: P0 / P1を優先確認する。

親Issue番号やIssue作成日時を実装順として使用しません。依存Issueが完了したものから次の実装Issueへ進みます。

## 9. Issue作成前の確認条件

実装Issueを作る前に次を確認します。

1. 対象機能のゲーム上の挙動が確定している。
2. 実装方式を決めないとIssue境界が変わる未解決事項が残っていない。
3. 対応する要件定義・基本設計が存在する。
4. 既存実装との競合・重複を確認している。
5. 実装Issueが単独で検証可能な受入条件を持つ。
6. 基本設計の要件ID / Issue LinkがTraceability Ruleを満たしている。

数値調整、Asset最終選定など、後からDataで変更できる事項はIssue作成を妨げません。

## 10. Commit

```text
feat: 剣の通常攻撃Abilityを追加
fix: パリィ失敗時に攻撃権が残る問題を修正
refactor: 攻撃評価をEnemyAttackEvaluatorへ分離
docs: GASクラス構成図を更新
test: スタミナ枯渇テストを追加
perf: ボス攻撃評価の更新頻度を削減
```

## 11. Tag

```text
prototype-movement
prototype-combat
initial-playable-0.1
portfolio-build-0.1
steam-demo-0.1
```

## 12. Asset管理

購入AssetごとにAsset Name、Seller、License、Commercial Use、Redistribution Restriction、Project Usage等を記録します。

## 13. READMEへ記載する注意

- 購入Assetを含む場合の再配布条件
- 使用Engine Version
- 必要Plugin
- Build手順
- 操作方法
- 既知の問題

### [戻る](../README.md#ドキュメント一覧)
