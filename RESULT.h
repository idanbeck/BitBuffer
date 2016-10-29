#ifndef RESULT_H_
#define RESULT_H_

#include <stdint.h>
#include <stdbool.h>

#define CHECK_ERR(r) ((r & 0x80000000) != 0)

#define CNRM_NA(x, str) 
#define CRM_NA(x, str) x

/// <resultor>
typedef enum incident_result {
    // Failure Codes
    R_FAIL  		= 0x80000000,
    R_NO    		= 0x80000000,
    R_ERROR 		= 0x80000000,
    R_FALSE 		= 0x80000000,
    R_DEPRECATED	= 0x80000001,			// Deprecated is an error, since this should not be called
    R_OUT_OF_BOUNDS	= 0x80000002,
    
    // Success Codes
    R_SUCCESS       = 0x00000000,
    R_YES           = 0x00000000,
    R_TRUE			= 0x00000000,
    R_OK            = 0x00000000,
    R_DONE          = 0x00000000,
    
    // Warning
    R_UNSUPPORTED   = 0x00000010,
    R_NO_EFFECT		= 0x00000010,
    
    
    R_INVALID_RESULT        = 0xFFFFFFFF        // Last result EVER!
} RESULT; // End of typedef enum incident_results

#endif // RESULT_H_