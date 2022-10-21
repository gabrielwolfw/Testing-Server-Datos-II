#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/filesystem.hpp>

#include <opencv2/core.hpp>
#include <boost/serialization/split_free.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

#include <string>
#include <utility>
#include <vector>


using namespace std;
using namespace cv;
int Segment_image(const cv::Mat& img, const int blockWidth, std::vector<cv::Mat>& blocks){
    // Checking if the image was passed correctly
    if (!img.data || img.empty())
    {
        std::cout << "Error al cargar imagen, no es posible empezar la segmentacion" << std::endl;
        return EXIT_FAILURE;
    }

    // Inicializa las dimensiones de la imagen
    int imgWidth = img.cols;
    int imgHeight = img.rows;
    std::cout << "IMAGE SIZE: " << "(" << imgWidth << "," << imgHeight << ")" << std::endl;

    // Inicializa las dimensiones del segmento
    int bwSize;
    int bhSize = img.rows;

    int y0 = 0;
    int x0 = 0;
    while (x0 < imgWidth)
    {
        bwSize = ((x0 + blockWidth) > imgWidth) * (blockWidth - (x0 + blockWidth - imgWidth)) + ((x0 + blockWidth) <= imgWidth) * blockWidth;

        blocks.push_back(img(cv::Rect(x0, y0, bwSize, bhSize)).clone());

        x0 = x0 + blockWidth;

    }
    return EXIT_SUCCESS;
}
