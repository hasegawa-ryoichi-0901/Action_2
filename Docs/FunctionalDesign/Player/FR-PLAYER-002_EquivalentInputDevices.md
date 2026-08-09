# FR-PLAYER-002 ゲームパッドとキーボード・マウスで同等に操作できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-002` |
| 要件名 | ゲームパッドとキーボード・マウスで同等に操作できる |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |

## 2. 目的

入力デバイスに依存せず同じゲームプレイ機能へ到達できる入力基盤を提供する。

## 3. 設計方針

```text
[Input Mapping Context]
      ↓
[Enhanced Input]
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent]
      ↓
[UBasePlayerInputComponent派生]
      +--> Move
      +--> Look
      +--> Jump / Dodge / Combat / Targeting（追加予定）
```

`ABasePlayer`は個別派生Componentの具体型へ依存せず、`IPlayerInputComponent`の契約だけで登録・Setup・Teardownする。

## 4. IPlayerInputComponent契約

```cpp
virtual const FTaggedInputAction& GetTaggedInputAction() const = 0;
virtual bool IsPressed() const = 0;
virtual void Setup(UInputComponent& InputComponent) = 0;
virtual void Teardown() = 0;
```

- `FTaggedInputAction`でInputActionとInputTagを対応付ける。
- 同一PlayerでInputTag重複を許可しない。
- Setup / Teardownを再実行可能にする。
- Started / Completed / Canceledと`IsPressed()`を同期する。

## 5. 基本フロー

1. PlayerがPossessされInputComponentが準備される。
2. `ABasePlayer`がアタッチ済み`UBasePlayerInputComponent`を収集する。
3. `IPlayerInputComponent`へCastする。
4. InputTagの有効性・重複を検証する。
5. `TMap<FGameplayTag, TScriptInterface<IPlayerInputComponent>>`へ登録する。
6. `Setup()`でEnhanced Input Bindingを構築する。
7. 入力無効状態が設定されていればMapping Contextを無効状態に保つ。

## 6. ライフサイクル

- Setup前に既存入力ComponentをTeardownする。
- UnPossessedではControllerが有効なうちにMapping Contextを解除する。
- EndPlayでもTeardownする。
- 再Possess / InputComponent再構築時にBindingを二重登録しない。

## 7. デバイス同等性

初期Vertical Sliceで以下を両デバイスから実行可能にする。

- Move
- Look / Camera
- Jump
- Light / Heavy Attack
- Dodge
- Parry
- Heal
- Soft / Manual Lock関連操作
- Interaction

UI上のキー表記自動切替は別途UI実装範囲とし、本要件の必須条件は「同一ゲームプレイ機能へ到達できること」とする。

## 8. 責務分割

| 対象 | 責務 |
|---|---|
| Input Mapping Context | デバイスごとの物理入力とInputActionの対応 |
| `ABasePlayer` | Mapping Contextと入力Component lifecycle |
| `IPlayerInputComponent` | 入力Component共通契約 |
| 派生Input Component | Action固有の入力解釈・配送 |
| GAS / Gameplay Systems | 入力後のゲームルール |

## 9. 受入条件

- [ ] GamepadとKeyboard / Mouseで初期Vertical Sliceをクリアできる。
- [ ] 同じInputTagを持つComponentが重複登録されない。
- [ ] UnPossessed / EndPlay後に古いBindingが残らない。
- [ ] 再Setupで入力が重複発火しない。
- [ ] `IsPressed()`がStarted / Completed / Canceledと矛盾しない。
- [ ] `ABasePlayer`に新しい入力種別ごとの個別Setupコードを追加せず、Interface実装Componentを追加できる。

## 10. 未決事項

Combat入力を1Action = 1 Componentとするか、複数Actionを集約するかは`Docs/15_OpenQuestions.md`で管理する。集約方式を採る場合は現在1つの`FTaggedInputAction`を返すInterface契約の変更要否を先に決定する。
