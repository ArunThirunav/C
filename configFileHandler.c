#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char dev_address[8];
    char data_bits[1];
    char stop_bits[1];
    char parity[4];
    char hw_flowctrl[4];
    uint32_t baud_rate;
}uart_config_t;


void findIndex(char* buff, uart_config_t* config);
char res[10];

void findIndex(char* buff, uart_config_t* config){
    uint8_t parsercount = 1;
    int max_lent = 0;

    while (parsercount){
        if (*buff == ':'){
            buff++;
            break;
        }
        buff += 1;
        parsercount++;
    }
    memset(res, '\0', sizeof(res));
    int i = 0;
    while (*buff != '\0') {
        res[i++] = *buff++;
    }
    res[i++] = '\0';
    strncpy(config->dev_address, res, strlen(res));
}



int main(){
    FILE* fp;
    uart_config_t configValue;
    char buff[255];
    int device_address = 0;
    int baud_rate = 0;
    int data_bits = 0;
    memset(buff, 0, sizeof(buff));

    fp = fopen("data.cfg", "r");

    fgets(buff, sizeof(buff), fp);
    findIndex(buff, &configValue);
    printf("device_address: %s\n", configValue.dev_address);

    fclose(fp);
    return 0;
}