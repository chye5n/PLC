#include "pch.h"
#include "ConvertCount.h"

ConvertCount::ConvertCount()
{
}

ConvertCount::~ConvertCount()
{
}

CString ConvertCount::ConvertBinary(short bpGetData)			//10������ 2������ ��ȯ
{
	CString strData, strBinary;	//strData : ��ȯ�� 2���� �� ����, strBinary : �� Bit �� ����
	for (int i = sizeof(bpGetData) * 8 - 1; i >= 0; i--)		//16bit ��ŭ �ݺ�
	{
		strBinary.Format(_T("%d "), ((bpGetData >> i) & 1));	//�� Bit���� ������ 2���� �������� strBinary�� ����
		if (i % 4 == 3) { strData += "  "; }					//4bit���� ���� �߰�
		strData += strBinary;									//strData�� Bit�� �߰�
	}
	return strData;
}

CString ConvertCount::ConvertChar(short nBlockData)	//10������ ���ڿ��� ��ȯ(�ƽ�Ű�ڵ� �� 32������ 127�� ���� ����)
{
	BYTE upperByte = (BYTE)(nBlockData);		// ���� 8bit ����
	BYTE lowerByte = (BYTE)(nBlockData >> 8);	// ���� 8bit ����

	CString strUpperByte, strLowerByte;			//�ƽ�Ű�ڵ� �� 32������ 127�� ���� ���� �ƴ� ��� ��ĭ���� ����
	if (((int)upperByte > 31) && ((int)upperByte < 128)) { strUpperByte.Format(_T("%c"), upperByte); }
	else { strUpperByte = " "; }
	if (((int)lowerByte > 31) && ((int)lowerByte < 128)) { strLowerByte.Format(_T("%c"), lowerByte); }
	else { strLowerByte = " "; }

	return strLowerByte + strUpperByte;
}

int ConvertCount::AlphaCount(CString DeviceAddress)	//���� �� ī��Ʈ
{
	int nAlphacnt = 0;
	for (int i = 0; i < DeviceAddress.GetLength(); i++)	//���ڿ��� ���̸�ŭ �ݺ�
	{
		if (isalpha(DeviceAddress[i])) { nAlphacnt++; }	//������ ��� nAlphacnt����
	}
	return nAlphacnt;
}
