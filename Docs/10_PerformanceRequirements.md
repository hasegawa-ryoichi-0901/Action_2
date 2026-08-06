# 10. パフォーマンス要件

## 1. 目標

### 必須

- 60fpsを安定維持する
- 進行中に大きなカクつきを発生させない
- ボス戦でフレーム時間を安定させる

### 挑戦

- 120fps
- 1080pを基準とした高フレームレート動作

## 2. 基準環境

現時点の開発・検証基準はRTX 3060程度のPCです。

最低動作環境として公開する具体的なCPU、GPU、メモリ、品質設定は、Vertical Sliceの計測後に確定します。

## 3. フレーム時間

```text
60fps  = 約16.67ms / frame
120fps = 約 8.33ms / frame
```

平均fpsだけでなく、次を記録します。

- Game Thread
- Render Thread
- GPU
- 1% Low相当の落ち込み
- メモリ使用量
- ロード時間
- シェーダーコンパイル由来の停止
- 敵数増加時のAI負荷
- Niagara負荷
- Animation負荷

## 4. 計測地点

```text
Test_01 : プレイヤーのみ
Test_02 : 近接敵1体
Test_03 : 近接敵2体
Test_04 : 近接敵2体 + 遠距離敵
Test_05 : 最大通常戦
Test_06 : ボスPhase1
Test_07 : ボスPhase2
Test_08 : エフェクト最大時
```

## 5. 使用候補

- Unreal Insights
- `stat unit`
- `stat gpu`
- `stat game`
- `stat anim`
- `stat niagara`
- GPU Visualizer
- Memory Insights
- Animation Insights

## 6. 設計ルール

- 常時Tickを避ける
- AIの高頻度評価を必要最小限にする
- 攻撃評価を毎フレーム実行しない
- 遠距離や非戦闘の敵は更新頻度を下げる
- Soft Referenceと非同期ロードを検討する
- VFXに品質段階を設ける
- アセットのLODを確認する
- 高負荷なControl Rig処理をランタイムで無制限に使用しない
- Mover採用時は移動シミュレーション負荷を比較する

### [戻る](../README.md#ドキュメント一覧)
