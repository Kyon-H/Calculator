#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

/// <summary>
/// �����ַ���βָ��
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
char* findend(char* a);

/// <summary>
/// �Ƚ������ַ�����С
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <returns></returns>
int abigerb(char* numa, char* numb);

/// <summary>
/// �����ӷ�
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
void addition(char* numa, char* numb, char* result);

/// <summary>
/// ��������
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
void subtract(char* numa, char* numb, char* result);

/// <summary>
/// �����˷�
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
void multiply(char* numa, char* numb, char* result);

/// <summary>
/// ��������
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
/// <param name="remainder"></param>
void divide2(char* numa, char* numb, char* result, char* remainder);

/// <summary>
/// ����ģ
/// </summary>
/// <param name="bigNumber"></param>
/// <param name="divisor"></param>
/// <param name="result"></param>
void mod(char* bigNumber, char* divisor, char* result);

