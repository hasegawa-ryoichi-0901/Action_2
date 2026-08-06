# FR-ENEMY-004 同時に近接攻撃する敵を最大2体に制限する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-ENEMY-004` |
| 要件名 | 同時に近接攻撃する敵を最大2体に制限する |
| 要件種別 | 機能要件 |
| 要件カテゴリ | 敵 |
| 元要件 | [Docs/01_Requirements.md](../../01_Requirements.md)「同時に近接攻撃する敵を最大2体に制限する」 |
| 優先度 | `Must` |
| 設計状態 | `Draft` |
| 対応範囲 | Vertical Slice対象 |
| 関連Issue | 未割当 |
| 関連PR | 未割当 |
| 関連設計書 | [Docs/03_CombatSystem.md](../../03_CombatSystem.md)<br>[Docs/05_GASDesign.md](../../05_GASDesign.md)<br>[Docs/06_EnemyAI.md](../../06_EnemyAI.md)<br>[Docs/07_ClassDesign.md](../../07_ClassDesign.md)<br>[Docs/08_DataDesign.md](../../08_DataDesign.md) |

---

## 2. 目的

回避不能な近接攻撃集中を抑え、公平な集団戦を維持する。

---

## 3. スコープ

### 3.1 対象

- 元要件「同時に近接攻撃する敵を最大2体に制限する」を実現する。
- 最大2枠を原子的に付与し、完了・中断・死亡・登録解除時に確実に解放する。
- 成功・拒否・中断時の状態整合性と通知までを扱う。

### 3.2 対象外

- 要件に直接関係しない演出の最終調整と詳細アルゴリズム。
- 数値・アセットの最終調整とprivate関数の内部アルゴリズム。

---

## 4. アクター

| アクター | 役割 |
|---|---|
| `AEnemyAIController` | 入力または処理開始条件を発行する |
| `UEnemyAttackCoordinatorSubsystem` | 実行可否判定、状態変更、主要処理を担当する |
| `AEnemyCharacter / Player` | 処理結果の反映または影響を受ける |

---

## 5. 事前条件

- 関連Actor、Component、Data Assetが初期化済みで有効である。
- 要求者が登録済み・生存・近接攻撃可能で、使用枠が2未満か検証する。
- 死亡、Owner破棄、Level遷移などの処理禁止状態ではない。
- 多重実行を識別できる状態または一意な要求が存在する。

---

## 6. 事後条件

### 6.1 成功時

- 許可・拒否と枠Tokenが要件どおり反映される。
- 完了通知が必要な連携先へ1回だけ送られる。
- 一時Tag、Timer、Delegate、参照が不要になった時点で解除される。

### 6.2 失敗時

- 事前条件を満たさない要求は状態を変更せず拒否する。
- コスト、進行データ、永続データを部分的に変更しない。
- 設定不備または不正参照は開発用Warningへ理由を記録する。

### 6.3 中断時

- 実行中Tag、Timer、Delegate、非同期処理、一時参照を解除する。
- Owner破棄後のUObjectまたはActorへアクセスしない。
- 再実行可否は通常状態への復帰後に改めて判定する。

---

## 7. 基本フロー

```text
[開始条件成立]
      |
      v
[敵ID、近接枠要求を受け付ける]
      |
      v
[要求者が登録済み・生存・近接攻撃可能で、使用枠が2未満か検証する]
      |
      +-- 不成立 --> [状態を変えず拒否]
      |
      v
[最大2枠を原子的に付与し、完了・中断・死亡・登録解除時に確実に解放する]
      |
      v
[許可・拒否と枠Tokenを通知]
      |
      v
[一時状態を解除して終了]
```

### 7.1 処理手順

1. 開始Eventまたは入力を1回受け付ける。
2. 参照、現在状態、必要データ、禁止条件を検証する。
3. 実行中の同一処理があれば重複開始を拒否する。
4. 最大2枠を原子的に付与し、完了・中断・死亡・登録解除時に確実に解放する。
5. 許可・拒否と枠Tokenを反映する。
6. UI、Animation、AIまたは保存先へ結果を通知する。
7. 一時状態を解除し通常状態へ戻す。

---

## 8. 代替フロー・異常系

### 8.1 実行条件を満たさない場合

- 事前条件を満たさない要求は状態を変更せず拒否する。
- Gameplay Attribute、所持数、進行、保存データは変更しない。
- User操作が原因の場合は必要最小限の拒否理由をUIへ通知する。

### 8.2 実行中に中断された場合

- 死亡、被弾、強制リアクション、Owner破棄、Level遷移を中断候補とする。
- Ability、Animation、Timer、Delegate、攻撃枠など要件が所有する一時状態を解除する。
- 中断前の変更を確定するか破棄するかは一つのTransaction境界で統一する。

### 8.3 参照対象が無効になった場合

- 無効参照へアクセスせず、安全に処理を終了する。
- ロック、UI、カメラ、AI枠など対象へ紐づく状態を解除する。
- Asset設定不備は開発BuildでWarningを出す。

### 8.4 多重実行された場合

- 同一要求の重複開始とDelegateの重複登録を拒否する。
- 既存処理を再利用できる場合は新規Instanceを生成しない。
- 完了・失敗通知を要求1回につき最大1回とする。

---

## 9. 状態遷移

```text
[Ready]
   |
   | 条件成立
   v
[Executing] ----中断----> [Cancelled]
   |
   +----失敗------------> [Ready]
   |
   +----成功------------> [Completed]
                              |
                              v
                           [Ready]
```

### 9.1 使用するGameplay Tag

| Gameplay Tag | 用途 | 付与タイミング | 解除タイミング |
|---|---|---|---|
| `State.AI.MeleeSlot` | 要件の状態・受付・通知 | 処理開始または条件成立時 | 完了・中断・条件解除時 |

---

## 10. 入出力

### 10.1 入力

| 入力項目 | 型・形式 | 必須 | 説明 |
|---|---|---:|---|
| 実行入力 | InputAction / Gameplay Event / System Event | Yes | 敵ID、近接枠要求 |
| 状態・対象参照 | Gameplay Tag / Attribute / Weak Object Reference | Yes | 要求者が登録済み・生存・近接攻撃可能で、使用枠が2未満か検証する |
| 設定データ | Data Asset / Config | Yes | Melee Attack Slots |

### 10.2 出力

| 出力項目 | 型・形式 | 説明 |
|---|---|---|
| 実行結果 | State / Attribute / Result Event | 許可・拒否と枠Token |
| 通知 | Delegate / Gameplay Event | 完了・失敗・中断を必要な連携先へ通知する |
| フィードバック | UI / Animation / VFX / SE | デバッグ表示で使用中2枠と待機列を確認可能にする |

---

## 11. 責務分割

| クラス・システム | 責務 | 実装区分 |
|---|---|---|
| `UEnemyAttackCoordinatorSubsystem` | 実行可否、状態遷移、主要ロジック、重複防止 | `C++` |
| `EnemyDefinition` | Melee Attack SlotsとAsset参照 | `Data Asset / Config` |
| `Animation / Widget / VFX` | 表示、Animation、演出、デザイナー調整 | `Blueprint / Asset` |

### 11.1 C++の責務

- 状態、実行可否、Transaction境界、ライフサイクルを管理する。
- データと参照を検証し、Blueprint未設定時も安全に失敗する。
- 公開APIと通知Eventを必要最小限に保つ。

### 11.2 Blueprintの責務

- Animation、VFX、SE、Camera、WidgetのAsset割当と演出調整を行う。
- ゲームルールや永続データの正本をBlueprintだけに保持しない。

### 11.3 DataAssetの責務

- Melee Attack Slotsを保持する。
- 武器・敵・Ability・難易度ごとの差分をC++分岐なしで表現する。
- 必須参照、値域、重複IDをEditor Validationで検証可能にする。

---

## 12. インターフェース

### 12.1 公開操作

```cpp
// 概念レベル。詳細な型と名前は詳細設計または実装時に確定する。
bool CanRequestMeleeSlot() const;
void RequestRequestMeleeSlot();
void CancelRequestMeleeSlot();
bool IsRequestMeleeSlotActive() const;
```

### 12.2 通知イベント

```cpp
DECLARE_MULTICAST_DELEGATE(FOnRequestMeleeSlotStarted);
DECLARE_MULTICAST_DELEGATE(FOnRequestMeleeSlotCompleted);
DECLARE_MULTICAST_DELEGATE(FOnRequestMeleeSlotCancelled);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestMeleeSlotFailed, EFailureReason);
```

### 12.3 呼び出し方向

```text
[AEnemyAIController]
        |
        v
[UEnemyAttackCoordinatorSubsystem]
   |          |
   v          v
[EnemyDefinition]  [AEnemyCharacter / Player]
        |
        v
[Animation / VFX / UI / Save]
```

---

## 13. データ設計

| データ項目 | 型候補 | 初期値 | 設定場所 | 説明 |
|---|---|---:|---|---|
| Melee Attack Slots | Data Asset / Struct / Config | 2 | EnemyDefinition | 要件固有の判定・調整データ |
| 状態識別子 | `FGameplayTag`またはEnum | 設計済みTag / TBD | NativeTags / Config | 実行・禁止・通知状態 |
| Asset参照 | `TSoftObjectPtr`候補 | `None` | Data Asset / Blueprint | Animation・VFX・SE・Widget参照 |

### 13.1 データ駆動対象

- 調整頻度が高い数値、時間、距離、コスト、Score。
- 武器・敵・Abilityごとの差分とAnimation・VFX・SE参照。

### 13.2 ハードコードを許可する内容

- 変更可能性が低い安全制約、配列境界、エンジン仕様上の固定値。
- 要件で確定した不変値。調整対象値は含めない。

### 13.3 バリデーション

- 必須ID・Class・Asset・Gameplay Tagが設定されている。
- 数値が有効範囲内で、MinがMaxを超えない。
- 重複ID、矛盾Tag、存在しない派生参照を許可しない。

---

## 14. UI・フィードバック

| 種別 | 内容 |
|---|---|
| UI | デバッグ表示で使用中2枠と待機列を確認可能にする |
| Animation | 状態の開始・成功・失敗・中断を必要な場合に識別可能にする |
| VFX / SE | 成功と失敗を混同しない演出をData AssetまたはBlueprintで割り当てる |
| Camera | 操作性を損なわず、必要な対象補正・注視・Hit Stopだけを適用する |
| Controller | 重要な成功・被弾等に限り、設定で無効化可能な振動を使用する |

---

## 15. 非機能要件

### 15.1 パフォーマンス

- 常時Tickと毎Frameの全Actor検索を避け、Event・Timer・Subsystemを優先する。
- 基準環境・1920x1080で60fps目標への影響を代表シナリオで計測する。

### 15.2 保守性

- C++は状態と制約、Blueprintは演出、Data Assetは調整値を担当する。
- Gameplay Tagと共通Interfaceを使用し、具体実装への直接依存を抑える。

### 15.3 安全性

- UObject参照、Owner、Avatar、Targetの有効性を使用直前に確認する。
- EndPlay、UnPossessed、死亡、中断時にTimer・Delegate・Tag・一時参照を解除する。

### 15.4 品質

- 進行不能と既知Crashを残さず、ゲームパッドとキーボード・マウスで確認する。
- DevelopmentとShipping BuildでAsset参照と主要フローを確認する。

---

## 16. 受入条件

### 16.1 正常系

- [ ] 同時に近接Attack AbilityがActiveとなる通常敵が2体を超えない。
- [ ] 成功通知が1回発行され、一時状態が完了時に解除される。
- [ ] デバッグ表示で使用中2枠と待機列を確認可能にする。

### 16.2 異常系

- [ ] 事前条件を満たさない要求は状態を変更せず拒否する。
- [ ] 不正参照、Owner破棄、多重要求でもCrash・重複実行・二重消費が発生しない。
- [ ] 中断後に一時Tag、Timer、Delegate、攻撃枠、UI状態が残らない。

### 16.3 入力・ビルド

- [ ] Player操作を伴う場合、ゲームパッドとキーボード・マウスで同じ結果になる。
- [ ] Development BuildとShipping Buildで主要フローが完了する。

---

## 17. テスト観点

| ID | 分類 | 条件 | 操作 | 期待結果 |
|---|---|---|---|---|
| `TC-FR-ENEMY-004-001` | 正常系 | すべての事前条件を満たす | 敵ID、近接枠要求を発生させる | 同時に近接Attack AbilityがActiveとなる通常敵が2体を超えない |
| `TC-FR-ENEMY-004-002` | 異常系 | 必須参照または実行条件を1つ無効にする | 同じ要求を発生させる | 状態とリソースを変更せず安全に拒否する |
| `TC-FR-ENEMY-004-003` | 多重・中断 | 処理中または連続要求 | 再要求、死亡、Owner破棄のいずれかを発生させる | 重複せず一時状態を解除しCrashしない |

---

## 18. 依存関係

### 18.1 前提となる要件

- `FR-ENEMY-003`

### 18.2 この要件に依存する要件

- なし

### 18.3 関連システム

- Behavior Tree
- AI Perception
- Gameplay Ability System
- Enemy Attack Coordinator

---

## 19. 未決事項

| ID | 内容 | 影響範囲 | 決定期限 | 状態 |
|---|---|---|---|---|
| - | 現行資料から追加の未決事項なし | - | - | Closed |

### 19.1 未決事項の運用

- Open項目は実装Issue開始前に決定するか、TBDの仮値と検証期限をIssueへ記録する。
- 仮定で実装した場合は設計判断とテスト結果を残す。

---

## 20. 設計判断

| 判断ID | 判断事項 | 採用案 | 不採用案 | 理由 |
|---|---|---|---|---|
| `ADR-FR-ENEMY-004-001` | 責務配置 | C++で状態と判定を管理し、調整値とアセット参照はデータへ分離する | Blueprintだけにルールと状態を保持する | 状態整合性、検証容易性、データ調整性を保つため |

---

## 21. Issue・PR分割案

| 実装順 | Issue案 | 完了条件 | 依存Issue |
|---:|---|---|---|
| 1 | `FR-ENEMY-004: データ・状態・公開Interface` | 必須データ、状態、Validation、APIが定義される | なし |
| 2 | `FR-ENEMY-004: 主要ロジック` | 正常・拒否・中断・多重実行テストが通る | #1 |
| 3 | `FR-ENEMY-004: Asset・UI・結合確認` | 必須Assetを設定し受入条件を確認できる | #2 |

---

## 22. 変更履歴

| 日付 | 変更者 | 内容 |
|---|---|---|
| `2026-08-07` | `Codex` | 要件定義と既存設計書から初版作成 |
