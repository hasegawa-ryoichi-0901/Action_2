# 05. Gameplay Ability System設計

## 1. 方針

GASはAttack・Dodge・Stamina・State・Damage / Reaction等のGameplay処理を管理する。Enhanced InputのBinding LifecycleそのものはGASの責務にせず、`IPlayerInputComponent`を入口とする入力層からGameplay要求を配送する。

ASCはPlayerState側へ配置する方針を維持する。

```text
PlayerState
├─ AbilitySystemComponent
└─ AttributeSet

Player Character / ABasePlayer
├─ ASC Avatar
├─ Input
├─ Camera
└─ Collision / Animation
```

## 2. Player Inputとの境界

```text
[Enhanced Input]
      ↓
[ABasePlayer::SetupPlayerInputComponent]
      ↓
[IPlayerInputComponent]
      ├─ Move / Look → Movement / Camera
      └─ Combat Input → Ability Input Tag / Gameplay Request → ASC
```

- `ABasePlayer`は具体Input Component型を列挙しない。
- Attack / Dodge / Parry / Heal / Fatal Attack等をASCへ接続できる。
- `1 Action = 1 Component`は前提にしない。
- 1 Action 1 Component / 複数Action集約のどちらも許容し、Gameplay Tag、GAS、責務、Lifecycleに応じて決定する。
- Component粒度は意図的に固定せず、Action Issue作成・実装開始の前提条件にしない。

## 3. Attribute / Runtime Data

Player側で少なくとも次を扱う。

- Health / MaxHealth
- Stamina / MaxStamina
- AttackPower等のCombat値
- Healing Item関連値
- Player Reaction内部蓄積値

Enemy / BossはHealth / Posture等を扱う。

Gold / Upgrade Material / Boss Unique ItemはGAS AttributeではなくPlayer Inventoryを正本とする。Inventory共通基盤は[#153](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/153)で管理する。

## 4. Ability構成

α版の主なAbility：

- Light Attack
- Heavy Attack
- Air Attack
- Dodge
- Perfect Dodge Counter
- Parry
- Heal
- Jump
- Fatal Attack

Post-VSでGuard / Axe / Bow固有Abilityを追加する。

## 5. Attack Phase / Window

Light / Heavyは個別基本設計に従い、次のPhaseを持つ。

```text
Startup → Commitment → Active → Recovery
```

Gameplay上必要なWindow：

- Hitbox Active
- Combo Accept Input
- Cancel Window
- Perfect Dodge Window
- Counter Window
- Parry Window
- Fatal Attack Available

Commitment中は許可されていないCancelを拒否する。

## 6. Fatal Attack

```text
[Enemy Down / Fatal受付]
      ↓
[Playerが受付Collision内でAttack Input]
      ↓
[Target / Transform確定]
      ↓
[UGA_FatalAttack]
      ↓
[位置合わせ]
      ↓
[Fatal Attack Montage]
      ↓
[Fatal Damage]
```

Enemy Down終了・Defeat・Fatal成立時は受付を解除する。

## 7. Player Reaction

Enemy / Boss Attack DataがPlayer Reaction用蓄積値を持ち、Player内部で加算する。

```text
Attack Hit
↓
Health更新
+-- Health <= 0 → Dead
↓
Reaction累積
├─ Hit
├─ Stagger
└─ Down
```

Reaction蓄積値はHUDへ表示しない。DeathをReactionより優先する。

## 8. Gameplay Tag方針

確定したState / WindowをGameplay Tagで一元管理可能にする。具体Tag名は既存`DefaultGameplayTags.ini`および各Action実装と整合させて決定するため、未実装Tag名を基本設計だけで実装済みと扱わない。

概念例：

```text
State.Action.Attacking
State.Action.Dodging
State.Action.Healing
State.Action.FatalAttacking
State.Reaction.Hit
State.Reaction.Staggered
State.Reaction.Downed
State.Dead
Window.Hitbox.Active
Window.Combo.AcceptInput
Window.Cancel.Dodge
Window.PerfectDodge
Window.Counter.Available
Window.Parry.Active
Window.FatalAttack.Available
```

## 9. Animation

Attack / Heal / Fatal Attack等のMontageとGameplay Event / Notifyを利用して、Hit / Combo / Cancel / Fatal Damage等のGameplay Windowと同期する。Animation Assetを差し替えてもGameplay Ruleの正本が壊れない構造にする。

Healing ItemはHeal Animation開始直後に1個消費し、消費後に被弾 / Cancelされても返却しない。

## 10. 初期化・Lifecycle

Possess / Re-Possess / UnPossessed / EndPlay / InputComponent再構築を考慮し、Input BindingとASC ActorInfoを重複初期化しない。Input側は`IPlayerInputComponent::Setup / Teardown`契約に従う。

## 11. Data境界

各FRの基本設計に`必要データ`を記載する。GAS / Gameplay Systemは具体的CSV Reader、DB Schema、JSON Schemaへ直接依存しない。

- Master Data Architecture: [#155](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/155)
- Save JSON Architecture: [#154](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)

### [戻る](../README.md#ドキュメント一覧)
