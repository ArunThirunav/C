#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dataHandler.h"

enum{
    modbus_address,
    baud_rate, 
    data_bit,
    parity_bit,
    stop_bit,
    end_of_param,
    BUF_SIZE = 100
};

/* UART Configuration Parameter */
static const char *uart_config[] = {
    "MODBUSADDRESS", 
    "BAUDRATE", 
    "DATABIT",
    "PARITYBIT",
    "STOPBIT"
};

/* User Defined Data Types */

typedef struct{
    char modbus_address[4];     /* address will be in hex */
    char baud_rate[7];          /* baud rate various from 9600, 19200, 38400, 57600, 115200 */
    char data_bit[1];           /* one byte for data bit */
    char parity_bit[4];         /* parity bit for authentication */
    char stop_bit[1];           /* stop bit placeholder */
}modbusFileHandling_t;

/* Function Prototypes */
void data_extraction(char* buffer, int index, modbusFileHandling_t* handler);
void config_data_handling(void);


void data_extraction(char* buffer, int index,modbusFileHandling_t* handler){
    char* ptr = NULL;
    char temp[10];
    memset(temp, '\0',10);
    ptr = strtok(buffer, "\"");
    int i = 0;
    while (ptr != NULL){
        if (3 == i){
            strcpy(temp, ptr);
        }
        i++;
        ptr = strtok(NULL, "\"");
    }
    switch (index){
        case modbus_address:{
            memset(handler->modbus_address, '\0', sizeof(handler->modbus_address));
            strcpy(handler->modbus_address, temp);
            break;
        }
        case baud_rate:{
            memset(handler->baud_rate, '\0', sizeof(handler->baud_rate));
            strcpy(handler->baud_rate, temp);
            break;
        }
        default:
            break;
    }
    
}

void config_data_handling(void){
    FILE* file_pointer = 0; /* File Pointer */
    modbusFileHandling_t config_handler;
    char buffer[BUF_SIZE];
    char* ptr = 0;
    int i = 0;
    file_pointer = fopen("ModbusSettings.xml", "r");
    memset(buffer, 0, sizeof(buffer));
    while (NULL != fgets(buffer, BUF_SIZE, file_pointer)){
        ptr = strstr(buffer, uart_config[i]);
        if (ptr){
            data_extraction(buffer, i, &config_handler);
            i++;
            if (end_of_param == i){
                break;
            }
            
        }
    }
    (void)fclose(file_pointer);
    // printf("0: %c\n", config_handler.modbus_address[0]);
    // printf("1: %c\n", config_handler.modbus_address[1]);
    int address = strtol(config_handler.modbus_address, NULL, 16);
    int baud_rate = strtol(config_handler.baud_rate, NULL, 10);
    printf("Modbus Address: 0x%02X\n", address);
    // printf("Modbus Address: %s\n", config_handler.modbus_address);
    printf("Str Baud Rate: %s\n", config_handler.baud_rate);
    printf("Baud Rate: %d\n", baud_rate);
}

int main(){
    config_data_handling();
    return 0;
}