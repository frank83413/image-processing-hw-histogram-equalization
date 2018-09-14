#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
using namespace std;
using namespace cv;
void homework1(Mat SrcImg ,Mat DstImg);		//第一個問題
void homework2(Mat SrcImg ,Mat DstImg);		//第二個問題
void homework3(Mat SrcImg ,Mat DstImg);		//第三個問題
double power(float a, float b);				//用來算次方

double power(float a, float b){
	double c=1;
	for(int i=0; i<b ;i++){
		c=c*a;
	}
	return c;
}

void homework1(Mat SrcImg ,Mat DstImg){
	double r,c=255;
	cout << "enter r:";
	cin >> r;
	c=1/power(c,r-1);							//計算c=255/(255^r)=1/255^(r-1)
	for(int i=0; i<SrcImg.rows; ++i){
		for(int j=0; j<SrcImg.cols; ++j)
		{
			DstImg.at<uchar>(i,j)=c*power(SrcImg.at<uchar>(i,j),r);	//S=c*R^r
		}
	}
}
void homework2(Mat SrcImg ,Mat DstImg){
	int bit;									//用來紀錄參考bit的位數
	int test=0;									//用來測試是在0區間還是1區間
	cout << "enter the reference bit:";			
	cin >> bit;
	bit=power(2,bit-1);							//將計算出來的區間大小存回bit中
	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j){
		{
			test=SrcImg.at<uchar>(i,j)/bit;		//test=pixel值/bit後的商
			if(test%2==0)DstImg.at<uchar>(i,j)=0;//test為偶數屬於0區間 奇數屬於1區間
			else DstImg.at<uchar>(i,j)=255;
		}
	}
}

void homework3(Mat SrcImg ,Mat DstImg){
	float pixelnumber[256]={0};				//紀錄每個值有多少個pixel
	float n=SrcImg.rows*SrcImg.cols;		//n=全部pixel數量
	for(int i=0; i<SrcImg.rows; ++i){		//計算每個值有多少個pixel
		for(int j=0; j<SrcImg.cols; ++j)
		{
			pixelnumber[SrcImg.at<uchar>(i,j)]++;
		}
	}	
	for(int i=1; i<256; ++i){
		cout <<pixelnumber[i]/n << "\n";		//輸出舊機率
		pixelnumber[i]=pixelnumber[i]+pixelnumber[i-1];	//累加
	}
	for(int i=0; i<256; ++i){
		pixelnumber[i]=255*pixelnumber[i]/n;			//除以n		
	}	
	for(int i=0; i<SrcImg.rows; ++i){
		for(int j=0; j<SrcImg.cols; ++j)
		{
			DstImg.at<uchar>(i,j)=pixelnumber[SrcImg.at<uchar>(i,j)];//存入新值
		}
	}
	for(int i=1; i<256; ++i){
		pixelnumber[i]=0;		
	}
	for(int i=0; i<SrcImg.rows; ++i){		//計算每個值有多少個pixel
		for(int j=0; j<SrcImg.cols; ++j)
		{
			pixelnumber[DstImg.at<uchar>(i,j)]++;
		}
	}	
	int stop;
	cout <<"請隨機輸入一個數字以繼續顯示新機率";
	cin >> stop;				//輸出完舊的機率後，隨便輸入一個數字，繼續輸出新的機率，並輸出圖片
	for(int i=1; i<256; ++i){
		cout<< pixelnumber[i]/n << "\n";//輸出新機率		
	}
}

int main(){
	int homework;
	// Read input images
	// Fig3.tif is in openCV\bin\Release
	cout << "enter the work number(1,2,3):";
	cin >> homework;
	Mat SrcImg;
	Mat DstImg;
	if(homework==1){
		SrcImg = imread("Fig01_Slide10.tif", CV_LOAD_IMAGE_GRAYSCALE);
		DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
		homework1(SrcImg , DstImg);
	}
	if(homework==2){
		SrcImg = imread("Fig02_Slide14.tif", CV_LOAD_IMAGE_GRAYSCALE);
		DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
		homework2(SrcImg , DstImg);
	}
	if(homework==3){
		SrcImg = imread("Fig03_Slide22.tif", CV_LOAD_IMAGE_GRAYSCALE);
		DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
		homework3(SrcImg , DstImg);
	}
	

	// Show images
	imshow("Input Image", SrcImg);
	imshow("Output Image", DstImg);

	// Write output images
	imwrite("Fig3_output.tif", DstImg);
	
	waitKey(0);
	return 0;
}