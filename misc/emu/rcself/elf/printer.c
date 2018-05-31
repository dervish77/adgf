#include <stdio.h>
#include "elf.h"

void configurePrinter(char* arg) {
  int port;
  portStruct ports;
  ports = parseArgs(arg);
  port = (ports.outPorts[0] == 0) ? 6 : ports.outPorts[0] - 1;
  usePrinter = 'Y';
  outPorts[port].out = printerOut;
  }

void printerOut(byte value) {
  FILE* printer;
  printer = fopen("printer.out","a");
  fprintf(printer,"%c",value);
  fclose(printer);
  }

