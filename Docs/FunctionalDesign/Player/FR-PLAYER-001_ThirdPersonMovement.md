# FR-PLAYER-001 三人称視点で移動できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-001` |
| 要件名 | 三人称視点で移動できる |
| 要件種別 | 機能要件 |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Draft` |
| 関連設計 | `FR-PLAYER-002`, `FR-PLAYER-021`, `NFR-MAINT-003` |

## 2. 目的

カメラ方向を基準とした応答性の高い三人称移動を提供する。

## 3. 設計方針

現行実装を正とし、存在しない`IMovementDriver` / `UMovementAdapterComponent`を前提にしない。

```text
[Enhanced Input / IA_Move]
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent]
      ↓
[UPlayerMoveInputComponent]
      ↓
[Move(FInputActionValue)]
      ↓
[Controller YawからForward / Right算出]
      ↓
[APawn::AddMovementInput]
      ↓
[CharacterMovement]
```

## 4. 事前条件

- `UPlayerMoveInputComponent`がPlayerへアタッチされている。
- `FTaggedInputAction`に有効なInputAction / InputTagが設定されている。
- `ABasePlayer`が有効なControllerを保持している。
- Inputが無効化されていない。
- 死亡等で移動を禁止する場合はGameplay状態側から入力または移動要求を拒否する。

## 5. 基本フロー

1. `ABasePlayer::SetupPlayerInputComponent`が入力Componentを収集する。
2. `IPlayerInputComponent::Setup()`でEnhanced InputへBindingする。
3. Move入力から2D軸を取得する。
4. ControllerのYawだけを使用してForward / Rightを算出する。
5. `AddMovementInput`へ要求する。
6. CharacterMovementが移動結果を反映する。

## 6. 異常系・ライフサイクル

- OwnerがPawnでない場合は処理しない。
- Controllerが無効な場合は処理しない。
- InputTag重複時は重複Componentを登録しない。
- `SetupPlayerInputComponent`再実行前に既存BindingをTeardownする。
- UnPossessed / EndPlay時にBindingとMapping Contextを解除する。

## 7. 責務分割

| 対象 | 責務 |
|---|---|
| `ABasePlayer` | Input Component発見・登録・Setup/Teardown、Mapping Context |
| `IPlayerInputComponent` | 入力Componentの共通契約 |
| `UBasePlayerInputComponent` | TaggedInputAction、押下状態、Binding共通処理 |
| `UPlayerMoveInputComponent` | Move入力解釈、カメラYaw基準の方向算出、移動要求 |
| CharacterMovement | 実際のCharacter移動 |
| Animation | 移動速度等からLocomotionを表示 |

## 8. インターフェース

本要件の入力Componentは`IPlayerInputComponent`を実装する。

```cpp
const FTaggedInputAction& GetTaggedInputAction() const;
bool IsPressed() const;
void Setup(UInputComponent& InputComponent);
void Teardown();
```

移動固有処理を`IPlayerInputComponent`へ追加しない。

## 9. データ

- InputAction / InputTag：`FTaggedInputAction`
- Mapping Context：`ABasePlayer::DefaultMappingContext`
- 移動速度・加減速等：CharacterMovementまたは将来の調整データ

## 10. 受入条件

- [ ] Keyboard / MouseでカメラYaw基準に前後左右移動できる。
- [ ] Gamepadで同等に移動できる。
- [ ] Controller未取得時にクラッシュしない。
- [ ] Setup再実行でMove入力が重複発火しない。
- [ ] UnPossessed / EndPlay後に古いBindingが残らない。
- [ ] `ABasePlayer`が`UPlayerMoveInputComponent`の具体型を個別登録しなくてもInterface経由でSetupできる。

## 11. テスト観点

- 通常移動
- 斜め入力
- カメラ回転後の移動方向
- Controller無効
- Input Disable / Enable
- Possess再実行
- InputTag重複

## 12. 未決事項

Moverは初期Vertical Sliceの必須要件ではない。具体的メリットを確認できた場合のみPost-Prototypeで評価し、必要ならMovement境界を追加する。

## 13. Issue分割方針

既に実装済みのMove入力基盤は新規Issueとして再実装しない。今後のIssueは本受入条件との差分または不足テストのみを対象とする。
