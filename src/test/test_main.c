#include <check.h>

#include "s21_math.h"

// Объявляем функции, которые создают Suite для каждой группы тестов
// Они написаны в отдельных файлах (test_exp.c, test_sqrt.c и т.д.)
Suite* exp_suite(void);
Suite* sqrt_suite(void);
Suite* abs_suite(void);
Suite* fabs_suite(void);
Suite* ceil_suite(void);
Suite* floor_suite(void);
Suite* log_suite(void);
Suite* fmod_suite(void);
Suite* sin_suite(void);
Suite* cos_suite(void);
Suite* tan_suite(void);
Suite* asin_suite(void);
Suite* acos_suite(void);
Suite* atan_suite(void);
Suite* pow_suite(void);

int main(void) {
  // 1. Создаём бегунок (runner), в который будем добавлять все Suite
  SRunner* runner = srunner_create(NULL);  // пока без Suite

  // 2. Добавляем каждый Suite в бегунок
  srunner_add_suite(runner, exp_suite());
  srunner_add_suite(runner, sqrt_suite());
  srunner_add_suite(runner, abs_suite());
  srunner_add_suite(runner, fabs_suite());
  srunner_add_suite(runner, ceil_suite());
  srunner_add_suite(runner, floor_suite());
  srunner_add_suite(runner, log_suite());
  srunner_add_suite(runner, fmod_suite());
  srunner_add_suite(runner, sin_suite());
  srunner_add_suite(runner, cos_suite());
  srunner_add_suite(runner, tan_suite());
  srunner_add_suite(runner, asin_suite());
  srunner_add_suite(runner, acos_suite());
  srunner_add_suite(runner, atan_suite());
  srunner_add_suite(runner, pow_suite());

  // 3. Запускаем все тесты
  // CK_NORMAL — стандартный вывод, CK_VERBOSE — подробный
  srunner_run_all(runner, CK_NORMAL);

  // 4. Считаем, сколько тестов упало
  int failed = srunner_ntests_failed(runner);

  // 5. Освобождаем память
  srunner_free(runner);

  // 6. Возвращаем код: 0 — всё хорошо, иначе — ошибка
  return (failed == 0) ? 0 : 1;
}