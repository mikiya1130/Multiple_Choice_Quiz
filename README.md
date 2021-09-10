# Multiple_Choice_Quiz

Linux用N択クイズアプリ  
GNOMEデスクトップ環境向け(他にも動作する環境はあると思う)  

## 説明

- JSONファイルに用意したN択クイズを遊ぶことができるアプリケーション
- 問題の出題順、選択肢の並び順のシャッフル対応
- 問題、解説はHTMLでの記述に対応
    - カスタムレイアウト、装飾、画像の埋め込み etc...
- 正解率の表示

***デモ：***

TODO

## 環境

### 動作環境

- GNOMEデスクトップ環境のLinux

### 開発・テスト環境

- Ubuntu20.04 (Host & Docker)

## 使用方法

### ダウンロードから実行まで

[Releasesページ](https://github.com/mikiya1130/Multiple_Choice_Quiz/releases)から最新の`Multiple_Choice_Quiz.tar.gz`をダウンロード
```shell
$ tar xvf ./Multiple_Choice_Quiz.tar.gz  # 解凍
$ cd ./Multiple_Choice_Quiz
$ ./Multiple_Choice_Quiz.AppImage  # 実行
```
ファイラーアプリでAppImageファイルをダブルクリックして実行してもOK

### 操作方法

1. 必要に応じて出題順や選択肢のシャッフルを有効にし、クイズセットを選択する
1. 選択肢をクリックすると正誤判定が行われ、解説が表示される
    - 9個目までの選択肢は1~9キーにも対応
    - 上部に統計情報が表示される
1. 矢印ボタンで前後の問題へ移動
    - h,lキーでの移動にも対応
1. HOMEボタンでクイズセット選択画面へ戻る
    - 記録は消えるので注意

### 起動しない場合

コマンドライン上で実行し、エラーが出力されないか確認する(ライブラリの不足など)  

### JSONファイルの記述方法

```json
[
    {
        "question": "問題文",
        "choice": [
            "選択肢1",
            "選択肢2",
            ...
        ],
        "correct": 0,  // choice配列のindex(0-based)に対応する正解の選択肢の番号
        "explanation": "解説文"
    },
    {
        "question": "question/q2.html",
        ...
    },
    ...
]
```
- rootは配列
- 配列の中の1つのオブジェクトが1つの問題に対応
- オブジェクトの要素は`question(str)`, `choice(array\<str\>)`, `correct(int)`, `explanation(str)`, `question(str)`からなる
- `question`と`explanation`には直接HTMLを記述したり、jsonファイルからの相対パスを記述してHTMLファイルを読み込ませたりすることが可能
- "choice"配列の要素数(=選択肢の数)は可変
- JSONファイル名(拡張子を除く)がクイズセット名としてHOME画面に表示される

## 開発メモ

### xhost

```shell
(local)$ xhost          # 確認
(local)$ xhost local:   # 許可
(local)$ xhost -local:  # 拒否
```

### Makefile

コンパイルから実行まで
```shell
$ make exec SRCDIR=<srcdir>  # default:src
```

参考：https://soratobi96.hatenablog.com/entry/20191024/1571849722

### Document

[Multiple_Choice_Quiz](https://mikiya1130.github.io/Multiple_Choice_Quiz/)

## ライブラリ

- [gtkmm](https://www.gtkmm.org/)
- [JSON for Modern C++](https://json.nlohmann.me/)
- [Doxygen](https://www.doxygen.nl/index.html)

## ライセンス

[MITライセンス](https://github.com/mikiya1130/Multiple_Choice_Quiz/blob/master/LICENSE)
