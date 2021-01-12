#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"

// Get error message from id
void display_error_message(int message_id)
{
    switch (message_id) {
        case SUCCESS:
            printf(" Output message : Success \n");
            break;
        // Check size
        case INCOMPATIBLE_INPUT_SIZE:
            printf(" Output message : [ERROR] Incompatble input size \n");
            break;
        case INCOMPATIBLE_OUTPUT_SIZE:
            printf(" Output message : [ERROR] Incompatble output size \n");
            break;
        case INCOMPATIBLE_NB_BATCHS:
            printf(" Output message : [ERROR] Incompatble number of batches \n");
            break;
        case INCOMPATIBLE_BATCH_SIZE:
            printf(" Output message : [ERROR] Incompatble batches size \n");
            break;
        // Check size
        case INVALID_INDEX:
            printf(" Output message : [ERROR] Invalid index \n");
            break;
        case INVALID_BATCH_ID:
            printf(" Output message : [ERROR] Invalid batch id \n");
            break;
        case INVALID_VAL_ID:
            printf(" Output message : [ERROR] Invalid value id in batch \n");
            break;
        // Undefined or unimplmented feature
        case UNDEFINED:
            printf(" Output message : [ERROR] Undefined parameter \n");
            break;
        case UNIMPLEMENTED:
            printf(" Output message : [ERROR] Unimplemented feature \n");
            break;

        default:
            printf(" Output message : [ERROR] Unknown Message id \n");
    }
}
