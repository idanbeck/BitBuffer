#ifndef WRAP_BUFFER_H_
#define WRAP_BUFFER_H_

#include "RESULT.h"

// TODO: Verify these functions!!!
RESULT UnwrapBuffer7F(uint8_t *pBuffer7F, int pBuffer7F_n, uint8_t **n_pBuffer, int *pn_pBuffer_n);
RESULT WrapBuffer7F(uint8_t *pBuffer, int pBuffer_n, uint8_t **n_pBuffer7F, int *pn_pBuffer7F_n);

RESULT OLDWrapBuffer7F(uint8_t *pBuffer, int pBuffer_n, uint8_t **n_pBuffer7F, int *pn_pBuffer7F_n);

#endif // ! WRAP_BUFFER_H_