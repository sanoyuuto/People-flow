# Arduinoを用いた人流カウンター

## 制作物の概要
二つの超音波センサ(HCSR-04)を使い、センサの前を通った人の人数とその通った方向(右から左か左から右)をキャラクターディスプレイ(LCD1602 Module)に表示するものである。また、人が通ったことを感知した場合は、ブザーから音が鳴るようになっている。 そして、 シリアルモニタには、 通った時刻からの経過時間とセンサからの距離、通った人数の合計、右から左に通った人数、 左から右に通った人数の合計を表示する。

## プログラムの概要
センサの前を人が通過した時刻を格納する配列をセンサごとに定義する。センサに反応があった場合は、反応があったセンサの配列の0番目に時間の経過を測る関数mills()を使って求めた計測開始からの経過時間を格納する。 もし、二つのセンサの0番目の配列が、 0より大きくなった場合、 人が通ったと判断する。 また、この各センサの配列の０番目の大小関係を比較することで、 右から左に移動したか左から右に移動したかを判定する。 すべての動作(キャラクターディスプレイの通った人数の更新, シリアルモニタに通った人数や各センサを通過した時間などを表示)が終了したら、 配列の初期化を行い同様の操作でセンサの前を通過した人数を計測する。
今回作成したプログラムの仕様上、片方のセンサだけが反応した場合センサに人が通った時間が配列に格納されたままになり、 次に人が通過して来る方向を誤って認識してしまうという問題が発生する場合がある。 この問題に対処するために、 片方のセンサだけが反応して3秒以上もう一方のセンサに反応がなければ配列を初期化し、 人が通ってないと認識するようにしている。

## 実行中の動画
https://user-images.githubusercontent.com/103728140/170539380-caddfd80-9b3a-4af9-9ca2-6602cd313c4e.mp4

## 回路図
以下に使用した回路図を示す.
HCSR-04二つとLCD1602 Module一つの合計三つを5V電源とGNDが共有するようにブレッドボード上で回路を作成した。また、 echoやTrigなどの各端子がプログラム上で設定した番号と一致するように回路が組まれている。

<img src="https://github.com/sanoyuuto/People-flow/blob/master/%E5%9B%9E%E8%B7%AF%E5%9B%B3.png" width="50%" />

