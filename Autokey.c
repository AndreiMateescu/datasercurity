#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define VAL(PTR) (*PTR)

typedef char* STRING;
typedef char** STRING_REF;

void autokey_encrypt_decrypt(STRING_REF str, char key, int encrypt){
	int str_length, itr_str, next_key,current_key, remainder;
	str_length = strlen(VAL(str));
	for(itr_str = 0 ; itr_str < str_length ; ++itr_str){
		if(isalpha(VAL(str)[itr_str])){
			VAL(str)[itr_str] = toupper(VAL(str)[itr_str]);
		}
	}
	next_key = toupper(key)-'A';
	for(itr_str = 0 ; itr_str < str_length ; ++itr_str){
		if(isalpha(VAL(str)[itr_str])){
			current_key = next_key;
			if(encrypt){
				next_key = VAL(str)[itr_str]-'A';
				VAL(str)[itr_str] = (VAL(str)[itr_str]-'A'+current_key)%26+'A';
			}
			else{
				remainder = (VAL(str)[itr_str]-'A'-current_key)%26+'A';
				VAL(str)[itr_str] = remainder < 'A' ? remainder + 26 : remainder ;
				next_key = VAL(str)[itr_str]-'A';
			}
		}
	}
}

void flush_stdin()
{
	while(fgetc(stdin) != '\n');
}

int main(int argc, char **argv)
{
	int length;
	char key;
	char *str;
	printf("Enter the key to be used for encryption: ");
	scanf("%c",&key);
	printf("Enter the length of the string: ");
	scanf("%d",&length);
	str = (char*)malloc((length+1)*sizeof(char));
	flush_stdin();
	printf("Input the string you want to encrypt: ");
	fgets(str,length+1,stdin);
	flush_stdin();
	autokey_encrypt_decrypt(&str,key,1);
	printf("\nThe text after encrypting is: %s",str);
	autokey_encrypt_decrypt(&str,key,0);
	printf("\nAfter decrypting the same encrypted text: %s",str);
	printf("\n");
	free(str);
	return 0;
}
