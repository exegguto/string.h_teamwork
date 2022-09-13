#include "s21_string.h"

#include <math.h>
#include <stddef.h>

/**
 * Функция s21_memcmp сравнивает первые n байтов двух блоков памяти
 * @param str1 Указатель на начало первого блока (строки)
 * @param str2 Указатель на начало второго блока (строки)
 * @param n Количество сравнимаемых байт
 * @return 0, если сравниваемые блоки одинаковы, иначе возвращается разница
 * кодов первых встретившихся различных байтов
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *s1 = str1;
  const char *s2 = str2;
  int res = 0;
  // Проходим по n элементам массивов, пока не встретим первый различающийся
  // символ
  while (n-- > 0) {
    if (*s1++ != *s2++) {
      res = *--s1 - *--s2;  // если встретили отличные символы, запоминаем
                            // разницу их кодов
      break;
    }
  }
  return res;
}
/**
 * Функция s21_strncat добавляет строку, на которую указывает src, в конец
 * строки, на которую указывает dest, длиной до n символов.
 * @param dest Указатель на массив, в который будет добавлена строка
 * @param src Указатель на массив, из которого будет скопирована добавленная
 * строка
 * @param n Максимальная длина добавляемой строки
 * @return Указатель на массив, в который добавлена строка (dest)
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  // Вычисляем длину обеих строк
  s21_size_t len_dest = s21_strlen(dest);
  s21_size_t len_src = s21_strlen(src);
  if (len_src < n) {  // Случай, когда строка scr добавляется полностью
    s21_strcpy(&dest[len_dest], src);
  } else {  // Случай, когда добавить нужно только первые n элементов строки src
    s21_strncpy(&dest[len_dest], src, n);
  }
  dest[len_dest + n] = '\0';
  return dest;
}
/**
 * Функция s21_strncpy копирует до n символов из строки, на которую указывает
 * src, в dest
 * @param dest Указатель на строку, куда будет копироваться строка
 * @param src Указатель на копируемую строку
 * @param n Максимальное количество копируемых символов
 * @return Указатель на массив, в который скопирована строка (dest)
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  while (n-- > 0) {
    if ((*dest++ = *src++) ==
        '\0') {  // Если n > strlen(src), оставшиеся байты заполняем нулями
      while (--n > 0) *dest++ = '\0';
      break;
    }
  }
  return dest;
}
/**
 * Функция s21_strrchr выполняет поиск последнего вхождения символа c
 * (беззнаковый тип) в строке, на которую указывает аргумент str
 * @param str Указатель на строку
 * @param c Код символа для поиска
 * @return Указатель на последнее вхождение символа, если он найден, иначе NULL
 */
char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str) + 1; i++)
    if ((int)str[i] == c) res = (char *)&str[i];
  return res;
}

/**
 * s21_memmove Еще одна функция для копирования n символов из str2 в str1.
 * @param *dest Указатель на строку назначения
 * @param *src Указатель на строку источника для копирования
 * @param n Количество сравнимаемых байт
 * @return возвращает указатель на строку назначения
 */
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *charPointerDest = (unsigned char *)dest;
  const unsigned char *charPointerSrc = (const unsigned char *)src;
  // выделить память для массива (статически)
  unsigned char tmp[n];
  // копировать источник во временную строку
  for (s21_size_t i = 0; i < n; i++) {
    *(tmp + i) = *(charPointerSrc + i);
  }
  // копировать временную строку в пункт назначения
  for (s21_size_t i = 0; i < n; i++) {
    *(charPointerDest + i) = *(tmp + i);
  }
  return dest;
}

/**
 * s21_strcmp Сравнивает строку, на которую указывает str1, со строкой, на
 * которую указывает str2.
 * @param *str1 Указатель на начало первого блока (строки)
 * @param *str2 Указатель на начало второго блока (строки)
 * @return возвращает разность первых расходящихся символов в строке, пригодную
 * для лексикографического сравнения
 */
int s21_strcmp(const char *str1, const char *str2) {
  // до тех пор, пока первая строка не закончена двигаем счётсчик и символы
  // равны двигаем счётчик вперёд
  while (*str1) {
    if (*str1 == *str2) {
      str1++;
      str2++;
    } else {
      break;
    }
  }
  // возвращаем разницу символов первой строки и второй на последней
  // рассмотренной позиции
  return *str1 - *str2;
}

/**
 * s21_strerror Выполняет поиск во внутреннем массиве номера ошибки errnum и
 возвращает указатель на строку с сообщением об ошибке. Нужно объявить макросы,
 содержащие массивы сообщений об ошибке для операционных систем mac и linux.
 Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
 осуществляется с помощью директив.
 * @param errnum Прринимает численный код ошибки
 * @return возвращает соответствующее данному численому коду текстровое
 сообщение
 */
char *s21_strerror(int errnum) {
  static char result[100] = {0};
  if (errnum >= ERROR_NUM || errnum < 0) {
    char str_err[100] = {0};
#ifdef OSX
    s21_strcpy(result, "Unknown error: ");
#endif
#ifndef OSX
    s21_strcpy(result, "Unknown error ");
#endif
    s21_strcat(result, s21_int_to_str(str_err, errnum));
  } else {
    char *error_message[] = ERROR_LIST;
    s21_strcpy(result, error_message[errnum]);
  }
  return result;
}

/**
 * Функция s21_int_to_str превращает int в str
 * @param *result Указатель выходную строку с полученной из числа строкой
 * @param n целое число для конвертации в строку
 * @return ссылка на итоговую строку
 */
char *s21_int_to_str(char *result, const long long n) {
  long long num = n, pow_of_ten = 1, minus = 0;
  if (num < 0) {
    minus = 1;
    num = -num;
  }
  if (num == 0) {
    result[0] = '0';
    result[1] = '\0';
  } else {
    while (pow_of_ten <= num) {
      pow_of_ten *= 10;
    }
    pow_of_ten /= 10;
    int position;
    if (minus == 0) {
      position = 0;
    } else {
      result[0] = '-';
      position = 1;
    }
    while (pow_of_ten != 0) {
      result[position] = '0' + num / pow_of_ten;
      num = num - num / pow_of_ten * pow_of_ten;
      pow_of_ten /= 10;
      position++;
    }
    result[position] = '\0';
  }
  return result;
}

/**
 * s21_strstr Находит первое вхождение всей строки needle
 (не включая завершающий нулевой символ), которая появляется в строке haystack.
 * @param *haystack Указатель на начало первого блока (исследуемой строки)
 * @param *needle Указатель на начало второго блока (искомой строки)
 * @return Возвращает указатель на первое вхождение подстроки в строку
 */
char *s21_strstr(const char *haystack, const char *needle) {
  char *answer = s21_NULL;
  char *position = (char *)haystack;
  if (haystack != s21_NULL && needle != s21_NULL) {
    while (*position) {
      s21_size_t sameSymbolsCounter = 0;
      while (*(needle + sameSymbolsCounter)) {
        if (*(needle + sameSymbolsCounter) !=
            *(position + sameSymbolsCounter)) {
          break;
        }
        sameSymbolsCounter++;
      }
      if (sameSymbolsCounter == s21_strlen(needle)) {
        answer = position;
        break;
      }
      position++;
    }
  }
  return answer;
}

/**
 * Функция s21_memcpy копирует n символов из src в dest.
 * @param *dest Указатель на начало первого блока (строки)
 * @param *src Указатель на начало второго блока (строки)
 * @param n Количество символов, которые надо скопировать из src в dest
 * @return dest, возвращаем строку, куда все скопировали
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *p = (char *)dest;
  char *q = (char *)src;
  while (n--) {
    *p = *q;
    p++;
    q++;
  }
  return dest;
}

/**
 * Функция s21_strchr выполняет поиск первого вхождения символа c (беззнаковый
 * тип) в строке, на которую указывает аргумент str.
 * @param *str Указатель на начало первого блока (строки)
 * @param c код символа, по которому нужно найти вхождение
 * @return result, возвращаем строку, c начала символа
 */
char *s21_strchr(const char *str, int c) {
  int i = 0;
  char *result;
  while ((str[i] != '\0') && (str[i] != c)) {
    i++;
  }
  if (str[i] == '\0') {
    result = s21_NULL;
  } else {
    result = (char *)&str[i];
  }
  return result;
}

/**
 * Функция s21_strcspn вычисляет длину начального сегмента str1, который
 * полностью состоит из символов, не входящих в str2.
 * @param *str1 Указатель на начало первого блока (строки)
 * @param *str2 Указатель на начало второго блока (строки)
 * @return len, возвращаем длину сегмента str1
 */
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if ((str1 != s21_NULL) && (str2 != s21_NULL)) {
    while (*str1) {
      if (s21_strchr(str2, *str1)) {
        break;
      } else {
        str1++;
        len++;
      }
    }
  }
  return len;
}

/**
 * Функция s21_strspn вычисляет длину начального сегмента str1, который
 * полностью состоит из символов str2.
 * @param *str1 Указатель на начало первого блока (строки)
 * @param *str2 Указатель на начало второго блока (строки)
 * @return len, возвращаем длину сегмента str1
 */
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if ((str1 != s21_NULL) && (str2 != s21_NULL)) {
    while (*str1 && s21_strchr(str2, *str1++)) {
      len++;
    }
  }
  return len;
}

/**
 * Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
 * указывает аргумент str
 * @param str Исходный аргумент
 * @param str_temp Копия указателя на исходный аргумент
 * @param c Символ для копирования
 * @param n Количество заменяемых символов
 * @return Результирующий аргумент
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  if (str) {
    char *str_temp = (char *)str;
    while (n--) *str_temp++ = c;
  }
  return str;
}

/**
 * Сравнивает не более первых n байтов str1 и str2.
 * @param str1 Первая сравниваемая строка
 * @param str2 Вторая сравниваемая строка
 * @param n Максимальное количество сравниваемых символов
 * @return Возвращает неоднозначное значение, информирующее о результате
 * сравнения строк:
 * Нулевое значение указывает на то, что содержимое обоих блоков памяти равны.
 * Значение большее нуля указывает на то, что строка string1 больше строки
 * string2, значение меньше нуля свидетельствует об обратном.
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int ret = 0;
  while (n-- > 0 && ret == 0) ret = *str1 - *str2, str1++, str2++;
  return ret;
}

/**
 * Вычисляет длину строки str, не включая завершающий нулевой символ
 * @param str входная строка
 * @param len длинна строки
 * @return длинна строки
 */
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str != s21_NULL) {
    for (; str[len] != '\0'; len++) {
    }
  }
  return len;
}

/**
 * Разбивает строку str на ряд токенов, разделенных delim
 * @param str указатель на разбиваемую строку
 * @param delim указатель на строку, содержащую набор символов разделителей
 * @return NULL – если строку str невозможно разделить на части.
 * Указатель на первый символ выделенной части строки.
 * strcspn(const char *str1, const char *str2) | Вычисляет длину начального
 * сегмента str1, который полностью состоит из символов, не входящих в str2.
 * strspn(const char *str1, const char *str2) | Вычисляет длину начального
 * сегмента str1, который полностью состоит из символов str2.
 */
char *s21_strtok(char *str, const char *delim) {
  char *end;
  static char *old;
  char **save_ptr = &old;
  if (str == s21_NULL) str = *save_ptr;
  str += s21_strspn(str, delim);
  end = str + s21_strcspn(str, delim);
  if (*end != '\0') *end = '\0', end++;
  *save_ptr = end;
  if (*str == '\0') str = s21_NULL;
  return str;
}

/**
 * Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
 * байтах строки, на которую указывает аргумент str.
 * @param str строка в которой ищем
 * @param с символ который ищем
 * @param n длинна для поиска
 * @return указатель на найденный символ
 */
void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *p = (unsigned char *)str;
  unsigned char *find = s21_NULL;
  for (size_t i = 0; i < n; i++) {
    if ((unsigned char)c == *p) {
      find = p;
      break;
    } else {
      p++;
    }
  }
  return find;
}

/**
 * Добавляет строку, на которую указывает src, в конец строки, на которую
 * указывает dest.
 * @param dest строка в конец которой дописываем
 * @param src строка которую дописываем
 * @return указатель на сложенную строку
 */
char *s21_strcat(char *dest, const char *src) {
  int l = s21_strlen(dest);
  int i;
  for (i = 0; src[i] != '\0'; i++) {
    dest[l + i] = src[i];
  }
  dest[l + i] = '\0';
  return dest;
}

/**
 * Копирует строку, на которую указывает src, в dest.
 * @param dest строка в начало которой копируем
 * @param src строка которую копируем
 * @return указатель на сложенную строку
 */
char *s21_strcpy(char *dest, const char *src) {
  int i;
  for (i = 0; src && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}

/**
 * Находит первый символ в строке str1, который соответствует любому символу,
 * указанному в str2.
 * @param str строка подвергнутая поиску
 * @param str2 строка с набором символов для поиска
 * @return указатель на символ иначе s21_NULL
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  if ((str1 != s21_NULL) && (str2 != s21_NULL)) {
    while (*str1) {
      if (s21_strchr(str2, *str1)) {
        result = (char *)str1;
        break;
      }
      str1++;
    }
  }
  return result;
}

/**
 * Функция create_capsule создаёт и инициализирует начальное состояние капсулы
 * @return item, возвращаем ссылку на инициализированный экземпляр структуры
 * капсулы
 */
capsule *create_capsule() {
  capsule *item = (capsule *)malloc(sizeof(capsule));
  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 0;
  item->precision = -2;
  item->length = '\0';
  item->type = '\0';
  item->text = s21_NULL;
  item->variable = s21_NULL;
  item->str_end = s21_NULL;
  return item;
}

/**
 * Функция norm_func нормализует до промежутка -1 - 1 разницу чаров
 * @param i значенеие разницы исходное
 * @return result, возвращаем -1 при отрицательных 1 при положительных иначе
 * нуль
 */
int norm_func(int i) {
  int result = 0;
  if (i < 0) {
    result = -1;
  } else {
    if (i > 0) {
      result = 1;
    }
  }
  return result;
}

/**
 * Функция free_capsule очистки выделенной динамически памяти для нужд капсулы и
 * самой капсулы
 */
void free_capsule(capsule **item) {
  for (int i = 0; item[i]; i++) {
    if (item[i]->text) free(item[i]->text);
    if (item[i]->str_end) free(item[i]->str_end);
    free(item[i]);
  }
  free(item);
}

/**
 * Функция s21_sprintf отправляет форматированный вывод в строку, на которую
 * указывает str.
 * @param str указывает на строковый буфер, в который записывается результат
 * @param format указатель на строку, записанную в файловый поток
 * @param ... представляет другие параметры, такие как ширина, точность, длина и
 * спецификатор.
 * @return  в случае успеха функция возвращает количество символов,
 * записанных в буфер, за исключением завершающего нулевого символа. В случае
 * ошибки функция возвращает отрицательное целочисленное значение.
 */
int s21_sprintf(char *str, const char *format, ...) {
  int err = 1;
  if (format == s21_NULL || *format == '\0') {
    s21_strerror(6);
    err = -1;
  } else {
    char *format_temp = (char *)calloc(s21_strlen(format) + 5, sizeof(char));
    s21_strcpy(format_temp, format);
    char **mass = parsing(format_temp);
    if (mass) {
      capsule **strmass = pars_mass(mass);
      if (strmass[0]->type != '-') {
        va_list ap;
        va_start(ap, format);
        char *str_decoder = decoder(strmass, ap);
        if (str_decoder)
          s21_strcpy(str, str_decoder);
        else
          err = -1;
        va_end(ap);
        free_capsule(strmass);
        free(str_decoder);
      } else {
        err = -1;
        s21_strerror(6);
        free_capsule(strmass);
      }
      free(mass);
    } else {
      err = -1;
    }
    free(format_temp);
    if (err > 0) err = s21_strlen(str);
  }
  return err;
}

/**
 * Функция parsing возвращает массив указателей на разбитые строки по
 * спецификаторам
 * @param str Указатель на копию изначальной строки
 * @return istr, возвращаем ссылку на начало массива ссылок на места в строке
 */
char **parsing(char *str) {
  int row = s21_strlen(str) / 2 + 1;
  char **istr = (char **)calloc(row + 2, sizeof(char *));
  if (istr == s21_NULL) {
    s21_strerror(13);
    istr = s21_NULL;
  } else {
    if (*str != '%') istr[0] = str;
    for (int n = 1; *str != '\0'; str++) {
      if (*str == '%') {
        int end = 1;
        char *suf = s21_strpbrk((str + 1), SUFFIX);
        if (suf && *suf == '%') {
          if (*str) *str = '\0';
          istr[n++] = str + 1;
          suf = s21_strpbrk(suf, "%");
          str = suf;
          end = 0;
        }
        if (suf && end && *suf != '%') {
          if (*str) *str = '\0';
          istr[n++] = str + 1;
          suf = s21_strpbrk(suf, "%");
          if (suf)
            str = suf - 1;
          else
            str = &(str[s21_strlen(str) - 1]);
          end = 0;
        }
        if (!suf && end) {
          s21_strerror(6);
          free(istr);
          istr = s21_NULL;
        }
      }
    }
  }
  return istr;
}

/**
 * Функция pars_mass заполнения капсул спецификаторами и параметрами
 * @param istr массив указателей на места в строке
 * @return result, возвращаем указатель на сформированные капсулы
 */
capsule **pars_mass(char **istr) {
  int n = 1, err = 1;
  for (; istr[n++];) {
  }
  capsule **result = (capsule **)calloc(n-- + 3, sizeof(capsule *));
  for (int i = 0; i < n && err; i++) {
    result[i] = create_capsule();
    if (i > 0) {
      char *suf = s21_strpbrk(istr[i], SUFFIX);
      if (!suf) err = 0;
      for (int val = 0; err && val != -1; val++) {
        if (!s21_strchr(ALL, istr[i][val])) err = 0;
        if (&istr[i][val] == suf || istr[i][val] == '\0') val = -2;
      }
      if (err) {
        result[i]->type = *suf;
        *suf++ = '\0';
        if (suf && *suf != '\0')
          s21_strcpy(
              result[i]->text = calloc((s21_strlen(suf) + 1), sizeof(char)),
              suf);
        int len_spec = s21_strlen(istr[i]);
        if (len_spec > 0) {
          char *prec = s21_strpbrk(istr[i], ".");
          if (prec) {
            *prec = '\0', pars_elem_right(++prec, result[i]);
          } else {
            if (s21_strpbrk(LENGTH, &istr[i][len_spec - 1]))
              result[i]->length = istr[i][--len_spec], istr[i][len_spec] = '\0';
            char temp1[2] = {result[i]->type, '\0'};
            if (s21_strpbrk(PRECISION, temp1)) result[i]->precision = 6;
          }
          pars_elem_left(istr[i], result[i]);
          if (result[i]->type == '-') err = 0;
        } else {
          char temp1[2] = {result[i]->type, '\0'};
          if (s21_strpbrk(PRECISION, temp1)) result[i]->precision = 6;
        }
      }
    } else {
      if (istr[0] != s21_NULL)
        s21_strcpy(
            result[i]->text = calloc((s21_strlen(istr[0]) + 1), sizeof(char)),
            istr[0]);
    }
  }
  if (!err) result[0]->type = '-';
  return result;
}

/**
 * Функция pars_elem_left разбивает строку до точки с параметрами заполняя
 * капсулу
 * @param buff Указатель на строку параметров спецификатора
 * @param result Указатель на капсулу
 * @param len_spec длинна строки с параметрами
 */
void pars_elem_left(char *buff, capsule *result) {
  for (int ex = 1; ex;) switch (*(buff++)) {
      case '0':
        result->zero_printing = 1;
        break;
      case '-':
        result->alignment = 1;
        break;
      case '+':
        result->explicit_sign = 1;
        break;
      case ' ':
        result->space_with_no_sign = 1;
        break;
      case '#':
        result->full_writing = 1;
        break;
      default:
        ex = 0;
        buff--;
        break;
    }
  if (*buff == '*' && *(buff + 1) == '\0') {
    result->width = -1;
    buff++;
  } else {
    for (; *buff != '\0' && *buff >= '0' && *buff <= '9'; buff++)
      result->width = result->width * 10 + *buff - 48;
  }
  if (*buff != '\0') result->type = '-';
}

/**
 * Функция pars_elem_right разбивает строку с параметрами справа от точки
 * заполняя капсулу
 * @param buff Указатель на строку параметров спецификатора
 * @param result Указатель на капсулу, в которую сохраняются парамметры
 */
void pars_elem_right(char *buff, capsule *result) {
  result->precision = 0;
  if (s21_strlen(buff) > 0) {
    char temp[2] = {*(buff + 1), 0};
    if (*buff == '*' && (temp[0] == '\0' || s21_strpbrk(LENGTH, temp))) {
      result->precision = -1;
      buff++;
    } else {
      for (; *buff != '\0' && *buff >= '0' && *buff <= '9'; buff++)
        result->precision = result->precision * 10 + *buff - 48;
    }
    temp[0] = *buff;
    if (s21_strpbrk(LENGTH, temp)) result->length = *buff++;
    if (*buff != '\0') result->type = '-';
  }
}

/**
 * Функция decoder вызывает нужную функцию согласно спецификатора в капсуле,
 * получая назад преобразованный аргумент в строку
 * @param strmass Указатель массив капсул
 * @param ap Лист с аргументами
 * @return result, полностью собранную строку
 */
char *decoder(capsule **strmass, va_list ap) {
  char *result = calloc(8000, sizeof(char));
  for (int j = 0; strmass[j]; j++) {
    if (strmass[j]->width == -1) strmass[j]->width = va_arg(ap, int);
    if (strmass[j]->precision == -1) strmass[j]->precision = va_arg(ap, int);
    char ch[2] = {strmass[j]->type, 0};
    if (s21_strpbrk("idoXxu", ch)) ch[0] = 'i';
    if (s21_strpbrk("gGeEfF", ch)) ch[0] = 'f';
    switch (ch[0]) {
      case 'c': {
        char x = va_arg(ap, int);
        strmass[j]->variable = &x;
        type_c(strmass[j]);
        break;
      }
      case 'p': {
        void *p = va_arg(ap, void *);
        strmass[j]->variable = p;
        type_p(strmass[j]);
        break;
      }
      case 'i': {
        long long int lx = 0;
        type_d_temp(strmass[j], ap, &lx);
        break;
      }
      case 'f': {
        long double lx1 = 0;
        type_f_temp(strmass[j], ap, &lx1);
        break;
      }
      case 's': {
        char *x = va_arg(ap, char *);
        strmass[j]->variable = x;
        type_s(strmass[j]);
        break;
      }
      case 'n': {
        int *x1 = va_arg(ap, int *);
        *x1 = s21_strlen(result);
        break;
      }
      case '%': {
#ifdef OSX
        char x = '%';
        strmass[j]->variable = &x;
        type_c(strmass[j]);
#else
        strmass[j]->str_end = calloc(2, sizeof(char));
        s21_strcpy(strmass[j]->str_end, "%\0");
#endif
        break;
      }
    }

    if (strmass[j]->str_end != s21_NULL)
      s21_strcat(result, strmass[j]->str_end);
    if (strmass[j]->text != s21_NULL) s21_strcat(result, strmass[j]->text);
  }
  return result;
}

/**
 * Функция type_d_temp промежуточная функция для чтения из va_arg нужного типа
 * @param strmass Указатель на капсулу
 * @param ap Лист с аргументами
 * @param lx указатель на переменную тип void
 */
void type_d_temp(capsule *strmass, va_list ap, long long int *lx) {
  if (strmass->type == 'd' || strmass->type == 'i')
    *lx = (strmass->length == 'l') ? va_arg(ap, long int) : va_arg(ap, int);

  if (strmass->type == 'o' || strmass->type == 'X' || strmass->type == 'x' ||
      strmass->type == 'u') {
    *lx = (strmass->length == 'l')   ? va_arg(ap, unsigned long int)
          : (strmass->length == 'h') ? va_arg(ap, int)
                                     : va_arg(ap, unsigned int);
  }
  strmass->variable = lx;
  strmass->length = 'L';
  if (strmass->type == 'o') type_o(strmass);
  if (strmass->type == 'X') type_X(strmass);
  if (strmass->type == 'x') type_x(strmass);
  if (strmass->type == 'd' || strmass->type == 'i' || strmass->type == 'u')
    type_d(strmass);
}

/**
 * Функция type_f_temp промежуточная функция для чтения из va_arg нужного типа
 * @param strmass Указатель на капсулу
 * @param ap Лист с аргументами
 * @param lx указатель на переменную тип void
 */
void type_f_temp(capsule *strmass, va_list ap, long double *lx1) {
  *lx1 =
      (strmass->length == 'L') ? va_arg(ap, long double) : va_arg(ap, double);
  strmass->variable = lx1;
  strmass->length = 'L';
  if (strmass->type == 'f' || strmass->type == 'F') type_f(strmass);
  if (strmass->type == 'g') type_g(strmass);
  if (strmass->type == 'G') type_G(strmass);
  if (strmass->type == 'e') type_e(strmass);
  if (strmass->type == 'E') type_E(strmass);
}

/**
 * функция fabs_llint берет  модуль от числа
 * @param num число
 * @return long long int модуль числа
 */
long long int fabs_llint(long long int num) {
  if (num < 0) num = (-1) * num;
  return num;
}

/**
 * функция подготавливает строку, определяя нужные для нее параметры
 *
 * @param precision указатель на точность
 * @param width указатель на ширину
 * @param explicit_sign явное описание знака
 * @param space_with_no_sign пробел при положительных числах
 * @param zero_printing указатель на заполнение строки нулями вместо пробелов
 * @param p_width указатель на ширину, с которой работаем при ненулевой точности
 * @param nul указатель на оттсутвие точности (превращается в 0 для удобства
 * работы)
 * @param negative_number переменная определяющая является ли число
 * отрицательным
 * @param str указатель на строку с которой работаем
 * @return char* строка с которой работаем
 */
char *preparation_type_d(int *precision, int *width, int explicit_sign,
                         int space_with_no_sign, int *zero_printing,
                         int *p_width, int *nul, int negative_number,
                         char *str) {
  if (*precision == -2) {
    *precision = 0;
    *nul = 1;
  }
  if (*precision > 0) {
    *zero_printing = 1;
    *p_width = *width;
    *width = *precision;
    if (negative_number == 1) {
      *width = *width + 1;
      *p_width = *p_width - 1;
    }
  }
  if ((explicit_sign == 1) && (negative_number == 0)) {
    s21_strcat(str, "+");
    if (*precision > *p_width) {
      *width = *width + 1;
    } else {
      if (*precision > 0) {
        *width = *width + 1;
        *p_width = *p_width - 1;
      }
    }
  } else {
    if ((space_with_no_sign == 1) && (negative_number == 0))
      s21_strcat(str, " ");
  }
  return str;
}

/**
 * Функция type_d генерирует строку из целого числа,
 * согласно принятым из капсулы спецификаторам
 * @param caps Указатель на элемент из массива капсул
 */
void type_d(capsule *strmass) {
  long double a;
  char str_int[100];
  char str[100] = {0};
  char *str_fin = calloc(100, sizeof(char));
  int alignment, full_writing, explicit_sign, space_with_no_sign,
      al_tmp = 0, zero_printing, p_width = 0, nul = 0, precision, width = 0,
      pr_tmp = 0, negative_number = 0;
  read_capsule(strmass, &alignment, &precision, &full_writing, &width,
               &explicit_sign, &space_with_no_sign, &zero_printing, &a);
  long long int num = *((long long int *)(strmass->variable));
  if (strmass->type == 'i' || strmass->type == 'd') {
    if (strmass->length == 'h') num = (short int)num;
    if (strmass->length == 'l') num = (long int)num;
    if (strmass->length == '\0') num = (int)num;
  }
  if (strmass->type == 'u') {
    if (strmass->length == 'h') num = (unsigned short int)num;
    if (strmass->length == 'l') num = (unsigned long int)num;
    if (strmass->length == '\0') num = (unsigned int)num;
    explicit_sign = 0;
  }
  if (num < 0) negative_number = 1;
  preparation_type_d(&precision, &width, explicit_sign, space_with_no_sign,
                     &zero_printing, &p_width, &nul, negative_number, str);
  s21_int_to_str(str_int, num);
  s21_strcat(str, str_int);
  if ((num == 0) && (precision == 0) && (nul == 0)) s21_strcpy(str, "\0");
  al_tmp = alignment;
  pr_tmp = precision;
  if (precision <= log10(fabs_llint(num)))
    precision = (int)log10(fabs_llint(num)) + 1;
  if (pr_tmp > 0) alignment = 0;
  fit_to_width(str, width, zero_printing, alignment);
  if (pr_tmp > 0 && al_tmp == 1) alignment = 1;
  space_d(str_fin, str, p_width - precision, alignment);
  strmass->str_end = str_fin;
}

/**
 * Функция type_s вызывается для обработки спецификатора s (символ)
 * @param strmass Заполненная парсером капсула
 */
void type_s(capsule *strmass) {
  char *str_new, str[10000];
  s21_strcpy(str, (char *)strmass->variable);
  int length_str = 0;
  for (int i = 0; str[i] != '\0'; i++) length_str++;
  if (length_str <= strmass->width) {
    str_new = calloc(strmass->width + 1, sizeof(char));
    for (int i = 0; i < strmass->width; i++) str_new[i] = ' ';
    if (strmass->alignment == 1) {
      if (strmass->precision == -2) {
        for (int i = 0; i < length_str; i++) str_new[i] = str[i];
      } else {
        for (int i = 0; i < strmass->precision; i++) str_new[i] = str[i];
      }
    } else {
      int count = length_str, prec = strmass->precision;
      if (strmass->precision == -2) {
        for (int i = strmass->width - 1;
             i >= (strmass->width - 1) - length_str + 1; i--)
          str_new[i] = str[count - 1], count--;

      } else if (strmass->precision < length_str) {
        for (int i = strmass->width - 1;
             i >= (strmass->width - 1) - strmass->precision + 1; i--)
          str_new[i] = str[prec - 1], prec--;

      } else {
        for (int i = strmass->width - 1;
             i >= (strmass->width - 1) - length_str + 1; i--)
          str_new[i] = str[count - 1], count--;
      }
    }
  } else {
    if (strmass->precision == -2) {
      str_new = calloc(length_str + 1, sizeof(char));
      for (int i = 0; i < length_str; i++) str_new[i] = str[i];
    } else {
      str_new = calloc(strmass->precision + 1, sizeof(char));
      for (int i = 0; i < strmass->precision; i++) str_new[i] = str[i];
    }
  }
  strmass->str_end = calloc(s21_strlen(str_new) + 1, sizeof(char));
  for (int i = 0; str_new[i] != '\0'; i++) strmass->str_end[i] = str_new[i];
  free(str_new);
}

/**
 * Функция fit_to_width подгонки строки под требуемую ширину
 * @param str Строка для записи результата преобразования
 * @param width Значение ширины
 * @param zero_printing флаг заполенения нулями слева
 * @param alignment флаг выравнивания
 * @param space_with_no_sign флаг пробела для положительных чисел
 */
void fit_to_width(char *str, int width, int zero_printing, int alignment) {
  char filler[3], buffer[999] = {0}, spacer[9999];
  s21_strcat(buffer, str);
  int m = -1, d = 1;
  if ((*str == '0' && *(str + 1) == 'x') && zero_printing) {
    width -= 2, d++, m--;
    if (alignment == -3) width += 2;
  }
  if (alignment == -3) alignment = 0;
  if ((*str == '-' || *str == ' ' || *str == '+') && zero_printing)
    m = (int)(*str), width--;
  if (m != -1) s21_memmove(buffer, buffer + d, (int)s21_strlen(buffer));
  s21_strcpy(str, "");
  s21_strcpy(filler, "");
  if (alignment) zero_printing = 0;
  if (zero_printing && (s21_strchr(buffer, 'n') == s21_NULL))
    s21_strcat(filler, "0");
  else
    s21_strcat(filler, " ");
  s21_strcpy(spacer, "");
  if (width - (int)s21_strlen(buffer) > 0) {
    for (int i = 0; i < width - (int)s21_strlen(buffer); i++)
      s21_strcat(spacer, filler);
  }
  if (m == -2) {
    *filler = '0';
    *(filler + 1) = 'x';
    *(filler + 2) = '\0';
    s21_strcat(str, filler);
  } else {
    if (m != -1) {
      *filler = (char)m;
      s21_strcat(str, filler);
    }
  }
  if (alignment)
    s21_strcat(str, buffer), s21_strcat(str, spacer);
  else
    s21_strcat(str, spacer), s21_strcat(str, buffer);
}

/**
 * Функция int_part_of_float_to_str функция превращения части флоата в строку
 * @param dest Строка для записи результата преобразования
 * @param n Значение переменной с плавающей точкой
 * @param precision значение точности записи числа
 * @param explicit_sign флаг явности записи знака
 * @param space_with_no_sign флаг пробела для положительных чисел
 * @return dest возвращает отредактированную строку
 */
char *int_part_of_float_to_str(char *dest, long double n, int precision,
                               int explicit_sign, int space_with_no_sign) {
  long double num = n;
  int pow_of_ten = 1;
  if (precision == 0) {
    num = (long double)lrintl(num);
  }
  if (signbit(n)) {
    dest = s21_strcat(dest, "-");
    num = fabsl(num);
  } else {
    if (explicit_sign) {
      dest = s21_strcat(dest, "+");
    } else {
      if (space_with_no_sign) {
        dest = s21_strcat(dest, " ");
      }
    }
  }
  while ((long double)pow(10, pow_of_ten) <= num) {
    pow_of_ten++;
  }
  pow_of_ten--;
  while (pow_of_ten != -1) {
    char single_num = '0' + (int)(num / pow(10, pow_of_ten));
    char single_num_str[2] = {single_num, '\0'};
    dest = s21_strcat(dest, single_num_str);
    num = num - (s21_size_t)(num / pow(10, pow_of_ten)) * pow(10, pow_of_ten);
    pow_of_ten--;
  }
  return dest;
}
/**
 * Функция infnan_check проверка предельных значений
 * в короткие названия переменных удобных для работы
 * @param str Строка для записи результата проверки
 * @param n Значение переменной с плавающей точкой
 * @param explicit_sign флаг явности выражения знака
 * @param space_with_no_sign указатель флага пробела положительных чисел
 * @param zero_printing Указатель флага печати заполняющих нулей
 * @return flag, было ли значение предельным
 */
int infnan_check(char *str, long double n, int explicit_sign,
                 int *space_with_no_sign, int *zero_printing) {
  int flag = 1, osx = 0;
  char *pos = "01";
#ifdef OSX
  osx = 1;
#endif
  char limit[4] = {0};
  if (isinf(n)) {
    s21_strcat(limit, "inf");
    flag = 0;
  }
  if (isnan(n)) {
    s21_strcat(limit, "nan");
    flag = 0;
  }
  if (s21_strcmp(limit, "nan") || pos[osx] == '0') {
    if (!flag) {
      *zero_printing = 0, *space_with_no_sign = 0;
    }
    if (signbit(n) && !flag) {
      s21_strcat(str, "-");
    } else {
      if (explicit_sign && !flag) {
        s21_strcat(str, "+");
      } else {
        if (space_with_no_sign && !flag) {
          s21_strcat(str, " ");
        } else {
          s21_strcat(str, "");
        }
      }
    }
  }
  s21_strcat(str, limit);
  return flag;
}

/**
 * Функция read_capsule передаёт значения из капсулы
 * в короткие названия переменных удобных для работы
 * @param caps Указатель на элемент из массива капсул
 * @param alignment Указатель на выравнивание
 * @param precision Указатель на точность
 * @param full_writing Указатель на необходимость точки
 * @param width Указатель на ширину
 * @param explicit_sign Указатель на явное написание знака
 * @param space_with_no_sign Указатель на пробел положительных чисел
 * @param zero_printing Указатель на заполенение строки нулями
 * @param a Указатель на обрабатываемое число
 */
void read_capsule(capsule *caps, int *alignment, int *precision,
                  int *full_writing, int *width, int *explicit_sign,
                  int *space_with_no_sign, int *zero_printing, long double *a) {
  *alignment = caps->alignment;
  *full_writing = caps->full_writing;
  *width = caps->width;
  *explicit_sign = caps->explicit_sign;
  *space_with_no_sign = caps->space_with_no_sign;
  *zero_printing = caps->zero_printing;
  *precision = caps->precision;
  if (caps->length == '\0' && caps->type != 'v') {
    *a = (long double)(*((double *)(caps->variable)));
  } else {
    *a = *((long double *)(caps->variable));
  }
}

/**
 * просто функция для выноса части расчётов в другой модуль
 * @param str Указатель на финальную строку обработки
 * @param first_part Указатель на строку целой части флоата
 * @param second_part Остаток дробной части флоата
 * @param mult разрядность дробной части флоата
 * @param precision требуемая точность
 * @param full_writing необходимость точки при печати целой части
 */
void cut_part(char *str, char *first_part, long double second_part,
              s21_size_t precision, int full_writing) {
  s21_size_t p = precision;
  if (p == 0) {
    s21_strcat(str, first_part);
    if (full_writing) {
      s21_strcat(str, ".");
    }
  } else {
    s21_strcat(str, first_part);
    s21_strcat(str, ".");
    if (p < 17) {
      long long to_converting;
      to_converting = lrintl(second_part * pow(10, p));
      to_converting = to_converting % (long long)pow(10, p);
      char result[200];
      s21_int_to_str(result, to_converting);
      fit_to_width(result, p, 1, 0);
      s21_strcat(str, result);
    } else {
      while (p >= 1) {
        second_part *= 10;
        char single_num = '0' + (int)(second_part);
        char single_num_str[2] = {single_num, '\0'};
        s21_strcat(str, single_num_str);
        second_part = second_part - (int)second_part;
        p--;
      }
    }
  }
}

/**
 * функция для очистки незначащих нулей в строчном представлении числа
 * @param str Указатель на финальную строку обработки
 */
void clear_zeros(char *str) {
  int i = s21_strlen(str) - 1;
  int flag = 0;
  for (int j = 0; j <= i; j++) {
    if (str[j] == '.') flag++;
  }
  if (flag) {
    while (str[i] == '0' || str[i] == '.') {
      if (str[i] == '.') {
        str[i] = '\0';
        break;
      } else {
        str[i] = '\0';
        i--;
      }
    }
  }
}

/**
 * Функция type_f генерирует строку с из числа с плавающей точкой,
 * согласно принятым из капсулы спецификаторам
 * @param caps Указатель на элемент из массива капсул
 */
void type_f(capsule *caps) {
  long double a;
  char *str = calloc(100, sizeof(char));
  int alignment, full_writing, explicit_sign, space_with_no_sign, zero_printing,
      precision, width;
  read_capsule(caps, &alignment, &precision, &full_writing, &width,
               &explicit_sign, &space_with_no_sign, &zero_printing, &a);
  if (infnan_check(str, a, explicit_sign, &space_with_no_sign,
                   &zero_printing)) {
    char first_part[50] = {0};
    int_part_of_float_to_str(first_part, a, precision, explicit_sign,
                             space_with_no_sign);
    long double second_part = fabsl(fmodl(a, 1.0));
    cut_part(str, first_part, second_part, precision, full_writing);
  }
  if (caps->type == 'z' && caps->full_writing == 0) {
    clear_zeros(str);
  }
  if (caps->type != 'v') fit_to_width(str, width, zero_printing, alignment);
  caps->str_end = str;
}
/**
 * Функция type_F приводит type_f в верхний регистр
 * @param strmass указатель на содержащую капсулу
 */
void type_F(capsule *strmass) {
  type_f(strmass);
  s21_to_upper_first(strmass->str_end);
}

/**
 * функция доставляет пробелы в начало строки
 *
 * @param str1 незаполненная начальная строка
 * @param str2 строка, перед которой ставятся пробелы
 * @param spaces количество пробелов
 * @param alignment параметр, который определяет
 * с какой стороны добавлять пробелы (выравнивание)
 * @return char* конечная строка с пробелами
 */
char *space_d(char *str1, char *str2, int spaces, int alignment) {
  if (spaces < 0) spaces = 0;
  if (alignment == 0) {
    while (spaces != 0) {
      s21_strcat(str1, " ");
      spaces--;
    }
    s21_strcat(str1, str2);
  } else {
    s21_strcat(str1, str2);
    while (spaces != 0) {
      s21_strcat(str1, " ");
      spaces--;
    }
  }
  return str1;
}

/**
 * Функция type_c вызывается для обработки спецификатора с (символ)
 * @param strmass Заполненная парсером капсула
 */
void type_c(capsule *strmass) {
  char *str_new = calloc(strmass->width + 2, sizeof(char));
  char *symb = (char *)strmass->variable;
  if (strmass->width > 1) {
    for (int i = 0; i < strmass->width; i++) str_new[i] = ' ';
    if (strmass->alignment == 1)
      str_new[0] = *symb;
    else
      str_new[strmass->width - 1] = *symb;
  } else {
    *str_new = *symb;
  }
  strmass->str_end = str_new;
}

/**
 * функция сдвигает код символа так, что все буквы верхнего
 * регистра латинского алфавита переходят в нижний
 * @param symb код символа
 * @return int возвращаемое значение
 */
int tolower21(int symb) {
  if (symb >= 65 && symb <= 90) {
    symb = symb + 32;
  }
  return symb;
}
/**
 * функция сдвигает код символа так, что все буквы нижнего
 * регистра латинского алфавита переходят в верхний
 * @param symb код символа
 * @return int возвращаемое значение
 */
int toupper21(int symb) {
  if (symb >= 90 && symb <= 122) {
    symb = symb - 32;
  }
  return symb;
}

/**
 * Функция s21_to_lower возвращает новую строку,
 * в которой все символы из вернего регистра переходят в нижний
 * @param p исходная строка
 * @return str новая строка, полученная после преобразования
 */
void *s21_to_lower(const char *p) {
  char *str;
  void *res = s21_NULL;
  if (p != s21_NULL) {
    str = calloc(s21_strlen(p) + 1, sizeof(char));
    s21_strcpy(str, p);
    for (int i = 0; str[i]; i++) {
      str[i] = tolower21(str[i]);
    }
    res = str;
  }
  return res;
}

/**
 * Функция s21_to_upper возвращает новую строку,
 * в которой все символы из нижнего регистра переходят в верхний
 * @param p исходная строка
 * @return str новая строка, полученная после преобразования
 */
void *s21_to_upper(const char *p) {
  char *str;
  void *res = s21_NULL;
  if (p != s21_NULL) {
    str = calloc(s21_strlen(p) + 1, sizeof(char));
    s21_strcpy(str, p);
    for (int i = 0; str[i]; i++) {
      str[i] = toupper21(str[i]);
    }
    res = str;
  }
  return res;
}

/**
 * Функция s21_to_upper_first возвращает новую строку,
 * в которой все символы из нижнего регистра переходят в верхний
 * @param p исходная строка
 * @return str новая строка, полученная после преобразования
 */

void *s21_to_upper_first(const char *p) {
  char *str = (char *)p;
  for (int i = 0; str[i]; i++) {
    str[i] = toupper21(str[i]);
  }
  return (void *)p;
}

/**
 * Функция s21_trim возвращает новую строку, в которой удаляются все начальные и
 * конечные вхождения набора заданных символов
 * @param src Исходная строка
 * @param trim_chars Набр символов для удаления
 * @return res Новая строка, полученная после удаления, или NULL при ошибке
 */
void *s21_trim(const char *src, const char *trim_chars) {
  int n = s21_strlen(src);
  char *trim_string;
  void *res;
  if (n > 0 && s21_strlen(trim_chars) > 0) {
    trim_string = calloc(s21_strlen(src) + 1, sizeof(char));
    int beg = 0;
    int end = 0;
    for (int i = 0; i < n; i++) {
      if (s21_strchr(trim_chars, (int)src[i]) != s21_NULL)
        beg++;
      else
        break;
    }
    for (int i = n - 1; i >= 0; i--) {
      if (s21_strchr(trim_chars, (int)src[i]) != s21_NULL)
        end++;
      else
        break;
    }
    int res_size;
    if (beg == end && beg == 0) {
      s21_strcpy(trim_string, src);
    }
    if (beg == end && beg == n) {
      s21_strcpy(trim_string, "");
    }
    if (beg + end > n) {
      res_size = n - end;
      s21_strncpy(trim_string, &src[beg], res_size);
    } else {
      res_size = n - beg - end;
      s21_strncpy(trim_string, &src[beg], res_size);
    }
    res = trim_string;
  } else {
    res = s21_NULL;
  }
  return res;
}

/**
 * Функция s21_insert возвращает войд указатель на строку,
 * полученную в результате вставки одной строки в другую
 * @param src указатель на подвергаемую вставке строку
 * @param str указатель на внедряемую строку
 * @param start_index индекс размещения внедряемой строки в теле пациента
 */
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *double_concatenation;
  void *result;
  if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src)) {
    str = s21_NULL;
    result = s21_NULL;
  } else {
    double_concatenation =
        calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    s21_strcat(double_concatenation, "");
    s21_strncpy(double_concatenation, src, start_index);
    double_concatenation[start_index] = '\0';
    s21_strcat(double_concatenation, str);
    s21_strcat(double_concatenation, src + start_index);
    result = double_concatenation;
  }
  return result;
}

/**
 * Функция type_e перенаправляет печать научной натации в режим
 * печати с параметром строчной буквы 'e' перед мантисой
 * @param strmass указатель на содержащую капсулу
 */
void type_e(capsule *strmass) {
  int flag = 0;
  if (strmass->type == 'z') flag++;
  strmass->type = 'v';
  char *strTemp = calloc(100, sizeof(char));
  long double m = 0;
  static long double a;
  if (strmass->length == 'L') {
    a = *((long double *)(strmass->variable));
  } else {
    a = (long double)(*((double *)(strmass->variable)));
  }
  if (infnan_check(strTemp, a, strmass->explicit_sign,
                   &(strmass->space_with_no_sign), &(strmass->zero_printing))) {
    char *exp = "e", str[100] = {0};
    free(strTemp);
    Pow(&a, &m);
    strmass->variable = &a;
    type_f(strmass);
    if (flag) {
      clear_zeros(strmass->str_end);
    }
    s21_strcat(strmass->str_end, exp);
    s21_sprintf(str, "%+03.Lf", m);
    s21_strcat(strmass->str_end, str);
  } else {
    strmass->str_end = strTemp;
  }
  fit_to_width(strmass->str_end, strmass->width, strmass->zero_printing,
               strmass->alignment);
}

/**
 * Функция type_E приводит type_e в верхний регистр
 * @param strmass указатель на содержащую капсулу
 */
void type_E(capsule *strmass) {
  type_e(strmass);
  s21_to_upper_first(strmass->str_end);
}

/**
 * Функция Pow определяетс в переменную m степень научной нотации
 * приводя число a к нужному диапазону
 * @param a указатель на печатаемое число
 * @param m указатель на степень числа a
 */
void Pow(long double *a, long double *m) {
  if (fabsl(*a) < 1 && fabsl(*a) != 0.0) {
    while (fabsl(*a) < 1) {
      (*m)--;
      *a *= 10;
    }
  } else {
    while (fabsl(*a) > 10) {
      (*m)++;
      *a /= 10;
    }
  }
}

/**
 * Функция type_G приводит type_g в верхний регистр
 * @param strmass указатель на содержащую капсулу
 */
void type_G(capsule *strmass) {
  type_g(strmass);
  s21_to_upper_first(strmass->str_end);
}

/**
 * Функция type_g вызывается для обработки спецификатора g
 * печать кратчайшего представления флоата
 * @param strmass указатель на содержащую капсулу
 */
void type_g(capsule *strmass) {
  long double m = 0;
  long double a;
  if (strmass->length == 'L') {
    a = *((long double *)(strmass->variable));
  } else {
    a = (long double)(*((double *)(strmass->variable)));
  }
  Pow(&a, &m);
  strmass->type = 'z';
  if (strmass->precision == 0) strmass->precision = 1;
  if (m >= -4 && m < strmass->precision) {
    strmass->precision = strmass->precision - (m + 1);
    type_f(strmass);
  } else {
    strmass->precision = strmass->precision - 1;
    type_e(strmass);
  }
}

/**
 * Функция type_x вызывается для обработки спецификатора
 * печать числа в 16-ти ричной системой счисления (строчное)
 * @param strmass указатель на содержащую капсулу
 */
void type_x(capsule *strmass) {
  long double a;
  int alignment, full_writing, explicit_sign, space_with_no_sign, zero_printing;
  int precision, width;
  strmass->str_end = malloc(100 * sizeof(char));
  s21_strcpy(strmass->str_end, "");
  read_capsule(strmass, &alignment, &precision, &full_writing, &width,
               &explicit_sign, &space_with_no_sign, &zero_printing, &a);
  long long int num = *(long long int *)(strmass->variable);
  if (full_writing) {
    s21_strcat(strmass->str_end, "0x");
  }
  hex_oct(strmass->str_end, num, 16);
  fit_to_width(strmass->str_end, precision, 1, -3);
  fit_to_width(strmass->str_end, width, zero_printing, alignment);
}

/**
 * Функция type_X вызывается для обработки спецификатора
 * печать числа в 16-ти ричной системой счисления (прописные)
 * @param strmass указатель на содержащую капсулу
 */
void type_X(capsule *strmass) {
  type_x(strmass);
  s21_to_upper_first(strmass->str_end);
}

/**
 * Функция type_o вызывается для обработки спецификатора
 * печать числа в 8-ти ричной системой счисления (прописные)
 * @param strmass указатель на содержащую капсулу
 */
void type_o(capsule *strmass) {
  long double a;
  int alignment, full_writing, explicit_sign, space_with_no_sign, zero_printing;
  int precision, width;
  strmass->str_end = malloc(100 * sizeof(char));
  s21_strcpy(strmass->str_end, "");
  read_capsule(strmass, &alignment, &precision, &full_writing, &width,
               &explicit_sign, &space_with_no_sign, &zero_printing, &a);
  long long int num = *(long long int *)(strmass->variable);
  if (full_writing) {
    s21_strcat(strmass->str_end, "0");
  }
  hex_oct(strmass->str_end, num, 8);
  fit_to_width(strmass->str_end, precision, 1, 0);
  fit_to_width(strmass->str_end, width, zero_printing, alignment);
}

/**
 * Функция char_of_hex возвращает символ числа в сновании до 16
 * @param n число
 * @return символ переданного числа
 */
char char_of_hex(long long int n) {
  int result;
  if (n >= 10) {
    result = 'a' - 10;
  } else {
    result = '0';
  }
  return result + (int)n;
}

/**
 * Функция hex_oct возвращает строку конвертированого числа
 * по выбранной базе системы счисления
 * @param r_str строка результатов
 * @param num число конвертации
 * @param base база системы счисления
 */
void hex_oct(char *r_str, long long int num, int base) {
  char str[999] = {0}, temp[2];
  int start_len = s21_strlen(r_str);
  temp[1] = '\0';
  while (num >= base) {
    temp[0] = char_of_hex(num % base);
    s21_strcat(str, temp);
    num = num / base;
  }
  temp[0] = char_of_hex(num);
  s21_strcat(str, temp);
  for (int i = s21_strlen(str) - 1; i >= 0; i--) {
    temp[0] = str[i];
    s21_strcat(r_str, temp);
  }
  r_str[s21_strlen(str) + start_len] = '\0';
}

/**
 * Функция type_p вызывается для обработки спецификатора
 * печать адреса указателя в 16-ти ричной системой счисления
 * @param strmass указатель на содержащую капсулу
 */
void type_p(capsule *strmass) {
  long long int a = (long long int)(strmass->variable);
  strmass->variable = &a;
  strmass->full_writing = 1;
  type_x(strmass);
  strmass->variable = s21_NULL;
}
