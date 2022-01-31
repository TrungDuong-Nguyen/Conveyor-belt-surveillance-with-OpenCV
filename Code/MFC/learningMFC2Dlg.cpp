
// learningMFC2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "learningMFC2.h"
#include "learningMFC2Dlg.h"
#include "afxdialogex.h"
#include "highgui.h"
#include "cv.h"
#include "BlobResult.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <time.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ClearningMFC2Dlg dialog

ClearningMFC2Dlg::ClearningMFC2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClearningMFC2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strFILENAME = _T("");
	m_strFILENAME2 = _T("");
	m_strINFO = _T("");
	m_strINFOLINK = _T("");
	m_strMODE = _T("");
}

void ClearningMFC2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME, m_strFILENAME);
	DDX_Text(pDX, IDC_FILENAME2, m_strFILENAME2);
	DDX_Text(pDX, IDC_EDIT1, m_strINFO);
	//  DDX_Control(pDX, IDC_EDIT2, m_strINFOLINK);
	DDX_Text(pDX, IDC_EDIT2, m_strINFOLINK);
	DDX_Text(pDX, IDC_EDIT3, m_strMODE);
}

BEGIN_MESSAGE_MAP(ClearningMFC2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &ClearningMFC2Dlg::OnOpenImage)
	ON_BN_CLICKED(IDOK, &ClearningMFC2Dlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDCANCEL, &ClearningMFC2Dlg::OnBnClickedCancel)
//	ON_BN_CLICKED(IDC_BUTTON2, &ClearningMFC2Dlg::OnProcess)
	ON_BN_CLICKED(IDOK, &ClearningMFC2Dlg::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_FILENAME, &ClearningMFC2Dlg::OnEnChangeFilename)
//ON_BN_CLICKED(IDC_BUTTON2, &ClearningMFC2Dlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON2, &ClearningMFC2Dlg::OnOpenVideo)
ON_BN_CLICKED(IDC_BUTTON3, &ClearningMFC2Dlg::OnViewInfo3)
ON_BN_CLICKED(IDC_BUTTON4, &ClearningMFC2Dlg::OnOpenCAM)
ON_BN_CLICKED(IDC_BUTTON5, &ClearningMFC2Dlg::OnMODE1)
ON_BN_CLICKED(IDC_BUTTON6, &ClearningMFC2Dlg::OnMODE2)
ON_BN_CLICKED(IDC_BUTTON7, &ClearningMFC2Dlg::OnMODE3)
END_MESSAGE_MAP()


// ClearningMFC2Dlg message handlers

BOOL ClearningMFC2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	 //cvNamedWindow( "Original Image");   // create the window on which
  	//cvNamedWindow( "Processed Image");  // the image will be displayed
	//image= 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ClearningMFC2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ClearningMFC2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ClearningMFC2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void ClearningMFC2Dlg::OnOpenImage()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
    OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
    _T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||"),NULL);

  dlg.m_ofn.lpstrTitle= _T("Open Image");

  if (dlg.DoModal() == IDOK) {

    CString path= dlg.GetPathName();  // contain the selected filename

	m_strFILENAME= path;
	UpdateData(FALSE);
	SetDlgItemText(IDC_FILENAME,m_strFILENAME);
	cvNamedWindow ("IMAGE");
	IplImage*image= cvLoadImage(path);              // load the image
	cvShowImage("IMAGE", image);  // display it
	if(cvWaitKey(0)==27)
	{cvReleaseImage(&image);
	 cvDestroyWindow("IMAGE"); }
  }
}

void ClearningMFC2Dlg::OnOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}

void ClearningMFC2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//cvDestroyAllWindows();
	//cvReleaseImage(&image);
	CDialogEx::OnOK();
}

void ClearningMFC2Dlg::OnOpenVideo()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.avi"), NULL,
    OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
    _T("video files (*.avi;*.wmv) |*.avi;*.wmv|All Files (*.*)|*.*||"),NULL);
    dlg.m_ofn.lpstrTitle= _T("Open Video");
    if (dlg.DoModal() == IDOK) {
    CString path2= dlg.GetPathName();  // contain the selected filename
	m_strFILENAME2= path2;
	UpdateData(FALSE);
	SetDlgItemText(IDC_FILENAME2,m_strFILENAME2);
	cvNamedWindow ("VIDEO");
	CvCapture* capture1 = cvCreateFileCapture( path2 );
	IplImage* frame;
	while(1) {
	frame = cvQueryFrame(capture1);
	if( !frame ) break;
	cvShowImage( "VIDEO", frame );
	char c = cvWaitKey(33);
	if( c == 27 ) break;
	{
	cvReleaseCapture( &capture1 );
	cvDestroyWindow( "VIDEO" );
   }
	}
}
}

void ClearningMFC2Dlg::OnViewInfo3()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.xml"), NULL,
    OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
    _T("XML files (*.xml) |*.xml|All Files (*.*)|*.*||"),NULL);

  dlg.m_ofn.lpstrTitle= _T("Search Info");

  if (dlg.DoModal() == IDOK) {

    CString path3= dlg.GetPathName();  // contain the selected filename

	m_strINFOLINK = path3;
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT2,m_strINFOLINK);

	//char* string1;
	CString string1;
	//char* string2;
	CString string2;
	char doc[100];
	CvFileStorage* info = cvOpenFileStorage (path3, 0, CV_STORAGE_READ);
	int product = cvReadIntByName(info, 0, "Product", 5 );
	string1 = cvReadStringByName(info, 0, "Time_beginning", 0);
	string2 = cvReadStringByName(info, 0, "Time_ending", 0);
	//const char*string2 = cvReadStringByName();
	//printf("frame_count=%d, frame_width=%d, frame_height=%d\n",frame_count,frame_width,frame_height);
	//sprintf (doc,"%s\n%s\nThe quantity of product is: %d\n", string1, string2, product );
	CString kaka;
		
	kaka.Format("%s\r\n%s\r\nThe quantity of product is: %d\r\n",string1,string2,product);
	
	m_strINFO = kaka;
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT1,m_strINFO);
	cvReleaseFileStorage (&info);

	}
}

void ClearningMFC2Dlg::OnOpenCAM()
{
	// TODO: Add your control notification handler code here
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* frame;
	cvNamedWindow("CAMERA"); 
	if(!capture)
	{m_strMODE = "Capture failed";}
	m_strMODE = "Test CAMERA";
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT3,m_strMODE);
	while(1)
	{ frame = cvQueryFrame (capture);
	  if (!frame) break;
	  cvShowImage("CAMERA", frame);
	  char c = cvWaitKey(33);
	  if ( c==27 ) break;
	 }
	cvReleaseCapture (&capture);
	cvDestroyWindow ("CAMERA");
}


void ClearningMFC2Dlg::OnMODE1()
{
	// TODO: Add your control notification handler code here
	 CBlobResult blobs;  
    CBlob *currentBlob; 
	CBlob blob;
    CvPoint pt1, pt2, point;		// 2 opposite corner points of the bounding rectangle and the center point of the blob
    CvRect cvRect;					// bounding rectangle for each blob
	CBlobGetXCenter getXCenter;		//	x-coordinate of the center point
	CBlobGetYCenter getYCenter;		//	y-coordinate of the center point
	int count = 0;                  // starting with counting value = 0
	char buffer3[100];				// display quantity of product

///////////////////////////////// Font initialization to PutText in frame /////////////////////////////////////////////////////////////////
	CvFont font;
	cvInitFont( &font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA );

///////////////////////////////// Variables declaration for displaying time //////////////////////////////////////////////////////////////  
	//time_t timeObj;
	//time( &timeObj );
	char buffer1[100];
	char buffer2[100];

//////////////////////////////// Variables declaration for saving image //////////////////////////////////////////////////////////////////
	//int p = 0;
	char buffer4[100];

//////////////////////////////// Variables declaration for saving video //////////////////////////////////////////////////////////////////
	char buffer5[100];

//////////////////////////////// XML file ///////////////////////////////////////////////////////////////////////////////////////////////
	char buffer6[100]; // XMLfile label
	char buffer7[100]; // Time beginning  (XMLfile)
	char buffer8[100]; // Time ending     (XMLfile)

//////////////////////////////// Variables declaration for cvFilter2D (sharpen edge -> video look nicer) ////////////////////////////////////	
	//// continue to test.......
	/*float value[] = { 0, -1, 0,
					  -1, 5, -1,
					   0, -1, 0};
	CvMat matrix;
	CvMat* kernel = cvInitMatHeader(&matrix,3, 3, CV_32FC1, value);*/

//////////////////////////////// Initialize capturing from CAM1 (overhead) /////////////////////////////////////////////////////////////////
    IplImage* frame = 0;
	IplImage* frame1 = 0;
	//IplImage* result = 0;
	CvCapture* capture = 0;
    capture = cvCaptureFromCAM( 0 );  
	
	/** check whether capturing initialization is successful **/
	if( !capture )  
    {m_strMODE = "Capture failed";}
	m_strMODE = "MODE 1";
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT3,m_strMODE);  
          
	assert (capture != NULL);  // If no capturing done, rest of the program proceeds totally ignorant

    /** Window used to display input video with bounding rectangles **/ 
    cvNamedWindow( "VideoInput", CV_WINDOW_AUTOSIZE );
	/** Window used to display binary video **/
	cvNamedWindow( "Binary", CV_WINDOW_AUTOSIZE ); 
	//*Notice that the CAM's resolutionis 640x480 so the window will fixed to this size 
   
	/// cvNamedWindow( "Grayscale Gauss" );

// Time in videofile labelling
time_t timeObj1;
time( &timeObj1);
tm *pTime1 = gmtime(&timeObj1);
sprintf (buffer5, "D:/SaveVideo/CAM1demo/%d-%d-%d_%dh-%dm.avi",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
sprintf (buffer6, "D:/SaveInfo/CAM1demo/%d-%d-%d_%dh-%dm.xml",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
sprintf (buffer7, "Process begins  %d-%d-%d_%dh-%dm",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
CvVideoWriter* writer = cvCreateVideoWriter (buffer5, CV_FOURCC('M','J','P','G'), 15, cvSize(640, 480), true);

//=============================== infinite main loop ===========================================================//
 	while( 1 )
        { 
            frame = cvQueryFrame( capture );
			frame1 = cvCloneImage( frame );    // "frame1" is a full copy of "frame"

         //============ Draw 2 green lines which limit counting zone =======================//
			cvLine (frame,cvPoint(0,210),cvPoint(640,210),cvScalar(0,255,0),2,8,0);
			cvLine (frame,cvPoint(0,270),cvPoint(640,270),cvScalar(0,255,0),2,8,0);

		/* Put green text to the original frame */
			cvPutText(frame,"counting zone", cvPoint(0,240), &font, cvScalar(0, 255, 0));
		
		/* Display current time in the original frame */
			time_t timeObj2;
			time( &timeObj2 );
			tm *pTime2 = gmtime(&timeObj2);
			sprintf (buffer1, "%d/%d/%d",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900);
			sprintf (buffer2, "%dh:%dm",(pTime2->tm_hour+7)%24, pTime2->tm_min);
			cvPutText(frame, buffer1, cvPoint(520,20), &font, cvScalar(0, 255, 0));
			cvPutText(frame, buffer2, cvPoint(520,40), &font, cvScalar(0, 255, 0));
      
		//============= Convert to Grayscale then perform smoothing operation =============//
        /* Allocate memory for the grayframe (single channel) version of the copy frame */
			IplImage* grayframe = cvCreateImage( cvGetSize(frame),  
                                         IPL_DEPTH_8U, 1);
        /* Make grayframe version of the copy frame (without line and text)*/
			cvCvtColor(frame1, grayframe, CV_RGB2GRAY); 
			frame1 = NULL;
			cvReleaseImage(&frame1);
		
		/* Perform Gaussian blur */
			IplImage* smoothframe = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
			cvSmooth(grayframe, smoothframe, CV_GAUSSIAN, 15,15); // (not the fastest but probably the most useful )

		//// continue to test .....
		/*IplImage*laplace = cvCreateImage(cvGetSize(frame),IPL_DEPTH_32F,1);
		  cvFilter2D(smoothframe, laplace, kernel);*/

		/////cvShowImage ("GrayScale Gauss",smoothframe);

		//============== Convert to Binary then perform morphology operation ===============//
		/* Allocate memory for the processing frames */
   		IplImage* binaryframe = cvCreateImage (cvGetSize(frame),IPL_DEPTH_8U,1);      // binary frame (after Threshold)
		IplImage* newbinaryframe = cvCreateImage (cvGetSize(frame),IPL_DEPTH_8U,1);   // (after closing operation)
		IplImage* lastbinaryframe = cvCreateImage (cvGetSize(frame),IPL_DEPTH_8U,1);  // (after opening operation)
        cvThreshold( smoothframe,       // source image  
                    binaryframe,        // destination image  
                    55,                 // threhold val.  
                    255,                // max. val  
                    CV_THRESH_BINARY ); // binary type );
			
		//========== Make new kernel for morphology operation ========// 
		IplConvKernel *element;
		element = cvCreateStructuringElementEx (5,5,3,3,CV_SHAPE_RECT, NULL); // 11x11 rectangle shape, anchor in the center
		IplImage*timg = cvCloneImage(binaryframe);								// temp image

		//========== Perform morphology operation ====================//
		cvMorphologyEx (binaryframe, newbinaryframe, timg, element,CV_MOP_CLOSE , 1);  // closing operation 1 time
		cvMorphologyEx (newbinaryframe, lastbinaryframe,timg,element,CV_MOP_OPEN,1);   // closing operation 1 time
		cvReleaseImage (&timg);						// Memory Release
		cvReleaseStructuringElement(&element );		

        /*IplConvKernel *element1;
		element1 = cvCreateStructuringElementEx (9,9,3,3,CV_SHAPE_ELLIPSE, NULL);
		cvDilate (binaryframe,newbinaryframe,element1,3);
		cvReleaseStructuringElement(&element1 );*/
				
		//============================= Counting blob process ==========================//	
		/* Detect the white blobs from the black background */ 
        blobs = CBlobResult( lastbinaryframe, NULL, 0 );    
      
        /* Exclude white blobs smaller than the given value (5000) */  
        blobs.Filter( blobs,  
                      B_EXCLUDE,  
                      CBlobGetArea(),  
                      B_LESS,  
                      5000 );  // The bigger the last parameter, the bigger the blobs need to be for inclusion  
        
		/* Get the total number of the blob */
        int num_blobs = blobs.GetNumBlobs();  
		//std::cout<<"The amount of blobs is :"<<num_blobs<<std::endl;

		/* Allocate memory for the binary frame (to display the result of the counting process)*/
		 IplImage*result = cvCreateImage( cvGetSize( lastbinaryframe ),  
                                           IPL_DEPTH_8U,  
                                           3 );  // Image will contain color elements like text, line, ...  
        /* Result frame's combination from image after morphology operation */
		cvMerge( lastbinaryframe, lastbinaryframe, lastbinaryframe, NULL, result );
		
		/* Display time in the result frame */
		//tm *pTime = gmtime(&timeObj);
		//sprintf (buffer1, "%d/%d/%d  %dh:%dm",pTime->tm_mday,pTime->tm_mon+1,pTime->tm_year+1900, pTime->tm_hour+7, pTime->tm_min);
		cvPutText(result, buffer1, cvPoint(520,20), &font, cvScalar(0, 255, 0));
		cvPutText(result, buffer2, cvPoint(520,40), &font, cvScalar(0, 255, 0));
      

		/* Display the total quantity of product in the original video input and the result frame*/
		sprintf(buffer3,"$Product: %u",count);
		cvPutText(frame, buffer3, cvPoint(520,60), &font, cvScalar(0, 255, 0));
		cvPutText(result, buffer3, cvPoint(520,60), &font, cvScalar(0, 255, 0));

			//========= Process for each blob =================//
            for ( int i = 0; i < num_blobs; i++ )  
            {  
                currentBlob = blobs.GetBlob( i );  // Get the current blob
				/* Attach a bounding rectangle for each blob discovered */  
            	cvRect = currentBlob->GetBoundingBox();  
				//std::cout<<"<width,height> of the Rect BoundingBox is:"<<"<"<<cvRect.width<<","<<cvRect.height<<">"<<std::endl;

				/* Identify the coordinates of 2 opposite corners points which form the bouding rectangle */ 
                pt1.x = cvRect.x;  
                pt1.y = cvRect.y;  
                pt2.x = cvRect.x + cvRect.width;  
                pt2.y = cvRect.y + cvRect.height;  
      
                /* Attach bounding rectangle to blob in orginal video input */ 
                cvRectangle( frame,  
                             pt1,  
                             pt2,  
                             cvScalar(0, 255, 0, 0),  // green color
                             3,  
                             8,  
                             0 ); 
				/* Attach bounding rectangle to blob in the result frame */
				cvRectangle( result,  
                             pt1,  
                             pt2,  
                            cvScalar(0, 255, 0, 0),  // green color
                             3,  
                             8,  
                            0 );  

				blob = blobs.GetBlob(i); // Get the current blob
				/* Get the center's coordinates of the current blob */
				point = cvPoint((int)(getXCenter(blob)), (int)(getYCenter(blob)));
				//std::cout<<"the center of the blob No"<<i<<"<"<<(int)(getXCenter(blob))<<","<<(int)(getYCenter(blob))<<">"<<std::endl;

				/* Attach a circle in the center of the blob in original video input */
				cvCircle(frame, point, 4, CV_RGB(255, 0, 0), -1);
				/* Attach a circle in the center of the blob in the result frame */
				cvCircle(result, point, 4, CV_RGB(255, 0, 0), -1);
			
				/* Whenever the center of an arbitrary blob exist in the couting zone....*/
				if((210<(int)(getYCenter(blob)))&&(((int)(getYCenter(blob))<270)))
				{
					count++;													    //... then increase the counting value
					std::cout<<"The total number of product is:"<<count<<std::endl;	//	Display the counting value
					blob.FillBlob( result, CV_RGB(255,0,0));						//  Fill this blob with red color 	
				    //std::cout<<"the center of the blob No"<<i<<"<"<<(int)(getXCenter(blob))<<","<<(int)(getYCenter(blob))<<">"<<std::endl;
					
					//p++;				
					sprintf(buffer4,"D:/SaveImage/CAM1demo/%d-%d-%d_%dh-%dm Product%u.jpg",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900,(pTime2->tm_hour+7)%24, pTime2->tm_min ,count);
					cvSaveImage(buffer4,frame);
					//p++;

				}									
			}
		
			/* Display original video input */  
            cvShowImage( "VideoInput", frame  );  
            /* Display result frame */  
			cvShowImage ("Binary", result);
			cvWriteFrame( writer, frame );

           	if (cvWaitKey(66)==27)  // assume that the input framerate is 15 frames/s
			{
				sprintf (buffer8, "Process ends    %d-%d-%d_%dh-%dm",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900,(pTime2->tm_hour+7)%24, pTime2->tm_min);
				CvFileStorage* info = cvOpenFileStorage (buffer6, 0, CV_STORAGE_WRITE);
				cvWriteString (info, "Time_beginning", buffer7, 0);
				cvWriteString (info, "Time_ending", buffer8, 0);
				cvWriteInt ( info, "Product", count );
				cvReleaseFileStorage (&info);
				break;
			}      
			cvReleaseImage (&result);
			cvReleaseImage (&grayframe);
			cvReleaseImage (&smoothframe);
			cvReleaseImage (&binaryframe);
			cvReleaseImage (&newbinaryframe);
			cvReleaseImage (&lastbinaryframe);
			}  
		cvReleaseVideoWriter (&writer);
        cvReleaseCapture( &capture );  
		cvDestroyWindow( "VideoInput" );
		cvDestroyWindow( "Binary" );
		//cvReleaseImage( &frame );
		//cvReleaseImage ( &result);
}


void ClearningMFC2Dlg::OnMODE2()
{
	// TODO: Add your control notification handler code here
		cv::BackgroundSubtractorMOG mog;

	CBlobResult blobs;  
    CBlob *currentBlob; 
	CBlob blob;
    CvPoint pt1, pt2, point;		// 2 opposite corner points of the bounding rectangle and the center point of the blob
    CvRect cvRect;					// bounding rectangle for each blob
	CBlobGetXCenter getXCenter;		//	x-coordinate of the center point
	CBlobGetYCenter getYCenter;	

	int count = 0;                  // starting with counting value = 0
	char buffer3[100];

	///////////////////////////////// Font initialization to PutText in frame /////////////////////////////////////////////////////////////////
	CvFont font;
	cvInitFont( &font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA );

///////////////////////////////// Variables declaration for displaying time //////////////////////////////////////////////////////////////  
	//time_t timeObj;
	//time( &timeObj );
	char buffer1[100];
	char buffer2[100];

	char buffer4[100];		//	SaveImage
	//////////////////////////////// Variables declaration for saving video //////////////////////////////////////////////////////////////////
	char buffer5[100];

//////////////////////////////// XML file ///////////////////////////////////////////////////////////////////////////////////////////////
	char buffer6[100]; // XMLfile label
	char buffer7[100]; // Time beginning  (XMLfile)
	char buffer8[100]; // Time ending     (XMLfile)


	cv::VideoCapture capture(0);
	if (!capture.isOpened())
	{m_strMODE = "Capture failed";}
	m_strMODE = "MODE 3";
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT3,m_strMODE);
	cv::namedWindow("VideoInput",1);
	//cv::namedWindow("BlurFrame",1);
	//cv::namedWindow("Extracted Foreground",1);
	cvNamedWindow("Binary",1);
	//cvNamedWindow("MorphologyEx",1);	
	time_t timeObj1;
	time( &timeObj1);
	tm *pTime1 = gmtime(&timeObj1);
	sprintf (buffer5, "D:/SaveVideo/CAM2demo/%d-%d-%d_%dh-%dm.avi",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
	sprintf (buffer6, "D:/SaveInfo/CAM2demo/%d-%d-%d_%dh-%dm.xml",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
	sprintf (buffer7, "Process begins  %d-%d-%d _ %dh-%dm",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);

	cv::VideoWriter writer;
	writer.open(buffer5, CV_FOURCC('M','J','P','G'), 10, cv::Size(640, 480), true );

	int numframe = 0;
	 
	for(;;)
	{
		cv::Mat frame;
		cv::Mat foreground;
		capture >>frame;
		numframe++;
		//cv::imshow ("CameraInput",frame);
		cv::Mat blurframe;
		cv::GaussianBlur(frame, blurframe, cv::Size(5,5), 1.5);
		//cv::imshow ("BlurFrame", blurframe);
		//writer<<frame;

		mog(blurframe, foreground, 0.01);
		cv::threshold(foreground, foreground, 128, 255, cv::THRESH_BINARY_INV);
		

		//============ Draw 2 green lines which limit counting zone =======================//
			cv::line (frame,cvPoint(260,0),cvPoint(260,480),cvScalar(0,255,0),2,8,0);
			cv::line (frame,cvPoint(305,0),cvPoint(305,480),cvScalar(0,255,0),2,8,0);

		/* Put green text to the original frame */
			cv::putText(frame,"counting zone", cvPoint(290,30), CV_FONT_HERSHEY_PLAIN, 1.0, cvScalar(0, 255, 0));
		
		/* Display time in the original frame */
			time_t timeObj2;
			time( &timeObj2 );
			tm *pTime2 = gmtime(&timeObj2);
			sprintf (buffer1, "%d/%d/%d",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900);
			sprintf (buffer2, "%dh:%dm",(pTime2->tm_hour+7)%24, pTime2->tm_min);
			cv::putText(frame, buffer1, cvPoint(520,20), CV_FONT_HERSHEY_PLAIN,1.0, cvScalar(0, 255, 0));
			cv::putText(frame, buffer2, cvPoint(520,40), CV_FONT_HERSHEY_PLAIN,1.0, cvScalar(0, 255, 0));
		
		
		IplImage iplframe = foreground;
		IplImage* inverseframe = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 1);

		cvNot(&iplframe,inverseframe);
		//cv::imshow ("Extracted Foreground", foreground);
		//cvShowImage ("Inverse", inverseframe);

		//cv::Mat newbinaryframe = cvCreateImage(cvGetSize(&iplframe),IPL_DEPTH_8U,1);
		//cv::Mat lastbinaryframe = cvCreateImage(cvGetSize(&iplframe), IPL_DEPTH_8U,1);
		cv::Mat newbinaryframe;
		cv::Mat lastbinaryframe;
		cv::Mat  element (5,5,CV_8U,cv::Scalar(1));
		cv::morphologyEx(inverseframe, newbinaryframe, cv::MORPH_CLOSE, element);
		cv::morphologyEx(newbinaryframe, lastbinaryframe, cv::MORPH_OPEN, element);
		//cv::imshow ("MorphologyEx",lastbinaryframe);

		IplImage ipllastbinaryframe = lastbinaryframe;

		 blobs = CBlobResult( &ipllastbinaryframe, NULL, 0 );    
      
        /* Exclude white blobs smaller than the given value (5000) */  
        blobs.Filter( blobs,  
                      B_EXCLUDE,  
                      CBlobGetArea(),  
                      B_LESS,  
                      3000 );  // The bigger the last parameter, the bigger the blobs need to be for inclusion  
        
		/* Get the total number of the blob */
        int num_blobs = blobs.GetNumBlobs();  
		//std::cout<<"The amount of blobs is :"<<num_blobs<<std::endl;

		/* Allocate memory for the binary frame (to display the result of the counting process)*/
		 IplImage*result = cvCreateImage( cvGetSize( &ipllastbinaryframe ),  
                                           IPL_DEPTH_8U,  
                                           3 );  // Image will contain color elements like text, line, ...  
        /* Result frame's combination from image after morphology operation */
		cvMerge( &ipllastbinaryframe, &ipllastbinaryframe, &ipllastbinaryframe, NULL, result );

		cvPutText(result, buffer1, cvPoint(520,20), &font, cvScalar(0, 255, 0));
		cvPutText(result, buffer2, cvPoint(520,40), &font, cvScalar(0, 255, 0));

		/* Display the total number of product in the original video input and the result frame*/
		sprintf(buffer3,"$Product: %u",count);
		cv::putText(frame, buffer3, cvPoint(520,60), CV_FONT_HERSHEY_PLAIN,1.0, cvScalar(0, 255, 0));
		cvPutText(result, buffer3, cvPoint(520,60), &font, cvScalar(0, 255, 0));
		if (numframe > 60){
		cv::putText(frame,"System ready",cvPoint(10,20),  CV_FONT_HERSHEY_PLAIN,1.0, cvScalar(0, 255, 0));
		cvPutText(result, "System ready", cvPoint(10,20), &font, cvScalar(0, 255, 0));	
		//========= Process for each blob =================//
            for ( int i = 0; i < num_blobs; i++ )  
            {  
                currentBlob = blobs.GetBlob( i );  // Get the current blob
				/* Attach a bounding rectangle for each blob discovered */  
            	cvRect = currentBlob->GetBoundingBox();  
				//std::cout<<"<width,height> of the Rect BoundingBox is:"<<"<"<<cvRect.width<<","<<cvRect.height<<">"<<std::endl;

				/* Identify the coordinates of 2 opposite corners points which form the bouding rectangle */ 
                pt1.x = cvRect.x;  
                pt1.y = cvRect.y;  
                pt2.x = cvRect.x + cvRect.width;  
                pt2.y = cvRect.y + cvRect.height;  
      
                /* Attach bounding rectangle to blob in orginal video input */ 
                cv::rectangle( frame,  
                             pt1,  
                             pt2,  
                             cvScalar(0, 255, 0, 0),  // green color
                             3,  
                             8,  
                             0 ); 
				/* Attach bounding rectangle to blob in the result frame */
				cvRectangle( result,  
                             pt1,  
                             pt2,  
                            cvScalar(0, 255, 0, 0),  // green color
                             3,  
                             8,  
                            0 );  

				blob = blobs.GetBlob(i); // Get the current blob
				/* Get the center's coordinates of the current blob */
				point = cvPoint((int)(getXCenter(blob)), (int)(getYCenter(blob)));
				//std::cout<<"the center of the blob No"<<i<<"<"<<(int)(getXCenter(blob))<<","<<(int)(getYCenter(blob))<<">"<<std::endl;

				/* Attach a circle in the center of the blob in original video input */
				cv::circle(frame, point, 4, CV_RGB(255, 0, 0), -1);
				/* Attach a circle in the center of the blob in the result frame */
				cvCircle(result, point, 4, CV_RGB(255, 0, 0), -1);

				/* Whenever the center of an arbitrary blob exist in the couting zone....*/
				if((260<(int)(getXCenter(blob)))&&(((int)(getXCenter(blob))<305)))
				{
					count++;													    //... then increase the counting value
					std::cout<<"The total number of product is:"<<count<<std::endl;	//	Display the counting value
					blob.FillBlob( result, CV_RGB(255,0,0));						//  Fill this blob with red color 	
				    //std::cout<<"the center of the blob No"<<i<<"<"<<(int)(getXCenter(blob))<<","<<(int)(getYCenter(blob))<<">"<<std::endl;
					
					//p++;				
					sprintf(buffer4,"D:/SaveImage/CAM2demo/%d-%d-%d_%dh-%dm Product%u.jpg",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900,(pTime2->tm_hour+7)%24, pTime2->tm_min ,count);
					cv::imwrite(buffer4,frame);
					cv::imwrite("Fillblob.jpg",result);
					//p++;

				}	
			}
			}
		/* Display original video input */  
			cv::imshow( "VideoInput", frame  );  
            /* Display result frame */  
			cvShowImage ("Binary", result);
			writer<<frame;

		if (cvWaitKey(66)==27)  // assume that the input framerate is 15 frames/s
			{
				sprintf (buffer8, "Process ends    %d-%d-%d_%dh-%dm",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900,(pTime2->tm_hour+7)%24, pTime2->tm_min);
				CvFileStorage* info = cvOpenFileStorage (buffer6, 0, CV_STORAGE_WRITE);
				cvWriteString (info, "Time_beginning", buffer7, 0);
				cvWriteString (info, "Time_ending", buffer8, 0);
				cvWriteInt ( info, "Product", count );
				cvReleaseFileStorage (&info);
				break;
			}      
		cvReleaseImage (&inverseframe);
	}

	cvDestroyWindow("VideoInput");
	cvDestroyWindow("Binary");
}


void ClearningMFC2Dlg::OnMODE3()
{
	// TODO: Add your control notification handler code here
	CBlobResult blobs;  
    CBlob *currentBlob; 
	CBlob blob;
    CvPoint pt1, pt2, point;		// 2 opposite corner points of the bounding rectangle and the center point of the blob
    CvRect cvRect;					// bounding rectangle for each blob
	CBlobGetXCenter getXCenter;		//	x-coordinate of the center point
	CBlobGetYCenter getYCenter;		//	y-coordinate of the center point
	
	int count = 0;                  // starting with counting value = 0
	char buffer3[100];				// display quantity of product

///////////////////////////////// Font initialization to PutText in frame /////////////////////////////////////////////////////////////////
	CvFont font;
	cvInitFont( &font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA );

///////////////////////////////// Variables declaration for displaying time //////////////////////////////////////////////////////////////  
	//time_t timeObj;
	//time( &timeObj );
	char buffer1[100];
	char buffer2[100];

//////////////////////////////// Variables declaration for saving image //////////////////////////////////////////////////////////////////
	//int p = 0;
	char buffer4[100];

//////////////////////////////// Variables declaration for saving video //////////////////////////////////////////////////////////////////
	char buffer5[100];

//////////////////////////////// XML file ///////////////////////////////////////////////////////////////////////////////////////////////
	char buffer6[100]; // XMLfile label
	char buffer7[100]; // Time beginning  (XMLfile)
	char buffer8[100]; // Time ending     (XMLfile)

//////////////////////////////// Variables declaration for cvFilter2D (sharpen edge -> video look nicer) ////////////////////////////////////	
	//// continue to test.......
	/*float value[] = { 0, -1, 0,
					  -1, 5, -1,
					   0, -1, 0};
	CvMat matrix;
	CvMat* kernel = cvInitMatHeader(&matrix,3, 3, CV_32FC1, value);*/

//////////////////////////////// Initialize capturing from CAM1 (overhead) /////////////////////////////////////////////////////////////////
    IplImage* frame = 0;
	IplImage* frame1 = 0;
	//IplImage* result = 0;
	CvCapture* capture = 0;
    capture = cvCaptureFromCAM( 0 );  
	
	/** check whether capturing initialization is successful **/
	if( !capture )  
            {m_strMODE = "Capture failed";}
	m_strMODE = "MODE 2";
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT3,m_strMODE);  

    assert (capture != NULL);  // If no capturing done, rest of the program proceeds totally ignorant

    /** Window used to display input video with bounding rectangles **/ 
    cvNamedWindow( "VideoInput", CV_WINDOW_AUTOSIZE );
	/** Window used to display binary video **/
	cvNamedWindow( "Binary", CV_WINDOW_AUTOSIZE ); 
	//*Notice that the CAM's resolutionis 640x480 so the window will fixed to this size 
   
	/// cvNamedWindow( "Grayscale Gauss" );

// Time in videofile labelling
time_t timeObj1;
time( &timeObj1);
tm *pTime1 = gmtime(&timeObj1);
sprintf (buffer5, "D:/SaveVideo/CAM1demo(mode2)/%d-%d-%d_%dh-%dm.avi",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
sprintf (buffer6, "D:/SaveInfo/CAM1demo(mode2)/%d-%d-%d_%dh-%dm.xml",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
sprintf (buffer7, "Process begins  %d-%d-%d_%dh-%dm",pTime1->tm_mday,pTime1->tm_mon+1,pTime1->tm_year+1900,(pTime1->tm_hour+7)%24, pTime1->tm_min);
CvVideoWriter* writer = cvCreateVideoWriter (buffer5, CV_FOURCC('M','J','P','G'), 15, cvSize(640, 480), true);

//=============================== infinite main loop ===========================================================//
 	while( 1 )
        { 
            frame = cvQueryFrame( capture );
			frame1 = cvCloneImage( frame );    // "frame1" is a full copy of "frame"

         //============ Draw 2 green lines which limit counting zone =======================//
			cvLine (frame,cvPoint(0,210),cvPoint(640,210),cvScalar(0,255,0),2,8,0);
			cvLine (frame,cvPoint(0,270),cvPoint(640,270),cvScalar(0,255,0),2,8,0);

		/* Put green text to the original frame */
			cvPutText(frame,"counting zone", cvPoint(0,240), &font, cvScalar(0, 255, 0));
		
		/* Display current time in the original frame */
			time_t timeObj2;
			time( &timeObj2 );
			tm *pTime2 = gmtime(&timeObj2);
			sprintf (buffer1, "%d/%d/%d",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900);
			sprintf (buffer2, "%dh:%dm",(pTime2->tm_hour+7)%24, pTime2->tm_min);
			cvPutText(frame, buffer1, cvPoint(520,20), &font, cvScalar(0, 255, 0));
			cvPutText(frame, buffer2, cvPoint(520,40), &font, cvScalar(0, 255, 0));
      
		//============= Convert to Grayscale then perform smoothing operation =============//
        /* Allocate memory for the grayframe (single channel) version of the copy frame */
			IplImage* grayframe = cvCreateImage( cvGetSize(frame),  
                                         IPL_DEPTH_8U, 1);
        /* Make grayframe version of the copy frame (without line and text)*/
			cvCvtColor(frame1, grayframe, CV_RGB2GRAY); 
			frame1 = NULL;
			cvReleaseImage(&frame1);
		
		/* Perform Gaussian blur */
			IplImage* smoothframe = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
			cvSmooth(grayframe, smoothframe, CV_GAUSSIAN, 15,15); // (not the fastest but probably the most useful )

		//// continue to test .....
		/*IplImage*laplace = cvCreateImage(cvGetSize(frame),IPL_DEPTH_32F,1);
		  cvFilter2D(smoothframe, laplace, kernel);*/

		/////cvShowImage ("GrayScale Gauss",smoothframe);

		//============== Convert to Binary then perform morphology operation ===============//
		/* Allocate memory for the processing frames */
   		IplImage* binaryframe = cvCreateImage (cvGetSize(frame),IPL_DEPTH_8U,1);      // binary frame (after Threshold)
		IplImage* newbinaryframe = cvCreateImage (cvGetSize(frame),IPL_DEPTH_8U,1);   // (after closing operation)
		IplImage* lastbinaryframe = cvCreateImage (cvGetSize(frame),IPL_DEPTH_8U,1);  // (after opening operation)
        cvThreshold( smoothframe,       // source image  
                    binaryframe,        // destination image  
                    55,                 // threhold val.  
                    255,                // max. val  
                    CV_THRESH_BINARY ); // binary type );
			
		//========== Make new kernel for morphology operation ========// 
		IplConvKernel *element;
		element = cvCreateStructuringElementEx (5,5,3,3,CV_SHAPE_RECT, NULL); // 11x11 rectangle shape, anchor in the center
		IplImage*timg = cvCloneImage(binaryframe);								// temp image

		//========== Perform morphology operation ====================//
		cvMorphologyEx (binaryframe, newbinaryframe, timg, element,CV_MOP_CLOSE , 1);  // closing operation 1 time
		cvMorphologyEx (newbinaryframe, lastbinaryframe,timg,element,CV_MOP_OPEN,1);   // closing operation 1 time
		cvReleaseImage (&timg);						// Memory Release
		cvReleaseStructuringElement(&element );		

        /*IplConvKernel *element1;
		element1 = cvCreateStructuringElementEx (9,9,3,3,CV_SHAPE_ELLIPSE, NULL);
		cvDilate (binaryframe,newbinaryframe,element1,3);
		cvReleaseStructuringElement(&element1 );*/
				
		//============================= Counting blob process ==========================//	
		/* Detect the white blobs from the black background */ 
        blobs = CBlobResult( lastbinaryframe, NULL, 0 );    
      
        /* Exclude white blobs smaller than the given value (5000) */  
        blobs.Filter( blobs,  
                      B_EXCLUDE,  
                      CBlobGetArea(),  
                      B_LESS,  
                      5000 );  // The bigger the last parameter, the bigger the blobs need to be for inclusion  
        
		/* Get the total number of the blob */
        int num_blobs = blobs.GetNumBlobs();  
		//std::cout<<"The amount of blobs is :"<<num_blobs<<std::endl;

		/* Allocate memory for the binary frame (to display the result of the counting process)*/
		 IplImage*result = cvCreateImage( cvGetSize( lastbinaryframe ),  
                                           IPL_DEPTH_8U,  
                                           3 );  // Image will contain color elements like text, line, ...  
        /* Result frame's combination from image after morphology operation */
		cvMerge( lastbinaryframe, lastbinaryframe, lastbinaryframe, NULL, result );
		
		/* Display time in the result frame */
		//tm *pTime = gmtime(&timeObj);
		//sprintf (buffer1, "%d/%d/%d  %dh:%dm",pTime->tm_mday,pTime->tm_mon+1,pTime->tm_year+1900, pTime->tm_hour+7, pTime->tm_min);
		cvPutText(result, buffer1, cvPoint(520,20), &font, cvScalar(0, 255, 0));
		cvPutText(result, buffer2, cvPoint(520,40), &font, cvScalar(0, 255, 0));
      

		/* Display the total quantity of product in the original video input and the result frame*/
		sprintf(buffer3,"$Product: %u",count);
		cvPutText(frame, buffer3, cvPoint(520,60), &font, cvScalar(0, 255, 0));
		cvPutText(result, buffer3, cvPoint(520,60), &font, cvScalar(0, 255, 0));

			//========= Process for each blob =================//
            for ( int i = 0; i < num_blobs; i++ )  
            {  
                currentBlob = blobs.GetBlob( i );  // Get the current blob
				/* Attach a bounding rectangle for each blob discovered */  
            	cvRect = currentBlob->GetBoundingBox();  
				//std::cout<<"<width,height> of the Rect BoundingBox is:"<<"<"<<cvRect.width<<","<<cvRect.height<<">"<<std::endl;

				/* Identify the coordinates of 2 opposite corners points which form the bouding rectangle */ 
                pt1.x = cvRect.x;  
                pt1.y = cvRect.y;  
                pt2.x = cvRect.x + cvRect.width;  
                pt2.y = cvRect.y + cvRect.height;  
      
                /* Attach bounding rectangle to blob in orginal video input */ 
                cvRectangle( frame,  
                             pt1,  
                             pt2,  
                             cvScalar(0, 255, 0, 0),  // green color
                             3,  
                             8,  
                             0 ); 
				/* Attach bounding rectangle to blob in the result frame */
				cvRectangle( result,  
                             pt1,  
                             pt2,  
                            cvScalar(0, 255, 0, 0),  // green color
                             3,  
                             8,  
                            0 );  

				blob = blobs.GetBlob(i); // Get the current blob
				/* Get the center's coordinates of the current blob */
				point = cvPoint((int)(getXCenter(blob)), (int)(getYCenter(blob)));
				//std::cout<<"the center of the blob No"<<i<<"<"<<(int)(getXCenter(blob))<<","<<(int)(getYCenter(blob))<<">"<<std::endl;

				/* Attach a circle in the center of the blob in original video input */
				cvCircle(frame, point, 4, CV_RGB(255, 0, 0), -1);
				/* Attach a circle in the center of the blob in the result frame */
				cvCircle(result, point, 4, CV_RGB(255, 0, 0), -1);
			
				/* Whenever the center of an arbitrary blob exist in the couting zone....*/
				if((210<(int)(getYCenter(blob)))&&(((int)(getYCenter(blob))<270)))
				{

					//... then increase the counting value
					if((42000<(blob.Area()))&&((blob.Area())<50000))
					{count=count+3;}
					
					if((29000<(blob.Area()))&&((blob.Area())<36000))
					{count=count+2;}
					
					if((14500<(blob.Area()))&&((blob.Area())<18000))
					{count++;}
					//count++;
					std::cout<<"blob's area :"<<blob.Area()<<std::endl;
					std::cout<<"The total number of product is:"<<count<<std::endl;	//	Display the counting value
					blob.FillBlob( result, CV_RGB(255,0,0));						//  Fill this blob with red color 	
				    //std::cout<<"the center of the blob No"<<i<<"<"<<(int)(getXCenter(blob))<<","<<(int)(getYCenter(blob))<<">"<<std::endl;
					
					//p++;				
					sprintf(buffer4,"D:/SaveImage/CAM1demo(mode2)/%d-%d-%d_%dh-%dm Product%u.jpg",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900,(pTime2->tm_hour+7)%24, pTime2->tm_min ,count);
					cvSaveImage(buffer4,frame);
					//p++;

				}									
			}
		
			/* Display original video input */  
            cvShowImage( "VideoInput", frame  );  
            /* Display result frame */  
			cvShowImage ("Binary", result);
			cvWriteFrame( writer, frame );

           	if (cvWaitKey(66)==27)  // assume that the input framerate is 15 frames/s
			{
				sprintf (buffer8, "Process ends    %d-%d-%d_%dh-%dm",pTime2->tm_mday,pTime2->tm_mon+1,pTime2->tm_year+1900,(pTime2->tm_hour+7)%24, pTime2->tm_min);
				CvFileStorage* info = cvOpenFileStorage (buffer6, 0, CV_STORAGE_WRITE);
				cvWriteString (info, "Time_beginning", buffer7, 0);
				cvWriteString (info, "Time_ending", buffer8, 0);
				cvWriteInt ( info, "Product", count );
				cvReleaseFileStorage (&info);
				break;
			}      
			cvReleaseImage (&result);
			cvReleaseImage (&grayframe);
			cvReleaseImage (&smoothframe);
			cvReleaseImage (&binaryframe);
			cvReleaseImage (&newbinaryframe);
			cvReleaseImage (&lastbinaryframe);
			}  
		cvReleaseVideoWriter (&writer);
        cvReleaseCapture( &capture );  
		cvDestroyWindow( "VideoInput" );
		cvDestroyWindow( "Binary" );
		//cvReleaseImage( &frame );
		//cvReleaseImage ( &result);
}
