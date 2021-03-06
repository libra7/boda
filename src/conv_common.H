#ifndef _CONV_COMMON_H_
#define _CONV_COMMON_H_

#include"geom_prim.H"

namespace boda 
{
  struct conv_support_info_t {  
    u32_pt_t support_sz;
    u32_pt_t support_stride;
    u32_pt_t eff_tot_pad;
    bool valid( void ) const { return support_stride != u32_pt_t{}; }
    void init_as_source( void ) { assert_st( !valid() ); support_sz = u32_pt_t(1,1); support_stride = u32_pt_t(1,1); }
  };

  typedef vector< conv_support_info_t > vect_conv_support_info_t; 
  typedef shared_ptr< conv_support_info_t > p_conv_support_info_t; 
  typedef vector< p_conv_support_info_t > vect_p_conv_support_info_t;

  // struct metadata about inputs/outputs of conv ops
  struct conv_io_t {
    u32_pt_t used_sz; // used only for dump_ios() diagnostic prints about size mismatches / truncations between operations
    uint32_t max_val; // used only for error-checking/testing on label inputs; each single value for this node must be < this value.
    conv_io_t( void ) : max_val(0) {}
  };
  
  typedef vector< conv_io_t > vect_conv_io_t; 
  typedef shared_ptr< conv_io_t > p_conv_io_t; 
  typedef vector< p_conv_io_t > vect_p_conv_io_t;
  typedef shared_ptr< vect_conv_io_t > p_vect_conv_io_t; 

  // note: see conv_common.cc for details on the semantics of these functions
  enum conv_mode_t : uint8_t { cm_valid = 0, cm_any_valid = 1, cm_core_valid = 2 };
  void in_box_to_out_box( i32_box_t & out_box, u32_box_t const & in_box, conv_mode_t const mode, 
			  conv_support_info_t const & csi );
  void unchecked_out_box_to_in_box( i32_box_t & in_box, i32_box_t const & out_box, conv_mode_t const mode, 
				    conv_support_info_t const & csi ); 
  void unchecked_out_box_to_in_boxes( i32_box_t & valid_in_box, i32_box_t & core_valid_in_box, 
				      i32_box_t const & out_box, conv_support_info_t const & csi,
				      u32_pt_t const & full_in_sz );

}
#endif /* _CONV_COMMON_H_ */
