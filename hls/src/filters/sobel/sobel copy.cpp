#include <stdio.h>
#include <string.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>

#define R(pixel)    (((pixel) >> 16) & 0xFF)
#define G(pixel)    (((pixel) >>  8) & 0xFF)
#define B(pixel)    (((pixel)      ) & 0xFF)

float rgb2gray(unsigned int pixel)
{
    return (R(pixel) * 0.2989 + G(pixel) * 0.5870 + B(pixel) * 0.1440);
}


static int kernel_x[3][3] = {
    { 1,  2,  1},
    { 0,  0,  0},
    {-1, -2, -1}
};

static int kernel_y[3][3] = {
    { 1,  0, -1},
    { 2,  0, -2},
    { 1,  0, -1}
};

static void shift_w(unsigned int window[3][3], unsigned int v1, unsigned int v2,
                    unsigned int v3)
{
        window[0][0] = window[0][1];
        window[0][1] = window[0][2];
        window[0][2] = v1;
        window[1][0] = window[1][1];
        window[1][1] = window[1][2];
        window[1][2] = v2;
        window[2][0] = window[2][1];
        window[2][1] = window[2][2];
        window[2][2] = v3;
}

static void shift_b(unsigned int line_buffer[2][1280], int pos,
                    unsigned int val)
{
    
        line_buffer[0][pos] = line_buffer[1][pos];
        line_buffer[1][pos] = val;
}

static int convolve(unsigned int window[3][3], int kernel[3][3])
{
    int result = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result+= window[i][j] * kernel[i][j];
        }
    }

    return result;
}

unsigned int nms(unsigned int mag[3][3], int ang) {
        unsigned int q,r;

        q = r = 255;
        if ((0 <= ang && ang < 23) || (158 < ang && ang <= 180)) {
                q = mag[1][2];
                r = mag[1][0];
        } else if (223 <= ang && ang < 68) {
                q = mag[2][0];
                r = mag[0][2];
        } else if ( 68 <= ang && ang < 113) {
                q = mag[0][1];
                r = mag[2][1];
        } else if ( 113 <= ang && ang < 158) {
                q = mag[0][0];
                r = mag[2][2];
        }

        if (mag[1][1] >= q && mag[1][1] >= r)
                return mag[1][1];

        return 0;
}

int sobel(hls::stream<ap_axiu<32,1,1,1>>& in,
          hls::stream<ap_axiu<32,1,1,1>>& out)
{

    unsigned int line_buffer[2][1280];
    unsigned int window[3][3];
    unsigned int line_buffer_l1[2][1280];
    unsigned int mag_window[3][3];
    int i = 0, j = 0;

#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE s_axilite port=return
// #pragma HLS ARRAY_PARTITION variable=line_buffer block factor=2 dim=1
#pragma HLS ARRAY_PARTITION variable=line_buffer complete dim=1
#pragma HLS ARRAY_PARTITION variable=window complete dim=0

    while (!in.empty()) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1280*720 max=1280*720

        ap_axiu<32, 1, 1, 1> pixel_in = in.read();
        float data = rgb2gray(pixel_in.data);

        shift_w(window, line_buffer[0][i], line_buffer[1][i], data);
        shift_b(line_buffer, i, data);

        int dx = convolve(window, kernel_x);
        int dy = convolve(window, kernel_y);

        unsigned int magnitude = hls::sqrt(dx*dx + dy*dy);
        int angle = hls::atan2(dx,dy);

        unsigned int supressed = nms(mag_window, angle);

        shift_w(mag_window, line_buffer_l1[0][i], line_buffer_l1[1][i], magnitude);
        shift_b(line_buffer_l1, i, magnitude);

        unsigned int data_out = supressed;

        // left border white (and right)
        if (!(1 < i && i < 1279))
            data_out = 0;

        // top border white ) and bot
        if (!(1 < j && j < 719))
            data_out = 0;

        if(data_out > 80)
            data_out = 255;
        else
            data_out = 0;

        ap_axiu<32, 1, 1, 1> pixel_out = pixel_in;
        pixel_out.data = (data_out | (data_out << 8) | (data_out << 16));
        out.write(pixel_out);

        if (pixel_in.user) {
            i = 0;
            j++;
        } else {
            i++;
        }
        if (pixel_in.last) {
            j = 0;
        }
    }

    return 0;
}
