#pragma once
#include "pch.h"
#include "BigInt.h"

struct Node    // ����һ��˫�����������������
{
	char data;     // ����*����Ϊ�ַ���ԭ��Ҫ��ʾ����
	Node* next;    // βָ��
	Node* ahead;   // ��ָ��
};

char* findend(char* a)
{
	a = a + strlen(a)-1;
	return a;
}

//����ֵ˵��:0��along ; 1��blong ; 2��along=blong
int abigerb(char* numa, char* numb)
{
	int along = (int)strlen(numa); //�������a�ĳ��ȣ�
	int blong = (int)strlen(numb); //�������b�ĳ��ȣ�
	char* pna = numa; //ָ����A�����λ��
	char* pnb = numb; //ָ����B�����λ��
	if (along > blong) return 1;
	if (along == blong)
	{
		while (*pna) //�Ƚ���������һ����
		{
			if (*pna > *pnb)return 1;
			else if (*pna < *pnb)return 0;
			else if (*pna == *pnb) { pna++; pnb++; }
		}
		return 2;
	}
	return 0;
}
/*--------------------------------------------------------------------------
*�������ƣ� �����ӷ�
*�������̣�1 �Ƚ���������һ����
* 2 �Գ�����Ϊѭ������
* 3 ��Ӧ����� ��λ����ֱ���¸�λ�����
* 4 ֱ��ѭ������
* 5 û��Ƹ������
*��ڲ�����numa��numb��result�ַ���
*���ڲ�������
*--------------------------------------------------------------------------*/
void addition(char* numa, char* numb, char* result)//����������֮��
{
	char* pna = findend(numa);// ָ��numa��һ��ָ�롣pna ָ����������λ��
	char* pnb = findend(numb);//ָ��numb��һ��ָ��   pnb ָ�򱻳��������λ��
	int along = (int)strlen(numa);//�������a�ĳ��ȣ�
	int blong = (int)strlen(numb); //�������b�ĳ��ȣ�
	int times = 0; // ���Ҫ������ٴΡ�
	int carry = 0, temp_result=0; //������λ ����ʱ���
	Node* head, // ���ڴ���ͷָ��
		* pstart, // ���ڴ�������ʱ����ָ��
		* pnew; //���������½��
	head = pstart = new Node; //��ʼ���׽���ͷ��㡣
	pstart->data = 0;
	pstart->next = NULL;
	pstart->ahead = NULL;

	if (abigerb(numa, numb) >= 1)
		times = (int)strlen(numa);//�Ƚ������ַ������ȣ��Դ����Ϊѭ������
	else
	{
		times = (int)strlen(numb);
		pna = findend(numb); //����ָ��
		pnb = findend(numa);
		along = (int)strlen(numb); //�������a�ĳ��ȣ�
		blong = (int)strlen(numa); //�������b�ĳ��ȣ�
	}
	while ((times-- && times >= 0) || carry != 0)
	{
		if (!pstart->next)//�����ǰΪ�ս�㣬�������½��
		{
			pnew = new Node;
			pnew->data = 0;
			pnew->next = NULL;
			pnew->ahead = pstart;
			pstart->next = pnew;
		}
		if (blong < 0)
			temp_result = pstart->data + (*pna - 48) + carry;
		else 
			temp_result = (pstart->data + (*pna - 48) + (*pnb - 48) + carry); //�����ֵ+��ֵ+��λ ��Ϊ��ǰ����ֵ
		pstart->data = temp_result % 10;//������λ
		carry = temp_result / 10; //������λ
		pstart = pstart->next; //����ƶ�
		blong--;
		along--;
		if (blong > 0)
			pnb--;//ָ�����򱻼�����λ
		else
			*pnb = 48;//pnb=0
		if (along > 0)
			pna--;//����ָ���ƶ�
		else
			*pna = 48;//pna=0
	}
	pstart = head; //Ѱ������Ľ�β��
	while (pstart->next != 0)
	{
		pstart->data += 48;//��Ϊ���ǵ�������ַ��������ٴ˼���48,��˳���
		pstart = pstart->next;
	}
	int tip = 0;//תΪ�ַ�����
	pstart = pstart->ahead; //����Ч��
	while (pstart != 0) //�������Ľ����
	{
		result[tip] = pstart->data;
		tip++;
		//cout<data;
		pstart = pstart->ahead;
	}
	result[tip] = '\0';
	pstart = head; //�ͷſռ�
	while (pstart->next != 0)
	{
		pnew = pstart->next; delete pstart;
		pstart = pnew;
	}
	return;
}

/*--------------------------------------------------------------------------
*�������ƣ� ��������
*�������̣�1 �Ƚ���������һ����
* 2 �Գ�����Ϊѭ������
* 3 ���������������ȣ������λ��ʼ��ֱ��������һ��������ʹ�����ȥС��
* 4 ��Ӧ����� ��λ����ֱ���¸�λ�����
* 5 ÿһλ��Ӧ�����ʱ���������ֿ��ܵ������a=b,a>b,a<b;
* 6 a>=bʱ�������,11-12,111-112,Ҫ���ǽ�λ
* 7 ֱ��ѭ������
*��ڲ�����numa��numb��result�ַ���
*���ڲ�������
*--------------------------------------------------------------------------*/
void subtract(char* numa, char* numb, char* result)//�����
{
	char* pna = findend(numa);//ָ��numa��һ��ָ�� pna ָ����������λ��
	char* pnb = findend(numb);//ָ��numb��һ��ָ�� pnb ָ�򱻼��������λ��
	int  along = (int)strlen(numa);//�������a�ĳ��ȣ�
	int  blong = (int)strlen(numb);//�������b�ĳ��ȣ�
	int  times = 0;         // ���Ҫ������ٴΡ�
	int  carry = 0;           //������λ  
	int  clear0 = 0;          //���������ǰ�����õ�'0'  13-5 = 08 ��Ч������
	int  isnegative = 0;      //�������ϱ��������ڼ���ʱ�������һ������
	Node* head,   // ���ڴ���ͷָ��
		* pstart,  // ���ڴ�������ʱ����ָ��
		* pnew;    //���������½�� 

	head = pstart = new Node;//��ʼ���׽���ͷ��㡣
	pstart->data = 0;
	pstart->next = NULL;
	pstart->ahead = NULL;

	if (abigerb(numa, numb))
		times = strlen(numa);//�Ƚ������ַ������ȣ��Դ����Ϊѭ������
	else //����λ���Խ����Ѷ�
	{
		times = strlen(numb);//�������ַ��������ļ�ȥ�����ַ������̵�
		pna = findend(numb);//����ָ��
		pnb = findend(numa);
		along = (int)strlen(numb);//�������a�ĳ��ȣ�
		blong = (int)strlen(numa);//�������b�ĳ��ȣ�
		isnegative = 1;//������Ҫ���ϸ���
	}

	while ((times--&&times>=0)||carry!=0)//carry != 0 ˵û�н�λʱ
	{
		if (!pstart->next)//�����ǰΪ�ս�㣬�������½��
		{
			pnew = new Node;
			pnew->data = 0;
			pnew->next = NULL;
			pnew->ahead = pstart;
			pstart->next = pnew;
		}
		if (times < 0)//���������֮�󣬽�λ����1����˵����ȻΪ��ֵ;
		{
			pstart->data = -3;//�������ڸ��� '-'//-3��Դ�ڸ�����0���3
			break;
		}
		else
		{
			if (*pna == *pnb)//�������ڱ�����ʱ���������ֱ������Ľ�������ý�λΪ0 
			{
				if (carry == 0)
					pstart->data = (*pna - 48) - (*pnb - 48); //111-11�����
				else
				{
					pstart->data = (*pna - 48) - (*pnb - 48) + 10 - carry;//1121-1112
					carry = 1;
				}
			}
			else if (*pna > *pnb)//�������ڱ�����ʱ���������ֱ������Ľ�������ý�λΪ0 
			{
				pstart->data = (*pna - 48) - (*pnb - 48) - carry;  //������λ
				carry = 0;
			}
			else if (*pna < *pnb)//˵�����������ڼ������ý����10���൱�ڽ�λ (carry)Ϊ1 
			{
				if (times > 0) pstart->data = (*pna - 48) - (*pnb - 48) + 10 - carry;//13-5�������Ϊ��ֵ
				else  pstart->data = (*pnb - 48) - (*pna - 48) - carry; //3-5  ��Ϊ��ǰ����ֵ
				carry = 1;
			}
		}
		pstart = pstart->next;          //����ƶ�
		blong--;
		if (blong > 0)pnb--;//ָ�����򱻼�����λ
		else *pnb = 48;//֮������ͱ�Ϊ��0�����κ�����
		pna--;//����ָ���ƶ���
	}
	if (isnegative == 1)//���ϸ��Ŵ�������һ���Ȳ���Ϊ����
	{
		pnew = new Node;
		pnew->data = 0;
		pnew->next = NULL;
		pnew->ahead = pstart;
		pstart->next = pnew;
		pstart->data = -3;//��ΪѰ������Ľ�β��Ҫͳһ��48������Ϊ��-����45�����Ե��ڡ�-3��
	}
	pstart = head;//Ѱ������Ľ�β��
	while (pstart->next != 0)
	{
		pstart->data += 48;//!!<<<��Ϊ���ǵ�������ַ��������ٴ˼���48>>>>  ��˳���
		pstart = pstart->next;
	}
	int tip = 0;//תΪ�ַ�����
	clear0 = 0;//  ���������ǰ�����õ�'0'  13-5 = 08 ��Ч��  ..>>�޸��ַ�������ָ��
	pstart = pstart->ahead;//����Ч��
	while (pstart != 0)//�������Ľ����
	{
		if (clear0 == 0 && ((int)pstart->data) == 48 && pstart->ahead != 0);//  ���������ǰ�����õ�'0'
		else
			result[tip++] = pstart->data;
		if (((int)pstart->data) != 48 && ((int)pstart->data) != 45)clear0 = 1;//'��'��
		pstart = pstart->ahead;
	}
	result[tip] = '\0';

	pstart = head;  //�ͷſռ�
	while (pstart->next != 0)
	{
		pnew = pstart->next; delete pstart;
		pstart = pnew;
	}
	return;
}

/*--------------------------------------------------------------------------
*�������ƣ� �����˷�
*�������̣�1 ��������������Ϊ�ַ���
* 2 ��һ��˫������
* 3 ����ָ��ֱ�ָ�������ַ��������λ
* 4 �Ե�һ��������͵�һ��λ���Եڶ����������������������
* 5 ������ָ����
* 6 �ظ�4��5���δ����λ�˵����λ
* 7 �������Ϊ���λ�������ף����һλ������β����������˳�������
* 4 ֱ��ѭ������
*��ڲ�����numa��numb��result�ַ���
*���ڲ�������
*--------------------------------------------------------------------------*/
void multiply(char* numa, char* numb, char* result)//�����������)//����˻�
{
	char* pna = findend(numa);//ָ��numa��һ��ָ�롣point numa      pna ָ����������λ��
	char* pnb = findend(numb);//ָ��numb��һ��ָ��                 //pnb ָ�򱻳��������λ��
	int along = (int)strlen(numa);//�������a�ĳ��ȣ�
	int blong = (int)strlen(numb);//�������b�ĳ��ȣ�
	int  carry = 0, temp_result;//������λ  ����ʱ�����
	Node* head,   // ���ڴ���ͷָ��
		* pstart,  // ���ڴ�������ʱ����ָ��
		* pnew,    //���������½�� 
		* pgo;     //��Ϊÿ������һ��ʱ���ص���һ����ʼ�ڵ���,��λ��������
	head = pstart = new Node;//��ʼ���׽���ͷ��㡣

	pstart->data = 0;
	pstart->next = NULL;
	pstart->ahead = NULL;

	while (along--)
	{
		pgo = pstart;//�����λ��
		blong = (int)strlen(numb);//��ʼ������
		pnb = findend(numb); //��ʼ��ָ��
		while ((blong-- && (blong >= 0)) || carry != 0)
		{
			if (!pstart->next)//�����ǰΪ�ս�㣬�������½��
			{
				pnew = new Node;
				pnew->data = 0;
				pnew->next = NULL;
				pnew->ahead = pstart;
				pstart->next = pnew;
			}

			if (blong < 0)temp_result = carry;//����ֻ�н�λ�����
			else temp_result = (pstart->data + (*pna - 48) * (*pnb - 48) + carry);//����ֵ+��ֵ+��λ��Ϊ��ֵ   
			pstart->data = temp_result % 10;  //������λ
			carry = temp_result / 10;           //������λ
			pstart = pstart->next;          //����ƶ�         
			pnb--; //ָ�����򱻳�����λ
		}
		pstart = pgo->next; //ǰ��һ��λ�ã�
		pna--;   //ָ�����������λ
	}

	pstart = head;//Ѱ������Ľ�β��
	while (pstart->next != 0)
	{
		pstart->data += 48;//!!<<<��Ϊ���ǵ�������ַ��������ٴ˼���48>>>>  ��˳���
		pstart = pstart->next;
	}

	int tip = 0;//תΪ�ַ�����
	pstart = pstart->ahead;//����Ч��
	while (pstart != 0)//�������Ľ����
	{
		result[tip++] = pstart->data;
		pstart = pstart->ahead;
	}
	result[tip] = '\0';

	pstart = head;  //�ͷſռ�
	while (pstart->next != 0)
	{
		pnew = pstart->next; delete pstart;
		pstart = pnew;
	}
	return;
}


/*--------------------------------------------------------------------------
*�������ƣ� ��������2
*�����뷨��1 ��ָ��ָ����������λ��������ʱ�ַ����� tempstr[a++] = pna
* 2 �����ʱ�ַ������ڱ�������������������������
* 3 ���С�ڱ�������ָ�뵽ͷ������ ���� ��ʱ�ַ���
*��ڲ�����numa��numb��result,remainder�ַ���
*���ڲ�������
*--------------------------------------------------------------------------*/
void divide2(char* numa, char* numb, char* result, char* remainder)//�������2
{
	char one[] = "1";//��ʱ�ַ���....
	char one2[] = "1";//
	char zero[] = "0";//
	char numb2[6048];//
	char tempstr[6018] = "";//��ʱ�ַ���
	int  ia = 0, ia2 = 0;//tempstr��ָʾ��
	bool  moveon = false;//��ת��

	char* pna = numa;//ָ��numa��һ��ָ�롣point numa      pna ָ����������λ��
	char* pnb = findend(numb);//ָ��numb��һ��ָ��                 //pnb ָ�򱻼��������λ��
	Node* head,   // ���ڴ���ͷָ��
		* pstart,  // ���ڴ�������ʱ����ָ��
		* pnew;    //���������½�� 

	head = pstart = new Node;//��ʼ���׽���ͷ��㡣
	pstart->data = 0;
	pstart->next = NULL;
	pstart->ahead = NULL;

	moveon = false;

	while (*pna)
	{
		if (!pstart->next)//�����ǰΪ�ս�㣬�������½��
		{
			pnew = new Node;
			pnew->data = 0;
			pnew->next = NULL;
			pnew->ahead = pstart;
			pstart->next = pnew;
		}

		ia = (int)strlen(tempstr);//ȡ�ĳ���

		tempstr[ia++] = *(pna++);

		tempstr[ia] = '\0'; //ת��Ϊ�ַ���

		if (tempstr[0] == '0')//�����λҲ��0������ ��00
		{
			ia2 = 0;
			while (tempstr[ia2] == '0')++ia2;
			while (ia2 >= 1)//������õ�0
			{
				ia = ia2 - 1;
				tempstr[ia] = tempstr[ia2];
				--ia2;
			}
			tempstr[++ia2] = '\0';
		}

		while (abigerb(tempstr, numb) > 0)//���tempstr���ڵ���numb
		{
			if (tempstr[0] == '0')//�����λҲ��0������ ��00----����������룬����������            
			{
				ia2 = 0;
				while (tempstr[ia2] == '0')++ia2;
				if (ia == ia2)
				{
					moveon = true;
					break;
				}
			}

			strcpy(numb2, numb);
			subtract(tempstr, numb, tempstr);//A-B
			strcpy(numb, numb2);

			if (tempstr[0] == '-')//���жϵĲ�׼����Ϊ�˸������ټ���B����   
			{
				strcpy(numb2, numb);
				addition(tempstr, numb, tempstr);//A-B
				strcpy(numb, numb2);

				ia2 = 0; //����֮��ĳ��ȡ���Ϊ�ӷ���δ����������
				ia = 0;  //Ϊ������������һ�����ţ�������ǰ�ƶ���

				while (tempstr[ia2] != '\0')++ia2;
				while (ia2 >= 1)//������õ�0
				{
					tempstr[ia] = tempstr[ia + 1];
					++ia;
					--ia2;
				}
				tempstr[ia] = '\0';
				moveon = true;
				break;
			}

			pstart->data++; //����Լ�
			moveon = true;
		}
		if (moveon) pstart = pstart->next;          //����ƶ�
	}
	strcpy(remainder, tempstr);//��������

	int tip = 0;//תΪ�ַ�����
	pstart = head;//Ѱ������Ľ�β��
	while (pstart->next != 0)
	{
		pstart->data += 48;//!!<<<��Ϊ���ǵ�������ַ��������ٴ˼���48>>>>  ��˳���
		result[tip++] = pstart->data;
		pstart = pstart->next;
	}
	result[tip] = '\0';//�������

	pstart = head;  //�ͷſռ�
	while (pstart->next != 0)
	{
		pnew = pstart->next; delete pstart;
		pstart = pnew;
	}
	return;
}

//============================================================================
// ģ
// ���ܣ���һ������bigNumber������long int�Ĵ洢���ֵ����divisor����������
// ������bigNumber�Ǵ����ַ�����divisor�ǳ���,resultΪ���
//============================================================================
void mod(char* bigNumber, char* divisor, char* result)
{
	char* res=new char;
	divide2(bigNumber, divisor, res, result);
	return;
}