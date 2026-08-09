# NFR-MAINT-003 プレイヤー入力コンポーネントをIPlayerInputComponentで抽象化する

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `NFR-MAINT-003` |
| 要件種別 | 非機能要件 / 保守性 |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |

## 2. 目的

`ABasePlayer`がMove、Look、Combat等の個別入力Componentへ直接依存せず、入力Action追加時のPlayerクラス変更とInput Bindingの重複実装を抑制する。

## 3. 正とするアーキテクチャ

```text
ABasePlayer
   ↓ discovers
UBasePlayerInputComponent派生
   ↓ implements
IPlayerInputComponent
   +-- GetTaggedInputAction
   +-- IsPressed
   +-- Setup
   +-- Teardown
```

`ABasePlayer`は`TMap<FGameplayTag, TScriptInterface<IPlayerInputComponent>>`で入力Componentを管理する。

## 4. アーキテクチャ規則

- 新しい入力種別を追加するたびに`ABasePlayer::SetupPlayerInputComponent`へ具体型分岐を追加しない。
- InputAction / InputTag / 押下状態 / Setup / Teardownの共通契約は`IPlayerInputComponent`へ従う。
- InputTag重複は設定エラーとして登録しない。
- InputComponent再構築、UnPossessed、EndPlayを考慮する。
- Setupを複数回行ってもBindingを重複させない。
- GameplayロジックをInterface自体へ集約しない。
- Move / Look / Combat等の処理責務は派生Componentまたは配送先Systemへ分離する。

## 5. 受入条件

- [ ] `ABasePlayer`が入力Componentの具体型一覧を保持しなくても自動Setupできる。
- [ ] 追加した`IPlayerInputComponent`実装が有効なInputTagを持てば登録対象になる。
- [ ] 同一InputTagの重複を検出できる。
- [ ] Setup再実行前に旧BindingをTeardownできる。
- [ ] UnPossessed / EndPlay後にBindingが残らない。
- [ ] `IsPressed()`が入力Eventと同期する。
- [ ] Gameplayルールは`IPlayerInputComponent`へ実装しない。

## 6. テスト

- Component追加時の自動発見
- 無効InputTag
- 重複InputTag
- Setup → Setup
- Possess → UnPossessed → Possess
- EndPlay
- Started / Completed / Canceled時の`IsPressed`

## 7. 未決事項

Combat入力を1Action = 1 Componentとするか複数Action集約Componentとするかは未決。集約する場合は`GetTaggedInputAction()`が単一Actionを返す現在のInterface契約を拡張する必要性を先に評価する。

## 8. 設計判断

`IPlayerInputComponent`は「Movementを抽象化するInterface」ではない。入力Bindingと入力Component lifecycleを抽象化する境界であり、Movement実装の差し替えとは分離する。
