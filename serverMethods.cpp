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

class ImageProcessing{
private: //atributes
    int width;
    int height;
    int delta_bright;
    float gamma;
    Mat *source;
    Mat *destiny;
public:
    ImageProcessing(int, int, int, float, Mat*, Mat*);

    ImageProcessing();

    //constructor
    int gaussian_blur();
    int gray_scale();
    int bright_control();
    int gamma_correction();
};
//constructor
ImageProcessing::ImageProcessing(int _witdh, int _height, int _delta_bright, float _gamma, Mat *_source, Mat *_destiny) {
    width = _witdh;
    height = _height;
    delta_bright = _delta_bright;
    gamma = _gamma;
    source = _source;
    destiny = _destiny;
}
int ImageProcessing::gaussian_blur() {
    if (source->empty()){
        return -1;
    }else{
        GaussianBlur(*source, *destiny , Size(3, 3), 0);
        return 0;
    }
}
int ImageProcessing::gray_scale() {
    if (source->empty()){
        return -1;
    }else{
        cvtColor(*source, *destiny, COLOR_BGR2GRAY);
        return 0;
    }
}
int ImageProcessing::bright_control() {
    if (source->empty()){
        return -1;
    }else{
        source->convertTo(*destiny, -1, 1, delta_bright);
        return 0;
    }
}
int ImageProcessing::gamma_correction() {
    if (source->empty()){
        return -1;
    }else{
        float invGamma = 1 / gamma;
        Mat table(1, 256, CV_8U);
        uchar *p = table.ptr();
        for (int i = 0; i < 256; ++i) {
            p[i] = (uchar) (pow(i / 255.0, invGamma) * 255);
        }
        LUT(*source, table, *destiny);
        return 0;
    }
}

ImageProcessing::ImageProcessing() {}


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
