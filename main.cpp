#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "server.cpp"


using namespace std;


cons Mat image = imread("stitchTry.png",IMREAD_COLOR);

//clase funciones: contiene los metodos usados en el server
class funciones{
public:
    bool segmentImage_(const Mat& img,const int blockWidth, vector<cv::Mat>& blocks){
        int segmentImg = Segment_image(img, blockWidth,blocks);
    }
};


class mockSegmentingImg: public funciones{
public:
    MOCK_METHOD(bool,segmentImage_,(const Mat& img,const int blockWidth, vector<cv::Mat>& blocks));
};


//Crear un TEST para el mockObject "mockSegmentingImg"

/**
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

