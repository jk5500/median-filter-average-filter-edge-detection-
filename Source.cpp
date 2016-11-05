#include"iostream"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;


void insertionsort(int A[]) {

	for (int i = 0; i < 9; i++) {

		int j = i;

		while (j > 0 && A[j - 1]> A[j]) {

			int temp = A[j-1];
			A[j - 1] = A[j];
			A[j] = temp;
			j--;

		}
	}
}




int main() {

	Mat image;

	image = imread("C:\\Users\\kamal\\Documents\\Visual Studio 2015\\Projects\\median_filter\\data\\lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("original image");
	imshow("original image", image);

	Mat dst;
	dst = image.clone();
	
	int value[9];
	for (int a = 1; a < image.rows-1; a++) {
		for (int b = 1; b < image.cols-1; b++) {
			value[0] = image.at<uchar>(a - 1, b - 1);
			value[1] = image.at < uchar>(a, b- 1);
			value[2] = image.at<uchar>(a + 1, b - 1);
			value[3] = image.at<uchar>(a-1, b );
			value[4] = image.at<uchar>(a , b );
			value[5] = image.at<uchar>(a + 1, b );
			value[6] = image.at<uchar>(a - 1, b + 1);
			value[7] = image.at<uchar>(a , b +1);
			value[8] = image.at<uchar>(a + 1, b + 1);
			insertionsort(value);

			dst.at<uchar>(a,b) = value[5];




		}
	}

	namedWindow("final image");
	imshow("final image", dst);

	waitKey();
	return 0;
}