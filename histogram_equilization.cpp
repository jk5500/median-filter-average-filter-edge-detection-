#include"iostream"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;

int main() {


	Mat image;

	image = imread("C:\\Users\\kamal\\Documents\\Visual Studio 2015\\Projects\\histogram_equilization\\data\\lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("original image");
	imshow("original image", image);

	int intensity[256];
	for (int i = 0; i < 256; i++) {
		intensity[i] = 0;
	}
	for (int x = 0; x < image.rows; x++) {
		for (int y = 0; y < image.cols; y++) {


			intensity[(int)image.at<uchar>(x, y)]++;

		}
	}

	for (int i = 0; i < 256; i++) {
		cout << intensity[i] << " , ";
	}

	
	int cdf[256];
	for (int i = 0; i < 256; i++) {
		cdf[i] = 0;
	}
	
	int value = 0;
	for (int i = 1; i < 256; i++) {
		value += intensity[i];
		cdf[i] = value;
	}

	int min = 10000000000;
	for (int i = 0; i < 256; i++) {
		if (min > cdf[i]) {
			min = cdf[i];
		}
	}
	cout << "minimum value "<<min << endl;
	if (min == 0) {
		min = 1;
	}
	for (int i = 0; i < 256; i++) {
		cout << cdf[i] << " , ";
	}

	int size = image.rows * image.cols;
	float alpha = 255.0 / (size-min);

	int hvalue[256];
	for (int i = 0; i < 256; i++)
	{
		hvalue[i] = cvRound((cdf[i]-min) * alpha);
	}
	

	for (int i = 0; i < 256; i++) {
		cout << hvalue[i] << " , ";
	}
	Mat newimage = image.clone();

	for (int a = 0; a < image.rows; a++) {
		for (int b = 0; b < image.cols; b++) {
			newimage.at<uchar>(a, b) =  hvalue[image.at<uchar>(a, b)];
		}
	}

	

	namedWindow("final image");
	imshow("final image", newimage);
 	waitKey();

	return 0;
}