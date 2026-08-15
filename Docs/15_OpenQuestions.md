# 15. 未確定事項・プロトタイプ検証項目

本ドキュメントは、確定済み仕様と混同しないよう、今後の数値調整・Asset依存・Post-VS検証事項のみを管理します。

## 1. α版で残る調整事項

以下は基本仕様を変更せず、実装・Play Test中に調整可能な項目です。

### Dodge

- Invincible Windowの具体時間
- Perfect Dodge Windowの具体時間
- Roll移動距離・時間
- Back Step移動距離・時間
- Roll / Back Step Animation Asset

Dodge方向、無入力時Back Step、Air使用不可、Enemy Collision非通過、Invincible WindowとPerfect Dodge Windowの分離は確定済みです。

### Combat

- Max Stamina
- Stamina Recovery Delay
- Exhausted Recovery Threshold
- Counter受付時間
- Parry受付時間
- Parry Failure Recovery
- 各AttackのDamage / Posture Damage / Stamina Cost

### Camera / Targeting

- Mouse / Gamepad Sensitivity
- Pitch Clamp
- Y軸反転設定をα版へ追加するか
- LockOn最大距離
- 遮蔽による解除時間
- Camera Collision / SpringArmの最終調整値

LockOn中のCamera Look無効、Target追従、専用左右InputによるTarget Switch、対象死亡時の自動Lock解除は確定済みです。

### Enemy / Boss

- Normal Enemy最大同時出現数
- Ranged Attack Slot最大数
- Posture Recovery Rate
- Boss各AttackのScore調整値
- Enemy / BossのReward量

Rewardの種類と付与タイミングは確定済みです。

## 2. Stage ClearのMap・演出依存事項

進行ロジックは確定しています。

```text
Boss Defeat
↓
Reward Grant
↓
Auto Save
↓
Clear AreaのCollisionへ進入
↓
Skippable Ending Sequence
↓
Title
```

Map制作時に決定する事項：

- Clear Areaを城 / 洞窟 / 祠等のどの表現にするか
- Clear Triggerの具体座標・形状
- Ending Sequenceの映像・Camera・Text・Animation

これらはStage Clearの進行ロジックIssue作成・実装開始の前提条件にはしません。

## 3. Mover — 将来検証

現行実装はCharacterMovementを使用します。Moverはα版の必須依存ではありません。

Mover採用の具体的メリットが確認されるまで、`IMovementDriver`や`UMovementAdapterComponent`等の抽象化を先行追加しません。採用する場合もCombat層へMover固有型・APIを直接依存させません。

## 4. Axe — Post-VS

- Guard / Receiveの最終方式
- Guard中Stamina消費
- Guard Break
- Super Armor対象Attack
- Heavy Branchの具体Combo
- 各Attackの速度・Damage・Posture Damage

## 5. Bow — Post-VS

- 通常Attackを3段Comboにするか連続射撃にするか
- ProjectileとLine Traceの最終分担
- Weak Point倍率・判定表現
- Shoulder Aim時のMovement Speed
- Distance Falloff Curve
- Bow Counterの具体挙動

## 6. Asset依存

- 世界観：現代都市 / 近未来 / ファンタジー
- 最初のBoss：人型 / 獣型 / 大型怪物
- Boss Intro演出

## 7. Animation機能

使用候補：Animation Blueprint、Animation Montage、Motion Warping、Root Motion、Control Rig、IK Retargeter、Full Body IK、Pose Warping。

各機能は「何の問題を解決するために採用したか」を記録します。

## 8. 永続化・Master Data Architecture

Gameplay上の挙動とは分離して次を管理します。

- JSON Save Architecture: [#154](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/154)
- CSV / Master Data Architecture: [#155](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/155)
- Steam Cloud同期方式: Post-VS

## 9. Online / Steam

α版ではOnline、Network同期、EOS、Steam Cloudを対象外とします。Steam公開版でSteam Cloud、Achievement、Localization等を再評価します。

### [戻る](../README.md#ドキュメント一覧)
