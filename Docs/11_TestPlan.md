# 11. テスト計画

## 1. 単体・機能テスト

- `IPlayerInputComponent` Setup / Teardown / Input Tag重複検出
- Move / Look / LockOn / Target Switch Input
- Light Attack / Heavy Attack / Combo Attack
- Dodge Action（Roll / Back Step / Invincible / Perfect Result）
- Stamina消費・回復・Exhausted
- Player Health / Death
- Enemy / Boss Health / Defeat
- Upgrade Material / Gold所持値
- Weapon Upgrade Cost判定
- DeathDrop生成・回収・再死亡
- Checkpoint / Save Request
- Stage Clear Trigger / Ending
- AI Attack評価

## 2. Input・Lifecycle

```text
TC-INPUT-001
前提 : Input ComponentがPlayerへアタッチ済み
操作 : SetupPlayerInputComponent
期待 : 各IPlayerInputComponent::SetupがInputTagごとに1回有効化される

TC-INPUT-002
前提 : 同一InputTagのComponentが複数
操作 : SetupPlayerInputComponent
期待 : 重複登録せず設定不備をLogへ記録する

TC-INPUT-003
操作 : UnPossessed → Possess → Setup
期待 : 古いBindingが残らず入力が重複発火しない
```

## 3. Dodge

```text
TC-DODGE-001
前提 : Grounded / Stamina十分 / 移動入力あり
操作 : Dodge
期待 : 入力方向へRollする

TC-DODGE-002
前提 : Grounded / Stamina十分 / 移動入力なし
操作 : Dodge
期待 : 後方へBack Stepする

TC-DODGE-003
前提 : Airborne
操作 : Dodge
期待 : Dodgeを開始しない

TC-DODGE-004
前提 : Enemy AttackがInvincible Window内、Perfect Window外
期待 : No DamageだがPerfect Resultにならない

TC-DODGE-005
前提 : Enemy AttackがPerfect Window内
期待 : Perfect Dodge Resultを1回通知する
```

- Invincible WindowとPerfect Dodge Windowを独立調整できる。
- Dodge中にEnemy Collisionを通過しない。
- Perfect Dodge専用Inputが存在しない。

## 4. Attack

- Light Attack単体でInput → Ability → Stamina → Montage → Hit → Damageが成立する。
- Heavy AttackはLightとは別Input / Actionとして成立する。
- ComboはLight / Heavy単体完成後にWindowとInput Bufferを介して接続する。
- Hitbox Active Window外ではDamageを発生させない。
- 同一Swingで不正な多重Hitを発生させない。
- Cancel / Death後にAttack Tag、Collision、Input Bufferが残らない。

## 5. LockOn / Camera

- 非LockOn時はMouse / GamepadでYaw / Pitch操作できる。
- LockOn中のみCameraがCurrent Targetへ追従する。
- LockOn中は通常Camera Lookを無効化する。
- 同じLockOn入力でもう一度押すと解除する。
- Target SwitchはCamera Lookと別のLeft / Right専用入力を使用する。
- Current Target死亡・無効化時は別Targetへ自動切替せずLockOnを解除する。
- Player Death中もCamera Lookできる。

## 6. Enemy / Boss Reward

### Normal Enemy

- HP0でDefeatedへ1回だけ遷移する。
- AI / Attack Ability / 攻撃枠を終了する。
- Enemy1体につきUpgrade MaterialとGoldを1回だけ直接加算する。
- Reward World Dropを生成しない。

### Boss

- HP0でDefeatedへ1回だけ遷移する。
- AI / Abilityを停止する。
- Goldを直接加算する。
- 初回討伐時のみ固有収集ItemをInventoryへ直接付与する。
- 通常のUpgrade Materialを付与しない。
- Reward確定後にAuto Saveする。

## 7. DeathDrop / Respawn

```text
TC-DEATH-001
前提 : Material=100, Gold=1000
操作 : Player死亡
期待 : Death Animation後、DeathDropにMaterial=100、Gold=700を格納し、Gold=300は消失する

TC-DEATH-002
前提 : 未回収DeathDrop Aあり
操作 : Player再死亡
期待 : A本体とA内部Resourceが完全消失し、現在所持Resourceから新DeathDrop Bを生成する

TC-DEATH-003
前提 : 未回収DeathDropあり
操作 : DeathDrop回収
期待 : 格納Material / Goldを全量返却しDropを消去、直後にAuto Saveする
```

- DeathDrop位置・内容確定後にAuto Saveし、その後Camera確認・Fade Outへ進む。
- ActiveCheckpointがあればそこへRespawnする。
- 未設定ならPlayerStartへRespawnする。
- Respawn時にHP / Stamina / Healing Itemを全回復する。
- 通常敵を復活させる。
- Save/Load後も未回収DeathDropを1つだけ復元できる。

## 8. Checkpoint / Weapon Upgrade

- Checkpointへ近づくだけではSaveしない。
- Checkpointを操作してMenu Openした時にActiveCheckpoint更新後の状態をAuto Saveする。
- Checkpoint利用でHP / Stamina回復、Healing Item補充、通常敵復活を確認する。
- Checkpoint MenuからManual Saveできる。
- Weapon UpgradeはCheckpointでのみ可能。
- GoldまたはUpgrade Material不足時は両Resourceを消費しない。
- 成功時はGold + Materialを消費してWeapon Levelを更新する。
- Weapon Upgrade完了自体ではAuto Saveしない。

## 9. Stage Clear

- Boss生存中にClear Triggerへ入ってもEndingを開始しない。
- Boss Reward / Auto Save完了後にClear Triggerを有効化できる。
- Boss撃破直後に自動でEndingへ入らない。
- Clear Trigger進入でEnding Sequenceを1回だけ開始する。
- Ending SequenceをSkipできる。
- 通常終了 / SkipのどちらでもTitleへ戻る。
- Stage Clear自体では追加Auto Saveしない。

## 10. Save

確認する進行Auto Save契機：

- Checkpoint Menu Open
- DeathDrop生成内容確定
- DeathDrop回収完了
- Boss Reward付与完了

追加確認：

- Checkpoint Manual Save
- Settings変更時Save
- Weapon Upgrade / Stage Clearでは不要なAuto Saveが発生しない
- 同一EventからSave Requestが重複発火しない
- 保存失敗時にGameplay状態を破壊しない

JSON / Steam Cloud等の永続化方式固有テストは別Architecture Design作成後に追加します。

## 11. 性能・品質

- 各計測地点で60fpsを確認する。
- Boss Phase2でFrame Timeを確認する。
- 長時間PlayでMemory増加を確認する。
- Shipping Buildで最終確認する。
- Gamepad / Keyboard-Mouse双方でInitial Vertical Sliceを完走する。

### [戻る](../README.md#ドキュメント一覧)
