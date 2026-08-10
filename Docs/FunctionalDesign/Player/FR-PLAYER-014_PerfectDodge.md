# FR-PLAYER-014 ジャスト回避を実行できる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-PLAYER-014` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |
| 関連要件 | `FR-PLAYER-019`, `FR-PLAYER-015` |

## 2. 目的

Dodge Actionの高精度な成功結果としてPerfect Dodgeを判定し、Counterへ接続可能な報酬を提供する。

## 3. Action境界

Perfect Dodge専用のInput Action / Input Gameplay Tagは作りません。InputはDodgeのみで、Perfect DodgeはDodge実行中のEnemy Attackとの関係によって成立する結果です。

```text
[Dodge Action]
      ↓
[Perfect Dodge Window]
      + [Enemy Attack]
      ↓
[Perfect Dodge Result]
      +--> Result Tag / Gameplay Event
      +--> Target Enemy記録
      +--> Counter受付状態
      +--> Hit Stop / HUD Feedback
```

結果通知Tagは1種類へ固定せず、結果を利用するシステムごとに責務を分けて定義できます。

## 4. 判定仕様

- Perfect Dodge WindowとInvincible Windowは別パラメータ。
- Perfect Dodge Window内で対象となるEnemy Attack判定と重なった場合のみPerfect Result。
- Perfect Window外でもInvincible Window内なら通常回避としてNo Damageになり得る。
- 具体時間は調整可能なデータとする。

## 5. 成功処理

- スローモーションは使用しない。
- 短いHit Stopを使用する。
- HUDへ成功Feedbackを出す。
- Counter対象Enemyを記録する。
- Counter受付状態を開始する。
- Counterは強制しない。

## 6. 受入条件

- [ ] Perfect Dodge専用InputなしでDodge Actionから成立する。
- [ ] Perfect WindowとInvincible Windowを独立調整できる。
- [ ] Window外の通常回避をPerfect扱いしない。
- [ ] 成功時に対象Enemyと結果通知を取得できる。
- [ ] Counter受付終了時に一時状態が残らない。
- [ ] Perfect Dodge失敗がDodge Action自体の失敗を意味しない。

## 7. Issue管理

`FR-PLAYER-019`と`FR-PLAYER-014`は同じDodge Action親Issueで管理します。Perfect Dodgeは別の親Action Issueにせず、Dodge Action内の結果判定実装Issueとして扱います。
