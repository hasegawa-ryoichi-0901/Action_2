# FR-PLAYER-007 LockOn対象を切り替えられる

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | [`FR-PLAYER-007`](../../01_Requirements.md#fr-player-007) |
| 優先度 | `Must` |
| 対応範囲 | `α版` |
| 設計状態 | `Draft` |
| 関連Issue | [#79](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/79), [#80](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/80), [#81](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/81) |
| 関連要件・設計 | [`FR-PLAYER-006`](../../01_Requirements.md#fr-player-006), [`FR-PLAYER-021`](../../01_Requirements.md#fr-player-021) |

## 2. 目的

複数Enemyが存在する状況で、LockOnを解除せずPlayerが左右の別Targetへ切り替えられるようにする。

## 3. 確定仕様・スコープ

- LockOn中のみTarget Switchを受け付ける。
- Camera Lookとは別の専用左右Inputを使用する。
- 左右方向に対応する有効候補へCurrent Targetを更新する。
- 無効 / Defeated Targetを候補にしない。

## 4. 基本フロー

```text
Target Switch Input Left / Right
↓
LockOn中確認
├ No → Reject
└ Yes
  ↓
指定方向の候補検索
  ├ なし → Current Target維持
  └ あり → Current Target更新
             ↓
          Camera / Marker更新
```

## 5. 責務

| 対象 | 責務 |
|---|---|
| Input層 | 左右専用Input配送 |
| Targeting | 左右候補選択・Current Target更新 |
| Camera / HUD | 新Targetへ追従先・Marker更新 |

## 6. 状態 / Gameplay Tag

Manual LockOn中であることを実行条件とする。Target Switch専用の継続State Tagは不要。

## 7. 必要データ

| データ | 用途 | 備考 |
|---|---|---|
| Switch Direction | 左右判定 | Runtime |
| Candidate Targets | 切替候補 | Runtime |
| Current Target | 現在Target | Runtime |
| Search Range / Screen Direction Rule | 候補選択 | 調整値 |

## 8. UI / HUD / Animation / Feedback

| 種別 | 内容 |
|---|---|
| UI / HUD | LockOn Markerを新Targetへ更新する |
| Camera | Current Target更新後に追従先を切り替える |

## 9. 異常系・終了条件

- 候補なしではCurrent Targetを維持する。
- Switch中にCurrent Targetが死亡した場合は`FR-PLAYER-006`のUnlock Ruleを優先する。
- Input再Setupで左右Inputを重複Bindingしない。

## 10. 受入条件

- [ ] LockOn中だけ左右専用Inputで切替できる。
- [ ] 左右方向に対応する有効Targetへ更新できる。
- [ ] 候補なしでCurrent Targetが不正値にならない。
- [ ] Camera / Markerが新Targetへ同期する。

## 11. 依存・Issue反映

### 依存
- [#75 Manual LockOn](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/75)

### Issue反映
- [#79](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/79)を親Issue、[#80](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/80)をInput、[#81](https://github.com/hasegawa-ryoichi-0901/Action_2/issues/81)を候補選択 / Target更新として扱う。

## 12. 未決事項

なし
