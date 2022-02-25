#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

//�摜�T�C�Y���`����
#define X_SIZE 640
#define Y_SIZE 480

//�ǂݍ��݂ƕۑ��p�̃t�@�C���p�X��p��
char read_path[500];
char save_path[500];

//���͂�RGB�l��p��
unsigned char r_in[Y_SIZE][X_SIZE];
unsigned char g_in[Y_SIZE][X_SIZE];
unsigned char b_in[Y_SIZE][X_SIZE];

//�O���C�摜�̏o�͐�̔z��
unsigned char gray[Y_SIZE][X_SIZE];

//���E���]�摜�̏o�͐�̔z��
unsigned char sayuu[Y_SIZE][X_SIZE];

//�㉺���]�摜�̏o�͐�̔z��
unsigned char jouge[Y_SIZE][X_SIZE];

//���x�ύX�摜�̏o�͐�̔z��
unsigned char meido[Y_SIZE][X_SIZE];

//�֐��̃v���g�^�C�v��錾����
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

//���C���ƂȂ�֐�
void main(void)
{
	//���͉摜�̓ǂݍ���
	read_img(read_path, r_in, g_in, b_in);

	//�O���C�X�P�[����
	gray_img(r_in, g_in, b_in, gray);

	//���E���]
	sayuu_img(r_in, g_in, b_in, sayuu);

	//�㉺���]
	jouge_img(r_in, g_in, b_in, jouge);

	////���x�l���]
	meido_img(r_in, g_in, b_in, meido);

	//�o�͉摜�̕ۑ�
	save_img(save_path, gray);
}

//���͉摜�̓ǂݍ���
void read_img(char* read_path, unsigned char r[Y_SIZE][X_SIZE], unsigned char g[Y_SIZE][X_SIZE], unsigned char b[Y_SIZE][X_SIZE])
{
	int i, j;

	//�t�@�C�����߂̃t�@�C����p��
	printf("�ǂݍ��ރt�@�C��-->");
	//�W�����͂��o�b�t�@�Ɋi�[����
	scanf("%s", read_path);

	FILE* fp;

	//�t�@�C�����J��
	fp = fopen(read_path, "rb");

	//�����C�t�@�C���������Ƃ��ɏI��������
	if (fp == NULL)
	{
		printf("�t�@�C�������݂��܂���", read_path);
		exit(-1);
	}

	//�摜������RGB�l�̎擾�i���X�^�����j
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			r[j][i] = fgetc(fp);
			g[j][i] = fgetc(fp);
			b[j][i] = fgetc(fp);
		}
	}
	//�t�@�C�������
	fclose(fp);
}

//�O���C��
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

//���E���]
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

//�㉺���]
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

//���x�l���]
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

//�o�͉摜�̕ۑ�
void save_img(char* save_path, unsigned char img[Y_SIZE][X_SIZE])
{
	int i, j;

	FILE* fp;

	printf("�ǂ̃t�@�C���ɕۑ����܂����H-->");
	scanf("%s", save_path);

	//�t�@�C�����J��
	fp = fopen(save_path, "wb");

	//�����C�t�@�C���������Ƃ��ɏI��������
	if (fp == NULL)
	{
		printf("�t�@�C�������݂��܂���", save_path);
		exit(-1);
	}
	//�摜��RGB�l���t�@�C���ɕۑ�����
	for (j = 0; j < Y_SIZE; j++)
	{
		for (i = 0; i < X_SIZE; i++)
		{
			fputc(img[j][i], fp);
		}
	}
	//�t�@�C�������
	fclose(fp);
}