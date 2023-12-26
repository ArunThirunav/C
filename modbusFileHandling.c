#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum{
    BUF_SIZE = 100
};

typedef struct modbusFileHandling
{
    char modbus_address[2]; /* address will be in hex */
    char baud_rate[6];  /* baud rate various from 9600, 19200, 38400, 57600, 115200 */
    char data_bit[1]; /* one byte for data bit */
    char parity_bit[4]; /* parity bit for authentication */
    char stop_bit[1]; /* stop bit placeholder */
}modbusFileHandling_t;

int main(){
    FILE* file_pointer = 0;
    char buffer[BUF_SIZE];
    char* ptr = 0;
    file_pointer = fopen("ModbusSettings.xml", "r");
    memset(buffer, 0, sizeof(buffer));
    while (NULL != fgets(buffer, BUF_SIZE, file_pointer)){
        ptr = strstr(buffer, "MODBUSADDRESS");
        if (ptr){
            printf("%s", buffer);
        }
        
    }    
    (void)fclose(file_pointer);
    return 0;
}