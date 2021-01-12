#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MESSAGE_MAX_SIZE 200

// Success
#define SUCCESS 1

// Output from check size functions
#define COMPATIBLE_SIZES SUCCESS
#define INCOMPATIBLE_INPUT_SIZE -2
#define INCOMPATIBLE_OUTPUT_SIZE -3
#define INCOMPATIBLE_NB_BATCHS -4
#define INCOMPATIBLE_BATCH_SIZE -5

// Output from check index functions
#define VALID_INDEX SUCCESS
#define INVALID_INDEX -10
#define INVALID_BATCH_ID -11
#define INVALID_VAL_ID -12

// Not implmented
#define UNIMPLEMENTED -20
#define UNDEFINED -21

// Get error message from id
void display_error_message(int message_id);

#endif // CONSTANTS_H_INCLUDED
