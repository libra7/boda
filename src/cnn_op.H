#ifndef _CNN_OP_H_
#define _CNN_OP_H_

#include"conv_util.H"
#include"geom_prim.H"

namespace boda 
{

  struct op_tune_t : virtual public nesi // NESI(help="operation tuning parameters")
  {
    virtual cinfo_t const * get_cinfo( void ) const; // required declaration for NESI support
    // shared
    uint32_t use_culibs; //NESI(default=0,help="if 1, set use_culibs=1")

    // sgemm-specific (sort of)
    u32_pt_t MNt; //NESI(default="8:8",help="register blocking, M and N dims: compute Mt*Nt outputs per thread (sgemm+cnn)")
    u32_pt_t MNb;  //NESI(default="8:16",help="thread blocking, M and N dims: use Mb*Nb threads per block")
    uint32_t Kb; //NESI(default=8,help="inner loop unroll factor (for sgemm and k1conv)")
    uint32_t use_local_mem; //NESI(default=1,help="if 1, use local memory for sgemm (affects some cnn ops too, like k1conv)")
    uint32_t prof_variant; //NESI(default=0,help="if nonzero, run special experimental profiling variant")
    uint32_t vw; //NESI(default=8,help="vector width for simd variants")

    // cnn-specific
    //uint32_t opt; //xNESI(default=1,help="if 1, choose optimized variant (cnn operations only)")
    uint32_t k1conv; //NESI(default=0,help="if 1, enable k1conv variant (cnn operations only)")
    uint32_t tconv; //NESI(default=0,help="if 1, enable tconv variant (cnn operations only). if 2, (force-)enable tconv in more cases.")
    u32_pt_t tconv_max_ksz;  //NESI(default="11:11",help="max kernel size to use for tconv")
    uint32_t ipconv; //NESI(default=0,help="if 1, enable ipconv variant (cnn operations only)")
  };
  typedef vector< op_tune_t > vect_op_tune_t; 
  typedef shared_ptr< op_tune_t > p_op_tune_t; 
  typedef vector< p_op_tune_t > vect_p_op_tune_t;
  typedef map< string, op_tune_t > map_str_op_tune_t;


  string const k1conv_str = "k1conv"; 
  string const k1conv_simd_str = "k1conv_simd"; 
  string const tconv_str = "tconv"; 
  string const ipconv_str = "ipconv"; 
  string const conv_str = "conv";
  string const conv_simd_str = "conv_simd";

  inline bool is_k1_or_t_or_reg_conv( string const & cts ) { return (cts==k1conv_str) || (cts==tconv_str) || (cts==conv_str); }

  void add_cnn_codegen_annotations( conv_op_base_t * const op, op_tune_t const & op_tune,
                                    map_str_op_tune_t const *per_op_tune );
  
}

#endif /* _CNN_OP_H_ */
