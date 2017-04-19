#pragma once
#include "windows.h"
#include "stdio.h"
#define GET_DOS_HEADER(x) ((PIMAGE_DOS_HEADER)(x))
#define GET_NT_HEADER(x) ((PIMAGE_NT_HEADERS)((DWORD)GET_DOS_HEADER(x)->e_lfanew + (DWORD)(x)))
#define GET_SECTION_HEADER(x) IMAGE_FIRST_SECTION(x)

struct FileMapStruct
{
public:
	FileMapStruct()
	{
		m_lpFileData = NULL;
		m_hFile = NULL;
		length = 0;
	}
public:
	DWORD length;
	char* m_lpFileData;
	FILE* m_hFile;
};


struct PEstruct
{
public:
	PEstruct()
	{
		m_lpDosHeader = NULL;
		m_lpNtHeader = NULL;
		m_lpSecHeader = NULL;
		m_lpBaseReloc = NULL;
		m_lpImport = NULL;
		m_lpThunkData = NULL;
		m_ImprotName = NULL;
	}
public:
	IMAGE_DOS_HEADER* m_lpDosHeader;
	IMAGE_NT_HEADERS* m_lpNtHeader;
	IMAGE_SECTION_HEADER* m_lpSecHeader;
	IMAGE_BASE_RELOCATION* m_lpBaseReloc;
	IMAGE_IMPORT_DESCRIPTOR* m_lpImport;
	IMAGE_THUNK_DATA* m_lpThunkData;
	IMAGE_IMPORT_BY_NAME* m_ImprotName;
	FileMapStruct m_FileMapTag;
};

struct MySecInfo
{
public:
	MySecInfo()
	{
		RtlZeroMemory(&m_SecHeader, sizeof(m_SecHeader));
		m_lpSecData = NULL;
		m_isNeedPress = true;
	}
	~MySecInfo()
	{
	}
public:
	IMAGE_SECTION_HEADER m_SecHeader;
	char* m_lpSecData;
	bool m_isNeedPress;
};

typedef struct _SectionNode
{
	//��ѹ����
	DWORD SizeOfRawData;
	DWORD SectionRva;
}SectionNode;
typedef struct _GlogalExternVar
{
	SectionNode mSectionNodeArray[16];
	//�ӿǵĵ������ַ
	DWORD dwIATVirtualAddress;
	//�ӿǵ�tls���ݴ�С
	DWORD dwTLSSize;
	//�ӿǵ�tls�����ַ rva
	DWORD dwTLSVirtualAddress;
	//�ӿǵ�ԭʼoep
	DWORD dwOrignalOEP;
	//�ض�λrva
	DWORD dwRelocationRva;

	DWORD dwBaseOfCode;

	DWORD dwOrignalImageBase;
	DWORD dwPressSize;
}GlogalExternVar;

typedef struct _TYPEOFFSET
{
	WORD offset : 12;			//ƫ��ֵ
	WORD Type : 4;			//�ض�λ����(��ʽ)
}TYPEOFFSET, *PTYPEOFFSET;

#define WM_UPDATE WM_USER+100  
#define WM_UPDATEWRITEMEMORY WM_USER+101  
