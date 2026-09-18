#include "ColorTransformer.hpp"
int ColorTransformer::ChangeBrightness(const cv::Mat &srcImage, cv::Mat &dstImage, int b)
{
    if (srcImage.empty())
        return 0;

    dstImage = srcImage + b;
    return 1;
}

int ColorTransformer::ChangeContrast(const cv::Mat &srcImage, cv::Mat &dstImage, int b)
{
    if (srcImage.empty())
        return 0;

    dstImage = srcImage * b;
    return 1;
}

int ColorTransformer::AvgFilter(const cv::Mat &srcImage, cv::Mat &dstImage)
{
    if (srcImage.empty())
        return 0;

    int height = srcImage.rows;
    int width = srcImage.cols;
    dstImage = cv::Mat(height, width, CV_8UC1);
    int xStart = 1, xEnd = width - 1;
    int yStart = 1, yEnd = height - 1;
    int widthStep = srcImage.step[0];
    uchar *pSrcData = (uchar *)srcImage.data + widthStep + 1;
    uchar *pDstData = (uchar *)dstImage.data + widthStep + 1;
    int offsets[9] = {-widthStep - 1, -widthStep, -widthStep + 1, -1, 0, 1, widthStep - 1, widthStep, widthStep + 1};
    for (int y = yStart; y < yEnd; y++, pSrcData += widthStep, pDstData += widthStep)
    {
        uchar *pSrcRow = pSrcData;
        uchar *pDstRow = pDstData;
        for (int x = xStart; x < xEnd; x++, pSrcRow++, pDstRow++)
        {
            float avg = 0;
            for (int k = 0; k < 9; k++)
                avg += pSrcRow[offsets[k]];
            pDstRow[0] = (uchar)(avg / 9);
        }
    }
    return 1;
}

int ColorTransformer::RGB2Grayscale(const cv::Mat &srcImage, cv::Mat &dstImage)
{
    if (srcImage.empty())
        return 0;

    int height = srcImage.rows;
    int width = srcImage.cols;
    dstImage = cv::Mat(height, width, CV_8UC1);

    int srcWidthStep = srcImage.step[0];
    int dstWidthStep = dstImage.step[0];
    int nSrcChannels = srcImage.step[1];
    int nDstChannels = dstImage.step[1];
    uchar *pSrcData = (uchar *)srcImage.data;
    uchar *pDstData = (uchar *)dstImage.data;
    for (int y = 0; y < height; y++, pSrcData += srcWidthStep, pDstData += dstWidthStep)
    {
        uchar *pSrcRow = pSrcData;
        uchar *pDstRow = pDstData;
        for (int x = 0; x < width; x++, pSrcRow += nSrcChannels, pDstRow += nDstChannels)
        {
            pDstRow[0] = (uchar)((pSrcRow[0] + pSrcRow[1] + pSrcRow[2]) / 3);
        }
    }
    // int nSrcChannels = srcImage.channels();
    // int nDstChannels = dstImage.channels();
    // for (int y = 0; y < height; y++)
    // {
    //     uchar *pSrcRow = (uchar *)srcImage.ptr<uchar>(y);
    //     uchar *pDstRow = (uchar *)dstImage.ptr<uchar>(y);

    //     for (int x = 0; x < width; x++, pSrcRow += nSrcChannels, pDstRow += nDstChannels)
    //     {
    //         pDstRow[0] = (uchar)((pSrcRow[0] + pSrcRow[1] + pSrcRow[2]) / 3);
    //     }
    // }
    return 1;
}