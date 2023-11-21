
// imgproc_20191373Doc.h: Cimgproc20191373Doc 클래스의 인터페이스
//


#pragma once


class Cimgproc20191373Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	Cimgproc20191373Doc() noexcept;
	DECLARE_DYNCREATE(Cimgproc20191373Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~Cimgproc20191373Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//입력이미지
	unsigned char** Inputimg;    // [y][x]
	unsigned char** Inputimg2;    // [y][x]
	//출력이미지
	unsigned char** Resultimg;    // [y][x]

	int ImageWidth;
	int ImageHeight;
	int depth;		//1=흑백, 3=컬러

	int gImageWidth;
	int gImageHeight;
	//출력이미지
	unsigned char** gResultimg;    // [y][x]

	void LoadImageFile(CArchive& ar);
	void LoadSecondFile(CArchive& ar);
};
