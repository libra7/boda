// Copyright (c) 2016, Matthew W. Moskewicz <moskewcz@alumni.princeton.edu>; part of Boda framework; see LICENSE
#ifndef _CULIBS_WRAP_H_
#define _CULIBS_WRAP_H_

#include"boda_base.H"

namespace boda 
{
  struct culibs_wrap_t; typedef shared_ptr< culibs_wrap_t > p_culibs_wrap_t; 

  p_culibs_wrap_t culibs_wrap_init( void );
  void cublas_sgemm_wrap( p_culibs_wrap_t const & cw, uint64_t const & M, uint64_t const & N, uint64_t const & K, vect_rp_void const & args );

}
#endif /* _CULIBS_WRAP_H_ */