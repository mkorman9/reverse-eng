/*
	Cracked by Michał Korman
	
	Usage:
	gcc keygen.c -o keygen.exe
	keygen <username>
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	char *xor_1 = malloc(5); 
	xor_1[0] = 0xAA;
	xor_1[1] = 0x89;
	xor_1[2] = 0xC4;
	xor_1[3] = 0xFE;
	xor_1[4] = 0x46;
	char *xor_2 = malloc(5); 
	xor_2[0] = 0x78;
	xor_2[1] = 0xF0;
	xor_2[2] = 0xD0;
	xor_2[3] = 0x03;
	xor_2[4] = 0xE7;
	char *xor_3 = malloc(5); 
	xor_3[0] = 0xF7;
	xor_3[1] = 0xFD;
	xor_3[2] = 0xF4;
	xor_3[3] = 0xE7;
	xor_3[4] = 0xB9;
	char *xor_4 = malloc(5); 
	xor_4[0] = 0xB5;
	xor_4[1] = 0x1B;
	xor_4[2] = 0xC9;
	xor_4[3] = 'P';
	xor_4[4] = 's';
	
	int a = 0;
	int b = 0;
	int c = 0;
	int i = 0;
	int j = 0;
	int username_len;
	char *username;
	char *username_ptr;
	char *code;
	int var = 0;
	char *var_ptr = (char*) &var;
	
	if (argc != 2) {
		puts("Usage: keygen <username>");
		return 1;
	}

	username = malloc(100);
	memset (username, 0, 100);
	strcpy(username, argv[1]);
	
	code = malloc(100);
	memset (code, 0, 100);
	
	username_ptr = username;
	username_len = strlen(username); username_ptr += 1;
	
	while(i < username_len) {
		a = username_ptr[i];
		username_ptr[i] ^= xor_1[j];
		xor_1[j++] = a;
		if (j == 5) j = 0;
		i++;
	}
	
	i = 0;
	j = 0;
	
	while(i < username_len) {
		c = username_len - i - 1;
		a = username_ptr[c];
		username_ptr[c] ^= xor_2[j];
		xor_2[j++] = a;
		if (j == 5) j = 0;
		i++;
	}
	
	i = 0;
	j = 0;
	
	while(i < username_len) {
		a = username_ptr[i];
		username_ptr[i] ^= xor_3[j];
		xor_3[j++] = a;
		if (j == 5) j = 0;
		i++;
	}
	
	i = 0;
	j = 0;
	
	while(i < username_len) {
		c = username_len - i - 1;
		a = username_ptr[c];
		username_ptr[c] ^= xor_4[j];
		xor_4[j++] = a;
		if (j == 5) j = 0;
		i++;
	}
	
	i = 0;
	
	while (i < username_len) {
		c = i & 3;
		var_ptr[c] = *(var_ptr + c) + username_ptr[i];
		i++;
	}
	
	a = var;
	i = 0;
	
	while(a != 0) {
		b = a;
		a = ((unsigned) a) / 0xa;
		j = b - (a * 0xa);
		code[i++] = *((char*) &j) + 0x30;
	}
	
	strrev(code);
	printf("Code: %s\n", code);
	
	free(xor_4);
	free(xor_3);
	free(xor_2);
	free(xor_1);
	free(code);
	free(username);
	return 0;
}
