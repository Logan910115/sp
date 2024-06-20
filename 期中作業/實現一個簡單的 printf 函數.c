#include <stdio.h>
#include <stdarg.h>

// 定義自訂的 printf 函數
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *p = format;
    while (*p) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 'd': {
                    int i = va_arg(args, int);
                    printf("%d", i);
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
                    printf("%s", s);
                    break;
                }
                default:
                    putchar(*p);
                    break;
            }
        } else {
            putchar(*p);
        }
        p++;
    }

    va_end(args);
}

int main() {
    int num = 42;
    char *str = "Hello, World!";
    
    my_printf("Number: %d, String: %s\n", num, str);
    return 0;
}
