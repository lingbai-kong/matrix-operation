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
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
void menu()
{
	cout << "***********孔令百*********1852146*********矩阵操作*******\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "*\t" << "1 矩阵加法\t" << "2 矩阵数乘\t" << "3 矩阵转置\t" << "*\n";
	cout << "*\t" << "4 矩阵乘法\t" << "5 Hadamard乘积\t" << "6 矩阵卷积\t" << "*\n";
	cout << "*\t" << "7 卷积应用\t" << "8 OTSU算法\t" << "9 Canny算法\t" << "*\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "**********************输入 0 退出系统********************\n";
	cout << "选择菜单项<0-9>:\n";
}
void getfname(char name[])
{
	int choice;
	cout << "请选择被处理图像：\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "*\t" << "1 demolena\t" << "2 snowball\t" << "3 polyhedrosis\t" << "*\n";
	cout << "*\t" << "4 ship\t\t" << "5 brain\t\t" << "其余按键：自定义" << "*\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "选择菜单项<1-5>或自定义:\n";
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
		cout << "请输入图片名：";
		cin >> name;
	}
}

void Define_Matrix(int M[])
{
	int i, j;
	cout << "请输入矩阵的行数：";
	cin >> M[row];
	cout << "请输入矩阵的列数：";
	cin >> M[column];
	cout << "请输入矩阵：\n";
	for (i = 0; i < M[row]; i++)
	{
		cout << "\t┃";
		M[MAX_SIZE * i] = getint();
		cout << setw(5) << setfill(' ') << M[MAX_SIZE * i];
		for (j = 1; j < M[column]; j++)
		{
			M[MAX_SIZE * i + j] = getint();
			cout << setw(5) << setfill(' ') << M[MAX_SIZE * i + j];

		}
		cout << " ┃" << endl;
	}
	cout << "输入完毕。\n";
}
void Define_Kernel(int m[], int size)
{
	int i, j;
	m[row] = size;
	m[column] = size;
	cout << "请输入卷积核：\n";
	for (i = 0; i < m[row]; i++)
	{
		cout << "\t┃";
		m[MAX_SIZE * i] = getint();
		cout << setw(5) << setfill(' ') << m[MAX_SIZE * i];
		for (j = 1; j < m[column]; j++)
		{
			m[MAX_SIZE * i + j] = getint();
			cout << setw(5) << setfill(' ') << m[MAX_SIZE * i + j];

		}
		cout << " ┃" << endl;
	}
	cout << "输入完毕。\n";
}
void Define_MGroup(int M1[], int M2[])
{
	cout << "构造第一个矩阵\n";
	Define_Matrix(M1);
	cout << "构造第二个矩阵\n";
	Define_Matrix(M2);
}
void Display_Matrix(int M[])
{
	int i, j;
	for (i = 0; i < M[row]; i++)
	{
		cout << "\t┃" << setw(5) << setfill(' ') << M[MAX_SIZE * i];
		for (j = 1; j < M[column]; j++)
			cout << setw(5) << setfill(' ') << M[MAX_SIZE * i + j];
		cout << " ┃" << endl;
	}
}

int m1[MAX_SIZE * MAX_SIZE + 2];
int m2[MAX_SIZE * MAX_SIZE + 2];
int m3[MAX_SIZE * MAX_SIZE + 2];

void matriplus() {
	int i, j;
	Define_MGroup(m1, m2);
	if ((m1[row] != m2[row]) || (m1[column] != m2[column]))
		cout << "wrong:两矩阵不同型\n";
	else
	{
		m3[row] = m1[row];
		m3[column] = m1[column];
		for (i = 0; i < m3[row]; i++)
			for (j = 0; j < m3[column]; j++)
				m3[MAX_SIZE * i + j] = m1[MAX_SIZE * i + j] + m2[MAX_SIZE * i + j];
		cout << "两矩阵之和为：\n";
		Display_Matrix(m3);
	}
}
void hadamulti()
{
	int i, j;
	Define_MGroup(m1, m2);
	if ((m1[row] != m2[row]) || (m1[column] != m2[column]))
		cout << "wrong:两矩阵不同型\n";
	else
	{
		m3[row] = m1[row];
		m3[column] = m1[column];
		for (i = 0; i < m3[row]; i++)
			for (j = 0; j < m3[column]; j++)
				m3[MAX_SIZE * i + j] = m1[MAX_SIZE * i + j] * m2[MAX_SIZE * i + j];
		cout << "两矩阵的Hadamard乘积为：\n";
		Display_Matrix(m3);
	}
}
void nummulti()
{
	int i, j;
	int n;
	Define_Matrix(m1);
	cout << "请输入要数乘的数字：";
	cin >> n;
	m2[row] = m1[row];
	m2[column] = m1[column];
	for (i = 0; i < m2[row]; i++)
		for (j = 0; j < m2[column]; j++)
			m2[MAX_SIZE * i + j] = m1[MAX_SIZE * i + j] * n;
	cout << "该矩阵数乘后为：\n";
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
	cout << "该矩阵转置后为：\n";
	Display_Matrix(m2);
}
void matrimulti()
{
	int i, j, k;
	int s = m1[column];
	Define_MGroup(m1, m2);
	if (m1[column] != m2[row])
		cout << "wrong:矩阵A的列数和矩阵B的行数不相等\n";
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
		cout << "两矩阵相乘后为：\n";
		Display_Matrix(m3);
	}
}
void conv()
{
	int kernel_size = 3, padding = 1, stride = 1, dilation = 1;
	while (true)
	{
		cout << "请输入kernel_size 、 padding 并以空格分隔(受精力限制，仅可更改kernel_size和padding):\n";
		cin >> kernel_size >> padding;
		if (kernel_size % 2 == 0)
		{
			cout << "wrong:本程序不支持大小为偶数的卷积核,请重新输入。\n";
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
	cout << "卷积结果为：\n";
	Display_Matrix(m3);
}

void conv(int m1[], int m2[], int m3[])//conv函数重载
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

//以下为加分项

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
	cout << "请选择二值化方法：\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "*" << "1 THRESH_BINARY" << " 2 THRESH_BINARY_INV" << " 3 THRESH_TRUNC\t" << "*\n";
	cout << "*" << "4 THRESH_TOZERO" << " 5 THRESH_TOZERO_INV" << " 其余按键：不做处理\t" << "*\n";
	cout << setw(58) << setfill('*') << '\n';
	cout << "选择菜单项<1-5>或默认值:\n";
	choice = _getch();
	system("cls");
	switch (choice)//-1代表保持灰度值，-2代表灰度值设定为阀值
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
	cout << "请输入阀值调控因子\n";
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
		cout << "继续处理？<输入y/Y确定>";
		choice = _getch();
		system("cls");
		if (choice == 'y' || choice == 'Y')
			flag = true;
		else
			flag = false;

	} while (flag);
	t = greatthreshold();
	method(top, bottom);
	cout << "请输入阀值调控因子\n";
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
	cout << "是否使用RGB三通道处理？(输入y/Y确定，其他输入取消)" << endl;
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
	cout << "[0]腐蚀处理\t[1]膨胀处理\n输入其它取消处理\n选择菜单项<0 / 1>:\n";
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
	cout << "请输入核大小：";
	cin >> size;
	cout << "请输入腐蚀/膨胀重数：";
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
	imshow("腐蚀/膨胀效果图", image);
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
	cout << "[0]开运算\t[1]闭运算\n输入其它取消处理\n选择菜单项<0 / 1>:\n";
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
	cout << "请输入核大小：";
	cin >> size;
	cout << "请输入开闭重数：";
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
		imshow("闭运算效果图", image);
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
		imshow("开运算效果图", image);
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
	cout << "请输入Canny阈值：(snowball推荐213）";//value=213
	cin >> value;
	Canny(image, canny, value, value * 3, 3, false);
	for (i = 0; i < originalImage[row]; i++)
		for (j = 0; j < originalImage[column]; j++)
			originalImage[MAX_SIZE * i + j] = (int)canny.at<uchar>(i, j);
	imshow("轮廓图", canny);
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
	cout << "\n\n\n\n\n\n\n\n\n恭喜你发现彩蛋！d=====(￣▽￣*)b\n";
	cout << "我说：佛祖保佑，永无BUG\n佛曰：BUG泛滥，我已瘫痪！";
	wait_for_enter();
}

int main()
{
	char choice, ch;
	wait_for_enter();
	while (true) //注意该循环退出的条件
	{
		system("cls"); //清屏函数

		menu(); //调用菜单显示函数，自行补充完成

		choice = _getch();// 按要求输入菜单选择项choice

		system("cls");

		if (choice == '0') //选择退出
		{
			cout << "\n 确定退出吗?(输入y/Y确定)" << endl;
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
			cout << "\n 输入错误，请从新输入" << endl;
		}
	}
	return 0;
}