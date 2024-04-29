#include "readdata.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cassert>

using namespace std;

ReadData::ReadData(const char *pcMean, int nInputWidth, int nInputHeight, int nInputChannel):
			m_nInputWidth(nInputWidth), m_nInputHeight(nInputHeight), m_nInputChannel(nInputChannel)
{
	m_nImageSize = nInputWidth * nInputHeight;
	m_nInputSize = nInputWidth * nInputHeight * nInputChannel;
	m_pfInputData = new float[m_nInputSize];
	m_pfMean = new float[m_nInputSize];
    ReadMean(pcMean);
}

ReadData::~ReadData()
{
	delete[] m_pfInputData;
	delete[] m_pfMean;
}
/*
float *ReadData::ReadInput(const std::vector<std::string>& imageNames)
{
    // Initialize the input data array
    float* inputData = new float[m_nInputSize * imageNames.size()];

    // Loop through each image file name
    for (size_t i = 0; i < imageNames.size(); ++i)
    {
        // Construct the full file path for the image
        std::string fullPath = "../data/images/" + imageNames[i];

        // Load the image
        cv::Mat srcImage = cv::imread(fullPath, cv::IMREAD_UNCHANGED);

        if (srcImage.empty()) {
            std::cerr << "Error loading image: " << fullPath << std::endl;
            exit(EXIT_FAILURE);
        }

        // Resize the image
        cv::Mat dstImage;
        cv::resize(srcImage, dstImage, cv::Size(m_nInputWidth, m_nInputHeight), 0, 0, cv::INTER_LINEAR);

        // Subtract mean from each pixel and store in inputData
        for (int y = 0; y < dstImage.rows; ++y)
        {
            for (int x = 0; x < dstImage.cols; ++x)
            {
                int index = (i * m_nInputSize) + (y * dstImage.cols + x) * 3;
                inputData[index] = static_cast<float>(dstImage.at<cv::Vec3b>(y, x)[0]) - m_pfMean[index];
                inputData[index + 1] = static_cast<float>(dstImage.at<cv::Vec3b>(y, x)[1]) - m_pfMean[index + 1];
                inputData[index + 2] = static_cast<float>(dstImage.at<cv::Vec3b>(y, x)[2]) - m_pfMean[index + 2];
            }
        }
    }

    std::cout << "Reading Pictures Done..." << std::endl;

    return inputData;
}

*/
float *ReadData::ReadInput(const char *pcName)
{
    cout << "Reading Picture: " << pcName << "..." << endl;

    // Construct the full file path for the image
   string strImagePath = "../data/images/";
//string imageName = "img1.jpg"; 
//string imageName2 = "img2.jpg";  // or any other image file name


//string fullPath = strImagePath + imageName;
//string fullPath2 = strImagePath + imageName2;
string fullPath = pcName;
cout << "Full image path: " << fullPath << endl;

// Load the image
cv::Mat srcImage = cv::imread(fullPath, cv::IMREAD_UNCHANGED);

if (srcImage.empty()) {
    cerr << "Error loading image: " << fullPath << endl;
    exit(EXIT_FAILURE);
}

    // Resize the image
    cv::Mat dstImage;
   // cout << "Initializing4..." << endl;
    cv::resize(srcImage, dstImage, cv::Size(m_nInputWidth, m_nInputHeight), 0, 0, cv::INTER_LINEAR);
   // cout << "Initializing5..." << endl;

    // Access image data
    int nStep = dstImage.step;
    int nChannel = dstImage.channels();
  //  cout << "Initializing6..." << endl;
    int nOutputIndex = 0;

    // Subtract mean from each pixel and store in m_pfInputData
    for(int i = 0; i < dstImage.rows; i++)
    {
        for (int j = 0; j < dstImage.cols; j++)
        {
        //cout << "Initializing7..." << endl;
            nOutputIndex = i * m_nInputWidth + j;
            m_pfInputData[nOutputIndex] = (float)dstImage.at<cv::Vec3b>(i, j)[0] - m_pfMean[nOutputIndex];
            m_pfInputData[nOutputIndex + m_nImageSize] = (float)dstImage.at<cv::Vec3b>(i, j)[1] - m_pfMean[nOutputIndex + m_nImageSize];
            m_pfInputData[nOutputIndex + 2 * m_nImageSize] = (float)dstImage.at<cv::Vec3b>(i, j)[2] - m_pfMean[nOutputIndex + 2 * m_nImageSize];
        }
    }

    cout << "Reading Picture Done..." << endl;

    return m_pfInputData;
}
void ReadData::ReadMean(const char *pcMean)
{
    FILE *pM;
    pM = fopen(pcMean, "rb");

    if (pM == NULL) {
        perror("Error opening mean file");
        exit(EXIT_FAILURE);
    }

    int nMsize = m_nInputSize;
    int nMreadsize = fread(m_pfMean, sizeof(float), nMsize, pM);

    if (nMreadsize != nMsize) {
        fprintf(stderr, "Error reading mean file\n");
        exit(EXIT_FAILURE);
    }

    fclose(pM);
}

