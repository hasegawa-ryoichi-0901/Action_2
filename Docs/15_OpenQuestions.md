# 15. 未確定事項・プロトタイプ検証項目

本ドキュメントは、確定済み仕様と混同しないよう、今後の数値調整・アセット依存・Post-Vertical Slice検証事項のみを管理します。

## 1. 初期Vertical Sliceで残る調整事項

以下は基本仕様を変更せず、実装・プレイテスト中に調整可能な項目です。

### Dodge

- Invincible Windowの具体時間
- Perfect Dodge Windowの具体時間
- Roll移動距離・時間
- Back Step移動距離・時間
- Roll / Back Step Animation Asset

Dodge方向、無入力時Back Step、空中使用不可、敵Collision非通過、Invincible WindowとPerfect Dodge Windowの分離は確定済みです。

### Combat

- Stamina最大値
- Stamina回復開始遅延
- 息切れ解除閾値
- Counter受付時間
- Parry受付時間
- Parry失敗硬直
- 各AttackのDamage / Posture Damage / Stamina Cost

### Camera / Targeting

- Mouse / Gamepad感度
- Pitch Clamp
- Y軸反転設定を初期Vertical Sliceへ含めるか
- LockOn最大距離
- 遮蔽による解除時間
- Camera Collision / SpringArmの最終調整値

ロックオン中のCamera Look無効、Target追従、専用左右入力によるTarget Switch、対象死亡時の自動Lock解除は確定済みです。

### Enemy / Boss

- 通常敵最大同時出現数
- 遠距離攻撃枠の最大数
- 体勢値回復速度
- Boss各Attackの評価値
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

今後Map制作時に決定する事項：

- Clear Areaを城 / 洞窟 / 祠等のどの表現にするか
- Clear Triggerの具体座標・形状
- Ending Sequenceの映像・Camera・Text・Animation

これらはStage Clearの進行ロジックIssue作成を妨げません。

## 3. Mover — 将来検証

現行実装はCharacterMovementを使用します。Moverは初期Vertical Sliceの必須依存ではありません。

Mover採用の具体的メリットが確認されるまで、`IMovementDriver`や`UMovementAdapterComponent`等の抽象化を先行追加しません。採用する場合もCombat層へMover固有型・APIを直接依存させません。

## 4. 斧 — Post-Vertical Slice

- Guard / Receiveの最終方式
- Guard中Stamina消費
- Guard Break
- Super Armor対象Attack
- Heavy Branchの具体Combo
- 各Attackの速度・威力・体勢削り

## 5. 弓 — Post-Vertical Slice

- 通常攻撃を3段Comboにするか連続射撃にするか
- ProjectileとLine Traceの最終分担
- Weak Point倍率・判定表現
- 肩越し照準時の移動速度
- 距離減衰曲線
- Bow Counterの具体挙動

## 6. アセット依存

- 世界観：現代都市 / 近未来 / ファンタジー
- 最初のBoss：人型 / 獣型 / 大型怪物
- Boss登場演出

## 7. アニメーション機能

使用候補：Animation Blueprint、Animation Montage、Motion Warping、Root Motion、Control Rig、IK Retargeter、Full Body IK、Pose Warping。

各機能は「何の問題を解決するために採用したか」を記録します。

## 8. 永続化・Master Data Architecture

JSONによるPlayer Data、DeathDrop永続化の具体形式、独自Master Data Reader、Steam Cloud同期方式はゲーム要件とは分離し、別Architecture Designで定義します。本ドキュメントでは実装方式を確定しません。

## 9. オンライン / Steam

初期Vertical Sliceではオンライン、Network同期、EOS、Steam Cloudを対象外とします。Steam公開版でSteam Cloud、実績、対応言語等を再評価します。

### [戻る](../README.md#ドキュメント一覧)
