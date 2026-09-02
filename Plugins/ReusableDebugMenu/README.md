# 再利用可能なデバッグメニュー

`ReusableDebugMenu` は、ホストプロジェクトのゲームプレイクラスやアセットに
依存せず、汎用的なデバッグメニューの動作を提供する Unreal Engine の Runtime
Plugin です。

## 依存方向

1. `FDebugMenuNodeDefinition` と `UReusableDebugMenuRegistry` が検証済みのメニュー
   データを保持します。
2. `UReusableDebugMenuSubsystem` が Local Player 単位のライフサイクルと Window の
   ユースケースを管理します。
3. UMG クラスが Registry の内容を描画し、ユーザー操作を Subsystem へ伝えます。
4. プロジェクト固有の PlayerController、Catalog、Window Blueprint はアダプターです。

ゲームプレイシステムは、特定の Root Widget や List Widget に直接依存しないでください。
安定した Node ID を登録し、プロジェクト固有の Window は外側の境界で実装します。

## 自動テストの使い方

`Source/ReusableDebugMenu/Private/Tests/DebugMenuRegistryTests.cpp` は、Registry の
ツリー検証を行う Unreal Automation Test です。Data Asset や UMG を読み込まず、次の
不正な登録が原子的に拒否され、既存データが壊れないことを確認します。

- 親が存在しないノード
- 自分自身を親にするノード
- 複数ノードによる循環参照
- 同一バッチ内の重複 `NodeId`
- 空の `DisplayName`
- `Command` を親にするノード

テストは `#if WITH_DEV_AUTOMATION_TESTS` で囲まれているため、Shipping ビルドには
含まれません。登録名は次のとおりです。

```text
ReusableDebugMenu.Registry.AdversarialValidation
```

### Unreal Editor から実行する

UE 5.7 では、単独の `Test Automation` メニューが表示されないレイアウトがあります。
次の手順で Automation 画面を開いてください。

1. メインメニューの **`Tools` セクションから `Session Frontend`** を開きます。
   （旧バージョンやレイアウトによっては `Window > Developer Tools > Session Frontend` と
   表示されます。日本語 UI では各メニュー名が翻訳表示されます。）
2. Session Frontend の **`Window > Automation`** タブを選択します。
3. 検索欄に `ReusableDebugMenu.Registry.AdversarialValidation` を入力して実行します。

エンジンのバージョンやレイアウトによっては `Tools > Test Automation` または
`Window > Test Automation` と表示される場合もあります。これらは同じ Automation 画面です。
コンソールからは次のコマンドでテストを列挙・実行できます。

```text
Automation List
Automation RunTests ReusableDebugMenu.Registry.AdversarialValidation
```

`Test Automation` と `Session Frontend` は **UnrealEditor.exe のエディタ専用 UI** です。
`UnrealEditor-Cmd.exe`、パッケージ化したゲーム、Game ターゲットで起動した場合は表示されません。
これらはプロジェクトの `Edit > Plugins` で個別に有効化するプラグインではなく、Editor に組み込まれた
`SessionFrontend`／`AutomationWindow` モジュールです。
Session Frontend 自体が見つからない場合は、Editor ターゲットの `UnrealEditor.exe` を起動し直し、
`Window > Load Layout > Default Editor Layout` でレイアウトを初期化してください。

### コマンドレット／CI から実行する

Editor を終了した状態で、プロジェクトルートから次を実行します。

```powershell
& "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Win64-DebugGame-Cmd.exe" `
  "C:\MyProjects\UE\Action_2\Action_2.uproject" `
  -unattended -nop4 -nullrhi -nosound `
  '-ExecCmds=Automation RunTests ReusableDebugMenu.Registry.AdversarialValidation; Quit' `
  '-TestExit=Automation Test Queue Empty'
```

終了コードが `0` で、ログに `Test Completed ... AdversarialValidation` と表示されれば成功です。
失敗時は `TestTrue`／`TestFalse` の説明を確認してください。CI ではこの終了コードを
ジョブの成否に使用します。同じプロジェクトを開いた Editor と同時に実行すると、モジュールや
Derived Data Cache のロック競合が起こるため、必ず Editor を終了してから実行してください。

このテストは Registry の純粋な検証だけを対象にします。`DA_DebugMenuCatalog` の実際の
`NodeId`、`WindowClass`、Widget の BindWidget 設定は検証しないため、Data Asset と PIE の
動作確認は別途行ってください。

## プロジェクトへの導入

1. `ReusableDebugMenu` ディレクトリ全体を対象プロジェクトの `Plugins` ディレクトリに
   コピーして、有効化します。
2. `UReusableDebugMenuListEntryWidget` を継承した Widget Blueprint を作成します。
   `entryTitleText` という名前の `TextBlock` が必須です。`selectorText` と
   `entryButton` は任意です。
3. `UReusableDebugMenuRootWidget` を継承した Widget Blueprint を作成します。
   `debugListView` という名前の `ListView` を配置し、Entry Widget Class に手順2の
   List Entry Blueprint を指定します。
4. 各プロジェクト固有の Window は `UReusableDebugMenuWindow` を継承して作成し、
   `UReusableDebugMenuCatalog` Data Asset の `Command` Node に割り当てます。
5. 所有する Local Player の PlayerController から
   `ULocalPlayer::GetSubsystem<UReusableDebugMenuSubsystem>()` の `Configure` を呼び、
   1つの Input Action を `ToggleMenu` にバインドします。

### Data Asset でメニューを定義する

プロジェクト固有のメニューは `UReusableDebugMenuCatalog` の Data Asset に定義します。

1. Content Browser で右クリックし、`Miscellaneous > Data Asset` を選択します。
2. クラスに `ReusableDebugMenuCatalog` を指定して、例えば
   `DA_DebugMenuCatalog` として保存します。
3. `Entries` 配列にメニュー項目を追加し、各項目の `Node` を設定します。
   `NodeId` はプロジェクト内で一意かつ安定した値にしてください。
4. `NodeType` が `Category` の項目は、子項目をまとめるだけのノードです。
   `ParentId` は空にするか、既存の Category の `NodeId` を指定します。
   **Category の `WindowClass` は必ず空にしてください。**
5. `NodeType` が `Command` の項目は実行可能なノードです。`ParentId` に既存の
   Category を指定し、`WindowClass` に `UReusableDebugMenuWindow` を継承した
   **具象** Widget Blueprint を割り当てます。Abstract クラスは使用できません。
6. `DisplayName` と `SortOrder` を設定して Data Asset を保存します。

設定例は次のとおりです。

| NodeId | ParentId | NodeType | WindowClass |
| --- | --- | --- | --- |
| `Action2.Player` | （空） | `Category` | （空） |
| `Action2.Player.Health` | `Action2.Player` | `Command` | `WBP_DebugMenuWindow` |

`BP_ActionPlayerController` では、次の3つを同じ設定にします。

- `Toggle Debug Menu Action`: `IA_DebugMenu`
- `Debug Widget Class`: `WBP_DebugRootWidget`
- `Debug Menu Catalog`: `DA_DebugMenuCatalog`

`WBP_DebugRootWidget` には `debugListView` という名前の `ListView` を配置し、
その Entry Widget Class に List Entry Blueprint を指定します。List Entry Blueprint
には `entryTitleText` という名前の `TextBlock` が必須です。名前が異なると Blueprint
コンパイルエラーになり、項目名が描画されません。

Node ID は動作を識別するキーであるため、安定させてください。`DisplayName` は自由に
ローカライズ・変更できます。Catalog に重複 ID、存在しない親、Category ではない親、
循環、無効な Window class、空のラベルが含まれる場合、Catalog 全体が原子的に拒否されます。

Subsystem は `AddToPlayerScreen` を使用するため、Local Player ごとに独立したメニューが
表示されます。Player Index 0 を前提にしません。Shipping build では Runtime 生成を無効化しています。

デフォルトでは、Subsystem は一時的に `FInputModeGameAndUI` を適用し、マウスカーソルを
表示して、閉じる際に `FInputModeGameOnly` へ戻します。既存の Input Mode stack を持つ
プロジェクトでは `bInManageInputMode = false` を渡し、独自のアダプターで Input を復元してください。
Pause については所有権を追跡し、Subsystem 自身が正常に Pause した場合にのみ解除します。

## 運用方法

### 基本方針

メニューの動作は `ReusableDebugMenu`、プロジェクト固有の設定はホストプロジェクト側で管理します。
通常の項目追加でプラグインのC++を変更する必要はありません。

- メニュー階層と表示名: `UReusableDebugMenuCatalog` Data Asset
- コマンド画面の見た目と処理: `UReusableDebugMenuWindow` 派生Widget Blueprint
- ルートと一覧行のレイアウト: `UReusableDebugMenuRootWidget`／
  `UReusableDebugMenuListEntryWidget` 派生Widget Blueprint
- 入力とLocal Playerへの接続: ホスト側のPlayerControllerアダプター

### 初回セットアップ

1. プロジェクトの `Plugins/ReusableDebugMenu` を有効にし、Editorターゲットを一度ビルドします。
2. Root Widget、List Entry Widget、必要なCommand WindowのBlueprintを作成します。
3. Catalog Data Assetを作成し、CategoryとCommandを登録します（詳細は「Data Assetでメニューを定義する」を参照）。
4. PlayerControllerの `Toggle Debug Menu Action`、`Debug Widget Class`、
   `Debug Menu Catalog` にアセットを割り当てます。
5. Input Mapping ContextをLocal Playerへ登録し、Toggle用Input Actionにキーを割り当てます。
6. Editorを再起動してからPIEで入力を確認します。

### 日常の変更手順

メニュー項目を追加・変更する場合は、次の順序で作業します。

1. 既存のCategoryを親にしてCatalogへ新しいCommandを追加します。
2. Command用の具象Window Blueprintを `WindowClass` に割り当てます。
3. `NodeId`、`ParentId`、`NodeType`、`DisplayName`、`SortOrder`を確認してData Assetを保存します。
4. PIEを再起動し、Toggleキー、Enter（決定）、Escape／BackSpace（戻る・閉じる）を確認します。
5. 問題がなければ `.uasset` と必要なC++変更を同じ変更単位でバージョン管理へ登録します。

`NodeId` は保存済みデータや外部コードから参照される識別子です。表示名を変更しても構いませんが、
既存の `NodeId` を名前変更や再利用に使わないでください。Categoryへ `WindowClass` を設定したり、
Commandの `WindowClass` を空にしたりするとCatalog全体が拒否されます。

### Window Blueprintの実装ルール

Window Blueprintでは、表示開始時の初期化を `On Debug Window Opened`、終了時の後処理を
`On Debug Window Closed` イベントにまとめます。画面内の閉じるボタンからは
`RequestClose` を呼び出してください。SubsystemがWindowの生成、表示順、終了、GCを管理するため、
Blueprint側で別のWindowを生成して保持しないでください。

### C++から動的に登録する場合

Data Assetを使わず、ホスト側のユースケースで動的に登録することもできます。
`Configure` を先に呼び、Categoryは `RegisterNodes`、Commandは具象Windowと一緒に
`RegisterWindowNode` を呼び出します。エラー時は登録されず、既存のRegistryは変更されません。

```cpp
FText Error;
Subsystem->Configure(RootWidgetClass, nullptr, true, true);
Subsystem->RegisterNodes(CategoryNodes, Error);
Subsystem->RegisterWindowNode(CommandNode, WindowClass, Error);
```

`RegisterNodes` にCommandを渡すことはできません。複数ノードを一括登録する場合は、親を含む全ノードを
同じ配列に入れ、登録成功を確認してから次の処理へ進めてください。

### Action_2でのファイル管理

現在の `Action_2` は、旧 `Source/Action_2/Debug` 実装ではなく、`ReusableDebugMenu` と
`ActionPlayerController` のアダプターを使用します。新しいデバッグ項目を追加するときは、旧フォルダへ
互換クラスを戻さず、次のいずれかで実装してください。

- 表示だけの変更: Content内のWidget Blueprintを編集
- 項目の追加・並べ替え: `DA_DebugMenuCatalog` を編集
- プロジェクト固有の入力・登録: PlayerControllerアダプターを編集
- 他プロジェクトでの再利用: 各プロジェクトに薄いアダプターを作り、プラグイン本体は変更しない

Action_2のアダプターはCatalogが無効または空の場合、6つの既定Categoryへフォールバックします。
これはCommand Windowを復元する処理ではないため、ログのCatalogエラーを修正してから運用してください。

## トラブルシューティング

`Category 'Player' must not specify a window adapter` が出た場合は、Catalog の
`Player` エントリの `Node Type` を `Category` にし、`Window Class` を空にします。
`Window Class` を指定できるのは `Command` エントリだけです。1つでも不正なエントリが
あると、誤ったメニューを表示しないため Catalog 全体が拒否されます。

ホスト側のアダプターは Catalog が拒否された場合にデフォルトの Category を登録して
メニューを開けるようにできます。ただし Command の Window は復旧しないため、ログに
出た Catalog のエラーを修正してください。

トグル用 Input Action は `Started` にバインドしてください。`Triggered` はキーを押して
いる間、毎フレーム通知されるため、表示直後に再度 Toggle されることがあります。

### 「ゲームは停止するがメニューが見えない」場合

この症状は、画面に項目がない状態でも Widget の追加後に `SetPause(true)` が成功するため発生します。
`DA_DebugMenuCatalog` が上記の理由で拒否されると Registry に項目が登録されず、
Root Widget の ListView が空になります。その状態でも Widget の背景が見えないレイアウト
なら、ゲームだけが停止したように見えます。Catalog のエラーを直してから PIE を再起動
してください。

Action_2 の PlayerController アダプターは、Catalog が拒否された場合にデフォルトの
Category を登録するフォールバックを持っています。ただし、これは Command の Window
を復元するものではありません。修正後もエラーが出る場合は、エディタを一度終了して
から C++ を再ビルドし、古いモジュールが残らない状態で起動してください。

## C++ 再ビルド時の Data Asset 保護

Data Asset の内容は `Content` 配下の `.uasset` に保存されます。通常のフルビルドで
内容が消えることはありません。ただし、次の反射型を変更した状態で `Live Coding` や
`Hot Reload` を実行すると、UE が一時的な `LIVECODING_*` 構造体を作成します。

- `USTRUCT` の追加・削除・変更
- `UCLASS`、`UENUM`、`UPROPERTY` の型・名前の変更
- Data Asset が参照する構造体の移動・リネーム

この状態で `Struct Property ... type mismatch` または `Array Inner Type mismatch` が
表示された場合、Data Asset を保存しないでください。再インスタンス化された一時オブジェクト
の初期値で `.uasset` を上書きする危険があります。

安全な手順は次のとおりです。

1. PIE を停止します。型不一致の警告が出ていなければ Data Asset を保存します。警告が
   出ている場合は保存せず、そのまま Editor を終了します。
2. `Content/Project/Debug/Widgets/DA_DebugMenuCatalog.uasset` をバックアップするか、
   バージョン管理にコミットします。
3. Unreal Editor を完全に終了します。Live Coding のコンソールも終了させます。
4. Editor を閉じた状態で通常の C++ フルビルドを実行します。
5. Editor を再起動し、Data Asset の内容を確認してから PIE を開始します。

反射型を頻繁に変更する間は、`Editor Preferences > General > Live Coding > Enable Live Coding`
を一時的に無効にしておくと、同じ事故を防ぎやすくなります。

反射型を変更する必要がある場合は、既存の `UPROPERTY` 名と型をできるだけ維持し、
新しいプロパティは末尾に追加してください。名前を変更する場合は `CoreRedirects` を
用意し、変更直後に Data Asset を開いて保存し直します。すでに内容が消えた場合は、
上記バックアップまたはソース管理から `.uasset` を戻し、最終的な C++ 型で Editor を
再起動してから再保存してください。
