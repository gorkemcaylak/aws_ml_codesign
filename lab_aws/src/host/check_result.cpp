//=========================================================================
// cordic_test.cpp
//=========================================================================
// @brief: A C++ test bench (TB) for validating the sine & cosine functions
//         implemented using CORDIC.
/* @desc: 
   1. This TB generates angles between [1, NUM_DEGREE).
   2. It calculates the difference (or errors) between the results from
      CORDIC-based sin/cos with those from standard math library in <math.h>.
   3. All results are logged in the file out.dat for debugging purposes.
   4. The final cumulative errors are printed.
*/

#include <math.h>
#include "cordic.h"
#include <iostream>
#include <fstream>

//--------------------------------------
// Compute absolute value of a double
//--------------------------------------
double abs_double(double var)
{
    return ( var < 0 ) ? -var : var;
}

//--------------------------------------
// Compute absolute value of a double
//--------------------------------------
double RMSE(double total_error)
{
    return sqrt( total_error / (NUM_DEGREE - 1) );
}

//--------------------------------------
// main function of TB
//--------------------------------------
void check_results(cos_sin_type *s,cos_sin_type *c)
{   
    // radian input
    double radian; 
    // sin & cos calculated by math.h
    double m_s = 0.0, m_c = 0.0; 

    // Error terms
    double err_ratio_sin = 0.0;
    double err_ratio_cos = 0.0;
    double accum_err_sin = 0.0;
    double accum_err_cos = 0.0;

    // Output file stream
    std::ofstream fp;
    fp.open ("out.dat");
   
    //------------------------------------------------------------ 
    // Compute sin & cos values for angles up to (NUM_DEGREE - 1)
    //------------------------------------------------------------ 
    for (int i = 1; i < NUM_DEGREE; i++) {
        // Convert to radian
        radian = i * M_PI / 180;
        
        // Call math lib
        m_s = sin( radian );
        m_c = cos( radian );
        
        // Fixed point to double
        #ifdef FIXED_TYPE
          
          // Calculate normalized error
          err_ratio_sin = ( abs_double( s[i-1].to_double() - m_s) / (m_s) ) * 100.0;
          err_ratio_cos = ( abs_double( c[i-1].to_double() - m_c) / (m_c) ) * 100.0;

          // Accumulate error ratios
          accum_err_sin += err_ratio_sin * err_ratio_sin;
          accum_err_cos += err_ratio_cos * err_ratio_cos;

          // Print to output file
          fp << "fixed_degree = " << i << " radian = " << (double)radian << " "
             << "sin = " << s[i-1].to_double() << " : " << m_s << " "
             << "cos = " << c[i-1].to_double() << " : " << m_c << " "
             << "sin_error = " << err_ratio_sin << " "
             << "cos_error = " << err_ratio_cos << " "
             << "\n";
        #else 

          // Calculate normalized error
          err_ratio_sin = ( abs_double( (double)s[i-1] - m_s) / (m_s) ) * 100.0;
          err_ratio_cos = ( abs_double( (double)c[i-1] - m_c) / (m_c) ) * 100.0;
        
          // Accumulate error ratios
          accum_err_sin += err_ratio_sin * err_ratio_sin;
          accum_err_cos += err_ratio_cos * err_ratio_cos;

          // Print to output file
          fp << "double_degree = " << i << " radian = " << (double)radian << " "
             << "sin = " << (double)s[i-1] << " : " << m_s << " "           
             << "cos = " << (double)c[i-1] << " : " << m_c << " "
             << "sin_error = " << err_ratio_sin << " "
             << "cos_error = " << err_ratio_cos << " "
             << "\n";
        #endif
    }

    //------------------------------------------------------------ 
    // Write out root mean squared error (RMSE) of error ratios
    //------------------------------------------------------------ 
    // Print to file
    fp << "#------------------------------------------------\n"
       << "Overall_Error_Sin = " << RMSE(accum_err_sin) << "\n"
       << "Overall_Error_Cos = " << RMSE(accum_err_cos) << "\n"
       << "#------------------------------------------------\n";    
    // Print to screen
    std::cout << "#------------------------------------------------\n"
              << "Overall_Error_Sin = " << RMSE(accum_err_sin) << "\n"
              << "Overall_Error_Cos = " << RMSE(accum_err_cos) << "\n"
              << "#------------------------------------------------\n";

    // Clean up
    fp.close();

}
