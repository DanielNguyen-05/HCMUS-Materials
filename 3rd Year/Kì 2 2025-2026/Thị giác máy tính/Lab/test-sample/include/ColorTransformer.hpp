#include "libs.hpp"
class ColorTransformer
{
public:
    int ChangeBrightness(const cv::Mat &srcImage, cv::Mat &dstImage, int b);
    int ChangeContrast(const cv::Mat &srcImage, cv::Mat &dstImage, int b);
    int RGB2Grayscale(const cv::Mat &srcImage, cv::Mat &dstImage);
    int AvgFilter(const cv::Mat &srcImage, cv::Mat &dstImage);
    ColorTransformer() { std::cout << "abcd" << std::endl; }
    ~ColorTransformer() {}
};
