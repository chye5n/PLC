#include "pch.h"
#include "ConvertCount.h"

ConvertCount::ConvertCount()
{
}

ConvertCount::~ConvertCount()
{
}

CString ConvertCount::ConvertBinary(short bpGetData)			//10진수를 2진수로 변환
{
	CString strData, strBinary;	//strData : 변환된 2진수 값 저장, strBinary : 각 Bit 값 저장
	for (int i = sizeof(bpGetData) * 8 - 1; i >= 0; i--)		//16bit 만큼 반복
	{
		strBinary.Format(_T("%d "), ((bpGetData >> i) & 1));	//각 Bit값을 가져와 2진수 형식으로 strBinary에 저장
		if (i % 4 == 3) { strData += "  "; }					//4bit마다 띄어쓰기 추가
		strData += strBinary;									//strData에 Bit값 추가
	}
	return strData;
}

CString ConvertCount::ConvertChar(short nBlockData)	//10진수를 문자열로 변환(아스키코드 값 32번부터 127번 사이 값만)
{
	BYTE upperByte = (BYTE)(nBlockData);		// 상위 8bit 설정
	BYTE lowerByte = (BYTE)(nBlockData >> 8);	// 하위 8bit 설정

	CString strUpperByte, strLowerByte;			//아스키코드 값 32번부터 127번 사이 값이 아닐 경우 빈칸으로 설정
	if (((int)upperByte > 31) && ((int)upperByte < 128)) { strUpperByte.Format(_T("%c"), upperByte); }
	else { strUpperByte = " "; }
	if (((int)lowerByte > 31) && ((int)lowerByte < 128)) { strLowerByte.Format(_T("%c"), lowerByte); }
	else { strLowerByte = " "; }

	return strLowerByte + strUpperByte;
}

int ConvertCount::AlphaCount(CString DeviceAddress)	//문자 수 카운트
{
	int nAlphacnt = 0;
	for (int i = 0; i < DeviceAddress.GetLength(); i++)	//문자열의 길이만큼 반복
	{
		if (isalpha(DeviceAddress[i])) { nAlphacnt++; }	//문자일 경우 nAlphacnt증가
	}
	return nAlphacnt;
}
