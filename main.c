#include <stdio.h>
#include <stdarg.h>

#include "RESULT.h"
#include "WrapBuffer.h"

RESULT TestUnwrapWrap(int length, bool fRand) {
	RESULT r = R_OK;
	int i = 0;

	int pOriginalBuffer_n = length;
	uint8_t *pOriginalBuffer = (uint8_t *)malloc(sizeof(uint8_t) * pOriginalBuffer_n);

	uint8_t *pBuffer7F = NULL;
	int pBuffer7F_n = -1;

	uint8_t *pBuffer = NULL;
	int pBuffer_n = -1;

	for(i = 0; i < pOriginalBuffer_n; i++) {
		if(fRand)
			pOriginalBuffer[i] = (uint8_t)(rand());
		else
			pOriginalBuffer[i] = (uint8_t)(i);
	}
	
	printf("*** Original Buffer: %d bytes ***\n", pOriginalBuffer_n);

	CRM_NA(WrapBuffer7F(pOriginalBuffer, pOriginalBuffer_n, &pBuffer7F, &pBuffer7F_n), "Failed to wrap original buffer");

	printf("*** Wrapped Buffer: %d bytes ***\n", pBuffer7F_n);
	
	CRM_NA(UnwrapBuffer7F(pBuffer7F, pBuffer7F_n, &pBuffer, &pBuffer_n), "Failed to unwrap 7F buffer");
	
	printf("*** Unwrapped Buffer: %d bytes ***\n", pBuffer_n);
	
	bool fOK = true;
	
	if(pOriginalBuffer_n != pBuffer_n){
		fOK = false;
		printf("Unwrapped buffer length %d is not original length of %d", pBuffer_n, pOriginalBuffer_n);
	}
	
	for(i = 0; i < pOriginalBuffer_n; i++) {
		if(pBuffer[i] != pOriginalBuffer[i]) {
			printf("index %d doesn't match 0x%x vs 0x%x\n", i, pBuffer[i], pOriginalBuffer[i]);
			fOK = false;
		}
	}
	
	if(!fOK) {
		printf("Failed to verify wrap/unwrap for %d bytes\n", pOriginalBuffer_n);
		printf("Original: \n");
		PrintBuffer(pOriginalBuffer, pOriginalBuffer_n, 20);
		
		printf("Wrapped: \n");
		PrintBuffer(pBuffer7F, pBuffer7F_n, 20);
		
		printf("Unwraped: \n");
		PrintBuffer(pBuffer, pBuffer_n, 20);
		
		return R_FAIL;
	}

Error:
	return r;
}

long int Convert7FToInt(int num, ...) {
	long int retVal = 0x00;
	int i = 0;
	
	va_list valist;
	va_start(valist, num);
	
	for(i = 0; i < num; i++) {
		unsigned char temp = va_arg(valist, unsigned char);
		retVal += (temp & 0x7F) << (7 * i);
	}	
	
	va_end(valist);	
	
	return retVal;
}


int main(int argc, char **argv) {
	printf("Testing wrap/unwrap functions\n");
	
	int i = 0;
	time_t t;
	srand((unsigned) time(&t));
	
	//RESULT r = TestUnwrapWrap(7, true);
	
	/*
	for(i = 1; i < 1024 * 120; i++) {
		RESULT r = TestUnwrapWrap(i, true);
		if(r != R_OK) {
			printf("Test case for length %d failed\n", i);
			break;
		}
	}
	//*/
	long int val7f = Convert7FToInt(2, 0x7F, 0x7F);
	printf("val: 0x%x\n", val7f);
	
	system("pause");
	
	return 0;
}
