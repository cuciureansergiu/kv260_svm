#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_in_V_data_V "../tv/cdatafile/c.sobel.autotvin_in_V_data_V.dat"
#define AUTOTB_TVOUT_in_V_data_V "../tv/cdatafile/c.sobel.autotvout_in_V_data_V.dat"
#define AUTOTB_TVIN_in_V_keep_V "../tv/cdatafile/c.sobel.autotvin_in_V_keep_V.dat"
#define AUTOTB_TVOUT_in_V_keep_V "../tv/cdatafile/c.sobel.autotvout_in_V_keep_V.dat"
#define AUTOTB_TVIN_in_V_strb_V "../tv/cdatafile/c.sobel.autotvin_in_V_strb_V.dat"
#define AUTOTB_TVOUT_in_V_strb_V "../tv/cdatafile/c.sobel.autotvout_in_V_strb_V.dat"
#define AUTOTB_TVIN_in_V_user_V "../tv/cdatafile/c.sobel.autotvin_in_V_user_V.dat"
#define AUTOTB_TVOUT_in_V_user_V "../tv/cdatafile/c.sobel.autotvout_in_V_user_V.dat"
#define AUTOTB_TVIN_in_V_last_V "../tv/cdatafile/c.sobel.autotvin_in_V_last_V.dat"
#define AUTOTB_TVOUT_in_V_last_V "../tv/cdatafile/c.sobel.autotvout_in_V_last_V.dat"
#define AUTOTB_TVIN_in_V_id_V "../tv/cdatafile/c.sobel.autotvin_in_V_id_V.dat"
#define AUTOTB_TVOUT_in_V_id_V "../tv/cdatafile/c.sobel.autotvout_in_V_id_V.dat"
#define AUTOTB_TVIN_in_V_dest_V "../tv/cdatafile/c.sobel.autotvin_in_V_dest_V.dat"
#define AUTOTB_TVOUT_in_V_dest_V "../tv/cdatafile/c.sobel.autotvout_in_V_dest_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_data_V "../tv/stream_size/stream_size_in_in_V_data_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_data_V "../tv/stream_size/stream_ingress_status_in_V_data_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_keep_V "../tv/stream_size/stream_size_in_in_V_keep_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V "../tv/stream_size/stream_ingress_status_in_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_strb_V "../tv/stream_size/stream_size_in_in_V_strb_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V "../tv/stream_size/stream_ingress_status_in_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_user_V "../tv/stream_size/stream_size_in_in_V_user_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_user_V "../tv/stream_size/stream_ingress_status_in_V_user_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_last_V "../tv/stream_size/stream_size_in_in_V_last_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_last_V "../tv/stream_size/stream_ingress_status_in_V_last_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_id_V "../tv/stream_size/stream_size_in_in_V_id_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_id_V "../tv/stream_size/stream_ingress_status_in_V_id_V.dat"
#define WRAPC_STREAM_SIZE_IN_in_V_dest_V "../tv/stream_size/stream_size_in_in_V_dest_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V "../tv/stream_size/stream_ingress_status_in_V_dest_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_out_V_data_V "../tv/cdatafile/c.sobel.autotvin_out_V_data_V.dat"
#define AUTOTB_TVOUT_out_V_data_V "../tv/cdatafile/c.sobel.autotvout_out_V_data_V.dat"
#define AUTOTB_TVIN_out_V_keep_V "../tv/cdatafile/c.sobel.autotvin_out_V_keep_V.dat"
#define AUTOTB_TVOUT_out_V_keep_V "../tv/cdatafile/c.sobel.autotvout_out_V_keep_V.dat"
#define AUTOTB_TVIN_out_V_strb_V "../tv/cdatafile/c.sobel.autotvin_out_V_strb_V.dat"
#define AUTOTB_TVOUT_out_V_strb_V "../tv/cdatafile/c.sobel.autotvout_out_V_strb_V.dat"
#define AUTOTB_TVIN_out_V_user_V "../tv/cdatafile/c.sobel.autotvin_out_V_user_V.dat"
#define AUTOTB_TVOUT_out_V_user_V "../tv/cdatafile/c.sobel.autotvout_out_V_user_V.dat"
#define AUTOTB_TVIN_out_V_last_V "../tv/cdatafile/c.sobel.autotvin_out_V_last_V.dat"
#define AUTOTB_TVOUT_out_V_last_V "../tv/cdatafile/c.sobel.autotvout_out_V_last_V.dat"
#define AUTOTB_TVIN_out_V_id_V "../tv/cdatafile/c.sobel.autotvin_out_V_id_V.dat"
#define AUTOTB_TVOUT_out_V_id_V "../tv/cdatafile/c.sobel.autotvout_out_V_id_V.dat"
#define AUTOTB_TVIN_out_V_dest_V "../tv/cdatafile/c.sobel.autotvin_out_V_dest_V.dat"
#define AUTOTB_TVOUT_out_V_dest_V "../tv/cdatafile/c.sobel.autotvout_out_V_dest_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_data_V "../tv/stream_size/stream_size_out_out_V_data_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_data_V "../tv/stream_size/stream_egress_status_out_V_data_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_keep_V "../tv/stream_size/stream_size_out_out_V_keep_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_keep_V "../tv/stream_size/stream_egress_status_out_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_strb_V "../tv/stream_size/stream_size_out_out_V_strb_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_strb_V "../tv/stream_size/stream_egress_status_out_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_user_V "../tv/stream_size/stream_size_out_out_V_user_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_user_V "../tv/stream_size/stream_egress_status_out_V_user_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_last_V "../tv/stream_size/stream_size_out_out_V_last_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_last_V "../tv/stream_size/stream_egress_status_out_V_last_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_id_V "../tv/stream_size/stream_size_out_out_V_id_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_id_V "../tv/stream_size/stream_egress_status_out_V_id_V.dat"
#define WRAPC_STREAM_SIZE_OUT_out_V_dest_V "../tv/stream_size/stream_size_out_out_V_dest_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_out_V_dest_V "../tv/stream_size/stream_egress_status_out_V_dest_V.dat"
// wrapc file define:
#define AUTOTB_TVOUT_return "../tv/cdatafile/c.sobel.autotvout_ap_return.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_in_V_data_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_data_V.dat"
#define AUTOTB_TVOUT_PC_in_V_keep_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_in_V_strb_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_in_V_user_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_user_V.dat"
#define AUTOTB_TVOUT_PC_in_V_last_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_last_V.dat"
#define AUTOTB_TVOUT_PC_in_V_id_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_id_V.dat"
#define AUTOTB_TVOUT_PC_in_V_dest_V "../tv/rtldatafile/rtl.sobel.autotvout_in_V_dest_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_out_V_data_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_data_V.dat"
#define AUTOTB_TVOUT_PC_out_V_keep_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_out_V_strb_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_out_V_user_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_user_V.dat"
#define AUTOTB_TVOUT_PC_out_V_last_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_last_V.dat"
#define AUTOTB_TVOUT_PC_out_V_id_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_id_V.dat"
#define AUTOTB_TVOUT_PC_out_V_dest_V "../tv/rtldatafile/rtl.sobel.autotvout_out_V_dest_V.dat"
#define AUTOTB_TVOUT_PC_return "../tv/rtldatafile/rtl.sobel.autotvout_ap_return.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  in_V_data_V_depth = 0;
  in_V_keep_V_depth = 0;
  in_V_strb_V_depth = 0;
  in_V_user_V_depth = 0;
  in_V_last_V_depth = 0;
  in_V_id_V_depth = 0;
  in_V_dest_V_depth = 0;
  out_V_data_V_depth = 0;
  out_V_keep_V_depth = 0;
  out_V_strb_V_depth = 0;
  out_V_user_V_depth = 0;
  out_V_last_V_depth = 0;
  out_V_id_V_depth = 0;
  out_V_dest_V_depth = 0;
  return_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{in_V_data_V " << in_V_data_V_depth << "}\n";
  total_list << "{in_V_keep_V " << in_V_keep_V_depth << "}\n";
  total_list << "{in_V_strb_V " << in_V_strb_V_depth << "}\n";
  total_list << "{in_V_user_V " << in_V_user_V_depth << "}\n";
  total_list << "{in_V_last_V " << in_V_last_V_depth << "}\n";
  total_list << "{in_V_id_V " << in_V_id_V_depth << "}\n";
  total_list << "{in_V_dest_V " << in_V_dest_V_depth << "}\n";
  total_list << "{out_V_data_V " << out_V_data_V_depth << "}\n";
  total_list << "{out_V_keep_V " << out_V_keep_V_depth << "}\n";
  total_list << "{out_V_strb_V " << out_V_strb_V_depth << "}\n";
  total_list << "{out_V_user_V " << out_V_user_V_depth << "}\n";
  total_list << "{out_V_last_V " << out_V_last_V_depth << "}\n";
  total_list << "{out_V_id_V " << out_V_id_V_depth << "}\n";
  total_list << "{out_V_dest_V " << out_V_dest_V_depth << "}\n";
  total_list << "{ap_return " << return_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int in_V_data_V_depth;
    int in_V_keep_V_depth;
    int in_V_strb_V_depth;
    int in_V_user_V_depth;
    int in_V_last_V_depth;
    int in_V_id_V_depth;
    int in_V_dest_V_depth;
    int out_V_data_V_depth;
    int out_V_keep_V_depth;
    int out_V_strb_V_depth;
    int out_V_user_V_depth;
    int out_V_last_V_depth;
    int out_V_id_V_depth;
    int out_V_dest_V_depth;
    int return_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
extern "C" int sobel_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" int apatb_sobel_hw(volatile void * __xlx_apatb_param_in_V_data_V, volatile void * __xlx_apatb_param_in_V_keep_V, volatile void * __xlx_apatb_param_in_V_strb_V, volatile void * __xlx_apatb_param_in_V_user_V, volatile void * __xlx_apatb_param_in_V_last_V, volatile void * __xlx_apatb_param_in_V_id_V, volatile void * __xlx_apatb_param_in_V_dest_V, volatile void * __xlx_apatb_param_out_V_data_V, volatile void * __xlx_apatb_param_out_V_keep_V, volatile void * __xlx_apatb_param_out_V_strb_V, volatile void * __xlx_apatb_param_out_V_user_V, volatile void * __xlx_apatb_param_out_V_last_V, volatile void * __xlx_apatb_param_out_V_id_V, volatile void * __xlx_apatb_param_out_V_dest_V) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
    int AESL_return;
    {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_return);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > return_pc_buffer(1);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "return");
  
            // push token into output port buffer
            if (AESL_token != "") {
              return_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {((char*)&AESL_return)[0*4+0] = return_pc_buffer[0].range(7, 0).to_int64();
((char*)&AESL_return)[0*4+1] = return_pc_buffer[0].range(15, 8).to_int64();
((char*)&AESL_return)[0*4+2] = return_pc_buffer[0].range(23, 16).to_int64();
((char*)&AESL_return)[0*4+3] = return_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  long __xlx_apatb_param_in_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_in_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_in_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_in_stream_buf_final_size; ++i) {
((hls::stream<int>*)__xlx_apatb_param_in_V_data_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_V_keep_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_V_strb_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_V_user_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_V_last_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_V_id_V)->read();
((hls::stream<char>*)__xlx_apatb_param_in_V_dest_V)->read();
}
{unsigned xlx_stream_out_size = 0;

          std::vector<sc_bv<32> > out_V_data_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_data_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_data_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_data_V_pc_buffer.size();
out_V_data_V_pc_buffer_Copy=out_V_data_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_V_keep_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_keep_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_keep_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_keep_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_keep_V_pc_buffer.size();
out_V_keep_V_pc_buffer_Copy=out_V_keep_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_V_strb_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_strb_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_strb_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_strb_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_strb_V_pc_buffer.size();
out_V_strb_V_pc_buffer_Copy=out_V_strb_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_V_user_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_user_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_user_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_user_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_user_V_pc_buffer.size();
out_V_user_V_pc_buffer_Copy=out_V_user_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_V_last_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_last_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_last_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_last_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_last_V_pc_buffer.size();
out_V_last_V_pc_buffer_Copy=out_V_last_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_V_id_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_id_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_id_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_id_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_id_V_pc_buffer.size();
out_V_id_V_pc_buffer_Copy=out_V_id_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<32> > out_V_dest_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_out_V_dest_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > out_V_dest_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              out_V_dest_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_out_size=out_V_dest_V_pc_buffer.size();
out_V_dest_V_pc_buffer_Copy=out_V_dest_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (int j = 0, e = xlx_stream_out_size; j != e; ++j) {
int xlx_stream_elt_data;
((int*)&xlx_stream_elt_data)[0] = out_V_data_V_pc_buffer_Copy[j].to_int64();
((hls::stream<int>*)__xlx_apatb_param_out_V_data_V)->write(xlx_stream_elt_data);
char xlx_stream_elt_keep;
((char*)&xlx_stream_elt_keep)[0] = out_V_keep_V_pc_buffer_Copy[j].to_int64();
((hls::stream<char>*)__xlx_apatb_param_out_V_keep_V)->write(xlx_stream_elt_keep);
char xlx_stream_elt_strb;
((char*)&xlx_stream_elt_strb)[0] = out_V_strb_V_pc_buffer_Copy[j].to_int64();
((hls::stream<char>*)__xlx_apatb_param_out_V_strb_V)->write(xlx_stream_elt_strb);
char xlx_stream_elt_user;
((char*)&xlx_stream_elt_user)[0] = out_V_user_V_pc_buffer_Copy[j].to_uint64();
((hls::stream<char>*)__xlx_apatb_param_out_V_user_V)->write(xlx_stream_elt_user);
char xlx_stream_elt_last;
((char*)&xlx_stream_elt_last)[0] = out_V_last_V_pc_buffer_Copy[j].to_uint64();
((hls::stream<char>*)__xlx_apatb_param_out_V_last_V)->write(xlx_stream_elt_last);
char xlx_stream_elt_id;
((char*)&xlx_stream_elt_id)[0] = out_V_id_V_pc_buffer_Copy[j].to_uint64();
((hls::stream<char>*)__xlx_apatb_param_out_V_id_V)->write(xlx_stream_elt_id);
char xlx_stream_elt_dest;
((char*)&xlx_stream_elt_dest)[0] = out_V_dest_V_pc_buffer_Copy[j].to_uint64();
((hls::stream<char>*)__xlx_apatb_param_out_V_dest_V)->write(xlx_stream_elt_dest);
}}
    AESL_transaction_pc++;
    return  AESL_return;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//in
aesl_fh.touch(AUTOTB_TVIN_in_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_in_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_in_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_in_V_user_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_user_V);
aesl_fh.touch(AUTOTB_TVIN_in_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_last_V);
aesl_fh.touch(AUTOTB_TVIN_in_V_id_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_id_V);
aesl_fh.touch(AUTOTB_TVIN_in_V_dest_V);
aesl_fh.touch(AUTOTB_TVOUT_in_V_dest_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_data_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_user_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_user_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_last_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_id_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_id_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_in_V_dest_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V);
//out
aesl_fh.touch(AUTOTB_TVIN_out_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_out_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_out_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_out_V_user_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_user_V);
aesl_fh.touch(AUTOTB_TVIN_out_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_last_V);
aesl_fh.touch(AUTOTB_TVIN_out_V_id_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_id_V);
aesl_fh.touch(AUTOTB_TVIN_out_V_dest_V);
aesl_fh.touch(AUTOTB_TVOUT_out_V_dest_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_data_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_user_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_user_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_last_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_id_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_id_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_out_V_dest_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_out_V_dest_V);
CodeState = DUMP_INPUTS;
// data
std::vector<int> __xlx_apatb_param_in_V_data_V_stream_buf;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_in_V_data_V)->empty())
    __xlx_apatb_param_in_V_data_V_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_in_V_data_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_data_V_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_in_V_data_V)->write(__xlx_apatb_param_in_V_data_V_stream_buf[i]);
  }
long __xlx_apatb_param_in_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_in_V_data_V)->size();
// keep
std::vector<char> __xlx_apatb_param_in_V_keep_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_V_keep_V)->empty())
    __xlx_apatb_param_in_V_keep_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_V_keep_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_keep_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_V_keep_V)->write(__xlx_apatb_param_in_V_keep_V_stream_buf[i]);
  }
// strb
std::vector<char> __xlx_apatb_param_in_V_strb_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_V_strb_V)->empty())
    __xlx_apatb_param_in_V_strb_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_V_strb_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_strb_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_V_strb_V)->write(__xlx_apatb_param_in_V_strb_V_stream_buf[i]);
  }
// user
std::vector<char> __xlx_apatb_param_in_V_user_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_V_user_V)->empty())
    __xlx_apatb_param_in_V_user_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_V_user_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_user_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_V_user_V)->write(__xlx_apatb_param_in_V_user_V_stream_buf[i]);
  }
// last
std::vector<char> __xlx_apatb_param_in_V_last_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_V_last_V)->empty())
    __xlx_apatb_param_in_V_last_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_V_last_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_last_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_V_last_V)->write(__xlx_apatb_param_in_V_last_V_stream_buf[i]);
  }
// id
std::vector<char> __xlx_apatb_param_in_V_id_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_V_id_V)->empty())
    __xlx_apatb_param_in_V_id_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_V_id_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_id_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_V_id_V)->write(__xlx_apatb_param_in_V_id_V_stream_buf[i]);
  }
// dest
std::vector<char> __xlx_apatb_param_in_V_dest_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_in_V_dest_V)->empty())
    __xlx_apatb_param_in_V_dest_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_in_V_dest_V)->read());
  for (int i = 0; i < __xlx_apatb_param_in_V_dest_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_in_V_dest_V)->write(__xlx_apatb_param_in_V_dest_V_stream_buf[i]);
  }
// data
std::vector<int> __xlx_apatb_param_out_V_data_V_stream_buf;
long __xlx_apatb_param_out_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_out_V_data_V)->size();
// keep
std::vector<char> __xlx_apatb_param_out_V_keep_V_stream_buf;
// strb
std::vector<char> __xlx_apatb_param_out_V_strb_V_stream_buf;
// user
std::vector<char> __xlx_apatb_param_out_V_user_V_stream_buf;
// last
std::vector<char> __xlx_apatb_param_out_V_last_V_stream_buf;
// id
std::vector<char> __xlx_apatb_param_out_V_id_V_stream_buf;
// dest
std::vector<char> __xlx_apatb_param_out_V_dest_V_stream_buf;
CodeState = CALL_C_DUT;
int ap_return = sobel_hw_stub_wrapper(__xlx_apatb_param_in_V_data_V, __xlx_apatb_param_in_V_keep_V, __xlx_apatb_param_in_V_strb_V, __xlx_apatb_param_in_V_user_V, __xlx_apatb_param_in_V_last_V, __xlx_apatb_param_in_V_id_V, __xlx_apatb_param_in_V_dest_V, __xlx_apatb_param_out_V_data_V, __xlx_apatb_param_out_V_keep_V, __xlx_apatb_param_out_V_strb_V, __xlx_apatb_param_out_V_user_V, __xlx_apatb_param_out_V_last_V, __xlx_apatb_param_out_V_id_V, __xlx_apatb_param_out_V_dest_V);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_in_stream_buf_final_size = __xlx_apatb_param_in_stream_buf_size - ((hls::stream<int>*)__xlx_apatb_param_in_V_data_V)->size();

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_user_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_last_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_id_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in_V_dest_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_0_lv = ((int*)&__xlx_apatb_param_in_V_data_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_1_lv = ((char*)&__xlx_apatb_param_in_V_keep_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_2_lv = ((char*)&__xlx_apatb_param_in_V_strb_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_3_lv = ((char*)&__xlx_apatb_param_in_V_user_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_3_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_user_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_4_lv = ((char*)&__xlx_apatb_param_in_V_last_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_last_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_5_lv = ((char*)&__xlx_apatb_param_in_V_id_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_5_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_id_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_6_lv = ((char*)&__xlx_apatb_param_in_V_dest_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_6_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_in_V_dest_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_user_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_user_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_last_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_id_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_id_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_in_stream_buf_final_size, &tcl_file.in_V_dest_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in_V_dest_V, __xlx_sprintf_buffer.data());

// dump stream ingress status to file

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_data_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_data_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_data_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_data_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_data_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_data_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_data_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_data_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_keep_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_keep_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_keep_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_keep_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_strb_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_strb_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_strb_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_strb_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_user_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_user_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_user_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_user_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_user_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_user_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_user_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_user_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_user_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_user_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_user_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_last_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_last_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_last_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_last_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_last_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_last_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_last_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_id_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_id_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_id_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_id_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_id_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_id_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_id_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_id_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_id_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_id_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_id_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_in_stream_buf_final_size > 0) {
  long in_V_dest_V_stream_ingress_size = __xlx_apatb_param_in_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_dest_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_in_stream_buf_final_size; j != e; j++) {
    in_V_dest_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_dest_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V, __xlx_sprintf_buffer.data());
  }
} else {
  long in_V_dest_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", in_V_dest_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_in_V_dest_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_user_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_user_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_user_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_last_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_id_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_id_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_id_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_dest_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_in_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_dest_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_in_V_dest_V, __xlx_sprintf_buffer.data());
}
//********************** dump C output stream *******************
long __xlx_apatb_param_out_stream_buf_final_size = ((hls::stream<int>*)__xlx_apatb_param_out_V_data_V)->size() - __xlx_apatb_param_out_stream_buf_size;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_out_V_data_V)->empty())
    __xlx_apatb_param_out_V_data_V_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_out_V_data_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_data_V_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_out_V_data_V)->write(__xlx_apatb_param_out_V_data_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_V_keep_V)->empty())
    __xlx_apatb_param_out_V_keep_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_V_keep_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_keep_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_V_keep_V)->write(__xlx_apatb_param_out_V_keep_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_V_strb_V)->empty())
    __xlx_apatb_param_out_V_strb_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_V_strb_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_strb_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_V_strb_V)->write(__xlx_apatb_param_out_V_strb_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_V_user_V)->empty())
    __xlx_apatb_param_out_V_user_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_V_user_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_user_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_V_user_V)->write(__xlx_apatb_param_out_V_user_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_V_last_V)->empty())
    __xlx_apatb_param_out_V_last_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_V_last_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_last_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_V_last_V)->write(__xlx_apatb_param_out_V_last_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_V_id_V)->empty())
    __xlx_apatb_param_out_V_id_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_V_id_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_id_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_V_id_V)->write(__xlx_apatb_param_out_V_id_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_out_V_dest_V)->empty())
    __xlx_apatb_param_out_V_dest_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_out_V_dest_V)->read());
  for (int i = 0; i < __xlx_apatb_param_out_V_dest_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_out_V_dest_V)->write(__xlx_apatb_param_out_V_dest_V_stream_buf[i]);
  }

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_user_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_last_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_id_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_out_V_dest_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_out_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_0_lv = ((int*)&__xlx_apatb_param_out_V_data_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_1_lv = ((char*)&__xlx_apatb_param_out_V_keep_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<4> __xlx_tmp_2_lv = ((char*)&__xlx_apatb_param_out_V_strb_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_3_lv = ((char*)&__xlx_apatb_param_out_V_user_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_3_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_user_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_4_lv = ((char*)&__xlx_apatb_param_out_V_last_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_last_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_5_lv = ((char*)&__xlx_apatb_param_out_V_id_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_5_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_id_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_6_lv = ((char*)&__xlx_apatb_param_out_V_dest_V_stream_buf[__xlx_apatb_param_out_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_6_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_out_V_dest_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_user_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_user_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_last_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_id_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_id_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_out_stream_buf_final_size, &tcl_file.out_V_dest_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_out_V_dest_V, __xlx_sprintf_buffer.data());
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_user_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_user_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_user_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_last_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_id_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_id_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_id_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_dest_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_dest_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_out_V_dest_V, __xlx_sprintf_buffer.data());
}// print return Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data());
  sc_bv<32> __xlx_tmp_lv = ((int*)&ap_return)[0];

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVOUT_return, s.append("\n")); 
  
  tcl_file.set_num(1, &tcl_file.return_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
return ap_return;
}
