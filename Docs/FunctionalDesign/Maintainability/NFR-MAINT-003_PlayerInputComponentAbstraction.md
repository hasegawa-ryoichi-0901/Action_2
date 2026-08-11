# NFR-MAINT-003 プレイヤー入力コンポーネントをIPlayerInputComponentで抽象化する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-MAINT-003` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 目的

`ABasePlayer`がMove、Look、Combat等の個別入力Componentへ直接依存せず、入力追加時のPlayerクラス変更とBinding重複を抑える。

## 3. 確定仕様

```text
ABasePlayer
  ↓ discovers / manages
IPlayerInputComponent
  ↓ implemented by
UBasePlayerInputComponent派生
  ↓
Gameplay Request / Movement / Camera / ASC
```

- `ABasePlayer`は入力Componentを`IPlayerInputComponent`契約で管理する。
- InputAction / InputTag / Pressed State / Setup / Teardownを共通契約とする。
- Duplicate Input Tagは設定エラーとして拒否する。
- Setup再実行、UnPossessed、EndPlayで古いBindingを残さない。
- Gameplay RuleをInterfaceへ集約しない。
- **Component粒度は意図的に固定しない。** `1 Action = 1 Component`でも複数Action集約でもよく、Gameplay Tag、GAS、責務、Lifecycle、テスト容易性を見て仕様ごとに決定する。
- Component粒度の決定をAction Issue作成・実装開始のBlockerにはしない。

## 4. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| InputAction | Enhanced Input Binding | Asset |
| Input Gameplay Tag | 入力識別・配送 | Gameplay Tag |

## 5. 受入条件

- [ ] `ABasePlayer`が具体Input Component型の分岐を増やさずSetupできる。
- [ ] Duplicate Input Tagを検出できる。
- [ ] Setup再実行でBindingが重複しない。
- [ ] UnPossessed / EndPlay後に古いBindingが残らない。
- [ ] `IsPressed()`がInput Eventと同期する。
- [ ] Gameplay Ruleが`IPlayerInputComponent`へ混入しない。
- [ ] Component粒度をAction Issueの前提条件にしない。

## 6. 未決事項

なし。Component構成は各機能の実装時に臨機応変に判断する。
