# makeQC-MDPC_alist
alistファイルを出力する。

## alistファイルの構成
### row 1
N R Q
### row 2
colunm_weightの最大値  row_weightの最大値
### row 3
\[i列目の列重み\]
### row 4
\[i行目の列重み\]
### row 5~(N+4)
\[i列目の非ゼロ要素の位置\]
### row (N+5)~(R+N+4)
\[i行目の非ゼロ要素の位置\]
### row (R+N+5)~(R+2N+4)
\[i列目の非ゼロ要素の内容\]