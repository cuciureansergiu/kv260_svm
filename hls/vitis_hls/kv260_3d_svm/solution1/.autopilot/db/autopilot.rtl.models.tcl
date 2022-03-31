set SynModuleInfo {
  {SRCNAME {sqrt_fixed<32, 32>} MODELNAME sqrt_fixed_32_32_s RTLNAME sobel_sqrt_fixed_32_32_s}
  {SRCNAME sobel MODELNAME sobel RTLNAME sobel IS_TOP 1
    SUBMODULES {
      {MODELNAME sobel_fptrunc_64ns_32_2_no_dsp_1 RTLNAME sobel_fptrunc_64ns_32_2_no_dsp_1 BINDTYPE op TYPE fptrunc IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME sobel_dadd_64ns_64ns_64_5_full_dsp_1 RTLNAME sobel_dadd_64ns_64ns_64_5_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME sobel_dmul_64ns_64ns_64_5_max_dsp_1 RTLNAME sobel_dmul_64ns_64ns_64_5_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME sobel_uitodp_32ns_64_4_no_dsp_1 RTLNAME sobel_uitodp_32ns_64_4_no_dsp_1 BINDTYPE op TYPE uitodp IMPL auto LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME sobel_mul_32s_32s_32_1_1 RTLNAME sobel_mul_32s_32s_32_1_1 BINDTYPE op TYPE mul IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
      {MODELNAME sobel_line_buffer_0 RTLNAME sobel_line_buffer_0 BINDTYPE storage TYPE ram_2p IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME sobel_line_buffer_l1_1 RTLNAME sobel_line_buffer_l1_1 BINDTYPE storage TYPE ram_2p IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME sobel_control_s_axi RTLNAME sobel_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME sobel_regslice_both RTLNAME sobel_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME sobel_regslice_both_U}
      {MODELNAME sobel_flow_control_loop_pipe RTLNAME sobel_flow_control_loop_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME sobel_flow_control_loop_pipe_U}
    }
  }
}
