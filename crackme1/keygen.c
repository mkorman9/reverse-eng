/*
	Cracked by Michał Korman
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	char xor_1[] = { 0xAA, 0x89, 0xC4, 0xFE };
	char xor_2[] = { 0x78, 0xF0, 0xD0, 0x03 };
	char xor_3[] = { 0xF7, 0xFD, 0xF4, 0xE7 };
	char xor_4[] = { 0xB5, 0x1B, 0xC9, 0x50 };
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
	
	if (strlen(argv[1]) != 4) {
		puts("Username must be length 4");
		return 1;
	}

	username = malloc(4);
	memset (username, 0, 4);
	strcpy(username, argv[1]);
	
	code = malloc(32);
	memset (code, 0, 32);
	
	username_ptr = username;
	username_len = strlen(username); username_ptr += 1;
	
	while(i < username_len) {
		username_ptr[i] ^= xor_1[a++];
		if (a == 5) a = 0;
		i++;
	}
	
	i = 0;
	
	while(i < username_len) {
		c = username_len - i - 1;
		username_ptr[c] = xor_2[j++] ^ username_ptr[c];
		if (j == 5) j = 0;
		i++;
	}
	
	i = 0;
	j = 0;
	
	while(i < username_len) {
		username_ptr[i] ^= xor_3[j++];
		if (j == 5) j = 0;
		i++;
	}
		
	i = 0;
	j = 0;
	
	while(i < username_len) {
		c = username_len - i - 1;
		username_ptr[c] = xor_4[j++] ^ username_ptr[c];
		if (j == 5) j = 0;
		i++;
	}
	
	i = 0;
	
	while (i < username_len) {
		c = i & 3;
		var_ptr[c] = *(var_ptr + c) ^ username_ptr[i];
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
	
	free(code);
	free(username);
	return 0;
}
