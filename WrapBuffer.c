#include "WrapBuffer.h"

RESULT PrintBuffer(uint8_t *Buffer, int32_t Buffer_n, int32_t itemsPerRow) {	
	int32_t  i = 0;
	for(i = 1; i <= Buffer_n; i++) {
		printf("%02x ", Buffer[i - 1]);
		if(i % itemsPerRow == 0 && i != 0)
			printf("\r\n");	
	}
	printf("\r\n");
	
	return R_OK;
}

// TODO: Verify these functions!!!
RESULT UnwrapBuffer7F(uint8_t *pBuffer7F, int pBuffer7F_n, uint8_t **n_pBuffer, int *pn_pBuffer_n) {
	RESULT r = R_OK;

	signed char k = 1;
	int32_t serial_nc = 0, i = 0;

	// Count the bits of septets and cut off any remainder 
	int count = (pBuffer7F_n * 7) / 8;
		
	*pn_pBuffer_n = count;
	*n_pBuffer = (uint8_t *)malloc(sizeof(uint8_t) * count);
	
	memset((*n_pBuffer), 0, sizeof(sizeof(uint8_t) * count));
	CNRM_NA((*n_pBuffer), "Failed to allocate memory for the unwrapped buffer");

	for(i = 0; i < pBuffer7F_n; i++) {
		
		if(i != pBuffer7F_n - 1)
			(*n_pBuffer)[serial_nc] = (pBuffer7F[i] << k) + (pBuffer7F[i + 1] >> (7 - k));
		else 
			(*n_pBuffer)[serial_nc] += (pBuffer7F[i] << k);

		k++;
		serial_nc++;

		if(k == 8) {
			k = 1;
			i++;
			
			if(i < pBuffer7F_n)
				(*n_pBuffer)[serial_nc] = pBuffer7F[i - 1] & 0x01;
				
			//printf("yo %d l:%d!\n", i, pBuffer7F_n);
		}
	}

Error:
	return r;
}

RESULT WrapBuffer7F(uint8_t *pBuffer, int pBuffer_n, uint8_t **n_pBuffer7F, int *pn_pBuffer7F_n) {
	RESULT r = R_OK;

	int i = 0, j = 0, c = 0;

	// For every byte over 8 bytes we need another 7F byte
	int count = pBuffer_n + ceil(((float)(pBuffer_n))/((float)(7.0f)));
	*pn_pBuffer7F_n = count;
	(*n_pBuffer7F) = (uint8_t *)malloc(sizeof(uint8_t) * count);

	memset((*n_pBuffer7F), 0x00, sizeof(sizeof(uint8_t) * count));
	CNRM_NA((*n_pBuffer7F), "Failed to allocate memory for the wrapped buffer");
	
	uint8_t left, right;
	j = 1;
	c = 0;
	
	for(i = 0; i < pBuffer_n; i++) {
		left = (pBuffer[i] >> j) & 0x7F;
		right = ((pBuffer[i]) & (0xFF >> (8 - j))) & 0x7F;
		
		j++;
		
		(*n_pBuffer7F)[c] += left;
		(*n_pBuffer7F)[c + 1] = right << (8 - j);
		
		if(j == 8) {
			c++;			
			
			(*n_pBuffer7F)[c] = pBuffer[i] & 0x7F;
			(*n_pBuffer7F)[c + 1] = right << (7);
			
			j = 1;
		}
		
		c++;
	}

Error:
	return r;
}


RESULT OLDWrapBuffer7F(uint8_t *pBuffer, int pBuffer_n, uint8_t **n_pBuffer7F, int *pn_pBuffer7F_n) {
	RESULT r = R_OK;
	
	int j = 0, i = 0;
	signed char startCounter = 1;
    signed char endCounter = 6;
	
	// For every byte over 8 bytes we need another 7F byte
	int count = pBuffer_n + ceil(((float)(pBuffer_n))/((float)(7.0f)));
	*pn_pBuffer7F_n = count;
	(*n_pBuffer7F) = (uint8_t *)malloc(sizeof(uint8_t) * count);

	memset((*n_pBuffer7F), 0, sizeof(sizeof(uint8_t) * count));

	CNRM_NA((*n_pBuffer7F), "Failed to allocate memory for the wrapped buffer");
    
    for (i = 0; i < pBuffer_n; i++) {
        // Add current fragment and begining of next
        (*n_pBuffer7F)[j] += (pBuffer[i] >> startCounter) & 0x7F;
        (*n_pBuffer7F)[j + 1] = (0x7F & (pBuffer[i] << endCounter));
        
        // var upkeep
        j += 1;
        startCounter += 1;
        endCounter -= 1;
        
        // boundary check
        if ( startCounter == 8 && endCounter < 0 ) {			
            j++;
            startCounter = 1;
            endCounter = 6;
        }
    }
	
	return r;
}