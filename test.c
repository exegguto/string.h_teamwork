#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

// Тест для функции s21_memcmp
START_TEST(test_s21_memcmp) {
  char str1[15] = "Hello world";
  char str2[15] = "Hello world\n";
  char str3[15] = "a\n";
  char str4[15] = " \n";
  char str5[15] = " ";
  char str6[15] = "\n";
  char str7[15] = "";
  // строки одинаковы
  ck_assert_int_eq(norm_func(s21_memcmp(str1, str2, 10)),
                   norm_func(memcmp(str1, str2, 10)));
  // строки отличаются
  ck_assert_int_eq(norm_func(s21_memcmp(str1, str2, 12)),
                   norm_func(memcmp(str1, str2, 12)));
  // количество байт для сравнения равно 0
  ck_assert_int_eq(norm_func(s21_memcmp(str1, str2, 0)),
                   norm_func(memcmp(str1, str2, 0)));
  // сравнивается только первый байт
  ck_assert_int_eq(norm_func(s21_memcmp(str1, str2, 1)),
                   norm_func(memcmp(str1, str2, 1)));
  // строка, состоящая из пробела
  ck_assert_int_eq(norm_func(s21_memcmp(str4, str5, 1)),
                   norm_func(memcmp(str4, str5, 1)));
  // пустая строка
  ck_assert_int_eq(norm_func(s21_memcmp(str3, str7, 2)),
                   norm_func(memcmp(str3, str7, 2)));
  // две пустые строки
  ck_assert_int_eq(norm_func(s21_memcmp(str6, str7, 1)),
                   norm_func(memcmp(str6, str7, 1)));
}
END_TEST

// Tест для функции s21_strncat
START_TEST(test_s21_strncat) {
  char s21_dst[50] =
      "Hello world\n";  // Начальная строка для работы s21_strncat
  char dst[50] = "Hello world\n";  // Начальная строка для работы strncat
  char str[15] = "New string";  // Строка для добавления
  char s21_dst2[50] = "";  // Пустая начальная строка для работы s21_strncat
  char dst2[50] = "";  // Пустая начальная строка для работы strncat
  char s21_dst3[50] = " ";  // Начальная строка-пробел для работы s21_strncat
  char dst3[50] = " ";  // Начальная строка-пробел для работы strncat
  // n равно длине добавляемой строки
  s21_strncat(s21_dst, str, 12);
  strncat(dst, str, 12);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n = strlen(src) test failed");
  // n меньше длины добавляемой строки
  s21_strncat(s21_dst, str, 1);
  strncat(dst, str, 1);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n < strlen(src) test failed");
  // n больше длины добавляемой строки
  s21_strncat(s21_dst, str, 20);
  strncat(dst, str, 20);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n > strlen(src) test failed");
  // n == 0
  s21_strncat(s21_dst, str, 0);
  strncat(dst, str, 0);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n == 0 test failed");
  // добавляем пустую строку
  s21_strncat(s21_dst, "", 12);
  strncat(dst, "", 12);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "src is empty test failed");
  // добавляем к пустой строке
  s21_strncat(s21_dst2, str, 12);
  strncat(dst2, str, 12);
  ck_assert_msg(strcmp(s21_dst2, dst2) == 0, "dst is empty test failed");
  // добавляем к пробелу
  s21_strncat(s21_dst3, str, 12);
  strncat(dst3, str, 12);
  ck_assert_msg(strcmp(s21_dst3, dst3) == 0, "dst is a space test failed");
}
END_TEST

// Tест для функции s21_strncpy
START_TEST(test_s21_strncpy) {
  char s21_dst[50] = "";  // Начальная строка для работы s21_strncpy
  char dst[50] = "";  // Начальная строка для работы strncpy
  // Строки для копирования
  char str1[15] = "Hello world";
  // unsigned char str2[15] = "Hello world\n";
  char str3[15] = "a\n";
  char str4[15] = " \n";
  char str5[15] = " ";
  char str6[15] = "\n";
  char str7[15] = "";
  // n равно длине копируемой строки
  s21_strncpy(s21_dst, str1, 11);
  strncpy(dst, str1, 11);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n = strlen(src) test failed");
  // n меньше длины копируемой строки
  s21_strncpy(s21_dst, str1, 5);
  strncpy(dst, str1, 5);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n < strlen(src) test failed");
  // n больше длины копируемой строки
  s21_strncpy(s21_dst, str1, 20);
  strncpy(dst, str1, 20);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n > strlen(src) test failed");
  // n == 0
  s21_strncpy(s21_dst, str1, 0);
  strncpy(dst, str1, 0);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "n == 0 test failed");
  // копируем короткую строку
  s21_strncpy(s21_dst, str3, 5);
  strncpy(dst, str3, 5);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "short string test failed");
  // копируем пробел
  s21_strncpy(s21_dst, str4, 5);
  strncpy(dst, str4, 5);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "space\n test failed");
  s21_strncpy(s21_dst, str5, 5);
  strncpy(dst, str5, 5);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "space test failed");
  // копируем перенос строки
  s21_strncpy(s21_dst, str6, 5);
  strncpy(dst, str6, 5);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "enter test failed");
  // копируем пустую строку
  s21_strncpy(s21_dst, str7, 5);
  strncpy(dst, str7, 5);
  ck_assert_msg(strcmp(s21_dst, dst) == 0, "empty string test failed");
}
END_TEST

// Tест для функции s21_strrchr
START_TEST(test_s21_strrchr) {
  char str[100] =
      "We know what we are, but know not what we may be.";  // строка для поиска
  char str2[50] = "";
  // поик повторяющейся буквы (w)
  ck_assert_msg(s21_strrchr(str, 119) == strrchr(str, 119),
                "repeated letter test failed");
  // поиск буквы, отсутствующей в строке (c)
  ck_assert_msg(s21_strrchr(str, 99) == strrchr(str, 99),
                "missing letter test failed");
  // поиск символа с кодом 0
  ck_assert_msg(s21_strrchr(str, 0) == strrchr(str, 0),
                "\\0 symbol test failed");
  // поиск символа в пустой строке
  ck_assert_msg(s21_strrchr(str2, 99) == strrchr(str2, 99),
                "rempty string test failed");
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(test_s21_memmove) {
  /* Исходный код теста. */
  char *str = "Why_is_it_so_fucking_hard???";
  int length = s21_strlen(str);

  char s1[30];
  char s2[30];
  char s3[30];
  char s4[30];
  char s5[30];
  char s6[30];
  char s7[50] = "Why_is_it_so_fucking_hard???";
  char s8[50] = "Why_is_it_so_fucking_hard???";
  char s9[50] = "Why_is_it_so_fucking_hard???";
  char s10[50] = "Why_is_it_so_fucking_hard???";

  s21_memmove(s1, str, length);
  memmove(s2, str, length);

  s21_memmove(s3, str, 7);
  memmove(s4, str, 7);

  s21_memmove(s5, str, 0);
  memmove(s6, str, 0);

  s21_memmove(s7 + 1, s7 + 5, length - 5);
  memmove(s8 + 1, s8 + 5, length - 5);

  s21_memmove(s9 + 5, s9, length - 5);
  memmove(s10 + 5, s10, length - 5);

  ck_assert_msg(memcmp(s1, s2, length) == 0,
                "Overvolumed memmove test failed.");
  ck_assert_msg(memcmp(s3, s4, 7) == 0, "Standart memmove test failed.");
  ck_assert_msg(memcmp(s5, s6, 0) == 0, "Zero memmove test failed.");
  ck_assert_msg(memcmp(s7, s8, length - 5) == 0,
                "Left-overlay memmove test failed.");
  ck_assert_msg(memcmp(s9, s10, length) == 0,
                "Right-overlay memmove test failed.");
}
END_TEST

START_TEST(test_s21_strcmp) {
  /* Исходный код теста. */
  char s1[30] = "Why_is_it_so_fucking_hard???";
  char s2[30] = "Why_is_it_so_fucking_hard???";
  char s3[30] = "W";
  char s4[30] = "w";
  char s5[30] = "w";
  char s6[30] = "W";
  char s7[50] = "sdfgdslh\n";
  char s8[50] = "sdfgdslh";
  char s9[50] = "";
  char s10[50] = "";

  ck_assert_int_eq(norm_func(s21_strcmp(s1, s2)), norm_func(strcmp(s1, s2)));
  ck_assert_int_eq(norm_func(s21_strcmp(s3, s4)), norm_func(strcmp(s3, s4)));
  ck_assert_int_eq(norm_func(s21_strcmp(s5, s6)), norm_func(strcmp(s5, s6)));
  ck_assert_int_eq(norm_func(s21_strcmp(s7, s8)), norm_func(strcmp(s7, s8)));
  ck_assert_int_eq(norm_func(s21_strcmp(s9, s10)), norm_func(strcmp(s9, s10)));
  ck_assert_int_eq(s21_strcmp(s1, s2), strcmp(s1, s2));
  ck_assert_int_eq(strcmp(s3, s4), strcmp(s3, s4));
  ck_assert_int_eq(strcmp(s5, s6), strcmp(s5, s6));
  ck_assert_int_eq(strcmp(s7, s8), strcmp(s7, s8));
  ck_assert_int_eq(strcmp(s9, s10), strcmp(s9, s10));
}
END_TEST

START_TEST(test_s21_strstr) {
  /* Исходный код теста. */
  char *str1 = "Why_is_it_so_fucking_hard???";
  char *str2 = "fucking";
  char *str3 = "";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2),
                "1 strstr test failed");
  ck_assert_msg(s21_strstr(str1, str3) == strstr(str1, str3),
                "2 strstr test failed");
  ck_assert_msg(s21_strstr(str3, str2) == strstr(str3, str2),
                "3 strstr test failed");
  ck_assert_msg(s21_strstr(str2, str3) == strstr(str2, str3),
                "4 strstr test failed");
  ck_assert_msg(s21_strstr(str3, str1) == strstr(str3, str1),
                "5 strstr test failed");
}
END_TEST

START_TEST(test_s21_strerror) {
  /* Исходный код теста. */
  for (int i = 0; i < 10; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
#ifdef OSX
  ck_assert_str_eq(s21_strerror(1337), "Unknown error: 1337");
#endif
#ifndef OSX
  ck_assert_str_eq(s21_strerror(1337), "Unknown error 1337");
#endif
}
END_TEST

START_TEST(test_s21_memcpy) {
  /* Исходный код теста. */
  char str_1[10] = "AmAm";
  char str_2[10] = "AvAv";
  char str_3[10] = "AmAm";
  char str_4[10] = "AvAv";
  char str_5[10] = "";
  char str_6[10] = "yo";
  memcpy(str_1, str_2, 4);
  s21_memcpy(str_3, str_4, 4);

  ck_assert_msg(memcpy(str_1, str_2, 4) != s21_memcpy(str_3, str_4, 4),
                "1 s21_memcpy test failed");
  ck_assert_msg(memcpy(str_1, str_3, 4) != s21_memcpy(str_2, str_4, 4),
                "2 s21_memcpy test failed");
  ck_assert_msg(memcpy(str_5, str_6, 4) == s21_memcpy(str_5, str_6, 4),
                "3 s21_memcpy test failed");
}
END_TEST

START_TEST(test_s21_strchr) {
  /* Исходный код теста. */
  char str_1[10] = "AmAm";
  char str_2[10] = "AvAv";
  char str_3[10] = "AloALOOOOO";
  char str_4[10] = "GAVgAv";

  ck_assert_msg(strchr(str_1, 3) == s21_strchr(str_1, 3),
                "1 s21_strchr test failed");
  ck_assert_msg(strchr(str_2, 1) == s21_strchr(str_2, 1),
                "2 s21_strchr test failed");
  ck_assert_msg(strchr(str_3, 'o') == s21_strchr(str_3, 'o'),
                "3 s21_strchr test failed");
  ck_assert_msg(strchr(str_4, 5) == s21_strchr(str_4, 5),
                "4 s21_strchr test failed");
}
END_TEST

START_TEST(test_s21_strcspn) {
  /* Исходный код теста. */
  char str_1[10] = "AmAm";
  char str_2[10] = "AvAv";
  char str_3[10] = "AloALOOOOO";
  char str_4[10] = "GAVgAv";

  ck_assert_msg(strcspn(str_1, str_2) == s21_strcspn(str_1, str_2),
                "1 s21_strcspn test failed");
  ck_assert_msg(strcspn(str_1, str_3) == s21_strcspn(str_1, str_3),
                "2 s21_strcspn test failed");
  ck_assert_msg(strcspn(str_1, str_4) == s21_strcspn(str_1, str_4),
                "3 s21_strcspn test failed");
  ck_assert_msg(strcspn(str_2, str_4) == s21_strcspn(str_2, str_4),
                "4 s21_strcspn test failed");
}
END_TEST

START_TEST(test_s21_strspn) {
  /* Исходный код теста. */
  char str_1[10] = "AmAm";
  char str_2[10] = "AmAmAvAv";
  char str_3[20] = "AloALOOOOOAmAmAv";
  char str_4[20] = "GAVgAvAvAmAm";

  ck_assert_msg(strspn(str_1, str_2) == s21_strspn(str_1, str_2),
                "1 s21_strspn test failed");
  ck_assert_msg(strspn(str_1, str_3) == s21_strspn(str_1, str_3),
                "2 s21_strspn test failed");
  ck_assert_msg(strspn(str_1, str_4) == s21_strspn(str_1, str_4),
                "3 s21_strspn test failed");
  ck_assert_msg(strspn(str_2, str_4) == s21_strspn(str_2, str_4),
                "4 s21_strspn test failed");
}
END_TEST

START_TEST(test_s21_memset) {
  char test1[] = "Qwerty uiop123456\0";
  char test3[] = "Qwe\0";
  char test5[] = "\n\0";
  char test6[] = "\0";
  char test7[] = "6\0";
  char origin1[] = "Qwerty uiop123456\0";
  char origin3[] = "Qwe\0";
  char origin5[] = "\n\0";
  char origin6[] = "\0";
  char origin7[] = "6\0";

  ck_assert_str_eq(s21_memset(test1, '-', 4), memset(origin1, '-', 4));
  ck_assert_str_eq(s21_memset(test3, '\0', sizeof(test3)),
                   memset(origin3, '\0', sizeof(origin3)));
  ck_assert_str_eq(s21_memset(test5, '-', 2), memset(origin5, '-', 2));
  ck_assert_str_eq(s21_memset(test6, '-', 1), memset(origin6, '-', 1));
  ck_assert_str_eq(s21_memset(test7, '-', 1), memset(origin7, '-', 1));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char test9[] = "Qwerty uiop123456\0";
  char test10[] = "Qwerty\0";
  char test2[] = "Qwerty uiop123456 Qwerty uiop123456\0";
  char test3[] = "Qwe\0";
  char test4[] = "Qwerty Qwerty\0";
  char test5[] = "\n\0";

  ck_assert_int_eq(s21_strncmp(test9, test10, 4), strncmp(test9, test10, 4));
  ck_assert_int_eq(s21_strncmp(test2, test10, 4), strncmp(test2, test10, 4));
  ck_assert_int_eq(s21_strncmp(test3, test10, 3), strncmp(test3, test10, 3));
  ck_assert_msg(
      (s21_strncmp(test4, test10, 6) < 0) == (strncmp(test4, test10, 6) < 0),
      "s21_strncmp test4 failed");
  ck_assert_msg(
      (s21_strncmp(test5, test10, 1) > 0) == (strncmp(test5, test10, 1) > 0),
      "s21_strncmp test5 failed");

  char *t3 = "A";
  char *t4 = "";
  ck_assert_int_eq(s21_strncmp(t3, t4, 0), strncmp(t3, t4, 0));
  ck_assert_msg(s21_strncmp(t3, t4, 1) > 0 && strncmp(t3, t4, 1) > 0,
                "s21_strncmp test7 failed");
}
END_TEST

START_TEST(test_s21_strlen) {
  char test1[] = "Qwerty uiop123456\0";
  char test3[] = "Qwe\0";
  char test4[] = "Qwerty Qwerty\0";
  char test5[] = "\n\0";
  char test6[] = "\0";
  ck_assert_int_eq(s21_strlen(test1), strlen(test1));
  ck_assert_int_eq(s21_strlen(test3), strlen(test3));
  ck_assert_int_eq(s21_strlen(test4), strlen(test4));
  ck_assert_int_eq(s21_strlen(test5), strlen(test5));
  ck_assert_int_eq(s21_strlen(test6), strlen(test6));
}
END_TEST

START_TEST(test_s21_strtok) {
  char test1[] = "Qwerty uiop123456\0";
  char test5[] = "\n\0";
  char test8[] = "Qwe\0";
  char test99[] = "w%%123%%%%%%456%789%%%%\0";
  char origin1[] = "Qwerty uiop123456\0";
  char origin5[] = "\n\0";
  char origin8[] = "Qwe\0";
  char origin99[] = "w%%123%%%456%789\0";
  ck_assert_str_eq(s21_strtok(test1, " "), strtok(origin1, " "));
  ck_assert_str_eq(s21_strtok(test1, "b"), strtok(origin1, "b"));
  ck_assert_str_eq(s21_strtok(test8, " "), strtok(origin8, " "));
  ck_assert_str_eq(s21_strtok(test5, " "), strtok(origin5, " "));

  char *temp2[9999];
  int i = 0;
  temp2[0] = s21_strtok(test99, "%");

  while (temp2[i] != s21_NULL) temp2[++i] = s21_strtok(s21_NULL, "%");
  i = 0;
  char *temp_origin = strtok(origin99, "%");
  while (temp_origin != s21_NULL) {
    ck_assert_str_eq(temp2[i++], temp_origin);
    temp_origin = strtok(s21_NULL, "%");
  }
}
END_TEST

START_TEST(test_s21_memchr) {
  /* Исходный код теста. */
  char str1[10] = "abcdefg";
  char str2[10] = "AAeEdD";
  char str3[10] = "1 q 2 w";

  ck_assert_msg(memchr(str1, 'd', 5) == s21_memchr(str1, 'd', 5),
                "1 s21_memchr test succesful");
  ck_assert_msg(memchr(str1, 'd', 1) == s21_memchr(str1, 'd', 1),
                "2 s21_memchr test succesful");
  ck_assert_msg(memchr(str1, 'h', 10) == s21_memchr(str1, 'h', 10),
                "3 s21_memchr test succesful");
  ck_assert_msg(memchr(str2, 'E', 10) == s21_memchr(str2, 'E', 10),
                "4 s21_memchr test succesful");
  ck_assert_msg(memchr(str3, ' ', 5) == s21_memchr(str3, ' ', 5),
                "5 s21_memchr test succesful");
}
END_TEST

START_TEST(test_s21_strcat) {
  /* Исходный код теста. */
  char str2[100] = {0};
  char str3[100] = "HOTDOGMASTER";
  char str4[100] = "SCHOOL21";
  char str5[100] = {0};

  ck_assert_msg(strcat(str4, str2) == s21_strcat(str4, str2),
                "1 s21_strcat test succesful");
  ck_assert_msg(strcat(str2, str4) == s21_strcat(str2, str4),
                "2 s21_strcat test succesful");
  ck_assert_msg(strcat(str3, str4) == s21_strcat(str3, str4),
                "3 s21_strcat test succesful");
  ck_assert_msg(strcat(str5, str3) == s21_strcat(str5, str3),
                "4 s21_strcat test succesful");
}
END_TEST

START_TEST(test_s21_strcpy) {
  /* Исходный код теста. */
  char str1[20];
  char str2[20] = "";
  char str3[100] = "HOTDOGMASTER";
  char *str4 = "SCHOOL21";
  char str5[100];

  ck_assert_msg(strcpy(str1, str2) == s21_strcpy(str1, str2),
                "1 s21_strcpy test not succesful");
  ck_assert_msg(strcpy(str2, str4) == s21_strcpy(str2, str4),
                "2 s21_strcpy test not succesful");
  ck_assert_msg(strcpy(str3, str4) == s21_strcpy(str3, str4),
                "3 s21_strcpy test not succesful");
  ck_assert_msg(strcpy(str5, str3) == s21_strcpy(str5, str3),
                "4 s21_strcpy test not succesful");
}
END_TEST

START_TEST(test_s21_strpbrk) {
  /* Исходный код теста. */
  char str1[10] = "abcdefg";
  char str2[10] = "AAeEdD";
  char str3[10] = "1 a 2 w";
  char str4[100] = "";

  ck_assert_msg(strpbrk(str1, str2) == s21_strpbrk(str1, str2),
                "1 s21_strpbrk test not succesful");
  ck_assert_msg(strpbrk(str1, str3) == s21_strpbrk(str1, str3),
                "2 s21_strpbrk test not succesful");
  ck_assert_msg(strpbrk(str2, str3) == s21_strpbrk(str2, str3),
                "3 s21_strpbrk test not succesful");
  ck_assert_msg(strpbrk(str2, str4) == s21_strpbrk(str2, str4),
                "4 s21_strpbrk test not succesful");
}
END_TEST

START_TEST(test_create_capsule) {
  /* Исходный код теста. */
  capsule *item = create_capsule();

  ck_assert_msg(item->alignment == 0, "alignment test failed");
  ck_assert_msg(item->explicit_sign == 0, "explicit sign test failed");
  ck_assert_msg(item->space_with_no_sign == 0,
                "space with no sign test failed");
  ck_assert_msg(item->full_writing == 0, "full writing test failed");
  ck_assert_msg(item->zero_printing == 0, "zero printing test failed");
  ck_assert_msg(item->width == 0, "width test failed");
  ck_assert_msg(item->precision == -2, "precision test failed");
  ck_assert_msg(item->length == '\0', "length test failed");
  ck_assert_msg(item->type == '\0', "type test failed");

  free(item);
}

END_TEST

START_TEST(test_parsing) {
  const char *str = "%%%#-+0*.LdFasda";
  char *format_temp = (char *)calloc(s21_strlen(str) + 5, sizeof(char));
  s21_strcpy(format_temp, str);

  char **item = parsing(format_temp);
  ck_assert_str_eq(item[1], "%");
  ck_assert_str_eq(item[2], "#-+0*.LdFasda");

  free(format_temp);
  free(item);
}
END_TEST

START_TEST(test_parsing_mass) {
  const char *str0 = "%";
  const char *str1 = "#-+0*.LdFasda";
  //  char str[] = "%%%-+0*.LdFasda%c%d";
  char **format_temp = (char **)calloc(4, sizeof(char *));
  format_temp[0] = (char *)calloc(s21_strlen(str0) + 2, sizeof(char));
  format_temp[1] = (char *)calloc(s21_strlen(str1) + 2, sizeof(char));
  format_temp[2] = (char *)calloc(s21_strlen(str1) + 2, sizeof(char));
  s21_strcpy(format_temp[1], str0);
  s21_strcpy(format_temp[2], str1);

  capsule **item = pars_mass(format_temp);
  ck_assert_msg(item[2]->type == 'd', "parsing 1 test failed");
  ck_assert_int_eq(item[2]->alignment, 1);
  ck_assert_int_eq(item[2]->explicit_sign, 1);
  ck_assert_str_eq(item[2]->text, "Fasda");
  ck_assert_int_eq(item[2]->full_writing, 1);

  free_capsule(item);
  free(format_temp[0]);
  free(format_temp[1]);
  free(format_temp[2]);
  free(format_temp);
}
END_TEST

START_TEST(test_type_f) {
  capsule *item = create_capsule();

  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 0;
  item->precision = 4;
  item->length = '\0';
  item->type = 'f';
  double a = 666.666;
  item->variable = &a;
  char str[100];
  type_f(item);

  sprintf(str, "%.4f", a);
  ck_assert_str_eq(item->str_end, str);
  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_type_F) {
  capsule *item = create_capsule();

  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 0;
  item->precision = 4;
  item->length = '\0';
  item->type = 'f';
  double a = 0 / 0.0;
  item->variable = &a;
  char str[100];
  type_F(item);

  sprintf(str, "%.4F", a);
  ck_assert_str_eq(item->str_end, str);
  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_type_f2) {
  capsule *item = create_capsule();

  item->alignment = 0;
  item->explicit_sign = 1;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 1;
  item->width = 13;
  item->precision = 4;
  item->length = '\0';
  item->type = 'f';
  double a = 234.6785468;
  item->variable = &a;
  char str[100];
  type_f(item);

  sprintf(str, "%+013.4f", a);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_type_f3) {
  capsule *item = create_capsule();

  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 5;
  item->precision = 0;
  item->length = 'L';
  item->type = 'f';
  long double a = 3.5;
  item->variable = &a;
  type_f(item);
  char str[100];

  sprintf(str, "%5.Lf", a);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_f1) {
  // test f
  char strf1[200] = {};
  char strf2[200] = {};
  char strf[] = "%+-15.10f/%*.3f/%+*.9f";
  double f5 = 5.55;
  double *ff5 = &f5;
  s21_sprintf(strf1, strf, *ff5, 7, 7.77, 13, 999.9);
  sprintf(strf2, strf, *ff5, 7, 7.77, 13, 999.9);
  ck_assert_str_eq(strf1, strf2);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
  // test f
  char strf1[200] = {};
  char strf2[200] = {};
  char strf[] = "%%%.4f/%f/%.*f/% 5.f/%05.f/%5.3f/%*.3f/%+*.*f/%+*.9f";
  double f1 = 1.1, f2 = 2.22, f3 = 3.33, f4 = 4.4444, f5 = 5.55, f6 = 666.666;
  double *ff5 = &f5;
  int i3 = 10, i4 = 4;
  s21_sprintf(strf1, strf, f1, f2, i3, f3, f4, *ff5, f6, 7, 7.77, 8, i4, 8.88,
              13, 999.9);
  sprintf(strf2, strf, f1, f2, i3, f3, f4, *ff5, f6, 7, 7.77, 8, i4, 8.88, 13,
          999.9);
  ck_assert_str_eq(strf1, strf2);
}
END_TEST

START_TEST(test_s21_sprintf_c) {
  // test C
  char strc[] = "%10c/%-10c/%25c/%-30c/%25c/%*c/%2c/%*c";
  char strc1[200] = {};
  char strc2[200] = {};
  s21_sprintf(strc1, strc, 'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x');
  sprintf(strc2, strc, 'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x');
  ck_assert_str_eq(strc1, strc2);
}
END_TEST

// Тест для функции type_c
START_TEST(test_type_c) {
  char symb = 'D';
  char str[30];  // строка для работы стандартной функции
  // ширина равна 1 (печать 1 символа)
  capsule *test_1 = create_capsule();
  test_1->alignment = 0;
  test_1->width = 1;
  test_1->variable = &symb;

  // ширина больше 1 символа, выравнивание по правому краю (по умолчанию)
  capsule *test_2 = create_capsule();
  test_2->alignment = 0;
  test_2->width = 20;
  test_2->variable = &symb;

  // ширина больше 1 символа, выравнивание по левому краю
  capsule *test_3 = create_capsule();
  test_3->alignment = 1;
  test_3->width = 20;
  test_3->variable = &symb;

  // ширина равна 0 (ширина и выравнивание не указаны)
  capsule *test_4 = create_capsule();
  test_4->variable = &symb;

  // тестирование
  // test1
  sprintf(str, "%1c", symb);
  type_c(test_1);
  ck_assert_msg(strncmp(test_1->str_end, str, 1) == 0,
                "width == 1 test failed");
  free(test_1->str_end);
  free(test_1);
  // test2
  sprintf(str, "%20c", symb);
  type_c(test_2);
  ck_assert_msg(strncmp(test_2->str_end, str, 20) == 0,
                "width == 20 test failed");
  free(test_2->str_end);
  free(test_2);
  // test3
  sprintf(str, "%-20c", symb);
  type_c(test_3);
  ck_assert_msg(strncmp(test_3->str_end, str, 20) == 0,
                "width == 20, alignment == 1 test failed");
  free(test_3->str_end);
  free(test_3);
  // test4
  sprintf(str, "%c", symb);
  type_c(test_4);
  ck_assert_msg(strncmp(test_4->str_end, str, 1) == 0,
                "width == 0 test failed");
  free(test_4->str_end);
  free(test_4);
}
END_TEST

START_TEST(test_s21_sprintf_d) {
  // test d
  char strd[] =
      "1234%%%d%%%%-+02.*dFasda/%+-10d/%d/%09.5d/%05d/%-.10d/%.0d/%+1.3hd/"
      "%-10.1ld/%-25.10d/%-30.2d/%10.12d/%11d/%*d/%*.*d/%+-25.*d/%+10.2ld/"
      "%-11.*hd";
  char strd1[1000] = {};
  char strd2[1000] = {};
  short h = 34;
  int d1 = 1, d2 = 2, d3 = 3, d4 = -4, di1 = 55555;
  short int ds = -324;
  long int dl = 33333;
  int *dd1 = &d3;
  int n1 = 0, n2 = 0;
  s21_sprintf(strd1, strd, d1, d2, dd1, d4, 6, di1, 0, ds, dl, 253, 335, 1234,
              34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  sprintf(strd2, strd, d1, d2, dd1, d4, 6, di1, 0, ds, dl, 253, 335, 1234, 34,
          10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(strd1, strd2);
}
END_TEST

START_TEST(test_type_d) {
  capsule *item = create_capsule();
  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 0;
  item->precision = 0;
  item->length = 'l';
  item->type = 'd';
  long int a = 55555;
  long long int b = (long long int)a;
  item->variable = &b;
  char str[100];
  type_d(item);
  sprintf(str, "%ld", a);
  ck_assert_str_eq(item->str_end, str);
  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_u) {
  // test u
  char stru[] =
      "%u/%15u/%-20u/%010u/%-15.10u/%20.*u/%*.*u/%*.10u/%-20.12lu/%19hu";
  char stru1[200] = {};
  char stru2[200] = {};
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  s21_sprintf(stru1, stru, 4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u,
              10, 5, 2345u, 20, 2432u, l, h);
  sprintf(stru2, stru, 4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10,
          5, 2345u, 20, 2432u, l, h);
  ck_assert_str_eq(stru1, stru2);
}
END_TEST

START_TEST(test_type_u) {
  capsule *item = create_capsule();
  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 0;
  item->precision = 0;
  item->length = '\0';
  item->type = 'u';
  unsigned int a = 1;
  item->variable = &a;
  char str[100];
  type_d(item);
  sprintf(str, "%u", a);
  ck_assert_str_eq(item->str_end, str);
  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_i) {
  // test d
  char strd[] = "%+50.i/%-10.20i/%10.i/%012i/%*.*i/%-10.*i/%+10.1li/%*.25hi";
  char strd1[200] = {};
  char strd2[200] = {};
  int d1 = 34567, d2 = 225, d3 = 5230;
  int *dd1 = &d3;
  short h = 34;
  long l = 2353423523424;
  int i =
      s21_sprintf(strd1, strd, d1, d2, dd1, 125, 10, 5, 456, 10, 377, l, 12, h);
  int j = sprintf(strd2, strd, d1, d2, dd1, 125, 10, 5, 456, 10, 377, l, 12, h);
  ck_assert_str_eq(strd1, strd2);
  ck_assert_int_eq(i, j);
}
END_TEST

START_TEST(test_type_i) {
  capsule *item = create_capsule();
  item->alignment = 0;
  item->explicit_sign = 1;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 1;
  item->width = 6;
  item->precision = 0;
  item->length = '\0';
  item->type = 'i';
  int a = 3443334;
  item->variable = &a;
  char str[100];
  type_d(item);
  int l = sprintf(str, "%+06i", a);

  ck_assert_str_eq(item->str_end, str);
  ck_assert_int_eq(l, s21_strlen(item->str_end));
  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_to_upper_first) {
  char str1[20] = "hElLo!23@.sWEd";
  char str2[20] = "hello!23@.swed";
  char str3[20] = "HELLO!23@.SWED";
  char *tlw1 = s21_to_upper_first(str1);
  char *tlw2 = s21_to_upper_first(str2);
  ck_assert_str_eq(tlw1, str3);
  ck_assert_str_eq(tlw2, str3);
}
END_TEST

START_TEST(test_s21_sprintf_s) {
  // test s

  char strs1[200] = {};
  char strs[] = "%s/%23s/%-15s/%10.s/%15.10s/%*.*s/%*s/%16.*s";
  char strs2[200] = {};

  s21_sprintf(strs1, strs, "aboba", "helloworld", "ABOBA", "ABOBBAAA",
              "AAABOBA", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", 10,
              "QWERTY");
  sprintf(strs2, strs, "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA",
          15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", 10, "QWERTY");
  ck_assert_str_eq(strs1, strs2);
}
END_TEST

// Тест для функции type_s
START_TEST(test_type_s) {
  char *str_test = "5Dude";
  char str[30];  // строка для работы стандартной функции
  // ширина равна 1 (печать 1 символа)
  capsule *test_1 = create_capsule();
  test_1->alignment = 0;
  test_1->width = 1;
  test_1->variable = str_test;

  // ширина больше 1 символа, выравнивание по правому краю (по умолчанию)
  capsule *test_2 = create_capsule();
  test_2->alignment = 0;
  test_2->width = 20;
  test_2->variable = str_test;

  // ширина равна 0 (ширина и выравнивание не указаны)
  capsule *test_3 = create_capsule();
  test_3->variable = str_test;

  // ширина больше 1 символа, выравнивание по левому краю
  capsule *test_4 = create_capsule();
  test_4->alignment = 1;
  test_4->width = 20;
  test_4->variable = str_test;

  // точность меньше строки
  capsule *test_5 = create_capsule();
  test_5->precision = 2;
  test_5->variable = str_test;

  // точность и ширина больше строки
  capsule *test_6 = create_capsule();
  test_6->precision = 8;
  test_6->width = 10;
  test_6->variable = str_test;

  // точность и ширина меньше строки
  capsule *test_7 = create_capsule();
  test_7->precision = 3;
  test_7->width = 2;
  test_7->variable = str_test;

  // точность меньше строки, а ширина больше, выравнивание по левому краю
  capsule *test_8 = create_capsule();
  test_8->precision = 3;
  test_8->width = 10;
  test_8->variable = str_test;

  // точность меньше строки, а ширина больше, выравнивание по правому краю
  capsule *test_9 = create_capsule();
  test_9->alignment = 1;
  test_9->precision = 3;
  test_9->width = 10;
  test_9->variable = str_test;

  char *str_test2 = "AAAAABOOOOOBAAA";
  char str2[30];  // строка для работы стандартной функции
  // ширина равна 1 (печать 1 символа)
  capsule *test_10 = create_capsule();
  test_10->alignment = 0;
  test_10->precision = 4;
  test_10->width = 15;
  test_10->variable = str_test2;

  // тестирование
  // test1
  sprintf(str, "%1s", str_test);
  type_s(test_1);
  ck_assert_str_eq(test_1->str_end, str);
  free(test_1->str_end);
  free(test_1);
  // test2
  sprintf(str, "%20s", str_test);
  type_s(test_2);
  ck_assert_str_eq(test_2->str_end, str);
  free(test_2->str_end);
  free(test_2);
  // test3
  sprintf(str, "%s", str_test);
  type_s(test_3);
  ck_assert_str_eq(test_3->str_end, str);
  free(test_3->str_end);
  free(test_3);
  // test4
  sprintf(str, "%-20s", str_test);
  type_s(test_4);
  ck_assert_str_eq(test_4->str_end, str);
  free(test_4->str_end);
  free(test_4);
  // test5
  sprintf(str, "%.2s", str_test);
  type_s(test_5);
  ck_assert_str_eq(test_5->str_end, str);
  free(test_5->str_end);
  free(test_5);
  // test6
  sprintf(str, "%10.5s", str_test);
  type_s(test_6);
  ck_assert_str_eq(test_6->str_end, str);
  free(test_6->str_end);
  free(test_6);
  // test7
  sprintf(str, "%2.3s", str_test);
  type_s(test_7);
  ck_assert_str_eq(test_7->str_end, str);
  free(test_7->str_end);
  free(test_7);
  // test8
  sprintf(str, "%10.3s", str_test);
  type_s(test_8);
  ck_assert_str_eq(test_8->str_end, str);
  free(test_8->str_end);
  free(test_8);
  // test9
  sprintf(str, "%-10.3s", str_test);
  type_s(test_9);
  ck_assert_str_eq(test_9->str_end, str);
  free(test_9->str_end);
  free(test_9);
  // test10
  sprintf(str2, "%15.4s", str_test2);
  type_s(test_10);
  ck_assert_str_eq(test_10->str_end, str2);
  free(test_10->str_end);
  free(test_10);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char str1[20] = "hElLo!23@.sWEd";
  char str2[20] = "hello!23@.swed";
  char str3[20] = "HELLO!23@.SWED";
  char *tlw1 = s21_to_lower(str1);
  char *tlw2 = s21_to_lower(str3);
  ck_assert_str_eq(tlw1, str2);
  ck_assert_str_eq(tlw2, str2);
  free(tlw1);
  free(tlw2);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char str1[20] = "hElLo!23@.sWEd";
  char str2[20] = "hello!23@.swed";
  char str3[20] = "HELLO!23@.SWED";
  char *tlw1 = s21_to_upper(str1);
  char *tlw2 = s21_to_upper(str2);
  ck_assert_str_eq(tlw1, str3);
  ck_assert_str_eq(tlw2, str3);
  free(tlw1);
  free(tlw2);
}
END_TEST

/// Тест для функции s21_trim
START_TEST(test_s21_trim) {
  char *s1 = s21_trim("*&11dari*a1&*1", "1&*");
  char *s2 = s21_trim("*&11dari*a", "1&*");
  char *s3 = s21_trim("dari*a1&*1", "1&*");
  char *s4 = s21_trim("dari*a", "1&*");

  // удалить и в начале, и в конце
  ck_assert_msg(strcmp(s1, "dari*a") == 0, "1st test failed");
  // удалить и только в начале
  ck_assert_msg(strcmp(s2, "dari*a") == 0, "2nd test failed");
  // удалить только в конце
  ck_assert_msg(strcmp(s3, "dari*a") == 0, "3rd test failed");
  // не изменять строку
  ck_assert_msg(strcmp(s4, "dari*a") == 0, "4th test failed");
  free(s1);
  free(s2);
  free(s3);
  free(s4);
}
END_TEST

START_TEST(test_s21_insert) {
  char src1[50] = "JohnWick";
  char str1[50] = " ";
  char str2[1] = "";
  char src2[1] = "";

  char *s1 = s21_insert(src1, str1, 5);
  char *s2 = s21_insert("JohnWick", "", 5);
  char *s3 = s21_insert("WelcomeJacob", " here, ", 7);
  char *s4 = s21_insert("JohnWick", " ", 30);
  char *s5 = s21_insert("JohnWick", " ", -1);
  char *s6 = s21_insert(src2, str2, 0);
  char *s7 = s21_insert(" ", NULL, 5);
  char *s8 = s21_insert(NULL, NULL, 5);
  char *s9 = s21_insert(NULL, " ", 5);
  ck_assert_str_eq(s1, "JohnW ick");
  ck_assert_str_eq(s2, "JohnWick");
  ck_assert_str_eq(s3, "Welcome here, Jacob");
  ck_assert_msg(s4 == NULL, "Вставка в индекс больше размера не выдала NULL");
  ck_assert_msg(s5 == NULL,
                "Вставка в отрицательный индекс размера не выдала NULL");
  ck_assert_str_eq(s6, str2);
  ck_assert_msg(s7 == NULL, "Вторая строка NULL");
  ck_assert_msg(s8 == NULL, "Обе строки NULL");
  ck_assert_msg(s9 == NULL, "Первая строка NULL");
  free(s1);
  free(s2);
  free(s3);
  free(s4);
  free(s5);
  free(s6);
  free(s7);
  free(s8);
  free(s9);
}
END_TEST

START_TEST(test_s21_sprintf_eE) {
  char str1[1000];
  char str2[1000];
  char streE[] =
      "%20e/%010.*e/%-*.16e/%#025.10e/%*.*e/%+-25.4E/%25.*E/%-*.10E/%#02.E/";
  sprintf(str1, streE, 2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532,
          10, 15, 11111.22, 3456.4325, 10, 23452.43242, 5, -0.05234,
          25.432523432);
  s21_sprintf(str2, streE, 2543.43254, 10, 1012.34567, 15, -0.00123,
              45678.342532, 10, 15, 11111.22, 3456.4325, 10, 23452.43242, 5,
              -0.05234, 25.432523432);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_type_E) {
  capsule *item = create_capsule();

  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 25;
  item->precision = 6;
  item->length = '\0';
  item->type = 'E';
  double a = 2543.43254;
  item->variable = &a;
  type_E(item);
  char str[100];

  sprintf(str, "%25E", a);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_type_e) {
  capsule *item = create_capsule();

  item->alignment = 1;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 15;
  item->precision = 16;
  item->length = 'L';
  item->type = 'e';
  long double a = -0.00123;
  double b = -0.00123;
  item->variable = &a;
  type_e(item);
  char str[100];

  sprintf(str, "%-15.16e", b);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_G) {
  char str1[1000];
  char str2[1000];
  char strgG[] =
      "%G/%25G/%#-15G/%017G/%#05.2g/%#010.16G/%+#8.6G/%*.8g/%#-10.*G/%+#12.16G/"
      "%*.*G";
  s21_sprintf(str1, strgG, 43242.43242, 123432.43242, 0000.1234, -34252.43242,
              1234.5, 111.432534243243242, 4324.43242, 25, -3213.43242, 16,
              -43.43242353242342, 111.24324242, 25, 5, 0.000000342);
  sprintf(str2, strgG, 43242.43242, 123432.43242, 0000.1234, -34252.43242,
          1234.5, 111.432534243243242, 4324.43242, 25, -3213.43242, 16,
          -43.43242353242342, 111.24324242, 25, 5, 0.000000342);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_type_g) {
  capsule *item = create_capsule();

  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 25;
  item->precision = 10;
  item->length = '\0';
  item->type = 'g';
  double a = 1234567.0;
  item->variable = &a;
  type_g(item);
  char str[100];

  sprintf(str, "%25.10g", a);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_x) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 15;
  unsigned long l = 52312313242l;
  char strx[] =
      "%x/%-25x/%#10x/%#-10x/%#10.5x/%-25.34x/%#-10.2x/%*.*x/%#*.10x/%20.*"
      "x/%#10.*x/%*.5hx/%10.25lx";
  sprintf(str2, strx, 235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
          3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  s21_sprintf(str1, strx, 235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
              3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_type_x) {
  capsule *item = create_capsule();
  item->alignment = 1;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = -25;
  item->precision = 34;
  item->length = '\0';
  item->type = 'x';
  long long int a = 68432;
  unsigned int b = 68432;
  item->variable = &a;
  type_x(item);
  char str[100];

  sprintf(str, "%-25.34x", b);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_X) {
  char str1[1000];
  char str2[1000];
  char strX[] =
      "% X/%-10X/%15X/%#-15X/%#20.3X/%-30.12X/%#-12.3X/%*.*X/%#*.15X/%21.*X/%"
      "#12.*X/%*.8hx/%14.12lX";
  unsigned short h = 234;
  unsigned long l = 4325243132l;
  int r1 = sprintf(str1, strX, 235, 1234, 3456, 12345, 222234, 68432, 34567, 10,
                   15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2, strX, 235, 1234, 3456, 12345, 222234, 68432, 34567,
                       10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_type_X) {
  capsule *item = create_capsule();

  item->alignment = 0;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 1;
  item->zero_printing = 0;
  item->width = 8;
  item->precision = 15;
  item->length = '\0';
  item->type = 'X';
  long long int a = 300;
  unsigned int b = 300;
  item->variable = &a;
  type_X(item);
  char str[100];

  sprintf(str, "%#8.15X", b);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_o) {
  char str1[1000];
  char str2[1000];
  char strs[] = "% -25.10o/%-10o/%#-30.2o/%#*.10o/%#*.*o/%25.*o/%#.10ho/%*lo";
  unsigned short h = 234;
  unsigned long l = 43251343241422;
  int r1 = sprintf(str1, strs, 12345, 6532, 43522, 10, 64342, 15, 2, 343, 6,
                   678, h, 10, l);
  int r2 = s21_sprintf(str2, strs, 12345, 6532, 43522, 10, 64342, 15, 2, 343, 6,
                       678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_type_o) {
  capsule *item = create_capsule();

  long long int a = 300;
  unsigned int b = 300;
  char str[100];
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 1;
  item->zero_printing = 1;
  item->width = 3;
  item->precision = 0;
  item->length = '\0';
  item->type = 'o';
  item->variable = &a;
  type_o(item);

  sprintf(str, "%#03o", b);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_p) {
  // test p
  char strs1[200] = {};
  char strs[] = "%p/%20p/%-15p/%10p/%-15p/%*p/%10p/%*p";
  char strs2[200] = {};
  char *p1 = "12345";
  int p = 4;
  int *p2 = &p;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;

  s21_sprintf(strs1, strs, p1, p2, p3, p4, p2, 10, p3, p1, 10, p4);
  sprintf(strs2, strs, p1, p2, p3, p4, p2, 10, p3, p1, 10, p4);

  ck_assert_str_eq(strs1, strs2);
}
END_TEST

START_TEST(test_type_p) {
  capsule *item = create_capsule();
  item->alignment = 1;
  item->explicit_sign = 0;
  item->space_with_no_sign = 0;
  item->full_writing = 0;
  item->zero_printing = 0;
  item->width = 30;
  item->precision = 0;
  item->length = '\0';
  item->type = 'p';
  long long int a = 300;
  long long int *b = &a;
  item->variable = b;
  type_p(item);
  char str[100];

  sprintf(str, "%-30p", b);
  ck_assert_str_eq(item->str_end, str);

  free(item->str_end);
  free(item);
}
END_TEST

START_TEST(test_s21_sprintf_n) {
  // test n
  char strd[] = "123456%n";
  char strd1[200] = {};
  int n1 = 0, n2 = 6;
  s21_sprintf(strd1, strd, &n1);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_s21_proc) {
  char str1[100];
  char str2[100];
  char *str = "asdf%10%%10.15%%%%%%%%%%%%%%%%%%%%%%d";
  int r1 = sprintf(str1, str, 1);
  int r2 = s21_sprintf(str2, str, 1);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_s21_err) {
  char str1[100];
  char str2[100];
  int r1 = s21_sprintf(str1, "ASDV");
  int r2 = sprintf(str2, "ASDV");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);

  ck_assert_int_eq(s21_sprintf(str1, NULL), -1);
  ck_assert_int_eq(s21_sprintf(str1, ""), -1);
  ck_assert_int_eq(s21_sprintf(str1, "1%!%%"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "1%%%1"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "1%%%"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "%10.10d%"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "%10.10d%11w"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "%10#.10d"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "%10!.10d"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "%10.-*d"), -1);
  ck_assert_int_eq(s21_sprintf(str1, "%w10.4d"), -1);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("TheTest");
  TCase *tc = tcase_create("TheTest");
  SRunner *sr = srunner_create(suite);
  int nf;
  suite_add_tcase(suite, tc);
  tcase_add_test(tc, test_s21_memcpy);
  tcase_add_test(tc, test_s21_strchr);
  tcase_add_test(tc, test_s21_strcspn);
  tcase_add_test(tc, test_s21_strspn);
  tcase_add_test(tc, test_s21_memmove);
  tcase_add_test(tc, test_s21_strcmp);
  tcase_add_test(tc, test_s21_strstr);
  tcase_add_test(tc, test_s21_strerror);
  tcase_add_test(tc, test_s21_memset);
  tcase_add_test(tc, test_s21_strncmp);
  tcase_add_test(tc, test_s21_memchr);
  tcase_add_test(tc, test_s21_strcat);
  tcase_add_test(tc, test_s21_strcpy);
  tcase_add_test(tc, test_s21_strpbrk);
  tcase_add_test(tc, test_s21_memcmp);
  tcase_add_test(tc, test_s21_strncat);
  tcase_add_test(tc, test_s21_strncpy);
  tcase_add_test(tc, test_s21_strrchr);
  tcase_add_test(tc, test_s21_strlen);
  tcase_add_test(tc, test_s21_strtok);

  tcase_add_test(tc, test_create_capsule);
  tcase_add_test(tc, test_parsing);
  tcase_add_test(tc, test_parsing_mass);

  tcase_add_test(tc, test_type_f);
  tcase_add_test(tc, test_type_F);
  tcase_add_test(tc, test_type_f2);
  tcase_add_test(tc, test_type_f3);
  tcase_add_test(tc, test_type_E);
  tcase_add_test(tc, test_type_e);
  tcase_add_test(tc, test_type_g);

  tcase_add_test(tc, test_type_x);
  tcase_add_test(tc, test_type_o);
  tcase_add_test(tc, test_type_X);
  tcase_add_test(tc, test_type_d);
  tcase_add_test(tc, test_type_u);
  tcase_add_test(tc, test_type_i);
  tcase_add_test(tc, test_type_p);
  tcase_add_test(tc, test_type_c);
  tcase_add_test(tc, test_type_s);

  tcase_add_test(tc, test_s21_to_lower);
  tcase_add_test(tc, test_s21_to_upper);
  tcase_add_test(tc, test_s21_trim);
  tcase_add_test(tc, test_s21_insert);
  tcase_add_test(tc, test_s21_to_upper_first);

  tcase_add_test(tc, test_s21_sprintf_f);
  tcase_add_test(tc, test_s21_sprintf_f1);
  tcase_add_test(tc, test_s21_sprintf_eE);
  tcase_add_test(tc, test_s21_sprintf_G);
  tcase_add_test(tc, test_s21_sprintf_x);
  tcase_add_test(tc, test_s21_sprintf_o);
  tcase_add_test(tc, test_s21_sprintf_X);
  tcase_add_test(tc, test_s21_sprintf_p);
  tcase_add_test(tc, test_s21_sprintf_c);
  tcase_add_test(tc, test_s21_sprintf_s);
  tcase_add_test(tc, test_s21_sprintf_d);
  tcase_add_test(tc, test_s21_sprintf_u);
  tcase_add_test(tc, test_s21_sprintf_i);
  tcase_add_test(tc, test_s21_sprintf_n);
  tcase_add_test(tc, test_s21_proc);

  tcase_add_test(tc, test_s21_err);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
