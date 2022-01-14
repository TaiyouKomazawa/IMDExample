# IMDExample

## 概要

IMDControllerを用いたプログラム例を示す。

## 導入方法

ワークスペースで次のようにコマンドを実行。  
``` shell
git clone https://github.com/TaiyouKomazawa/IMDExample.git
```
IMDExample下で中のサブモジュールを再帰的にクローンする。
``` shell
git submodule update --init --recursive 
```
ビルドを行う際はIMDExample下のcmakeファイルを読み込む。
``` shell
cmake CMakeLists.txt
```
makeをすると、`check_serialnumber`と`motor_drive`のバイナリファイルができる。
``` shell
make all
```
## 注意事項
- シリアルナンバーはそれぞれ違うので`check_serialnumber`で調べて変更する。
- うまくビルドしないときはudev関係のパッケージが実行環境にあるか確認すること。
- またhid_raw実行権限の問題によりsudoでの実行になる場合があるが、永続的に権限を下げることで問題が解消される。詳しくはデバイスドライバ開発者の記事を参照。   
http://www.kerrywong.com/mcp2210-library-reference/
