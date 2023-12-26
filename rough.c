#include <stdio.h>
#include <string.h>
char address[3]; // Allocate space for the address + null terminator.

int main() {
  char str[] = "device address: 01";
  char* address = extract_device_address(str);

  if (address) {
    printf("Device address: %s\n", address);
  } else {
    printf("Error: Invalid string format.\n");
  }

  return 0;
}