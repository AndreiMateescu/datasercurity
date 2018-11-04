#include <stdio.h>

int main()
{
    char mesaj[100];
    int k, option;
    
    printf("Message: ");
    gets(mesaj);
    printf("k: ");
    scanf("%d", &k);
    
    printf("Encrypt press 0 or decrypt press 1: ");
    scanf("%d", &option);
    
    if(option == 0){
        encrypt(k, &mesaj);
    } else if(option == 1) {
        decrypt(k, &mesaj);    
    }
    
    printf("Final message: %s", mesaj);
}

void encrypt(int k, char* mesaj)
{
    char ch;
    int i;
    for(i = 0; mesaj[i] != '\0'; i++){
        ch = mesaj[i];
        
        if(ch >= 'a' && ch <= 'z'){
            ch = ch + k;
            
            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }
            
            mesaj[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + k;
            
            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }
            
            mesaj[i] = ch;
        }
    }    
}

void decrypt(int k, char* mesaj)
{
    char ch;
    int i;
    for(i = 0; mesaj[i] != '\0'; ++i){
        ch = mesaj[i];
        
        if(ch >= 'a' && ch <= 'z'){
            ch = ch - k;
            
            if(ch < 'a'){
                ch = ch + 'z' - 'a' + 1;
            }
            
            mesaj[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch - k;
            
            if(ch > 'a'){
                ch = ch + 'Z' - 'A' + 1;
            }
            
            mesaj[i] = ch;
        }
    }   
}
