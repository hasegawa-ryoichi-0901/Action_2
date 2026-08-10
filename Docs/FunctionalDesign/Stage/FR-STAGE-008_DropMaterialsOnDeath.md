# FR-STAGE-008 死亡時に回収対象ResourceをDeathDropへ移す

## 1. 基本情報

| 項目 | 内容 |
|---|---|
| 要件ID | `FR-STAGE-008` |
| 優先度 | `Must` |
| 対応範囲 | 初期Vertical Slice |
| 設計状態 | `Review` |

## 2. 基本フロー

```text
[Death Animation完了]
      ↓
[旧DeathDrop処理]
      ↓
[現在所持Resource計算]
      +--> Upgrade Material 100% → DeathDrop
      +--> Gold 70%             → DeathDrop
      +--> Gold 30%             → 消失
      ↓
[死亡座標にDeathDrop生成]
      ↓
[位置・内容確定]
      ↓
[Auto Save]
```

## 3. 確定仕様

- Upgrade Materialは現在所持量の100%を格納する。
- Goldは現在所持量の70%を格納し、30%を永久消失させる。
- DeathDropはPlayer死亡座標に生成する。
- DeathDrop状態確定後、Camera確認・Respawnより前にAuto Saveする。
- 保存方式は別Architecture Designで扱う。

## 4. 受入条件

- [ ] Death Animation完了後にDeathDropを生成する。
- [ ] Material全量がPlayer所持値からDeathDropへ移る。
- [ ] Gold70%のみDeathDropへ移り、残り30%は回収不能になる。
- [ ] DeathDrop生成前後でResourceが複製されない。
- [ ] DeathDrop確定後にAuto Save要求を1回発行する。
