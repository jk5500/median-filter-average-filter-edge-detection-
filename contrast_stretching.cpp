#include"iostream"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;





int c_compute(int x, int r1, int s1, int r2, int s2) {
	float output;
	// r1 minimum value of pixel intensity in the original image
	// r2 maximum value of pixel intensity
	// s1 minimum value of pixel intensity in the new image that we want
	// s2 maximum valu of pixel intensity
	if (x >= 0 && x <= r1) {
		 output = s1 / r1*x;
	}
	else if(x > r1 && r2 <= r2) {
		output = ((s2 - s1) / (r2 - r1))*(x - r1) + s1;
	}
	else if (x > r2 && x <= 255) {
		output = ((255 - s2) / (255 - r2))*(x - r2) + s2;
	}
	return int (output);
}

void hist(Mat image, int histogram[])
{

	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}

	// calculate the no of pixels for each intensity values
	for (int x = 0; x < image.rows; x++)
		for (int y = 0; y< image.cols; y++)
			histogram[(int)image.at<uchar>(x, y)]++;

}



void histDisplay(int histogram[], const char* name)
{
	int hist[256];
	for (int i = 0; i < 256; i++)
	{
		hist[i] = histogram[i];
	}
	// draw the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = hist[0];
	for (int i = 1; i < 256; i++) {
		if (max < hist[i]) {
			max = hist[i];
		}
	}

	// normalize the histogram between 0 and histImage.rows

	for (int i = 0; i < 256; i++) {
		hist[i] = ((double)hist[i] / max)*histImage.rows;
	}


	// draw the intensity line for histogram
	for (int i = 0; i < 256; i++)
	{
		line(histImage, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - hist[i]),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	// display histogram
	namedWindow(name, CV_WINDOW_AUTOSIZE);
	imshow(name, histImage);
}


int main() {
	Mat image;

	image = imread("C:\\Users\\kamal\\Documents\\Visual Studio 2015\\Projects\\contrast\\data\\hotspot.png", CV_LOAD_IMAGE_GRAYSCALE);

	namedWindow("original image");
	imshow("original image",image);

	// Generate the histogram
	int histogram[256];
	hist(image, histogram);

	// Display the original Histogram
	histDisplay(histogram, "Original Histogram");


	int r1, s1, r2, s2;
	cout << "Enter r1: " << endl; cin >> r1;
	cout << "Enter s1: " << endl; cin >> s1;
	cout << "Enter r2: " << endl; cin >> r2;
	cout << "Enter s2: " << endl; cin >> s2;
	Mat newimage;
	newimage = image.clone();

	for (int a = 0; a < image.rows; a++) {

		for (int b = 0; b < image.cols; b++) {

			int output = image.at<uchar>(a, b);
			int result = c_compute(output, r1, s1, r2, s2);

			newimage.at<uchar>(a, b) = result;
		}
	}

	namedWindow("final image");
	imshow("final image", newimage);
	
	

	waitKey();
	return 0;
}