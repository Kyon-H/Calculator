#pragma once
#include "pch.h"
#include<iostream>
#include <afxstr.h>
using namespace std;

/// <summary>
/// 格式化
/// 将CString类型的有正负，小数点的数转化为Number类型的数
/// </summary>
/// <param name="n">要格式化的数</param>
void FormatNum(Number& n)
{
	if (n.num.GetAt(0) == '-')
	{
		n.isnega = true;
		n.num = n.num.Right(n.num.GetLength() - 1);
	}
	else
		n.isnega = false;
	//查找是否有小数点
	if (n.num.Find('.')>0)
	{
		n.poz = n.num.GetLength() - n.num.Find('.') - 1;
		//去除小数点
		n.num.Remove('.');
	}
	else
	{
		n.poz = 0;
	}
	//0.01去除小数点后变成001，去除前面的0
	while (n.num.GetAt(0) == '0'&&n.num.GetLength()>1)
	{
		n.num = n.num.Right(n.num.GetLength() - 1);
	}
}

/// <summary>
/// 格式化
/// 将CString类型的有正负，小数点的数转化为Number类型的数
/// </summary>
/// <param name="t">要格式化的数</param>
/// <param name="n">小数点位置<0 =0 >0</param>
void FormatNum(Number& t, int n)
{
	if (t.num.GetAt(0) == '-')
	{
		t.isnega = true;
		t.num = t.num.Right(t.num.GetLength() - 1);
	}
	else
		t.isnega = false;
	t.poz = n;
}

/// <summary>
/// 去格式化
/// 将Number类型的数，转化为CString类型的有正负，小数点的数
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
CString relFormatNum(Number n)
{
	CString s=n.num;
	//去除多余的0
	while (s.Find('0') == 0)
	{
		s = s.Right(s.GetLength() - 1);
	}
	//添加小数点
	//n.poz<0
	for (int i = n.poz; i < 0; ++i)
	{
		s = s + '0';
	}
	//n.poz>0
	for (int i = s.GetLength(); i < n.poz; ++i)
	{
		s = '0' + s;
	}
	if (s.GetLength() - n.poz == 0)
	{
		CString temp("0.");
		s = temp + s;
	}
	else if (s.GetLength() - n.poz > 0 && n.poz > 0)
		s.Insert(s.GetLength() - n.poz, '.');
	

	//添加正负号
	if (n.isnega)
		s = '-' + s;
	return s;
}

/// <summary>
/// num后面增加n个0
/// </summary>
/// <param name="num"></param>
/// <param name="n"></param>
void Addzero(Number& num, int n)
{
	for (int i = 0; i < n; ++i)
	{
		CString temp('0');
		num.num = num.num + temp;
	}
}