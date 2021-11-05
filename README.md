# HACK TO THE FUTURE 2022 予選
https://atcoder.jp/contests/future-contest-2022-qual

## What is this repository?

私が個人で参加した時に利用したものです。
考察日記、ソースのバージョン管理を目的としています。

## ルール

タスクとタスク処理班がいる。タスク処理班には技能レベルがあり、タスクには要求技能レベルがある。タスク処理メンバーとタスクの要求技能レベルとの差に応じて処理時間が決まる。処理時間は要求技能レベルが高い場合の差の和に、±3の誤差が加わって計算される。

### 入力
N:タスク数。
M:メンバー数。
K:技能数。
R:依存関係数。
d[i][j]:i番目のタスクのj番目の技能の要求レベル
u, v:依存するタスクの組みのリスト。vがuに依存しており、vを開始する前にvが完了していなければならない。

### 出力
1日ごとに出力する。1日ごとに、出力後の入力を受け取る。
出力:その日にタスクを開始するメンバーと担当タスクの組みのリスト。
入力:その日の終わりにタスクを完了したメンバーのリスト。


## 考察

### 1日目(11/4)

入出力の制約を満たすところで終了。

### 2日目(11/5)

まずは貪欲に割り振ってどんな結果になるか考察してみる。

前から単純に割り振ると大勢が到達している'81084'になった。

あるタスクをあるメンバーが担当したら、何日かかった。
なので、このタスクはこのメンバーが担当するべきである。
という評価を下す。


