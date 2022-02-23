#include <stdint.h>

#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include <xf_video_core.hpp>
#include <xf_video_types.hpp>


#define WIDTH     1280
#define HEIGHT    720
#define KSIZE     3

// struct uint24_t{
//     uint32_t data : 24;
// };

using namespace cv;

// uint8_t kernel[KSIZE][KSIZE];

typedef ap_axiu<24, 1, 1, 1> axis;
typedef cv::Mat<HEIGHT, WIDTH, 3> rgb_img_t;

void rgb2gray(hls::stream<axis> &src, hls::stream<axis> &dst)
{
#pragma HLS INTERFACE mode=axis port=src
#pragma HLS INTERFACE mode=axis port=dst
#pragma HLS dataflow
	int const rows = HEIGHT;
	int const cols = WIDTH;

	rgb_img_t img0(rows, cols);
	rgb_img_t img1(rows, cols);

	cv::AXIvideo2Mat(src, img0);
	cv::CvtColor<HLS_RGB2GRAY>(img0, img1);
	cv::Mat2AXIvideo(img1, dst);
}
