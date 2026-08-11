# 17. Master Data / CSV読込Architecture

## 1. 目的

各基本設計が列挙する`必要データ`と、CSV / DB / Master Dataの具体的な読込実装を分離する。Gameplay Systemが特定CSV ReaderやTable構造へ直接依存しない境界を定義する。

## 2. 確定している境界

```text
[Gameplay System]
      ↓
[Gameplay Data Contract / Repository相当の境界]
      ↓
[Master Data Reader]
      ↓
[CSV / DB Master]
```

- 各`FR-*`基本設計はGameplay上必要なDataだけを記載する。
- CSV列、Table、PK / FK、Reader Class、Cache方式等は本Architecture側で扱う。
- Gameplay SystemはReward件数やCSV列順等へ依存しない。
- Data ValidationでID / Reference / Value整合性を確認可能にする。

## 3. Reward Masterの確定概念

Reward件数に依存しない構造とする。

```text
EnemyID(PK) -> RewardID
RewardID -> ItemID / Amount ... (0..N)
```

例：

```text
EnemyID = 1 -> RewardID = 1
RewardID = 1 -> ItemID = 1
RewardID = 1 -> ItemID = 2
```

Gameplay側は`RewardID`から0..N件のReward Entryを取得する契約へ依存する。Rewardが1件、2件、それ以上になってもReward付与ロジックの構造を変更しない。

## 4. 各基本設計との契約

各FRの`必要データ`欄に記載されたData Nameを入力として、Master Data側でどのTable / CSVから提供するかを後続設計で対応付ける。

## 5. 未確定事項

以下は必要Dataの棚卸し完了後に本ドキュメントで決定する。

- CSVファイル分割単位
- Table / PK / FKの最終Schema
- Reader / Cache / Reload方式
- Editor Validation方式
- Build時のData配置
- Data Versioning / Migration

これらは各Gameplay FRの挙動を確定するBlockerにはしない。
