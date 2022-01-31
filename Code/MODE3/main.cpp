#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "BlobResult.h"
#include <time.h>
#include <iostream>

int main()
{
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
		return -1;
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