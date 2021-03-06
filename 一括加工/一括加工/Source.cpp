#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

//画像サイズを定義する
#define X_SIZE 640
#define Y_SIZE 480

//読み込みと保存用のファイルパスを用意
char read_path[500];
char save_path[500];

//入力のRGB値を用意
unsigned char r_in[Y_SIZE][X_SIZE];
unsigned char g_in[Y_SIZE][X_SIZE];
unsigned char b_in[Y_SIZE][X_SIZE];

//グレイ画像の出力先の配列
unsigned char gray[Y_SIZE][X_SIZE];

//左右反転画像の出力先の配列
unsigned char sayuu[Y_SIZE][X_SIZE];

//上下反転画像の出力先の配列
unsigned char jouge[Y_SIZE][X_SIZE];

//明度変更画像の出力先の配列
unsigned char meido[Y_SIZE][X_SIZE];

//関数のプロトタイプを宣言する
void read_img(char* read_path, 
				unsigned char r_in[Y_SIZE][X_SIZE], 
				unsigned char g_in[Y_SIZE][X_SIZE], 
				unsigned char b_in[Y_SIZE][X_SIZE]);
void gray_img(unsigned char r[Y_SIZE][X_SIZE], 
				unsigned char g[Y_SIZE][X_SIZE], 
				unsigned char b[Y_SIZE][X_SIZE], 
				unsigned char img[Y_SIZE][X_SIZE]);
void sayuu_img(unsigned char r[Y_SIZE][X_SIZE],
				unsigned char g[Y_SIZE][X_SIZE],
				unsigned char b[Y_SIZE][X_SIZE],
				unsigned char sayuu[Y_SIZE][X_SIZE]);
void jouge_img(unsigned char r[Y_SIZE][X_SIZE],
				unsigned char g[Y_SIZE][X_SIZE],
				unsigned char b[Y_SIZE][X_SIZE],
				unsigned char jouge[Y_SIZE][X_SIZE]);
void meido_img(unsigned char r[Y_SIZE][X_SIZE],
			   unsigned char g[Y_SIZE][X_SIZE],
			   unsigned char b[Y_SIZE][X_SIZE],
			   unsigned char meido[Y_SIZE][X_SIZE]);
void save_img(char* save_path, 
				unsigned char img[Y_SIZE][X_SIZE]);

//メインとなる関数
void main(void)
{
	//入力画像の読み込み
	read_img(read_path, r_in, g_in, b_in);

	//グレイスケール化
	gray_img(r_in, g_in, b_in, gray);

	//左右反転
	sayuu_img(r_in, g_in, b_in, sayuu);

	//上下反転
	jouge_img(r_in, g_in, b_in, jouge);

	////明度値反転
	meido_img(r_in, g_in, b_in, meido);

	//出力画像の保存
	save_img(save_path, gray);
}

//入力画像の読み込み
void read_img(char* read_path, unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE])
{
	int i, j;

	//ファイルためのファイルを用意
	printf("読み込むファイル-->");
	//標準入力をバッファに格納する
	scanf("%s", read_path);

	FILE* fp;

	//ファイルを開く
	fp = fopen(read_path, "rb");

	//もし，ファイルが無いときに終了させる
	if (fp == NULL)
	{
		printf("ファイルが存在しません", read_path);
		exit(-1);
	}

	//画像内からRGB値の取得（ラスタ走査）
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			r[j][i] = fgetc(fp);
			g[j][i] = fgetc(fp);
			b[j][i] = fgetc(fp);
		}
	}
	//ファイルを閉じる
	fclose(fp);
}

//グレイ化
void gray_img(unsigned char r[Y_SIZE][X_SIZE], 
				unsigned char g[Y_SIZE][X_SIZE], 
				unsigned char b[Y_SIZE][X_SIZE], 
				unsigned char img[Y_SIZE][X_SIZE])
{
	int i, j;

	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			img[j][i] = (unsigned char)(0.30 * r[j][i] + 0.59 * g[j][i] + 0.11 * b[j][i]);
		}
	}
}

//左右反転
void sayuu_img(unsigned char r[Y_SIZE][X_SIZE],
	unsigned char g[Y_SIZE][X_SIZE],
	unsigned char b[Y_SIZE][X_SIZE],
	unsigned char sayuu[Y_SIZE][X_SIZE])
{
	int x, y, w = 0, h = 0,c;

	for (y = 0; y < h; y++)
		for (x = 0; x < w / 2; x++) {
			int tmp = sayuu[y][x];
			sayuu[y][x] = sayuu[y][w - x - 1];
			sayuu[y][w - x - 1] = tmp;
		}
}

//上下反転
void jouge_img(unsigned char r[Y_SIZE][X_SIZE],
	unsigned char g[Y_SIZE][X_SIZE],
	unsigned char b[Y_SIZE][X_SIZE],
	unsigned char jouge[Y_SIZE][X_SIZE])
{
	int x, y, w = 0, h = 0;

	for (y = 0; y < h / 2; y++)
		for (x = 0; x < w; x++) {
			int tmp = jouge[y][x];
			jouge[y][x] = jouge[h - y - 1][x];
			jouge[h - y - 1][x] = tmp;
		}
}

//明度値反転
void meido_img(unsigned char r[Y_SIZE][X_SIZE],
	unsigned char g[Y_SIZE][X_SIZE],
	unsigned char b[Y_SIZE][X_SIZE],
	unsigned char meido[Y_SIZE][X_SIZE])
{
	int x, y, w = 0, h = 0;

	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++) {
			meido[y][x] = 255 - meido[y][x];
		}
}

//出力画像の保存
void save_img(char* save_path, unsigned char img[Y_SIZE][X_SIZE])
{
	int i, j;

	FILE* fp;

	printf("どのファイルに保存しますか？-->");
	scanf("%s", save_path);

	//ファイルを開く
	fp = fopen(save_path, "wb");

	//もし，ファイルが無いときに終了させる
	if (fp == NULL)
	{
		printf("ファイルが存在しません", save_path);
		exit(-1);
	}
	//画像のRGB値をファイルに保存する
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			fputc(img[j][i], fp);
		}
	}
	//ファイルを閉じる
	fclose(fp);
}