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

### 3日目(11/6)
ビジュアライズ結果を見てみると
タスクに依存関係がある関係で、いい感じに割り振らないと
途中20個以上アサインできるタスクが存在しないみたいになるっぽい。

シンプルな実装が強いのは、
依存関係が基本的に数字の小さい方を先に終わらせないと
数字の大きいものを処理できないみたいになってるから。

先に数字の大きいものを処理してしまうと、手待ちが発生しがち。

手待ち時間最小化問題っぽいですね〜〜〜〜〜〜〜。

案としては、
1. タスク依存関係グラフをトポロジカルソートする
1. 何かしらの指標で優先順位をつけて処理していく

指標は
あるタスクを見て、そのタスクの依存が完了してる度の高い順に処理していく。

- 案1
タスクについて、アサインしたメンバー、かかった時間が取れるので、
その情報をもとに、タスクをどのメンバーに割り振るかという選択の時に、
その情報を参考にしたい。

例えば、要求されるスキルの形が近い（単純に距離とか？）タスクを過去に素早く処理したことがあるならば、
それを再度同じ人にアサインしたほうが早く処理される可能性が高い、など。

- 案2
メンバーについて、過去にやったタスクと、そレニかかった時間が取れる。
この情報が蓄積していくに従って、推定が正確になっていくのを利用する。

何かしらの方法で、ランダムでもなんでもいいので、スキルの分布を（それぞれの下限だけでも）推定できたら嬉しい。１

### 4日目
完全独立なタスクが多いときは、依存関係をそこまで考慮しなくてもいい感じで終えることができるが
少ない時には、最後に依存のせいでタスク処理に遅れが出て、手待ちが発生する。

完全独立なタスクに閾値を設けて対処したが、微増だし、これじゃダメ。
依存の生成過程をみれば、依存の辺は小->大にしか生えていないので、
トポロジカルソートなどで木構造の深さとかをいい感じに管理して、
最後に手待ちが発生しないような処理手順を考えなければならない。

これも大事だけど、もっと大事なのはメンバーのスキルの推定で
ここはなんらかの線形代数とか線形計画法などの問題に落ちそうだが
今はよくわからないので、評価関数を作って変な風にはならない制約を入れた上で
山登りとかするしかない気がする。今のminimumを決める方法でもスキルが全体的に高いものに関しては
推定精度が高い気がするので、他の小さいパターンについても同様にできたらいいと思う。

後者については案2が該当する。

戦略としては、
依存の数の大小で全くアルゴリズムを変える必要がありそうだということ。
トポロジカルソートなどで、統一的なアルゴリズムで扱えるとなおよいが・・・・。
文献などにあたってみるべきか。

それ以前の話として、推定精度を上げてくださいということ。