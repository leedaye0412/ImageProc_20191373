
// imgproc_20191373Doc.cpp: Cimgproc20191373Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imgproc_20191373.h"
#endif

#include "imgproc_20191373Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cimgproc20191373Doc

IMPLEMENT_DYNCREATE(Cimgproc20191373Doc, CDocument)

BEGIN_MESSAGE_MAP(Cimgproc20191373Doc, CDocument)
END_MESSAGE_MAP()


// Cimgproc20191373Doc 생성/소멸

Cimgproc20191373Doc::Cimgproc20191373Doc() noexcept
{
	Inputimg = NULL;
	Inputimg2 = NULL;
	Resultimg = NULL;

	gResultimg = NULL;

}

Cimgproc20191373Doc::~Cimgproc20191373Doc()
{
	int i;

	if (Inputimg != NULL) {
		for (i = 0; i < ImageHeight; i++) 
			free(Inputimg[i]);
		free(Inputimg);
	}
	if (Inputimg2 != NULL) {
		for (i = 0; i < ImageHeight; i++) 
			free(Inputimg2[i]);
		free(Inputimg2);
	}

	if (Resultimg != NULL) {
		for (i = 0; i < ImageHeight; i++) 
			free(Resultimg[i]);
		free(Resultimg);
	}

	if (gResultimg != NULL) {
		for (i = 0; i <gImageHeight; i++)
			free(gResultimg[i]);
		free(gResultimg);
	}
}


BOOL Cimgproc20191373Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// Cimgproc20191373Doc serialization

void Cimgproc20191373Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void Cimgproc20191373Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void Cimgproc20191373Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cimgproc20191373Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cimgproc20191373Doc 진단

#ifdef _DEBUG
void Cimgproc20191373Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cimgproc20191373Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cimgproc20191373Doc 명령


void Cimgproc20191373Doc::LoadImageFile(CArchive& ar)
{
	int maxValue,i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;


	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);	//P5	(16의 마지막 자리에 null0)

		//필요없는 문자열 버리기
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);	//문자열에서 가로 세로 데이터 받아드림

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else						 depth = 3;


	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp화일임을 나타내는 "BM"마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))	return;//<<옆으로 이동시킴

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount/8;

		//palette 처리
		if (depth == 1)//흑백
		{//palette존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}

	//메모리 할당
	Inputimg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	Resultimg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for ( i = 0; i < ImageHeight; i++)
	{
		Inputimg[i] = (unsigned char*)malloc(ImageWidth * depth);
		Resultimg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}
	if (!isbmp)
	{
		//파일에서 읽어서 저장
		for ( i = 0; i < ImageHeight; i++)
			ar.Read(Inputimg[i], ImageWidth * depth);
	}
	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4*3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (int i = 0; i < ImageHeight; i++)
		{
			if(depth==1)
				ar.Read(Inputimg[ImageHeight-1-i], ImageWidth * depth);
			else
			{
				//BGR=>RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++)
				{
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
					Inputimg[ImageHeight - 1 - i][3 * j + 0] = r;
					Inputimg[ImageHeight - 1 - i][3 * j + 1] = g;
					Inputimg[ImageHeight - 1 - i][3 * j + 2] = b;
				}

			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}

	}
	
	return;
}


void Cimgproc20191373Doc::LoadSecondFile(CArchive& ar)
{
	
	int maxValue,i;
	int temp_w, temp_h, temp_depth;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);	//P5	(16의 마지막 자리에 null0)

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &temp_w, &temp_h);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) temp_depth = 1;
		else						temp_depth = 3;


	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp화일임을 나타내는 "BM"마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))	return;//<<옆으로 이동시킴

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		temp_w = bih.biWidth;
		temp_h = bih.biHeight;
		temp_depth = bih.biBitCount / 8;

		//palette 처리
		if (temp_depth == 1)//흑백
		{//palette존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256*256크기의 raw화일만 읽을 수 있습니다");
			return;
		}

		temp_w = 256;
		temp_h = 256;
		temp_depth = 1;
	}
	
	if (ImageWidth != temp_w || ImageHeight != temp_h || depth != temp_depth)
	{
		AfxMessageBox("두번째 파일의 width,height,depth가 다르면 읽을 수 없습니다.");
		return;
	}

	//메모리 할당
	Inputimg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for ( i = 0; i < ImageHeight; i++)
	{
		Inputimg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp)
	{
		//파일에서 읽어서 저장
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(Inputimg2[i], ImageWidth * depth);
	}
	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for ( i = 0; i < ImageHeight; i++)
		{
			if (depth == 1)
				ar.Read(Inputimg2[ImageHeight - 1 - i], ImageWidth * depth);
			else
			{
				//BGR=>RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++)
				{
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
					Inputimg2[ImageHeight - 1 - i][3 * j + 0] = r;
					Inputimg2[ImageHeight - 1 - i][3 * j + 1] = g;
					Inputimg2[ImageHeight - 1 - i][3 * j + 2] = b;
				}

			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}
	}
	//영상데이터읽기
	for (int i = 0; i < ImageHeight; i++)
	{
		ar.Read(Inputimg2[i], ImageWidth * depth);
	}
		
	return;
}
