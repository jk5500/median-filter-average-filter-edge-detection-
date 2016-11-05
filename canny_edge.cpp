#include"iostream"
#include"opencv2\imgproc\imgproc.hpp"
#include"opencv2\highgui\highgui.hpp"

using namespace std;
using namespace cv;

int main() {

	Mat image, newimage,newimage1;

	image = imread("C:\\Users\\kamal\\Documents\\Visual Studio 2015\\Projects\\canny_edge_detection\\data\\lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	namedWindow("original image");
	imshow("original image", image);

	GaussianBlur(image, newimage, Size(7, 7), 0, 0);

	namedWindow("blurred image");
	imshow("blurred image", newimage);
	int ratio = 2;
	int lowerthreshold = 20;
	Canny(newimage, newimage1, lowerthreshold, lowerthreshold*ratio, 3);
	//reject a edge if it falls below the lowerthreshold
	//accept a edge if it falls above the upper threshold
	// if a edge falls in between two, then it accep those edges if they are connected to the edges with higher 
	//threshold value
	namedWindow("canny edge image");
	imshow("canny edge image", newimage1);

	waitKey();
	return 0;
}