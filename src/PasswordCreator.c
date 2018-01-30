#include "PasswordCreator.h"

/*
 * 桁数入力関数
 *
 * 戻り値：
 *	入力桁数
 *
 */
int input_password_length()
{
	int ret = 0;
	int password_length = 0;

	printf("パスワードの桁数を入力してください。\n");
	printf("(有効桁数%d〜%d桁)\n", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
	printf("%dを入力で終了します。\n", QUIT_NUMBER);
	printf("\n");

	ret = scanf("%d", &password_length);

	if(ret != 1){
		printf("不正な値が入力されました。\n");
		printf("\n");
		
		scanf("%*s");

		return 0;
	}

	if(password_length == QUIT_NUMBER){
		printf("終了します。\n");

		return QUIT_NUMBER;
	}
	else if(password_length < MIN_PASSWORD_LENGTH ||
			password_length > MAX_PASSWORD_LENGTH){
		printf("有効桁数の範囲外です。\n");
		printf("(有効桁数%d〜%d桁)\n", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
		printf("\n");

		return 0;	
	}

	return password_length;
}

/*
 * 文字種別取得関数
 * 
 * 引数：
 *	int type_count [in] 文字種数
 * 戻り値：
 *	選択された文字種別(0〜文字種数分の乱数)
 *
 */
int get_rand_chartype(int type_count)
{
	return rand()%type_count;
}

/*
 * 未選択文字種リスト初期化関数 
 * 引数：
 *	int*  array[out] 未選択文字種リスト
 *
 */
void init_selectabletype(int* array)
{
	for(int i=0; i<TYPE_COUNT; i++){
		array[i] = i;
	}
}

/*
 * ランダム文字取得関数
 *
 * 引数：
 *	int chartype [in] 文字種別
 * 戻り値：
 *	ランダムに抽出した文字
 *
 */
char get_rand_character(int chartype)
{
	char rand_character = '\0';
	int  rand_num = 0;
	const char* word_list[TYPE_COUNT] = {UPPERCASE_WORDS,
										 LOWERCASE_WORDS,
										 NUMBER_WORDS,
										 SYMBOL_WORDS};

	rand_num = rand() % strlen(word_list[chartype]);
	rand_character = word_list[chartype][rand_num];
	
	return rand_character;
}

/*
 * 選択可能文字種リスト更新関数
 * 引数：
 *	int* selectedtype_counter[in] 文字種カウンタ
 *	int* selectabletype[out] 選択可能文字種リスト
 * 戻り値：
 *	選択可能文字種数
 *
 */
int update_selectablelist(int* selectedtype_counter, int* selectabletype)
{
	int length = 0;
	
	for(int i=0; i<TYPE_COUNT; i++){
		if(selectedtype_counter[i] == 0){
			selectabletype[length++] = i;
		}
	}

	return length;	
}

/*
 * パスワード生成関数
 * 引数：
 *	char* password[out]		  生成されたパスワード
 *	int   password_length[in] パスワードの桁数
 * 戻り値：
 *	正常終了:0
 *	異常終了:-1
 *
 */
int create_password(char* password, int password_length)
{
	int chartype = 0;							// 文字種代入用変数
	int chartypeidx = 0;						// 文字種インデックス変数
	int selectablecount = TYPE_COUNT;			// 選択可能文字種数
	int unselectedtype_count = TYPE_COUNT;		// 未選択文字種数
	int selectedtype_counter[TYPE_COUNT] = {0};	// カウンタ
	int selectabletype[TYPE_COUNT] = {0};		// 選択可能文字種判別定数リスト

	// 選択可能文字種判別定数リストの初期化
	init_selectabletype(selectabletype);
	
	srand((unsigned)time(NULL));

	for(int i=0; i<password_length; i++){
		// 残り文字数=未選択文字種数の場合に選択可能文字種を更新
		if(i == password_length - unselectedtype_count){
			selectablecount = update_selectablelist(selectedtype_counter, selectabletype);
		}

		// ランダムで文字を取得
		chartypeidx = get_rand_chartype(selectablecount);	
		chartype = selectabletype[chartypeidx];
		password[i] = get_rand_character(chartype);

		// カウンタ更新
		if(selectedtype_counter[chartype] == 0){
			unselectedtype_count--;
		}
		selectedtype_counter[chartype]++;
	}

	password[password_length] = '\0';

	// 念のため選択されていない文字種がないかチェック
	// 実装上trueにはならないはず
	if(unselectedtype_count != 0)
	{
		printf("パスワード生成エラー\n");
		printf("%s\n",password);
		return -1;
	}

	return 0;
}

int main(void)
{
	int ret = 0;
	int password_length = 0;
	char* password = NULL;

	while(1){
		password_length = input_password_length();

		// 終了
		if(password_length == QUIT_NUMBER){
			break;
		}

		// inputエラー
		if(password_length == 0){
			continue;	
		}

		password = malloc(sizeof(char) * (password_length + 1));
		
		ret = create_password(password, password_length);
	
		// パスワード生成失敗	
		if(ret < 0){
			continue;	
		}

		printf("password = %s\n", password);
		printf("\n");

		if(password != NULL){
			free(password);
		}
	}	
		
	return 0;
}
