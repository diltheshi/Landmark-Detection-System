#include<opencv2\opencv.hpp>
#include"opencv2\highgui\highgui.hpp"
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

int H_MIN=0;
int H_MAX=256;
int S_MIN=0;
int S_MAX=256;
int V_MIN=0;
int V_MAX=256;

int x,a;
int y,n;

Mat img_rgb,img_thresh,img_hsv,drawing,output;

char* window_name= "Threshold_demo"; 
char* window_name1 = "Thresholded image";

char* trackbar_hmin= "H_MIN"; 
char* trackbar_hmax= "H_MAX";
char* trackbar_smin= "S_MIN";
char* trackbar_smax= "S_MAX";
char* trackbar_vmin= "V_MIN";
char* trackbar_vmax= "V_MAX";


void Threshold_Demo(int, void*);
void MorphOps(Mat & thresh)
{
	Mat erodeElement = getStructuringElement(MORPH_RECT,Size(3,3));
	Mat dilateElement = getStructuringElement(MORPH_RECT,Size(15,15));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);

	dilate(thresh,thresh,dilateElement);
	dilate(thresh,img_thresh,dilateElement);
}

int main(int argc,char *argv[])
{	
	cout<<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<"\t\t				AERIAL VIEW OF GOOGLE 2D IMAGE\n";
	cout<<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<"\n\n";
	cout<<" ...............................\n";
	cout<<"     Image Content \n ";	
	cout<<" ...............................\n";
	cout<<" \t(1)Source Images\n\n   \t(2)HSV Image\n\n   \t(3)Threshold Demo\n\n  \t(4)Thresholded Image\n\n  \t(5)Output Image\n\n";
	while(true)
	{
	cout<<" -------------------------\n";
	cout<<"     Selection Area  \n ";	
	cout<<"-------------------------\n";
	cout<<" (1)top rotated image\n (2)side rotated image\n (3)bottom rotated image\n";
	cout<<"\nselect one from the above: ";
	cin>>a;	
	
		int c; 
		if(a==1)
		{
			img_rgb = imread("Capture.PNG");
		}
		else if(a==2)
		{
			img_rgb = imread("Capture_ROTATE1.PNG");
		}
		else if(a==3)
		{
			img_rgb = imread("Capture_Rotate_a.PNG");
		}
		else
		{
			cout<<"sorry you have entered an invalid number.";			
		}
		if(a>3||a<1)
		{
			return -1;
		}
			
	cout<<"\n --------------------------------------\n";
	cout<<"     Selection of thresholded image  \n ";
	cout<<"--------------------------------------\n";
	cout<<" (1)Tennis Cort\n (2)Pool\n (3)Building  complex\n";
	cout<<"\nselect one from the above: ";
	cin>>x;
	
		if(x>3)	
		{
			cout<<"sorry you have entered an invalid number.";
		}
		if(x>3||x<1)
		{
			return -1;
		}
	cout<<"\n --------------------------------------\n";
	cout<<"     New selection  \n ";
	cout<<"--------------------------------------\n";
	cout<<" 1.click on the output image\n 2.press enter for the user\n 3.go through derections\n";


	cout<<"\n\t\tSee Our Creations\n";	
	cout<<"\n\t\t****************************************\n";
	cout<<"\t\t		Thank you \n";
	cout<<"\n\t\t****************************************\n";
	
	//namedWindow("source image",WINDOW_AUTOSIZE);	
	//imshow("source image",img_rgb);

	namedWindow( "Output", CV_WINDOW_AUTOSIZE );
	
	drawing = imread("Contours.PNG");
	 if (img_rgb.channels()>1)   
	 { 
		 cvtColor(img_rgb,img_hsv,CV_RGB2HSV);
		 blur(img_hsv,img_hsv,Size(10,10)); 		 
	 }	

	// namedWindow("hsv image",WINDOW_AUTOSIZE);
	 //imshow("hsv image",img_hsv);

	//namedWindow(window_name, 0);
 
	createTrackbar(trackbar_hmin,window_name,&H_MIN,H_MAX,Threshold_Demo);
	createTrackbar(trackbar_hmax,window_name,&H_MAX,H_MAX,Threshold_Demo);
	
	createTrackbar(trackbar_smin,window_name,&S_MIN,S_MAX,Threshold_Demo);
	createTrackbar(trackbar_smax,window_name,&S_MAX,S_MAX,Threshold_Demo);

	createTrackbar(trackbar_vmin,window_name,&V_MIN,V_MAX,Threshold_Demo);
	createTrackbar(trackbar_vmax,window_name,&V_MAX,V_MAX,Threshold_Demo);

    Threshold_Demo(0, 0);

	
	/*while(true)
      {  
		int c; 
		c = waitKey(20); 
		if((char)c == 27) 
			break;  
   } */
	
	waitKey(0);
	}
	return 0;

}

void Threshold_Demo(int, void*)
{
		
		 /* 0: Binary    
		 1: Binary Inverted    
		 2: Threshold Truncated 
		3: Threshold to Zero     
		4: Threshold to Zero Inverted     */ 

		
	
		/*inRange(img_hsv,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),img_thresh);
		imshow(window_name, img_thresh);*/

		if(x==1)
			{
				inRange(img_hsv,Scalar(0,89,145),Scalar(58,137,175),img_thresh);
				//imshow(window_name1, img_thresh);
				
			
			}
			else if(x==2)
			{
				inRange(img_hsv,Scalar(0,69,189),Scalar(38,256,248),img_thresh);
				//imshow(window_name1, img_thresh);				
			}
			else if(x==3)
			{
				inRange(img_hsv,Scalar(109,85,123),Scalar(161,200,256),img_thresh);
				//imshow(window_name1, img_thresh);		
				
			}

			MorphOps(img_thresh);

			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			 findContours(img_thresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );			 
			vector<vector<Point> > contours_poly( contours.size() );
			vector<Rect> boundRect( contours.size() );
			vector<Point2f>center( contours.size() );
		    vector<float>radius( contours.size() );		

			for( int i = 0; i < contours.size(); i++ )
				{
					approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
					 boundRect[i] = boundingRect( Mat(contours_poly[i]) );
					minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
				 }

			Mat output = img_rgb.clone();
			Mat drawing = Mat::zeros( img_thresh.size(), CV_8UC3 );

			for( int i = 0; i< contours.size(); i++ )
			 {
				 Scalar color = Scalar(255,0,0);
				 drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );				 
				 rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
				 /*circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );*/

				 drawContours(output, contours_poly, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
				 rectangle( output, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
			}
			
			//namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
			imshow("Output",output);
			//imshow("Contours", drawing );
			//imwrite("Contours.PNG",drawing );
			
				
}

