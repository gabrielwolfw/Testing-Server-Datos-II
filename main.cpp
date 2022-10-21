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

class applySegmenting{
public:
    bool get_SegmentImage_(funciones& funcion1,onst Mat& img,const int blockWidth, vector<cv::Mat>& blocks){
        if(!(img.empty())){
            funcion1.segmentImage_(img,blockWidth,blocks);
            return true;
        }else{
            return false;
        }
    }
};


//Crear un TEST para el mockObject "mockSegmentingImg"
class MockSegmentingImg: public funciones{
public:
    MOCK_METHOD(bool,segmentImage_,(const Mat& img,const int blockWidth, vector<cv::Mat>& blocks));
};




TEST(PruebaSegmentar,Prueba1){
    vector<Mat> blocks;
    MockSegmentingImg mockSegmentingImg;
    applySegmenting segmentImg;
    EXPECT_TRUE(segmentImg.get_SegmentImage_(mockSegmentingImg,image,65,blocks));
}



/**
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

