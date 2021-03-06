// 標準のシステムインクルードファイルのインクルードファイル、
// または参照回数が多く、かつあまり変更されないプロジェクト専用のインクルードファイルを記述します

#pragma once

// 利用可能な最上位の Windows プラットフォームが定義されます
#include "targetver.h"

// Windows ヘッダーから使用されていない部分を除外します
#define WIN32_LEAN_AND_MEAN             

// Windows ヘッダー ファイル
#include <windows.h>

// プログラムに必要な追加ヘッダーをここで参照してください
#include <thread>
#include "ReversiAiDll.h"
