#include "ColorTransformer.hpp"
int main(int argc, char *argv[])
{
    std::cout << "Hello, World" << std::endl;
    std::cout << argv[0] << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    cv::Mat src = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
    cv::Mat dst;
    ColorTransformer transformer;
    if (transformer.AvgFilter(src, dst) == 0)
    {
        std::cout << "Could not read the image ! " << std::endl;
        return 1;
    }

    // Get a named window
    // cv::namedWindow("Green Color plane");

    // show the green plane (gray image)
    cv::imshow("Src", src);
    cv::imshow("Dst", dst);
    int k = cv::waitKey(0);

    return 0;
}