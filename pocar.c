#include <stdio.h>                      //入出力用
#include <stdlib.h>                     //乱数使用するため
#include <time.h>                     //時間を使った乱数初期化に使用

void poker(void);                     //ポーカー起動

int rand_start(void);                  //乱数作成
void draw(int n,int hand);             //引いたカードを表示

void a_change(int n, int hand);        //交換するカード選択
int change_result(int cng, int hand);  //交換したときの役判定

int result(int hand);                  //役判定


int main(void) 
{

	int select;

	do {

		printf("\n\n＝＝＝＝＝簡易ポーカー＝＝＝＝＝\n");  //①起動画面表示
		printf("１：ゲーム開始\n");
		printf("２：ゲーム終了\n");
		printf("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");
		printf("選択してください：");

		scanf_s("%d", &select);
		scanf_s("%*[^\n]");
		scanf_s("%*c");

		switch (select) {
		case 1:								          //１ならゲーム起動
			poker();
			printf("\n\nEnterでTop画面に戻ります\n");             //Enter押すと自分のカードを引く
			scanf_s("%*[^\n]");
			scanf_s("%*c");
			break;

		case 2:
			printf("\n\nゲームを終了します\n");           //２ならゲーム終了
			break;

		default:
			printf("\n\n正しい数字を入力してください\n");
			break;
		}

	} while (select == 1);

	return 0;

}

void poker(void)										//ポーカー起動
{
	int n = 1;
	int i, hand, change, cng, player1, player2, cng_1, cng_2, error = 0;


	printf("\n\nplayer%dのカードを引きます。Enterを入力してください\n\n", n);           //②自分のカードを引く（役確認）
	scanf_s("%*[^\n]");
	scanf_s("%*c");

	for(i=0;i<2;i++){

		switch (n) {

		case 1:

			hand = rand_start();														//ランダムに引いたカードを作成

			printf("§§§§§§§§§§§§§§§§§§§§§\n\n");
			draw(n, hand);																//引いたカードを画面に表示
			printf("§§§§§§§§§§§§§§§§§§§§§\n\n");

			player1 = result(hand);

			printf("\n１：カード交換\n");												//③引き直すかそのまま勝負するか
			printf("２：そのまま\n\n");
			printf("選択してください：");
			scanf_s("%d", &change);
			scanf_s("%*[^\n]");
			scanf_s("%*c");

			switch (change) {

			case 1:																	    //交換する場合、交換したいカードの番号を入力する（全部の場合は５）

				a_change(n, hand);

				printf("\n交換したいカードの番号を2つまで入力してください(５：すべて交換)\n\n");
				printf("入力してください：");

				scanf_s("%d", &cng);
				scanf_s("%*[^\n]");
				scanf_s("%*c");

				if (cng >= 1 && cng <= 4) 													//交換するカードの番号を表示
					printf("\n%d番のカードを交換します\n\n", cng);

				else if (cng == 11 || cng == 12 || cng == 13 || cng == 21 || cng == 23 || cng == 24
					    || cng == 31 || cng == 32 || cng == 34 || cng == 41 || cng == 42 || cng == 43) {

					cng_1 = cng % 10;
					cng_2 = cng / 10;

					printf("\n%d番と%d番のカードを交換します\n\n", cng_2, cng_1);
				}

				else if (cng == 5)
					printf("\nすべてのカードを交換します\n\n");

				else {
					printf("error:入力が間違っています\n\n");
					error++;
				}

				//printf("%d",cng);

				if (error == 0)
				{
					hand = change_result(cng, hand);											//handに交換したカードの結果を代入する

					printf("§§§§§§§§§§§§§§§§§§§§§\n\n");
					draw(n, hand);																//交換した結果を表示する
					printf("§§§§§§§§§§§§§§§§§§§§§\n\n");

					player1 = result(hand);														//役の強さを判定し保存する
					printf("\n");

				}

				n++;

				break;

			case 2:

				player1 = result(hand);														//役の強さを判定し保存する
				printf("\n");

				n++;
				break;

			default:

				printf("error:入力が間違っています\n\n");
				n = n + 2;
				error++;

				break;

			}

			break;

		case 2:

			if (error == 0) {

				printf("\n\nplayer%dのカードを引きます。Enterを入力してください\n\n", n);   //④相手のカードを引く（役確認）
				scanf_s("%*[^\n]");
				scanf_s("%*c");

				hand = rand_start();														//ランダムに引いたカードを作成

				printf("§§§§§§§§§§§§§§§§§§§§§\n\n");
				draw(n, hand);																//引いたカードを画面に表示
				printf("§§§§§§§§§§§§§§§§§§§§§\n\n");

				player2 = result(hand);														//役の強さを判定し保存する

			}

			break;

		default:

			break;
		
		}
		
	}

	if (error == 0) {

		if (player1 > player2)														//⑤⑥勝敗の判定、結果出力
			printf("player1の勝ちです\n\n");

		else if (player1 < player2)
			printf("player2の勝ちです\n\n");

		else if (player1 == player2)
			printf("引き分けです\n\n");

	}

//	printf("%d %d\n", player1, player2);

}

int rand_start() {

	int j, card[5],hand;

	srand((unsigned int)time(NULL));											//乱数の初期設定

	for (j = 1; j < 5; j++) {													//乱数から数字を４つ決定する
		card[j] = rand() % 5 + 1;
	}

	hand = card[1]  + card[2] * 10 + card[3] * 100 + card[4] * 1000;            //カードのデータを１つにまとめる

	return hand;

}

void draw(int n,int hand)
{

	int card[5];

	for (int i = 1; i < 5; i++) {										//handから４つの数字を取り出す
		card[i] = hand % 10;
		hand = hand / 10;
	}

	if ((card[1] == card[2] && card[3] == card[4]) && card[1] == card[3]) {										//役を判定し、引いたカードと役を表示する
		printf("player%dのカード   %d %d %d %d      Four Card\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else if ((card[1] == card[2] && card[1] == card[3]) || (card[1] == card[3] && card[3] == card[4]) 
			|| (card[2] == card[3] && card[3] == card[4]) || (card[1] == card[2] && card[1] == card[4])) {
		printf("player%dのカード   %d %d %d %d      Three Card\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else if ((card[1] == card[2] && card[3] == card[4]) || (card[1] == card[3] && card[2] == card[4])) {
		printf("player%dのカード   %d %d %d %d      Two Pair\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else if (card[1] == card[2] || card[1] == card[3] || card[1] == card[4] || card[2] == card[3] || card[2] == card[4] || card[3] == card[4]) {
		printf("player%dのカード   %d %d %d %d      One Pair\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else {
		printf("player%dのカード   %d %d %d %d      No Pair\n\n", n, card[1], card[2], card[3], card[4]);
	}
	
}

void a_change(int n, int hand)
{

	int card[5];

	for (int i = 1; i < 5; i++) {										//handから４つの数字を取り出す
		card[i] = hand % 10;
		hand = hand / 10;
	}

	if ((card[1] == card[2] && card[3] == card[4]) && card[1] == card[3]) {										//交換したいカードを選びやすいように番号①～④を割り振る
		printf("player%dのカード    ①：%d ②：%d ③：%d ④：%d      Four Card\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else if ((card[1] == card[2] && card[1] == card[3]) || (card[1] == card[3] && card[3] == card[4])
		|| (card[2] == card[3] && card[3] == card[4]) || (card[1] == card[2] && card[1] == card[4])) {
		printf("player%dのカード    ①：%d ②：%d ③：%d ④：%d      Three Card\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else if ((card[1] == card[2] && card[3] == card[4]) || (card[1] == card[3] && card[2] == card[4])) {
		printf("player%dのカード    ①：%d ②：%d ③：%d ④：%d      Two Pair\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else if (card[1] == card[2] || card[1] == card[3] || card[1] == card[4] || card[2] == card[3] || card[2] == card[4] || card[3] == card[4]) {
		printf("player%dのカード    ①：%d ②：%d ③：%d ④：%d      One Pair\n\n", n, card[1], card[2], card[3], card[4]);
	}

	else {
		printf("player%dのカード    ①：%d ②：%d ③：%d ④：%d      No Pair\n\n", n, card[1], card[2], card[3], card[4]);
	}

}

int change_result(int cng, int hand)
{
	int card[5], k, j, a;

	for (int i = 1; i < 5; i++) {										//handから４つの数字を取り出す
		card[i] = hand % 10;
		hand = hand / 10;
	}

	srand((unsigned int)time(NULL));									//新しいカードを作成前に乱数の初期設定

	if (cng <= 4 && cng >= 1) {										    //交換するカードが１枚の時の処理

		card[cng] = rand() % 5 + 1;

	}

	else if (cng <= 43 && cng >= 12) {									//交換するカードが２枚の時の処理

		for (k = 0; k < 2; k++) {
			a = cng % 10;
			card[a] = rand() % 5 + 1;
			cng = cng / 10;
		}

	}

	else if (cng == 5) {												//交換するカードが全部の時の処理

		for (j = 1; j < 5; j++) {
			card[j] = rand() % 5 + 1;
		}

	}

	hand = card[1] + (card[2] * 10) + (card[3] * 100) + (card[4] * 1000);		//交換したカードデータを１つにまとめる

	return hand;

}

int result(int hand)											//役の強さ判定
{

	int card[5], yaku;

	for (int i = 1; i < 5; i++) {
		card[i] = hand % 10;
		hand = hand / 10;
	}

	if ((card[1] == card[2] && card[3] == card[4]) && card[1] == card[3]) {					//フォーカードの時の処理

		yaku = 40 + card[1];

	}

	else if ((card[1] == card[2] && card[1] == card[3]) || (card[1] == card[3] && card[3] == card[4])
			|| (card[2] == card[3] && card[3] == card[4]) || (card[1] == card[2] && card[1] == card[4])) {				//スリーカードの時の処理

		if ((card[1] == card[2] && card[1] == card[3]))
			yaku = 30 + card[1];

		else if((card[1] == card[3] && card[3] == card[4]))
			yaku = 30 + card[1];

		else if((card[2] == card[3] && card[3] == card[4]))
			yaku = 30 + card[2];

		else if((card[1] == card[2] && card[1] == card[4]))
			yaku = 30 + card[1];

	}

	else if ((card[1] == card[2] && card[3] == card[4]) || (card[1] == card[3] && card[2] == card[4])) {				//ツーペア時の処理

		if ((card[1] == card[2] && card[3] == card[4])) {

			if (card[1] > card[3])
				yaku = 20 + card[1];

			else if (card[1] < card[3])
				yaku = 20 + card[3];

		}

		else if ((card[1] == card[3] && card[2] == card[4])) {

			if (card[1] > card[2])
				yaku = 20 + card[1];

			else if (card[1] < card[2])
				yaku = 20 + card[2];

		}

	}

	else if (card[1] == card[2] || card[1] == card[3] || card[1] == card[4] || card[2] == card[3] || card[2] == card[4] || card[3] == card[4]) {

		if (card[1] == card[2] || card[1] == card[3] || card[1] == card[4])				//ワンペア時の処理
			yaku = 10 + card[1];

		else if (card[2] == card[3] || card[2] == card[4])
			yaku = 10 + card[2];

		else if (card[3] == card[4])
			yaku = 10 + card[3];

	}

	else {				//役なし

		yaku = 0;

	}

	return yaku;

}
