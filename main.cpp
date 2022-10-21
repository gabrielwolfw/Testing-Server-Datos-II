#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "serverMethods.cpp"


using namespace std;


const Mat image = imread("/home/gabrielwolf/Documents/Extraclase-II/Testing-Server-Datos-II/stitchTry.png",IMREAD_COLOR);


//clase funciones: contiene los metodos usados en el server
class funciones{
public:
    bool segmentImage_(const Mat& img,const int blockWidth, vector<cv::Mat>& blocks){
        Segment_image(img, blockWidth, blocks);
        return 1;
    }
};

class applySegmenting{
public:
    bool get_SegmentImage_(funciones& funcion1,const Mat& img,const int blockWidth, vector<cv::Mat>& blocks){
        if(!(image.empty())){
            funcion1.segmentImage_(img,blockWidth,blocks);
            return true;
        }else{
            return false;
        }
    }
};
class applyFilters{
public:
    bool get_gray_scale(ImageProcessing& funcion2){
        if(!(image.empty())){
            funcion2.gray_scale();
            return true;
        }else{
            return false;
        }
    }
};

class applyFilters2{
public:
    bool get_gaussian_blur(ImageProcessing& funcion3){
        if(!(image.empty())){
            funcion3.gaussian_blur();
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

class MockFilterGray: public ImageProcessing{
public:
    MOCK_METHOD(bool,gray_scale,(Mat *_source, Mat *_destiny));
};

class MockFilterGaussian: public ImageProcessing{
public:
    MOCK_METHOD(bool,gaussian_blur,(Mat *_source, Mat *_destiny));
};

TEST(PruebaSegmentar,Prueba1){
    vector<Mat> blocks;
    MockSegmentingImg mockSegmentingImg;
    applySegmenting Segment_image;
    EXPECT_TRUE(Segment_image.get_SegmentImage_(mockSegmentingImg,image,65,blocks));
}

TEST(PruebaFiltroGray,Prueba2){
    vector<Mat> blocksGray;
    MockFilterGray mockFilterGray;
    applyFilters grayImg;
    EXPECT_TRUE(grayImg.get_gray_scale(mockFilterGray));
}

TEST(PruebaFiltroGaussian,Prueba3){
    vector<Mat> blocksGaussian;
    MockFilterGaussian mockFilterGaussian;
    applyFilters2 gaussianImg;
    EXPECT_TRUE(gaussianImg.get_gaussian_blur(mockFilterGaussian));
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

