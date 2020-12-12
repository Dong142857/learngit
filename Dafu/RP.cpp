# include "Energy.h"

int THRESH_BR = 20;//56//56
int THRESH_GRAY = 20;//79//50

// 两个滑轨
void onBrThreshTrackbar(int, void*)
{
	setTrackbarPos("BR", "Object Detection", THRESH_BR);
}
void onGrayThreshTrackbar(int, void*)
{
	setTrackbarPos("GRAY", "Object Detection", THRESH_GRAY);
}

int main()
{
	Energy energy;// 击打能量机关
	VideoCapture capture("C:/Users/administered/Desktop/opencv/视觉大礼包/final.avi");
	Mat frame;
	Mat mask;
	ArmorRect present;
	ArmorRect former;
	namedWindow("source", WINDOW_NORMAL);
	namedWindow("mask", WINDOW_NORMAL);
	namedWindow("TrackBar", WINDOW_NORMAL);
	createTrackbar("BR", "TrackBar", &THRESH_BR, 255, onBrThreshTrackbar);
	createTrackbar("GRAY", "TrackBar", &THRESH_GRAY, 255, onGrayThreshTrackbar);
	int delay = 30;
	energy.isRed(false);//目标是否为红色
	while (1)
	{
		capture >> frame;
		energy.setThresh(THRESH_BR, THRESH_GRAY);		// 填入阈值
		energy.videoProcess(frame, mask, present, former);
		// 速度可以放进类里面计算
		//double Speed = (energy.retSpeed() + energy.retNewSpeed()) / 2;
		energy.updateSpeed(present, former, frame);

		//putText(frame, "UPDATE: " + std::to_string(Speed), Point(100, 100), CV_FONT_NORMAL, 1, Scalar(0, 255, 0), 2);
		imshow("mask", mask);
		imshow("source", frame);
		if (delay > 0 && waitKey(delay) >= 32)
			waitKey(0);
	}
	return 0;
}
