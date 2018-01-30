#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* パスワード桁数の範囲4桁~20桁 */
#define MIN_PASSWORD_LENGTH (4)
#define MAX_PASSWORD_LENGTH (20)

/* 文字種別判別定数 */
#define CHARTYPE_UPPERCASE	(0)
#define CHARTYPE_LOWERCASE	(1)
#define CHARTYPE_NUMBER		(2)
#define CHARTYPE_SYMBOL		(3)

/* 文字種数 */
#define TYPE_COUNT			(4)

/* 終了番号 */
#define QUIT_NUMBER			(-1)

/* 文字一覧 */
const char* UPPERCASE_WORDS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* LOWERCASE_WORDS = "abcdefghijklmnopqrstuvwxyz";
const char* NUMBER_WORDS	= "0123456789";
const char* SYMBOL_WORDS	= "!#$%&+*-@?";
