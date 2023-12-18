#include <stdio.h>
#include <string.h>

char* extract_device_address(char* str) {
  // Find the colon separating "device address" and the address.
  char* colon = strchr(str, ':');
  if (!colon) {
    return NULL; // String format invalid, no colon found.
  }

  // Skip whitespace after the colon.
  colon++;
  while (*colon == ' ') {
    colon++;
  }

  // Extract the address until the next space or null terminator.
  char address[3]; // Allocate space for the address + null terminator.
  int i = 0;
  while (*colon != ' ' && *colon != '\0') {
    address[i++] = *colon++;
  }
  address[i] = '\0';
    printf("Device address: %s\n", address);
  return address; // Return the extracted address.
}

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