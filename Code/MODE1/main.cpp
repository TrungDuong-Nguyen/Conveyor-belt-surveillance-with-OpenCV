#include "cv.h"  
#include "highgui.h"  
#include "BlobResult.h"  
#include <iostream>
#include <time.h>

int main( )  
{  
////////////////////////////////// Variables declaration for counting blob process /////////////////////////////////////////////////////////
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
        {  
            printf( "Could not initialize capturing...\n" );  
        }  

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
 
		return 0;  
    }  