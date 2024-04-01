#pragma once
class ConvertCount
{
public:
	ConvertCount();
	~ConvertCount();

	CString ConvertBinary(short bpGetData);	//10진수를 2진수로 변환
	CString ConvertChar(short nBlockData);	//10진수를 문자로 변환
	int AlphaCount(CString DeviceAddress);	//문자열에 문자 개수 카운트
};

