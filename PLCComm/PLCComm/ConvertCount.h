#pragma once
class ConvertCount
{
public:
	ConvertCount();
	~ConvertCount();

	CString ConvertBinary(short bpGetData);	//10������ 2������ ��ȯ
	CString ConvertChar(short nBlockData);	//10������ ���ڷ� ��ȯ
	int AlphaCount(CString DeviceAddress);	//���ڿ��� ���� ���� ī��Ʈ
};

