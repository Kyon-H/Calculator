#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

/// <summary>
/// 查找字符串尾指针
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
char* findend(char* a);

/// <summary>
/// 比较两个字符串大小
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <returns></returns>
int abigerb(char* numa, char* numb);

/// <summary>
/// 大数加法
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
void addition(char* numa, char* numb, char* result);

/// <summary>
/// 大数减法
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
void subtract(char* numa, char* numb, char* result);

/// <summary>
/// 大数乘法
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
void multiply(char* numa, char* numb, char* result);

/// <summary>
/// 大数除法
/// </summary>
/// <param name="numa"></param>
/// <param name="numb"></param>
/// <param name="result"></param>
/// <param name="remainder"></param>
void divide2(char* numa, char* numb, char* result, char* remainder);

/// <summary>
/// 大数模
/// </summary>
/// <param name="bigNumber"></param>
/// <param name="divisor"></param>
/// <param name="result"></param>
void mod(char* bigNumber, char* divisor, char* result);

