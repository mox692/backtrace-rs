#include <execinfo.h>   // backtraceとbacktrace_symbolsのためのヘッダ
#include <stdio.h>      // printfのためのヘッダ
#include <stdlib.h>     // exitとfreeのためのヘッダ

#define MAX_FRAMES 64   // スタックトレースで取得する最大フレーム数

void printStackTrace() {
    void *callstack[MAX_FRAMES];
    int frameCount;
    char **symbols;

    // 現在のスタックフレームを取得
    frameCount = backtrace(callstack, MAX_FRAMES);

    // スタックフレームに対応するシンボルを取得
    symbols = backtrace_symbols(callstack, frameCount);

    if (symbols == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    // スタックトレースを出力
    for (int i = 0; i < frameCount; i++) {
        printf("%p : %s\n", callstack[i], symbols[i]);
    }

    free(symbols);
}

int main() {
    // スタックトレースを表示する関数を呼び出し
    printStackTrace();

    return 0;
}
