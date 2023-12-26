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
    char modbus_address[3];     /* address will be in hex */
    char baud_rate[7];          /* baud rate various from 9600, 19200, 38400, 57600, 115200 */
    char data_bit[1];           /* one byte for data bit */
    char parity_bit[4];         /* parity bit for authentication */
    char stop_bit[1];           /* stop bit placeholder */
}modbusFileHandling_t;

/* Function Prototypes */
void data_extraction(char* buffer, int index, modbusFileHandling_t* handler);


void data_extraction(char* buffer, int index,modbusFileHandling_t* handler){
    char* ptr = NULL;
    char temp[10];
    memset(temp, '\0',10);
    ptr = strtok(buffer, "\"");
    printf("Modbus_Func:%s\n", handler->modbus_address);
    int i = 0;
    while (ptr != NULL){
        if (3 == i){
            strcpy(temp, ptr);
        }
        printf("Idx: %d; Str: %s\n", i, ptr);
        i++;
        ptr = strtok (NULL, "\"");
    }
    printf("Temp: %s\n", temp);
    switch (index){
        case modbus_address:{
            strcpy(handler->modbus_address, temp);
            handler->modbus_address[2] = '\0';
            printf("modbus_address:%s\n", handler->modbus_address);
            break;
        }
        case baud_rate:{
            strcpy(handler->baud_rate, temp);
            printf("%s\n", handler->modbus_address);
            printf("baud_rate:%s\n", handler->baud_rate);
            break;
        }
        default:
            break;
    }
    
}

int main(){
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
            printf("%s", buffer);
            printf("Modbus:%s\n", config_handler.modbus_address);
            data_extraction(buffer, i, &config_handler);
            i++;
            if (end_of_param == i){
                break;
            }
            
        }
    }
    (void)fclose(file_pointer);
    printf("Modbus Address: %s\n", config_handler.modbus_address);
    printf("Baud Rate: %s\n", config_handler.baud_rate);

    return 0;
}