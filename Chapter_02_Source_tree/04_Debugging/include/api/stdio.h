/*! Printing on stdout/stderr */
#pragma once

int PRINTF(char *format, ...);
int printf(char *format, ...);
void warn(char *format, ...);

int stdio_init();
