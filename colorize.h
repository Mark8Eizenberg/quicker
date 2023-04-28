#include <stdio.h>
#include <string.h>
#include <errno.h>

#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#define STR_RED(S)      ANSI_COLOR_RED""S""ANSI_COLOR_RESET
#define STR_GREEN(S)    ANSI_COLOR_GREEN""S""ANSI_COLOR_RESET
#define STR_YELLOW(S)   ANSI_COLOR_YELLOW""S""ANSI_COLOR_RESET
#define STR_BLUE(S)     ANSI_COLOR_BLUE""S""ANSI_COLOR_RESET
#define STR_MAGENTA(S)  ANSI_COLOR_MAGENTA""S""ANSI_COLOR_RESET
#define STR_CYAN(S)     ANSI_COLOR_CYAN""S""ANSI_COLOR_RESET

#define MSG_INFO(S, ...)        printf(ANSI_COLOR_GREEN"[INFO]:"ANSI_COLOR_RESET""S"\n", ##__VA_ARGS__)
#define MSG_WARNING(S, ...)     printf(ANSI_COLOR_YELLOW"[WARNING]:"ANSI_COLOR_RESET""S"\n", ##__VA_ARGS__)
#define MSG_ERROR(S, ...)       printf(ANSI_COLOR_RED "[ERROR]:"ANSI_COLOR_RESET""S"\n", ##__VA_ARGS__)

#define MSG_INFO_DEBUG(S, ...)        printf("\t"ANSI_COLOR_GREEN"[DEBUG INFO]:"ANSI_COLOR_RESET" func \"%s\" in file \"%s\" msg - "S"\n", __func__, __FILE__, ##__VA_ARGS__)
#define MSG_WARNING_DEBUG(S, ...)     printf("\t"ANSI_COLOR_YELLOW"[DEBUG WARNING]:"ANSI_COLOR_RESET" func \"%s\" in file \"%s\" msg - "S"\n", __func__, __FILE__, ##__VA_ARGS__)
#define MSG_ERROR_DEBUG(S, ...)       printf("\t"ANSI_COLOR_RED "[DEBUG ERROR]:"ANSI_COLOR_RESET" func \"%s\" in file \"%s\" msg - "S"\n", __func__, __FILE__, ##__VA_ARGS__)