#include"iostream"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;


int xgradient(Mat image, int x, int y){
	return 1 * image.at<uchar>(x - 1, y - 1) +2 * image.at<uchar>(x - 1, y)
		+ 1 * image.at<uchar>(x - 1, y + 1) - 1 * image.at<uchar>(x + 1, y - 1) -
		2 * image.at<uchar>(x , y - 1) - 1 * image.at<uchar>(x + 1, y + 1);
}

int ygradient(Mat image, int x, int y) {
	return 1 * image.at<uchar>(x - 1, y - 1) -1 * image.at<uchar>(x - 1, y + 1)
		+2 * image.at<uchar>(x, y - 1) -2 * image.at<uchar>(x, y+1) +
		1 * image.at<uchar>(x + 1, y - 1) - 1 * image.at<uchar>(x + 1, y + 1);

}

int main() {


	Mat image,dst;
	image = imread("C:\\Users\\kamal\\Documents\\Visual Studio 2015\\Projects\\edge_detection\\data\\bike.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	imshow("original image", image);
	dst = image.clone();
	int sum;
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			sum=abs(xgradient(image, i, j)) + abs(ygradient(image, i, j));
			sum =sum> 255 ? 255 : sum;
			sum=sum < 0 ? 0 : sum;
			dst.at<uchar>(i, j) = sum;
		}
	}
	imshow("final image", dst);
	waitKey();

	return 0;
}