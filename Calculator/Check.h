#pragma once
#include "pch.h"
#include<iostream>
#include <afxstr.h>
using namespace std;

/// <summary>
/// ��ʽ��
/// ��CString���͵���������С�������ת��ΪNumber���͵���
/// </summary>
/// <param name="n">Ҫ��ʽ������</param>
void FormatNum(Number& n)
{
	if (n.num.GetAt(0) == '-')
	{
		n.isnega = true;
		n.num = n.num.Right(n.num.GetLength() - 1);
	}
	else
		n.isnega = false;
	//�����Ƿ���С����
	if (n.num.Find('.')>0)
	{
		n.poz = n.num.GetLength() - n.num.Find('.') - 1;
		//ȥ��С����
		n.num.Remove('.');
	}
	else
	{
		n.poz = 0;
	}
	//0.01ȥ��С�������001��ȥ��ǰ���0
	while (n.num.GetAt(0) == '0'&&n.num.GetLength()>1)
	{
		n.num = n.num.Right(n.num.GetLength() - 1);
	}
}

/// <summary>
/// ��ʽ��
/// ��CString���͵���������С�������ת��ΪNumber���͵���
/// </summary>
/// <param name="t">Ҫ��ʽ������</param>
/// <param name="n">С����λ��<0 =0 >0</param>
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
/// ȥ��ʽ��
/// ��Number���͵�����ת��ΪCString���͵���������С�������
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
CString relFormatNum(Number n)
{
	CString s=n.num;
	//ȥ�������0
	while (s.Find('0') == 0)
	{
		s = s.Right(s.GetLength() - 1);
	}
	//���С����
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
	

	//���������
	if (n.isnega)
		s = '-' + s;
	return s;
}

/// <summary>
/// num��������n��0
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