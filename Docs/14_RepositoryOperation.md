# 14. Gitリポジトリ運用

## 1. 公開範囲

- リポジトリは非公開
- 応募先企業へ限定公開
- 購入アセットの再配布を行わない
- アセットのライセンス条件を別資料で管理する

## 2. 推奨構成

```text
ProjectRoot/
|
+-- README.md
+-- Docs/
+-- Config/
+-- Content/
+-- Plugins/
+-- Source/
+-- ProjectName.uproject
```

## 3. Git LFS候補

```text
*.uasset
*.umap
*.fbx
*.wav
*.mp4
*.psd
*.png
*.tga
```

Git LFSは利用可能な無料枠の範囲から開始し、容量を継続的に確認します。

## 4. 除外候補

```text
Binaries/
DerivedDataCache/
Intermediate/
Saved/
.vs/
.idea/
.vscode/
```

`.vscode/`は共有設定を使用する場合のみ必要ファイルを選択して管理します。

## 5. ブランチ

```text
main
  |
  +-- develop
         |
         +-- feature/player-combat
         +-- feature/gas
         +-- feature/enemy-ai
         +-- feature/boss-ai
         +-- feature/save-system
         +-- feature/ui
         +-- feature/performance
```

個人開発でも、機能単位で差分を確認できるようにします。

## 6. コミット

```text
feat: 剣の通常攻撃Abilityを追加
fix: パリィ失敗時に攻撃権が残る問題を修正
refactor: 攻撃評価をEnemyAttackEvaluatorへ分離
docs: GASクラス構成図を更新
test: スタミナ枯渇テストを追加
perf: ボス攻撃評価の更新頻度を削減
```

## 7. タグ

```text
prototype-movement
prototype-combat
vertical-slice-0.1
portfolio-build-0.1
steam-demo-0.1
```

## 8. アセット管理

購入アセットごとに次を記録します。

```text
Asset Name
Marketplace / Seller
Purchase Date
License
Commercial Use
Redistribution Restriction
Modified Files
Project Usage
Credit Requirement
```

## 9. READMEへ記載する注意

- 購入アセットを含むためリポジトリの再配布は禁止
- ソースコードの閲覧目的
- 使用エンジンバージョン
- 必要プラグイン
- ビルド手順
- 操作方法
- 既知の問題

### [戻る](../README.md#ドキュメント一覧)
