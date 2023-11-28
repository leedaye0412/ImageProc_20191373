
// imgproc_20191373View.h: Cimgproc20191373View 클래스의 인터페이스
//

#pragma once


class Cimgproc20191373View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	Cimgproc20191373View() noexcept;
	DECLARE_DYNCREATE(Cimgproc20191373View)

// 특성입니다.
public:
	Cimgproc20191373Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~Cimgproc20191373View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMenutest();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelMin();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelminmax();
	afx_msg void OnPixelBinarization();
	afx_msg void OnTwoImageAdd();
	int LoadTwoImage();
	void TwoImage();
	afx_msg void OnPixeltwoimageSub();
	afx_msg void OnRegionSharening();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3] , int bias, int depth);
	
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorToGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	void CopyResultToInput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryZoomoutAvgSampling();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnGeometryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAviMode;
	CString AVIFileName;
	void LoadAviFile(CDC* pDC);
};

#ifndef _DEBUG  // imgproc_20191373View.cpp의 디버그 버전
inline Cimgproc20191373Doc* Cimgproc20191373View::GetDocument() const
   { return reinterpret_cast<Cimgproc20191373Doc*>(m_pDocument); }
#endif

