# 07. クラス設計

## 1. 全体構成

```text
+------------------------------------------------------+
| AActionGameMode                                      |
|------------------------------------------------------|
| ステージルール                                       |
| プレイヤースポーン                                   |
| クリア・再開管理                                     |
+---------------------------+--------------------------+
                            |
                            v
+------------------------------------------------------+
| AActionPlayerController                              |
|------------------------------------------------------|
| 入力モード                                           |
| 操作デバイス変更                                     |
| 手動ロックオン入力                                   |
| HUD接続                                              |
+---------------------------+--------------------------+
                            |
            +---------------+---------------+
            |                               |
            v                               v
+---------------------------+   +---------------------------+
| AActionPlayerState        |   | AActionPlayerCharacter    |
|---------------------------|   |---------------------------|
| AbilitySystemComponent    |<->| ASC Avatar                |
| AttributeSet              |   | Mesh / Collision          |
| 永続プレイヤー状態        |   | Components保持            |
+---------------------------+   +-------------+-------------+
                                              |
       +----------------+---------------------+------------------+
       |                |                     |                  |
       v                v                     v                  v
+-------------+  +--------------+   +----------------+  +----------------+
| CombatComp  |  | TargetComp   |   | InputBuffer   |  | MovementAdapter|
+-------------+  +--------------+   +----------------+  +----------------+
```

## 2. プレイヤークラス

```text
AActionPlayerCharacter
    |
    +-- UCombatComponent
    |       |
    |       +-- 装備武器管理
    |       +-- 攻撃対象管理
    |       +-- 致命攻撃判定
    |
    +-- UTargetingComponent
    |       |
    |       +-- ソフトロック
    |       +-- 手動ロック
    |       +-- 対象切り替え
    |       +-- 遮蔽判定
    |
    +-- UInputBufferComponent
    |       |
    |       +-- 入力保存
    |       +-- 有効期限
    |       +-- 優先順位
    |       +-- 消費
    |
    +-- UMovementAdapterComponent
    |       |
    |       +-- IMovementDriverへ委譲
    |
    +-- UInteractionComponent
    |       |
    |       +-- チェックポイント
    |       +-- 素材回収
    |
    +-- UHealthPresentationComponent
            |
            +-- HP表示通知
            +-- スタミナ表示通知
            +-- カウンター表示通知
```

## 3. 移動抽象化

```text
+-----------------------------------+
| IMovementDriver                   |
|-----------------------------------|
| Move                              |
| Jump                              |
| Dodge                             |
| StopMovement                      |
| RequestFacing                     |
| ApplyMovementAction               |
| IsGrounded                        |
+----------------+------------------+
                 |
      +----------+----------+
      |                     |
      v                     v
+-------------------+  +-------------------------+
| UMoverDriver      |  | UCharacterMovementDriver|
+-------------------+  +-------------------------+
```

Moverは段階導入とします。

```text
[移動プロトタイプ]
      |
      v
[Moverで2～3週間検証]
      |
      +-- 採用可能 --> [MoverDriver継続]
      |
      +-- 問題あり --> [CharacterMovementDriverへ移行]
```

## 4. 武器クラス

```text
+----------------------------------+
| AWeaponActor                     |
|----------------------------------|
| Weapon Mesh                      |
| Hit Collision                    |
| WeaponDefinition参照             |
+----------------+-----------------+
                 |
                 v
+----------------------------------+
| UWeaponDefinition                |
| PrimaryDataAsset                 |
|----------------------------------|
| WeaponType                       |
| AbilitySet                       |
| ComboDefinition                  |
| StaminaCost                      |
| StaggerResistance               |
| PostureDamageMultiplier          |
| DodgeDefinition                  |
| CounterWindowDuration            |
+----------------------------------+
```

## 5. 敵クラス

```text
+----------------------------------+
| AEnemyCharacter                  |
|----------------------------------|
| AbilitySystemComponent           |
| AttributeSet                     |
| EnemyDefinition                  |
| CombatComponent                  |
| PerceptionContext                |
+----------------+-----------------+
                 |
      +----------+----------+
      |                     |
      v                     v
+-------------------+  +------------------------+
| AEnemyAIController|  | UEnemyCombatComponent  |
+-------------------+  +------------------------+
                               |
                               v
                      +------------------------+
                      | UEnemyAttackEvaluator  |
                      +------------------------+
```

## 6. ボスAI

```text
+----------------------------------+
| ABossAIController                |
|----------------------------------|
| StateTreeComponent               |
| AttackEvaluator                  |
| ActionHistory                    |
| DebugPresenter                   |
+----------------+-----------------+
                 |
                 v
+----------------------------------+
| UEnemyAttackEvaluator            |
|----------------------------------|
| BuildContext                     |
| ScoreAttack                      |
| SelectAttack                     |
| RecordResult                     |
+----------------+-----------------+
                 |
                 v
+----------------------------------+
| UEnemyAttackDefinition           |
| PrimaryDataAsset                 |
|----------------------------------|
| AbilityClass                     |
| Range                            |
| Angle                            |
| BaseScore                        |
| Cooldown                         |
| ComboBranches                    |
| AttackTags                       |
| PostureDamage                    |
+----------------------------------+
```

## 7. チェックポイント・死亡

```text
+----------------------------------+
| ACheckpointActor                 |
|----------------------------------|
| CheckpointId                     |
| Rest                             |
| RefillHealingItems               |
| OpenWeaponMenu                   |
| Save                             |
| RespawnEnemies                   |
+----------------+-----------------+
                 |
                 v
+----------------------------------+
| UCheckpointSubsystem             |
|----------------------------------|
| ActiveCheckpointId               |
| RegisterCheckpoint              |
| RespawnPlayer                    |
| ResetEnemies                     |
+----------------------------------+

+----------------------------------+
| ADeathDropActor                  |
|----------------------------------|
| DroppedMaterialAmount            |
| SourceDeathId                    |
| Recover                          |
| DestroyPreviousDrop              |
+----------------------------------+
```

## 8. セーブ

```text
+----------------------------------+
| UActionSaveGame                  |
|----------------------------------|
| SaveVersion                      |
| ActiveCheckpointId               |
| PlayerProgress                   |
| WeaponUpgradeStates              |
| UpgradeMaterial                  |
| HealingItemState                 |
| SettingsReference                |
+----------------------------------+

+----------------------------------+
| USaveGameSubsystem               |
|----------------------------------|
| Save                             |
| Load                             |
| MigrateVersion                   |
| ValidateData                     |
| Backup                           |
+----------------------------------+
```

### [戻る](../README.md#ドキュメント一覧)
