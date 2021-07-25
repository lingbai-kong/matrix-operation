#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <cmath>
#define MAX_SIZE 256
#define OK 1
#define ERROR 0
using namespace cv;
using namespace std;
typedef int Status;

const int row = MAX_SIZE * MAX_SIZE;
const int column = MAX_SIZE * MAX_SIZE + 1;

int getint()
{
	int x;
	char ch;
	bool flag = true;
	x = 0;
	ch = _getch();
	if (ch == '-')
	{
		flag = false;
		ch = _getch();
	}
	while (ch != '\n' && ch != ' ')
	{
		if (ch < '0' || ch>'9')
		{
			cout << "illegal input\n";
			exit(0);
		}
		x = x * 10 + ch - '0';
		ch = _getch();
	}
	if (flag)
		return x;
	else
		return -x;
}
void wait_for_enter()
{
	cout << endl << "���س�������";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
void menu()
{
	cout << "***********�����*********1852146*********�������*******\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "*\t" << "1 ����ӷ�\t" << "2 ��������\t" << "3 ����ת��\t" << "*\n";
	cout << "*\t" << "4 ����˷�\t" << "5 Hadamard�˻�\t" << "6 ������\t" << "*\n";
	cout << "*\t" << "7 ���Ӧ��\t" << "8 OTSU�㷨\t" << "9 Canny�㷨\t" << "*\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "**********************���� 0 �˳�ϵͳ********************\n";
	cout << "ѡ��˵���<0-9>:\n";
}
void getfname(char name[])
{
	int choice;
	cout << "��ѡ�񱻴���ͼ��\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "*\t" << "1 demolena\t" << "2 snowball\t" << "3 polyhedrosis\t" << "*\n";
	cout << "*\t" << "4 ship\t\t" << "5 brain\t\t" << "���ఴ�����Զ���" << "*\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "ѡ��˵���<1-5>���Զ���:\n";
	choice = _getch();
	system("cls");
	switch (choice)
	{
	case '1':strcpy(name,"demolena.jpg"); break;
	case '2':strcpy(name, "snowball.jpg"); break;
	case '3':strcpy(name, "polyhedrosis.jpg"); break;
	case '4':strcpy(name, "ship.jpg"); break;
	case '5':strcpy(name, "brain.jpg"); break;
	default:
		cout << "������ͼƬ����";
		cin >> name;
	}
}

void Define_Matrix(int M[])
{
	int i, j;
	cout << "����������������";
	cin >> M[row];
	cout << "����������������";
	cin >> M[column];
	cout << "���������\n";
	for (i = 0; i < M[row]; i++)
	{
		cout << "\t��";
		M[MAX_SIZE * i] = getint();
		cout << setw(5) << setfill(' ') << M[MAX_SIZE * i];
		for (j = 1; j < M[column]; j++)
		{
			M[MAX_SIZE * i + j] = getint();
			cout << setw(5) << setfill(' ') << M[MAX_SIZE * i + j];

		}
		cout << " ��" << endl;
	}
	cout << "������ϡ�\n";
}
void Define_Kernel(int m[], int size)
{
	int i, j;
	m[row] = size;
	m[column] = size;
	cout << "���������ˣ�\n";
	for (i = 0; i < m[row]; i++)
	{
		cout << "\t��";
		m[MAX_SIZE * i] = getint();
		cout << setw(5) << setfill(' ') << m[MAX_SIZE * i];
		for (j = 1; j < m[column]; j++)
		{
			m[MAX_SIZE * i + j] = getint();
			cout << setw(5) << setfill(' ') << m[MAX_SIZE * i + j];

		}
		cout << " ��" << endl;
	}
	cout << "������ϡ�\n";
}
void Define_MGroup(int M1[], int M2[])
{
	cout << "�����һ������\n";
	Define_Matrix(M1);
	cout << "����ڶ�������\n";
	Define_Matrix(M2);
}
void Display_Matrix(int M[])
{
	int i, j;
	for (i = 0; i < M[row]; i++)
	{
		cout << "\t��" << setw(5) << setfill(' ') << M[MAX_SIZE * i];
		for (j = 1; j < M[column]; j++)
			cout << setw(5) << setfill(' ') << M[MAX_SIZE * i + j];
		cout << " ��" << endl;
	}
}

int m1[MAX_SIZE * MAX_SIZE + 2];
int m2[MAX_SIZE * MAX_SIZE + 2];
int m3[MAX_SIZE * MAX_SIZE + 2];

void matriplus() {
	int i, j;
	Define_MGroup(m1, m2);
	if ((m1[row] != m2[row]) || (m1[column] != m2[column]))
		cout << "wrong:������ͬ��\n";
	else
	{
		m3[row] = m1[row];
		m3[column] = m1[column];
		for (i = 0; i < m3[row]; i++)
			for (j = 0; j < m3[column]; j++)
				m3[MAX_SIZE * i + j] = m1[MAX_SIZE * i + j] + m2[MAX_SIZE * i + j];
		cout << "������֮��Ϊ��\n";
		Display_Matrix(m3);
	}
}
void hadamulti()
{
	int i, j;
	Define_MGroup(m1, m2);
	if ((m1[row] != m2[row]) || (m1[column] != m2[column]))
		cout << "wrong:������ͬ��\n";
	else
	{
		m3[row] = m1[row];
		m3[column] = m1[column];
		for (i = 0; i < m3[row]; i++)
			for (j = 0; j < m3[column]; j++)
				m3[MAX_SIZE * i + j] = m1[MAX_SIZE * i + j] * m2[MAX_SIZE * i + j];
		cout << "�������Hadamard�˻�Ϊ��\n";
		Display_Matrix(m3);
	}
}
void nummulti()
{
	int i, j;
	int n;
	Define_Matrix(m1);
	cout << "������Ҫ���˵����֣�";
	cin >> n;
	m2[row] = m1[row];
	m2[column] = m1[column];
	for (i = 0; i < m2[row]; i++)
		for (j = 0; j < m2[column]; j++)
			m2[MAX_SIZE * i + j] = m1[MAX_SIZE * i + j] * n;
	cout << "�þ������˺�Ϊ��\n";
	Display_Matrix(m2);
}
void matritrans()
{
	int i, j;
	Define_Matrix(m1);
	m2[row] = m1[column];
	m2[column] = m1[row];
	for (i = 0; i < m2[row]; i++)
		for (j = 0; j < m2[column]; j++)
			m2[MAX_SIZE * i + j] = m1[MAX_SIZE * j + i];
	cout << "�þ���ת�ú�Ϊ��\n";
	Display_Matrix(m2);
}
void matrimulti()
{
	int i, j, k;
	int s = m1[column];
	Define_MGroup(m1, m2);
	if (m1[column] != m2[row])
		cout << "wrong:����A�������;���B�����������\n";
	else
	{
		m3[row] = m1[row];
		m3[column] = m2[column];
		for (i = 0; i < m3[row]; i++)
		{
			for (j = 0; j < m3[column]; j++)
			{
				m3[MAX_SIZE * i + j] = 0;
				for (k = 0; k < s; k++)
					m3[MAX_SIZE * i + j] += m1[MAX_SIZE * i + k] * m2[MAX_SIZE * k + j];
			}
		}
		cout << "��������˺�Ϊ��\n";
		Display_Matrix(m3);
	}
}
void conv()
{
	int kernel_size = 3, padding = 1, stride = 1, dilation = 1;
	while (true)
	{
		cout << "������kernel_size �� padding ���Կո�ָ�(�ܾ������ƣ����ɸ���kernel_size��padding):\n";
		cin >> kernel_size >> padding;
		if (kernel_size % 2 == 0)
		{
			cout << "wrong:������֧�ִ�СΪż���ľ����,���������롣\n";
			wait_for_enter();
			system("cls");
		}
		else
			break;
	}
	int i, j;
	int x, y;
	int m, n;
	int sum;
	Define_Matrix(m1);
	Define_Kernel(m2, kernel_size);
	m3[row] = m1[row] - (kernel_size / 2 - padding) * 2;
	m3[column] = m1[column] - (kernel_size / 2 - padding) * 2;
	for (i = 0; i < m3[row]; i++)
	{
		x = i + kernel_size / 2  - padding;
		for (j = 0; j < m3[column]; j++)
		{
			y = j + kernel_size / 2  - padding;
			sum = 0;
			for(m=-kernel_size/2;m<=kernel_size / 2;m++)
				for (n = -kernel_size / 2; n <= kernel_size / 2; n++)
				{
					if ((x + m >= 0) && (x + m < m1[row]) && (y + n >= 0) && (y + n < m1[column]))
						sum += m1[(x + m) * MAX_SIZE + y + n] * m2[(kernel_size / 2 + m) * MAX_SIZE + kernel_size / 2 + n];
				}
			m3[i * MAX_SIZE + j] = sum;
		}
	}
	cout << "������Ϊ��\n";
	Display_Matrix(m3);
}

void conv(int m1[], int m2[], int m3[])//conv��������
{
	int kernel_size = 3, padding = 1, stride = 1;
	int i, j;
	int x, y;
	int m, n;
	int sum;
	int t = 0;
	for (i = 0; i < 9; i++)
		t = t + m2[i];
	m3[row] = m1[row] - (kernel_size / 2 - padding) * 2;
	m3[column] = m1[column] - (kernel_size / 2 - padding) * 2;
	for (i = 0; i < m3[row]; i++)
	{
		x = i + kernel_size / 2 - padding;
		for (j = 0; j < m3[column]; j++)
		{
			y = j + kernel_size / 2 - padding;
			sum = 0;
			for (m = -kernel_size / 2; m <= kernel_size / 2; m++)
				for (n = -kernel_size / 2; n <= kernel_size / 2; n++)
				{
					if ((x + m >= 0) && (x + m < m1[row]) && (y + n >= 0) && (y + n < m1[column]))
						sum += m1[(x + m) * m1[column] + y + n] * m2[(kernel_size / 2 + m) * 3 + kernel_size / 2 + n];
				}
			if (t == 0)
				t = 1;
			if (sum/t < 0)
				sum = 0;
			if (sum / t > 255)
				sum = 255*t;
			m3[i * m3[column] + j] = sum / t;
		}
	}
}
Mat image(MAX_SIZE,MAX_SIZE,CV_8U);
int originalImage[MAX_SIZE * MAX_SIZE + 2];
int kernel1[] = { 1,1,1,1,1,1,1,1,1 };
int kernel2[] = { -1,-2,-1,0,0,0,1,2,1 };
int kernel3[] = { -1,0,1,-2,0,2,-1,0,1 };
int kernel4[] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
int kernel5[] = { -1,-1,0,-1,0,1,0,1,1 };
int kernel6[] = { 1,2,1,2,4,2,1,2,1 };
int mid1[MAX_SIZE * MAX_SIZE + 2];
int mid2[MAX_SIZE * MAX_SIZE + 2];
int mid3[MAX_SIZE * MAX_SIZE + 2];
int mid4[MAX_SIZE * MAX_SIZE + 2];
int mid5[MAX_SIZE * MAX_SIZE + 2];
int mid6[MAX_SIZE * MAX_SIZE + 2];
Mat jpg1(MAX_SIZE, MAX_SIZE, CV_8U);
Mat jpg2(MAX_SIZE, MAX_SIZE, CV_8U);
Mat jpg3(MAX_SIZE, MAX_SIZE, CV_8U);
Mat jpg4(MAX_SIZE, MAX_SIZE, CV_8U);
Mat jpg5(MAX_SIZE, MAX_SIZE, CV_8U);
Mat jpg6(MAX_SIZE, MAX_SIZE, CV_8U);
Status demo()
{
	int i, j;
	char fname[100] = { "demolena.jpg" };
	image = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Image no find,error!" << endl;
		return ERROR;
	}
	originalImage[row] = image.rows;
	originalImage[column] = image.cols;
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			originalImage[MAX_SIZE * i + j] = (int)image.at<uchar>(i, j);
	conv(originalImage, kernel1, mid1);
	conv(originalImage, kernel2, mid2);
	conv(originalImage, kernel3, mid3);
	conv(originalImage, kernel4, mid4);
	conv(originalImage, kernel5, mid5);
	conv(originalImage, kernel6, mid6);

	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			jpg1.at<uchar>(i, j) = (uchar)mid1[MAX_SIZE * i + j];
	imshow("kernel1", jpg1);
	imwrite("kernel1.jpg", jpg1);

	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			jpg2.at<uchar>(i, j) = (uchar)mid2[MAX_SIZE * i + j];
	imshow("kernel2", jpg2);
	imwrite("kernel2.jpg", jpg2);

	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			jpg3.at<uchar>(i, j) = (uchar)mid3[MAX_SIZE * i + j];
	imshow("kernel13", jpg3);
	imwrite("kernel3.jpg", jpg3);

	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			jpg4.at<uchar>(i, j)= (uchar)mid4[MAX_SIZE * i + j];
	imshow("kernel4", jpg4);
	imwrite("kernel4.jpg", jpg4);

	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			jpg5.at<uchar>(i, j) = (uchar)mid5[MAX_SIZE * i + j];
	imshow("kernel5", jpg5);
	imwrite("kernel5.jpg", jpg5);

	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			jpg6.at<uchar>(i, j) = (uchar)mid6[MAX_SIZE * i + j];
	imshow("kernel6", jpg6);
	imwrite("kernel6.jpg", jpg6);

	waitKey(0);
	return OK;
}

//����Ϊ�ӷ���

int greatthreshold()
{
	int i, j;
	int degree[256] = { 0 };
	int num;
	int threshold, greatthreshold;
	double w0, w1;
	double u0, u1, u;
	double S, greatS = 0;
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
		degree[originalImage[MAX_SIZE * i + j]]++;
	num = originalImage[row] * originalImage[column];
	for (threshold = 0; threshold < 256; threshold++)
	{
		w0 = 0;
		w1 = 0;
		u0 = 0;
		u1 = 0;
		for (i = 0; i < 256; i++)
		{
			if (i <= threshold)
			{
				w0 += degree[i];
				u0 += i * degree[i];
			}
			else
			{
				w1 += degree[i];
				u1 += i * degree[i];
			}
		}
		u0 = u0 / w0;
		u1 = u1 / w1;
		w0 = w0 / num;
		w1 = w1 / num;
		u = w0 * u0 + w1 * u1;
		S = w0 * (u0 - u) * (u0 - u) + w1 * (u1 - u) * (u1 - u);
		if (S > greatS)
		{
			greatS = S;
			greatthreshold = threshold;
		}
	}
	return greatthreshold;
}
void method(int &top, int &bottom)
{
	int choice;
	cout << "��ѡ���ֵ��������\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "*" << "1 THRESH_BINARY" << " 2 THRESH_BINARY_INV" << " 3 THRESH_TRUNC\t" << "*\n";
	cout << "*" << "4 THRESH_TOZERO" << " 5 THRESH_TOZERO_INV" << " ���ఴ������������\t" << "*\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "ѡ��˵���<1-5>��Ĭ��ֵ:\n";
	choice = _getch();
	system("cls");
	switch (choice)//-1�����ֻҶ�ֵ��-2����Ҷ�ֵ�趨Ϊ��ֵ
	{
	case '1':top = 255; bottom = 0; break;
	case '2':top = 0; bottom = 255; break;
	case '3':top = -2; bottom = -1; break;
	case '4':top = 0; bottom = -1; break;
	case '5':top = -1; bottom = 0; break;
	default:top = -1; bottom = -1;
	}
}
Status OTSU_GRAY()
{
	char fname[100];
	int t;
	int i, j;
	double INDEX;
	int top = 255, bottom = 0;
	getfname(fname);
	image = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Image no find,error!" << endl;
		return ERROR;
	}
	originalImage[row] = image.rows;
	originalImage[column] = image.cols;
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			originalImage[MAX_SIZE * i + j] = (int)image.at<uchar>(i, j);
	t = greatthreshold();
	method(top, bottom);
	cout << "�����뷧ֵ��������\n";
	cin >> INDEX;
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
		{
			if (originalImage[MAX_SIZE * i + j] > t* INDEX)
			{
				if (top == -2)
					originalImage[MAX_SIZE * i + j] = t;
				else if (top == -1)
					;
				else
					originalImage[MAX_SIZE * i + j] = top;
			}
			else
			{
				if (bottom == -2)
					originalImage[MAX_SIZE * i + j] = t;
				else if (bottom == -1)
					;
				else
					originalImage[MAX_SIZE * i + j] = bottom;
			}
		}
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			image.at<uchar>(i, j) = (uchar)originalImage[MAX_SIZE * i + j];
	imshow("otsu", image);
	imwrite("OTSU.jpg", image);
	waitKey(0);
	return OK;
}

int RGB[MAX_SIZE * MAX_SIZE * 3];
Mat picture(MAX_SIZE, MAX_SIZE, CV_8UC3);
Status OTSU_RGB()
{
	char fname[100];
	int t;
	int i, j, k;
	double INDEX;
	int top = 255, bottom = 0;
	bool flag = false;
	char choice;
	getfname(fname);
	image = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Image no find,error!" << endl;
		return ERROR;
	}
	do
	{
		Status Matting();
		Matting();
		Status OpenClose();
		OpenClose();
		cout << "��������<����y/Yȷ��>";
		choice = _getch();
		system("cls");
		if (choice == 'y' || choice == 'Y')
			flag = true;
		else
			flag = false;

	} while (flag);
	t = greatthreshold();
	method(top, bottom);
	cout << "�����뷧ֵ��������\n";
	cin >> INDEX;
	picture = imread(fname, CV_LOAD_IMAGE_COLOR);
	for (i = 0; i < picture.rows; i++)
		for (j = 0; j < picture.cols; j++)
			for (k = 0; k < 3; k++)
				RGB[picture.cols * 3 * i + 3 * j + k] = picture.at<Vec3b>(i, j)[k];
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
		{
			if (originalImage[MAX_SIZE * i + j] > t* INDEX)
			{
				if (top == -2)
					for (k = 0; k < 3; k++)
						RGB[picture.cols * 3 * i + 3 * j + k] = t;
				else if (top == -1)
					;
				else
					for (k = 0; k < 3; k++)
						RGB[picture.cols * 3 * i + 3 * j + k] = top;
			}
			else
			{
				if (bottom == -2)
					for (k = 0; k < 3; k++)
						RGB[picture.cols * 3 * i + 3 * j + k] = t;
				else if (bottom == -1)
					;
				else
					for (k = 0; k < 3; k++)
						RGB[picture.cols * 3 * i + 3 * j + k] = bottom;
			}
		}
	for (i = 0; i < picture.rows; i++)
		for (j = 0; j < picture.cols; j++)
			for (k = 0; k < 3; k++)
				picture.at<Vec3b>(i, j)[k] = RGB[picture.cols * 3 * i + 3 * j + k];
	imshow("otsu_rgb", picture);
	imwrite("OTSU_RGB.jpg", picture);
	waitKey(0);
	return OK;
}

void OTSU()
{
	char c;
	cout << "�Ƿ�ʹ��RGB��ͨ������(����y/Yȷ������������ȡ��)" << endl;
	c = _getch();
	system("cls");
	if (c == 'y' || c == 'Y')
		OTSU_RGB();
	else
		OTSU_GRAY();
}

Status Matting()
{
	bool flag = true;
	int i, j ,n;
	int x, y;
	char choice;
	int size = 3, degree;
	int max, min;
	originalImage[row] = image.rows;
	originalImage[column] = image.cols;
	cout << "[0]��ʴ����\t[1]���ʹ���\n��������ȡ������\nѡ��˵���<0 / 1>:\n";
	choice = _getch();
	system("cls");
	if (choice == '1')
		flag = true;
	else if (choice == '0')
		flag = false;
	else
	{
		for (i = 0; i < originalImage[row]; i++)
			for (j = 0; j < originalImage[column]; j++)
				originalImage[MAX_SIZE * i + j] = (int)image.at<uchar>(i, j);
		return OK;
	}
	cout << "������˴�С��";
	cin >> size;
	cout << "�����븯ʴ/����������";
	cin >> degree;
	system("cls");
	for (n = 1; n <= degree; n++)
	{
		for (i = 0; i < image.rows; i++)
			for (j = 0; j < image.cols; j++)
			{
				max = 0;
				min = 255;
				for (x = -size / 2; x <= size / 2; x++)
					for (y = -size / 2; y <= size / 2; y++)
					{
						if (i + x >= 0 && i + x < image.rows && j + y >= 0 && j + y < image.cols)
						{
							if (image.at<uchar>(i + x, j + y) > max)
								max = image.at<uchar>(i + x, j + y);
							if (image.at<uchar>(i + x, j + y) < min)
								min = image.at<uchar>(i + x, j + y);
						}
					}
				if (flag)
					originalImage[MAX_SIZE * i + j] = max;
				else
					originalImage[MAX_SIZE * i + j] = min;
			}
		for (i = 0; i < originalImage[row]; i++)
			for (j = 0; j < originalImage[column]; j++)
				image.at<uchar>(i, j) = (uchar)originalImage[MAX_SIZE * i + j];
	}
	imshow("��ʴ/����Ч��ͼ", image);
	waitKey(0);
	return OK;
}

Status OpenClose()
{
	bool flag = true;
	int i, j, n;
	int x, y;
	char choice;
	int size = 3;
	int degree = 1;
	int max, min;
	originalImage[row] = image.rows;
	originalImage[column] = image.cols;
	cout << "[0]������\t[1]������\n��������ȡ������\nѡ��˵���<0 / 1>:\n";
	choice = _getch();
	system("cls");
	if (choice == '1')
		flag = true;
	else if (choice == '0')
		flag = false;
	else
	{
		for (i = 0; i < originalImage[row]; i++)
			for (j = 0; j < originalImage[column]; j++)
				originalImage[MAX_SIZE * i + j] = (int)image.at<uchar>(i, j);
		return OK;
	}
	cout << "������˴�С��";
	cin >> size;
	cout << "�����뿪��������";
	cin >> degree;
	system("cls");
	if (flag)
	{
		for (n = 1; n <= degree; n++)
		{
			for (i = 0; i < image.rows; i++)
				for (j = 0; j < image.cols; j++)
				{
					max = 0;
					min = 255;
					for (x = -size / 2; x <= size / 2; x++)
						for (y = -size / 2; y <= size / 2; y++)
						{
							if (i + x >= 0 && i + x < image.rows && j + y >= 0 && j + y < image.cols)
							{
								if (image.at<uchar>(i + x, j + y) > max)
									max = image.at<uchar>(i + x, j + y);
								if (image.at<uchar>(i + x, j + y) < min)
									min = image.at<uchar>(i + x, j + y);
							}
						}
					originalImage[MAX_SIZE * i + j] = max;
				}
			for (i = 0; i < originalImage[row]; i++)
				for (j = 0; j < originalImage[column]; j++)
					image.at<uchar>(i, j) = (uchar)originalImage[MAX_SIZE * i + j];
			for (i = 0; i < image.rows; i++)
				for (j = 0; j < image.cols; j++)
				{
					max = 0;
					min = 255;
					for (x = -size / 2; x <= size / 2; x++)
						for (y = -size / 2; y <= size / 2; y++)
						{
							if (i + x >= 0 && i + x < image.rows && j + y >= 0 && j + y < image.cols)
							{
								if (image.at<uchar>(i + x, j + y) > max)
									max = image.at<uchar>(i + x, j + y);
								if (image.at<uchar>(i + x, j + y) < min)
									min = image.at<uchar>(i + x, j + y);
							}
						}
					originalImage[MAX_SIZE * i + j] = min;
				}
			for (i = 0; i < originalImage[row]; i++)
				for (j = 0; j < originalImage[column]; j++)
					image.at<uchar>(i, j) = (uchar)originalImage[MAX_SIZE * i + j];
		}
		imshow("������Ч��ͼ", image);
		waitKey(0);
	}
	else
	{
		for (n = 1; n <= degree; n++)
		{
			for (i = 0; i < image.rows; i++)
				for (j = 0; j < image.cols; j++)
				{
					max = 0;
					min = 255;
					for (x = -size / 2; x <= size / 2; x++)
						for (y = -size / 2; y <= size / 2; y++)
						{
							if (i + x >= 0 && i + x < image.rows && j + y >= 0 && j + y < image.cols)
							{
								if (image.at<uchar>(i + x, j + y) > max)
									max = image.at<uchar>(i + x, j + y);
								if (image.at<uchar>(i + x, j + y) < min)
									min = image.at<uchar>(i + x, j + y);
							}
						}
					originalImage[MAX_SIZE * i + j] = min;
				}
			for (i = 0; i < originalImage[row]; i++)
				for (j = 0; j < originalImage[column]; j++)
					image.at<uchar>(i, j) = (uchar)originalImage[MAX_SIZE * i + j];
			for (i = 0; i < image.rows; i++)
				for (j = 0; j < image.cols; j++)
				{
					max = 0;
					min = 255;
					for (x = -size / 2; x <= size / 2; x++)
						for (y = -size / 2; y <= size / 2; y++)
						{
							if (i + x >= 0 && i + x < image.rows && j + y >= 0 && j + y < image.cols)
							{
								if (image.at<uchar>(i + x, j + y) > max)
									max = image.at<uchar>(i + x, j + y);
								if (image.at<uchar>(i + x, j + y) < min)
									min = image.at<uchar>(i + x, j + y);
							}
						}
					originalImage[MAX_SIZE * i + j] = max;
				}
			for (i = 0; i < originalImage[row]; i++)
				for (j = 0; j < originalImage[column]; j++)
					image.at<uchar>(i, j) = (uchar)originalImage[MAX_SIZE * i + j];
		}
		imshow("������Ч��ͼ", image);
		waitKey(0);
	}
	return OK;
}

Status Canny()
{
	char fname[100];
	int i, j, k;
	int value;
	Mat canny;
	bool flag = false;
	getfname(fname);
	image = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Image no find,error!" << endl;
		return ERROR;
	}
	originalImage[row] = image.rows;
	originalImage[column] = image.cols;
	cout << "������Canny��ֵ��(snowball�Ƽ�213��";//value=213
	cin >> value;
	Canny(image, canny, value, value * 3, 3, false);
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			originalImage[MAX_SIZE * i + j] = (int)canny.at<uchar>(i, j);
	imshow("����ͼ", canny);
	picture = imread(fname, CV_LOAD_IMAGE_COLOR);
	for (i = 0; i < picture.rows; i++)
		for (j = 0; j < picture.cols; j++)
			for (k = 0; k < 3; k++)
				RGB[picture.cols * 3 * i + 3 * j + k] = picture.at<Vec3b>(i, j)[k];
	for (i = 0; i < originalImage[row]; i++)
	{
		flag=false;
		for (j = 0; j < originalImage[column]; j++)
		{
			if (originalImage[i * MAX_SIZE + j] ==255)
				flag = true;
			if (!flag)
			{
				for (k = 0; k < 3; k++)
					RGB[picture.cols * 3 * i + 3 * j + k] = 0;
			}
		}
		flag = false;
		for (j = originalImage[column] - 1; j >= 0; j--)
		{
			if (originalImage[i * MAX_SIZE + j] == 255)
				flag = true;
			if (!flag)
			{
				for (k = 0; k < 3; k++)
					RGB[picture.cols * 3 * i + 3 * j + k] = 0;
			}
		}
	}
	for (j = 0; j < originalImage[column]; j++)
	{
		flag = false;
		for (i = 0; i < originalImage[row]; i++)
		{
			if (originalImage[i * MAX_SIZE + j] == 255)
				flag = true;
			if (!flag)
			{
				for (k = 0; k < 3; k++)
					RGB[picture.cols * 3 * i + 3 * j + k] = 0;
			}
		}
		flag = false;
		for (i = originalImage[row] - 1; i >= 0 ; i--)
		{
			if (originalImage[i * MAX_SIZE + j] == 255)
				flag = true;
			if (!flag)
			{
				for (k = 0; k < 3; k++)
					RGB[picture.cols * 3 * i + 3 * j + k] = 0;
			}
		}
	}
	for (i = 0; i < picture.rows; i++)
		for (j = 0; j < picture.cols; j++)
			for (k = 0; k < 3; k++)
				picture.at<Vec3b>(i, j)[k] = RGB[picture.cols * 3 * i + 3 * j + k];
	imshow("canny", picture);
	imwrite("canny_RGB.jpg", picture);
	waitKey(0);
	return OK;
}

void eggshell()
{
	cout << "\n\n\n\n\n\n\n\n\n��ϲ�㷢�ֲʵ���d=====(������*)b\n";
	cout << "��˵�����汣�ӣ�����BUG\n��Ի��BUG���ģ�����̱����";
	wait_for_enter();
}

int main()
{
	char choice, ch;
	wait_for_enter();
	while (true) //ע���ѭ���˳�������
	{
		system("cls"); //��������

		menu(); //���ò˵���ʾ���������в������

		choice = _getch();// ��Ҫ������˵�ѡ����choice

		system("cls");

		if (choice == '0') //ѡ���˳�
		{
			cout << "\n ȷ���˳���?(����y/Yȷ��)" << endl;
			ch=_getch();
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}

		switch (choice)
		{
		case '1':matriplus(); break;
		case '2':nummulti(); break;
		case '3':matritrans(); break;
		case '4':matrimulti(); break;
		case '5':hadamulti(); break;
		case '6':conv(); break;
		case '7':demo(); break;
		case '8':OTSU(); break;
		case '9':Canny(); break;
		case '%':eggshell(); break;
		default:
			cout << "\n ����������������" << endl;
		}
	}
	return 0;
}