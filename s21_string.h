#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#define s21_NULL ((void *)0)

#include <stdarg.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
long double s21_float_round_to_int(long double num);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *s21_int_to_str(char *result, const long long n);
int norm_func(int i);

typedef struct Capsule {
  // выравнивание: 0 - по правому краю, 1 - по левому краю
  int alignment;

  // неявное обозначение знака - 0, явное обозначение знака - 1
  int explicit_sign;

  // пробельный символ при отсутсвии знака:
  // 0 - никаких пробелов, 1 - ставить пробел когда знак не печатается
  int space_with_no_sign;

  // подробная численная запись (та, которая в задании обозначается флагом #)
  // 0 - выключена, 1 - включена
  int full_writing;

  // заполнение пустого пространства нулями слева при указании ширины
  // 0 - выключена, 1 - включена
  int zero_printing;

  // ширина печатаемых значений; если -1, то взять из аргумента
  int width;

  // точность печатаемых значений; если -1, то взять из аргумента
  int precision;

  // символ длины для особенных типов (по умолчанию '\0')
  char length;

  // символ типа переменной (по умолчанию '\0')
  char type;

  // указатель на void для того чтобы принимать данные из любых типов переменных
  void *variable;

  // указатель на текст после типа до следующего %
  char *text;

  // преобразованная капсула в строку
  char *str_end;
} capsule;

capsule *create_capsule();

void free_capsule(capsule **item);

int s21_sprintf(char *str, const char *format, ...);
char **parsing(char *str);
capsule **pars_mass(char **str);
void pars_elem_right(char *buff, capsule *result);
void pars_elem_left(char *buff, capsule *result);
char *decoder(capsule **strmass, va_list ap);
void type_d_temp(capsule *strmass, va_list ap, long long int *lx);
void type_f_temp(capsule *strmass, va_list ap, long double *lx1);

void type_d(capsule *strmass);
void type_s(capsule *strmass);
void type_c(capsule *strmass);

void fit_to_width(char *str, int width, int zero_printing, int alignment);
char *int_part_of_float_to_str(char *dest, long double n, int precision,
                               int explicit_sign, int space_with_no_sign);
int infnan_check(char *str, long double n, int explicit_sign,
                 int *space_with_no_sign, int *zero_printing);
void read_capsule(capsule *caps, int *alignment, int *precision,
                  int *full_writing, int *width, int *explicit_sign,
                  int *space_with_no_sign, int *zero_printing, long double *a);
void cut_part(char *str, char *first_part, long double second_part,
              s21_size_t precision, int full_writing);

void clear_zeros(char *str);
void type_f(capsule *caps);
void type_F(capsule *caps);
void type_G(capsule *strmass);
void type_g(capsule *strmass);
void type_E(capsule *strmass);
void type_e(capsule *strmass);
void Pow(long double *a, long double *m);
void type_x(capsule *strmass);
void type_X(capsule *strmass);
void type_o(capsule *strmass);
void hex_oct(char *r_str, long long int num, int base);
char char_of_hex(long long int n);
void type_p(capsule *strmass);
char *space_d(char *str1, char *str2, int spaces, int alignment);

void *s21_to_lower(const char *p);
void *s21_to_upper(const char *p);
void *s21_to_upper_first(const char *p);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, size_t start_index);

int tolower21(int symb);
int toupper21(int symb);

#define SUFFIX "%cdeEfFgGinopsuxX"
#define CELOCHISL "diouxX"
#define LENGTH "hlL"
#define PRECISION "eEfgG"
#define ALL "%cdeEfFgGinopsuxXhlL0123456789.#+-* "

#ifndef OSX
#define ERROR_NUM 134
#define ERROR_LIST                                                             \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }
#endif
#ifdef OSX
#define ERROR_NUM 107
#define ERROR_LIST                                                             \
  {                                                                            \
    "Undefined error: 0", "Operation not permitted",                           \
        "No such file or directory", "No such process",                        \
        "Interrupted system call", "Input/output error",                       \
        "Device not configured", "Argument list too long",                     \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Resource busy", "File exists", "Cross-device link",                   \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disc quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable (or shared library)", "Bad CPU type in executable",    \
        "Shared library version mismatch", "Malformed Mach-o file",            \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "EMULTIHOP (Reserved)",          \
        "No message available on STREAM", "ENOLINK (Reserved)",                \
        "No STREAM resources", "Not a STREAM", "Protocol error",               \
        "STREAM ioctl timeout", "Operation not supported on socket",           \
        "Policy not found", "State not recoverable", "Previous owner died",    \
        "Interface output queue is full",                                      \
  }
#endif
#endif  // SRC_S21_STRING_H_
