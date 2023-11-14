
// imgproc_20191373View.cpp: Cimgproc20191373View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imgproc_20191373.h"
#endif

#include "imgproc_20191373Doc.h"
#include "imgproc_20191373View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cimgproc20191373View

IMPLEMENT_DYNCREATE(Cimgproc20191373View, CScrollView)

BEGIN_MESSAGE_MAP(Cimgproc20191373View, CScrollView)
//	ON_COMMAND(ID_MENUTEST, &Cimgproc20191373View::OnMenutest)
ON_COMMAND(ID_PIXEL_ADD, &Cimgproc20191373View::OnPixelAdd)
ON_COMMAND(ID_PIXEL_MIN, &Cimgproc20191373View::OnPixelMin)
ON_COMMAND(ID_PIXEL_MUL, &Cimgproc20191373View::OnPixelMul)
ON_COMMAND(ID_PIXEL_DIV, &Cimgproc20191373View::OnPixelDiv)
ON_COMMAND(ID_PIXEL_HISTO_EQ, &Cimgproc20191373View::OnPixelHistoEq)
ON_COMMAND(ID_PIXEL_minmax, &Cimgproc20191373View::OnPixelminmax)
ON_COMMAND(ID_PIXEL_BINARIZATION, &Cimgproc20191373View::OnPixelBinarization)
ON_COMMAND(ID_TWO_IMAGE_ADD, &Cimgproc20191373View::OnTwoImageAdd)
ON_COMMAND(ID_PIXELTWOIMAGE_Sub, &Cimgproc20191373View::OnPixeltwoimageSub)
ON_COMMAND(ID_REGION_SHARENING, &Cimgproc20191373View::OnRegionSharening)
ON_COMMAND(ID_REGION_SMOOTHING, &Cimgproc20191373View::OnRegionSmoothing)
ON_COMMAND(ID_REGION_EMBOSSING, &Cimgproc20191373View::OnRegionEmbossing)
ON_COMMAND(ID_REGION_PREWITT, &Cimgproc20191373View::OnRegionPrewitt)
ON_COMMAND(ID_REGION_ROBERTS, &Cimgproc20191373View::OnRegionRoberts)
ON_COMMAND(ID_REGION_SOBEL, &Cimgproc20191373View::OnRegionSobel)
ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &Cimgproc20191373View::OnRegionAverageFiltering)
ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &Cimgproc20191373View::OnRegionMedianFiltering)
ON_COMMAND(ID_MOPOLOGY_COLOR_TO_GRAY, &Cimgproc20191373View::OnMopologyColorToGray)
ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &Cimgproc20191373View::OnMopologyBinarization)
ON_COMMAND(ID_MOPOLOGY_EROSION, &Cimgproc20191373View::OnMopologyErosion)
ON_COMMAND(ID_MOPOLOGY_DILATION, &Cimgproc20191373View::OnMopologyDilation)
ON_COMMAND(ID_MOPOLOGY_OPENING, &Cimgproc20191373View::OnMopologyOpening)
ON_COMMAND(ID_MOPOLOGY_CLOSING, &Cimgproc20191373View::OnMopologyClosing)
ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &Cimgproc20191373View::OnGeometryZoominPixelCopy)
ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &Cimgproc20191373View::OnGeometryZoominBilinearInterpolation)
ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &Cimgproc20191373View::OnGeometryZoomoutSubsampling)
ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &Cimgproc20191373View::OnGeometryZoomoutMeanSub)
ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG_SAMPLING, &Cimgproc20191373View::OnGeometryZoomoutAvgSampling)
END_MESSAGE_MAP()

// Cimgproc20191373View 생성/소멸

Cimgproc20191373View::Cimgproc20191373View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cimgproc20191373View::~Cimgproc20191373View()
{
}

BOOL Cimgproc20191373View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// Cimgproc20191373View 그리기

void Cimgproc20191373View::OnDraw(CDC* pDC)
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int x, y;
	if (pDoc->Inputimg != NULL)
	{
		if (pDoc->depth == 1) {//흑백영상출력
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->Inputimg[y][x], pDoc->Inputimg[y][x], pDoc->Inputimg[y][x]));
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->Inputimg[y][3 * x + 0], pDoc->Inputimg[y][3 * x + 1], pDoc->Inputimg[y][3 * x + 2]));	//컬러
		}
	}

	if (pDoc->Resultimg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->Resultimg[y][x], pDoc->Resultimg[y][x], pDoc->Resultimg[y][x]));
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->Resultimg[y][3 * x + 0], pDoc->Resultimg[y][3 * x + 1], pDoc->Resultimg[y][3 * x + 2]));  //pDoc을 통해 Inputimg에 접근
		}

	}

	if (pDoc->Inputimg2 != NULL)
	{
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->Inputimg2[y][x], pDoc->Inputimg2[y][x], pDoc->Inputimg2[y][x]));
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth+20)*2 + x, y, RGB(pDoc->Inputimg2[y][3 * x + 0], pDoc->Inputimg2[y][3 * x + 1], pDoc->Inputimg2[y][3 * x + 2]));
		}
	}

	if (pDoc->gResultimg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel( x, pDoc->ImageHeight+20+y, RGB(pDoc->gResultimg[y][x], pDoc->gResultimg[y][x], pDoc->gResultimg[y][x]));
		}
		else {
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultimg[y][3 * x + 0], pDoc->gResultimg[y][3 * x + 1], pDoc->gResultimg[y][3 * x + 2]));
		}

	}

}

void Cimgproc20191373View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;    // 크기 늘려서 스크롤 생성
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// Cimgproc20191373View 진단

#ifdef _DEBUG
void Cimgproc20191373View::AssertValid() const
{
	CScrollView::AssertValid();
}

void Cimgproc20191373View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

Cimgproc20191373Doc* Cimgproc20191373View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cimgproc20191373Doc)));
	return (Cimgproc20191373Doc*)m_pDocument;
}
#endif //_DEBUG


// Cimgproc20191373View 메시지 처리기


//void Cimgproc20191373View::OnMenutest()
//{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	AfxMessageBox("안녕하세요 메뉴출력입니다");             //아무곳에나 쓸수있는 메시지 박스
//}


void Cimgproc20191373View::OnPixelAdd()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	
	if (pDoc->Inputimg == NULL) return;

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{

				value = pDoc->Inputimg[y][x] + 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][3 * x + 0] + 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] + 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] + 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	Invalidate();

}


void Cimgproc20191373View::OnPixelMin()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{

				value = pDoc->Inputimg[y][x] - 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][3 * x + 0] - 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] - 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] - 100;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	Invalidate();
}


void Cimgproc20191373View::OnPixelMul()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{

				value = pDoc->Inputimg[y][x] * 1.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][3 * x + 0] * 1.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] * 1.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] * 1.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	Invalidate();
}


void Cimgproc20191373View::OnPixelDiv()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{

				value = pDoc->Inputimg[y][x] * 0.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				value = pDoc->Inputimg[y][3 * x + 0] * 0.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] * 0.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] * 0.5;
				if (value > 255)value = 255;
				else if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}

	Invalidate();
}


void Cimgproc20191373View::OnPixelHistoEq()  //히스토그램 형활화 함수
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int i, x, y, k;
	int acc_hist;
	int N = pDoc->ImageHeight * pDoc->ImageWidth;
	int hist[256], sum[256];//그대로

	for (i = 0; i < 256; i++)  //그대로
		hist[i] = 0;

	//히스토그램 구하기
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			k = pDoc->Inputimg[y][x];
			hist[k]++;
		}

	//누적 분포 구하기
	acc_hist = 0;
	for (i = 0; i < 256; i++)
	{
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	//픽셀 밝기 변환
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			k = pDoc->Inputimg[y][x];
			pDoc->Resultimg[y][x] = (float)sum[k] / N * 255;
		}

	Invalidate();

}

void Cimgproc20191373View::OnPixelminmax() //명암대비 스트레칭
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	int x, y, value;
	int lowvalue = 255, highvalue = 0;

	//최저 화소값
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->Inputimg[y][x] < lowvalue)
				lowvalue = pDoc->Inputimg[y][x];
		}
	//최고 화소값
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->Inputimg[y][x] > highvalue)
				highvalue = pDoc->Inputimg[y][x];
		}

	//명암대비 스트레칭 계산
	//for (y = 0; y < 256; y++)
		//for (x = 0; x < 256; x++)
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			pDoc->Resultimg[y][x] = (pDoc->Resultimg[y][x] - lowvalue) / (highvalue - lowvalue) * 255;
		}

	Invalidate();

}


void Cimgproc20191373View::OnPixelBinarization() //이진화
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y;
	int threshold = 100;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			if (pDoc->Inputimg[y][x] >= threshold) pDoc->Resultimg[y][x] = 255;//처리전밝기값:pDoc->Inputimg[y][x] 255흰색 0검은색
			else									pDoc->Resultimg[y][x] = 0;
		}
	Invalidate();

}




void Cimgproc20191373View::OnTwoImageAdd() //두 영상의 덧셈
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	
	TwoImage();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++){
			value = 0.5*pDoc->Inputimg[y][x] + 0.5*pDoc->Inputimg2[y][x];
			if (value > 255)value = 255;
			else if (value < 0) value = 0;
			
			pDoc->Resultimg[y][x] = value;
		}

	Invalidate();
	
}


void Cimgproc20191373View::TwoImage() //두 영상 로드
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK) {
		CFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead); //화일열기
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondFile(ar);

		file.Close();
	}
}


void Cimgproc20191373View::OnPixeltwoimageSub() //두 영상의 뺄셈
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y, value;

	TwoImage();
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++){
			value = 0.5 * pDoc->Inputimg[y][x] - 0.5*pDoc->Inputimg2[y][x];
			if (value > 255)value = 255;
			else if (value < 0) value = 0;


			if (value > 64) value = 255;
			else			value = 0;
		
			pDoc->Resultimg[y][x] = value;
		}

	Invalidate();
}


void Cimgproc20191373View::OnRegionSharening()//선명화
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	float kernel[3][3] = { {0,-1,0},{-1,5,-1},{0,-1,0} };

	convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void Cimgproc20191373View::convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y;
	int i, j;
	int sum,rsum,gsum,bsum;
	for (y = 1; y < rows-1; y++)
		for (x = 1; x < cols-1; x++)
		{
			if (depth == 1) {
				sum = 0;

				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255) sum = 255;//흰색
				else if (sum < 0) sum = 0;//검은색

				outimg[y][x] = sum;
			}
			else
			{
				//컬러
				rsum = 0; gsum = 0; bsum = 0;

				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inimg[y + j - 1][3*(x + i - 1)+0] * mask[j][i]);
						gsum += (inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}
				rsum += bias;
				gsum += bias;
				bsum += bias;

				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				outimg[y][3*x+0] = rsum;
				outimg[y][3 * x + 1] = gsum;
				outimg[y][3 * x + 2] = bsum;

			}
		}
}




void Cimgproc20191373View::OnRegionSmoothing()//흐리게하기
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1 / 9.,1 / 9.,1 / 9.},{1 / 9.,1 / 9.,1 / 9.},{1 / 9.,1 / 9.,1 / 9.} };

	convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void Cimgproc20191373View::OnRegionEmbossing()//엠보싱효과
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1,0,0},
							{0,0,0},
							{0,0,1} };

	convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 128, pDoc->depth);

	Invalidate();
}


void Cimgproc20191373View::OnRegionPrewitt()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	float kernel_h[3][3] = {{-1,-1,-1},
							{0,0,0},
							{1,1,1} };

	float kernel_v[3][3] = {{-1,0,1},
							{-1,0,1},
							{-1,0,1} };

	int x, y,i;
	int value,rvalue,gvalue,bvalue;

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageWidth * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3*x+0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][3*x+0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}

		
		}

	//메모리삭제
	for (i = 0; i<pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);


	Invalidate();
}


void Cimgproc20191373View::OnRegionRoberts()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1,0,0},
							{0,1,0},
							{0,0,0} };

	float kernel_v[3][3] = { {-0,0,-1},
							{0,1,0},
							{0,0,0} };

	int x, y, i;
	int value, rvalue, gvalue, bvalue;

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageWidth * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}


		}

	//메모리삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);


	Invalidate();
}


void Cimgproc20191373View::OnRegionSobel()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1,-2,-1},
							{0,0,0},
							{1,2,1} };

	float kernel_v[3][3] = { {-1,0,1},
							{-2,0,2},
							{-1,0,1} };

	int x, y, i;
	int value, rvalue, gvalue, bvalue;

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageWidth * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}


		}

	//메모리삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);


	Invalidate();
}


void Cimgproc20191373View::OnRegionAverageFiltering()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y,i,j;
	int xpos, ypos;
	int sum,rsum,gsum,bsum;
	int pixelcount;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)	//중심좌표
		{
			sum = 0; pixelcount = 0; rsum = gsum = bsum = 0;
			for(j=-2;j<=2;j++)	//5X5		3X3-> j=-1 j<=1
				for (i = -2; i <= 2; i++)
				{
					xpos = x + i;
					ypos = y + j;
					if (xpos >= 0 && xpos <= pDoc->ImageWidth - 1 && ypos >= 0 && ypos <= pDoc->ImageHeight - 1)
					{
						if(pDoc->depth==1)
						sum += pDoc->Inputimg[y + j][x + i];
						else //컬러
						{
							rsum += pDoc->Inputimg[y + j][3*(x + i)+0];
							gsum += pDoc->Inputimg[y + j][3 * (x + i) + 1];
							bsum += pDoc->Inputimg[y + j][3 * (x + i) + 2];
						}
						pixelcount++;
					}
					
				}
			if(pDoc->depth==1)
				pDoc->Resultimg[y][x]=sum / pixelcount;
			else //컬러
			{
				pDoc->Resultimg[y][3*x+0] = rsum / pixelcount;
				pDoc->Resultimg[y][3 * x + 1] = gsum / pixelcount;
				pDoc->Resultimg[y][3 * x + 2] = bsum / pixelcount;
			}
		}

	Invalidate();
}


void Cimgproc20191373View::OnRegionMedianFiltering()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y,i,j;
	int n[9],temp;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			n[0] = pDoc->Inputimg[y - 1][x - 1];
			n[1] = pDoc->Inputimg[y - 1][x - 0];
			n[2] = pDoc->Inputimg[y - 1][x + 1];
			n[3] = pDoc->Inputimg[y - 0][x - 1];
			n[4] = pDoc->Inputimg[y - 0][x - 0];
			n[5] = pDoc->Inputimg[y - 0][x + 1];
			n[6] = pDoc->Inputimg[y + 1][x - 1];
			n[7] = pDoc->Inputimg[y + 1][x - 0];
			n[8] = pDoc->Inputimg[y + 1][x + 1];

			//버블소팅(오름차순)
			for(i=8;i>0;i--)
				for (j = 0; j < i; j++)
				{
					if (n[j] > n[j + 1])
					{
						temp = n[j + 1];
						n[j + 1] = n[j];
						n[j] = temp;
					}
				}
			pDoc->Resultimg[y][x] = n[4];
	
		}
	Invalidate();
}


void Cimgproc20191373View::OnMopologyColorToGray()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;
	
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2]) / 3;
			pDoc->Inputimg[y][3 * x + 0] = gray;
			pDoc->Inputimg[y][3 * x + 1] = gray;
			pDoc->Inputimg[y][3 * x + 2] = gray;
		}
	Invalidate();

}


void Cimgproc20191373View::OnMopologyBinarization()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	int x, y;
	int gray,threshold=100;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->Inputimg[y][x] > threshold)	pDoc->Inputimg[y][x] = 255;
				else									pDoc->Inputimg[y][x] = 0;
			}
			else
			{
				if ((pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2]) / 3 > threshold)
				{
					pDoc->Inputimg[y][3 * x + 0] = 255;
					pDoc->Inputimg[y][3 * x + 1] = 255;
					pDoc->Inputimg[y][3 * x + 2] = 255;
				}
				else {
					pDoc->Inputimg[y][3*x+0] = 0;
					pDoc->Inputimg[y][3 * x + 1] = 0;
					pDoc->Inputimg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}


void Cimgproc20191373View::OnMopologyErosion()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	
	int x, y,j,i;
	int min = 255,rmin,bmin,gmin;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			min = 255; rmin = 255; gmin = 255; bmin = 255;
			for(j=-1;j<=1;j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->Inputimg[y + j][x + i] < min)
							min = pDoc->Inputimg[y + j][x + i];
					}
					else
					{
						if (pDoc->Inputimg[y + j][3*(x + i)+0] < rmin)	rmin = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] < gmin)	gmin = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] < bmin)	bmin = pDoc->Inputimg[y + j][3 * (x + i) + 2];
					}
			

				}
			if(pDoc->depth==1)
				pDoc->Resultimg[y][x] = min;
			else
			{
				pDoc->Resultimg[y][3*x+0] = rmin;
				pDoc->Resultimg[y][3 * x + 1] = gmin;
				pDoc->Resultimg[y][3 * x + 2] = bmin;
			}
		}
	Invalidate();
}


void Cimgproc20191373View::OnMopologyDilation()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	int x, y, j, i;
	int max, rmax, bmax, gmax;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			max = 0; rmax = 0; gmax = 0; bmax = 0;
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->Inputimg[y + j][x + i] > max)
							max = pDoc->Inputimg[y + j][x + i];
					}
					else
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] > rmax)	rmax = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] > gmax)	gmax = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] > bmax)	bmax = pDoc->Inputimg[y + j][3 * (x + i) + 2];
					}


				}
			if (pDoc->depth == 1)
				pDoc->Resultimg[y][x] = max;
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = rmax;
				pDoc->Resultimg[y][3 * x + 1] = gmax;
				pDoc->Resultimg[y][3 * x + 2] = bmax;
			}
		}
	Invalidate();
}


void Cimgproc20191373View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();


}


void Cimgproc20191373View::CopyResultToInput()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight ; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			pDoc->Inputimg[y][x] = pDoc->Resultimg[y][x];
		}
}


void Cimgproc20191373View::OnMopologyClosing()
{
	
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

}


void Cimgproc20191373View::OnGeometryZoominPixelCopy()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultimg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;
	//메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	/*
	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
				pDoc->gResultimg[y*yscale][x*xscale] = pDoc->Inputimg[y ][x ];
		}
		*/

	//역방향사상
	for(y=0;y<pDoc->gImageHeight;y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->gResultimg[y][x] = pDoc->Inputimg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultimg[y][3*x+0] = pDoc->Inputimg[y / yscale][3*(x / xscale)+0];
				pDoc->gResultimg[y][3 * x + 1] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultimg[y][3 * x + 2] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 2];
			}
		}
	
	Invalidate();
}


void Cimgproc20191373View::OnGeometryZoominBilinearInterpolation()
{
	Cimgproc20191373Doc* pDoc = GetDocument();
	int x, y;

	float xscale = 2.1;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultimg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth =pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight  * yscale;
	//메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

		//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax+1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1)Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;
			if (pDoc->depth == 1) {
				E = (1 - alpha) * pDoc->Inputimg[Ay][Ax] + alpha * pDoc->Inputimg[By][Bx];
				F = (1 - alpha) * pDoc->Inputimg[Cy][Cx] + alpha * pDoc->Inputimg[Dy][Dx];

				pDoc->gResultimg[y][x] = (1 - beta) * E + beta * F;
			}
			else {
				E = (1 - alpha) * pDoc->Inputimg[Ay][3*Ax+0] + alpha * pDoc->Inputimg[By][3*Bx+0];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3*Cx+0] + alpha * pDoc->Inputimg[Dy][3*Dx+0];
				pDoc->gResultimg[y][3*x+0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 1] + alpha * pDoc->Inputimg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 1] + alpha * pDoc->Inputimg[Dy][3 * Dx +1];
				pDoc->gResultimg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 2] + alpha * pDoc->Inputimg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 2] + alpha * pDoc->Inputimg[Dy][3 * Dx + 2];
				pDoc->gResultimg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
			
		}

	Invalidate();
}


void Cimgproc20191373View::OnGeometryZoomoutSubsampling()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	int x, y,i;
	int xscale = 3;		//	1/3
	int yscale = 2;		//	1/2

	if (pDoc->gResultimg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	//메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultimg[y][x] = pDoc->Inputimg[y * yscale][x * xscale];
			else
			{
				pDoc->gResultimg[y][3*x+0] = pDoc->Inputimg[y * yscale][3*(x * xscale)+0];
				pDoc->gResultimg[y][3 * x + 1] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultimg[y][3 * x + 2] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 2];


			}
		}
	Invalidate();
}

void Cimgproc20191373View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}


void Cimgproc20191373View::OnGeometryZoomoutAvgSampling()
{
	Cimgproc20191373Doc* pDoc = GetDocument();

	int x, y, i,j;
	int xscale = 3;		//	1/3
	int yscale = 2;		//	1/2
	int src_x, src_y;
	int sum,rsum,bsum,gsum;

	if (pDoc->gResultimg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultimg[i]);
		free(pDoc->gResultimg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	//메모리 할당
	pDoc->gResultimg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultimg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y+=yscale)
		for (x = 0; x < pDoc->ImageWidth; x+=xscale)
		{
			sum = 0; rsum = 0; gsum = 0; bsum = 0;
			for(j=0;j<yscale;j++)
				for (i = 0; i<xscale; i++)
				{
					src_x = x + i;
					src_y = y + j;
					if (src_x > pDoc->ImageWidth - 1)	src_x = pDoc->ImageWidth - 1;
					if (src_y > pDoc->ImageHeight - 1)	src_y = pDoc->ImageHeight - 1;

					if(pDoc->depth==1)
						sum+=pDoc->Inputimg[src_y][src_x];
					else
					{
						rsum += pDoc->Inputimg[src_y][3*src_x+0];
						gsum += pDoc->Inputimg[src_y][3 * src_x + 1];
						bsum += pDoc->Inputimg[src_y][3 * src_x + 2];
					}
				}
			if (pDoc->depth == 1)
				pDoc->gResultimg[y/yscale][x/xscale] = sum / (xscale * yscale);
			else
			{
				pDoc->gResultimg[y / yscale][3*(x / xscale)+0] = rsum / (xscale * yscale);
				pDoc->gResultimg[y / yscale][3 * (x / xscale) + 1] = gsum / (xscale * yscale);
				pDoc->gResultimg[y / yscale][3 * (x / xscale) + 2] = bsum / (xscale * yscale);
			}
		}
		Invalidate();
}
