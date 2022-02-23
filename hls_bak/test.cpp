#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define HEIGHT 720
#define WIDTH 1280

//template<int D,int U,int TI,int TD>
//  struct ap_axiu{
//    ap_uint<D>       data;
//    ap_uint<(D+7)/8> keep;
//    ap_uint<(D+7)/8> strb;
//    ap_uint<U>       user;
//    ap_uint<1>       last;
//    ap_uint<TI>      id;
//    ap_uint<TD>      dest;
//  };

typedef ap_axiu<24, 1, 1, 1> axi_stream;

typedef hls::stream<axi_stream> pixel_stream;

#define WINDOW_SIZE 3

void convolve(int window[WINDOW_SIZE][WINDOW_SIZE],
			  int kernel[WINDOW_SIZE][WINDOW_SIZE])
{
	const int a =2


}


void example(pixel_stream &in, pixel_stream &out)
{
#pragma HLS INTERFACE mode=axis port=A
#pragma HLS INTERFACE mode=axis port=B
	pixel p;
    in.read(p);
    p.data += 5;
    out.write(p);
}


#define HEIGHT 720
#define WIDTH 1280

#define WIN_SIZE 3 // must be odd
#define HALF_SIZE (((WIN_SIZE) - 1) / 2)

inline bool bounds_ok(int y, int x)
{
  return (0 <= y && y < HEIGHT && 0 <= x && x < WIDTH);
}

// Defines the actual calculation for one output value.
inline int single_operation(int window[3][3], int y, int x)
{
  int result = 0;
  win_i : for (int i = -HALF_SIZE; i <= HALF_SIZE; i++)
    win_j : for (int j = -HALF_SIZE; j <= HALF_SIZE; j++)
      if (bounds_ok(y + i, x + j))
        result += window[i + HALF_SIZE][j + HALF_SIZE] * (i + j);
  return result;
}

// A simple implementation of a 2D filter.
void my_filter_v1(int data_out[HEIGHT][WIDTH],
                  const int data_in[HEIGHT][WIDTH])
{
  int window[WIN_SIZE][WIN_SIZE];
#pragma HLS ARRAY_PARTITION variable=window complete

  for_y : for (int y = 0; y < HEIGHT; y++)
  {
    for_x : for (int x = 0; x < WIDTH; x++)
    {
#pragma HLS PIPELINE

      // Load window
      load_i : for (int i = -HALF_SIZE; i <= HALF_SIZE; i++)
        load_j : for (int j = -HALF_SIZE; j <= HALF_SIZE; j++)
          if (bounds_ok(y + i, x + j))
            window[i + HALF_SIZE][j + HALF_SIZE] = data_in[y + i][x + j];

      // Calculate output value
      int val_out = single_operation(window, y, x);
      data_out[y][x] = val_out;
    }
  }
}









void rgb2gray(hls_stream &in_stream, hls_stream &out_stream)
{
#pragma HLS INTERFACE mode=axis port=in_stream
#pragma HLS INTERFACE mode=axis port=out_stream
  unsigned char r,g,b,gray;
  axi_stream pixel;
  in_stream.read(pixel);
  r = pixel.data & 0xFF;
  g = (pixel.data >> 8) & 0xFF;
  b = (pixel.data >> 16) & 0xFF;
  gray = (0.299 * r) + (0.587 * g) + (0.114 * b);
  pixel.data = gray | ((unsigned int) gray << 8 ) | ((unsigned int) gray << 16 );
  out_stream.write(pixel);
}
