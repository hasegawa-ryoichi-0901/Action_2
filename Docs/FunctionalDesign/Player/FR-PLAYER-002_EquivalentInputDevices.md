# FR-PLAYER-002 Gamepad / Keyboard-Mouseで同等に操作できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-002` |
| 優先度 | `Must` |
| 対応範囲 | Initial Vertical Slice |
| 設計状態 | `Review` |
| 関連Issue | `#111`, `#139` |
| 関連設計 | `NFR-MAINT-003` |

## 2. 目的

入力デバイスに依存せず、Initial Vertical Sliceの同じGameplay Actionへ到達できる入力基盤を提供する。

## 3. 確定仕様・基本フロー

```text
[Input Mapping Context]
      ↓
[Enhanced Input]
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent]
      ↓
[Gameplay Request / Move / Look / ASC / Targeting]
```

- `ABasePlayer`は具体Input Component型へ個別依存しない。
- InputAction / InputTag / Pressed State / Setup / Teardownは`IPlayerInputComponent`契約に従う。
- Duplicate Input Tagを許可しない。
- Setup / UnPossessed / EndPlayでBinding lifecycleを管理する。
- **Combat InputのComponent粒度は固定しない。** 1 Action = 1 Componentでも複数Action集約でもよく、仕様・Gameplay Tag・GAS・責務に応じて実装時に決定する。
- Component粒度の決定はIssue作成・実装開始のBlockerではない。

Initial VSで両デバイスから実行可能にする主要操作：

- Move / Look
- Jump
- Light / Heavy Attack
- Dodge
- Parry
- Heal
- Soft / Manual LockOn / Target Switch
- Fatal Attack
- Interaction
- Menu操作

## 4. 責務

| 対象 | 責務 |
|---|---|
| Input Mapping Context | 物理入力とInputActionの対応 |
| `ABasePlayer` | Mapping ContextとInput Component lifecycle |
| `IPlayerInputComponent` | 共通契約 |
| Input Component実装 | 入力解釈・Gameplay要求配送 |
| Gameplay System / ASC | 入力後のゲームルール |

## 5. 状態・Gameplay Tag

Input Gameplay TagをAction識別・配送に利用可能とする。具体Tag階層は各Action設計に従う。

## 6. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| InputAction | Gameplay入力定義 | Enhanced Input Asset |
| Input Mapping | Keyboard / Mouse / Gamepad割当 | IMC |
| Input Gameplay Tag | 識別・配送 | Gameplay Tag |

## 7. UI / Animation / Feedback

UI上のKey Prompt自動切替はUI側のPresentation責務。Gameplay Ruleはデバイス別に分岐しない。

## 8. 異常系・終了条件

- Setup再実行でBindingを重複させない。
- Duplicate Input Tagを検知する。
- UnPossessed / EndPlay後に古いBindingを残さない。

## 9. 受入条件

- [ ] Gamepad / Keyboard-Mouseの両方でInitial VSの主要Actionを実行できる。
- [ ] デバイス差によるGameplay Rule分岐を作らない。
- [ ] Duplicate Input Tagを検出できる。
- [ ] Setup再実行で入力を重複発火しない。
- [ ] UnPossessed / EndPlay後にBindingを残さない。
- [ ] Component粒度をAction Issue開始の前提にしない。

## 10. 依存・Issue反映

- `#111`, `#139`

## 11. 未決事項

なし。Component構成は機能ごとに臨機応変に決定する。
