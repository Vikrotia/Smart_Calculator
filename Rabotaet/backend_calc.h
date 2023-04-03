#ifndef BACKEND_CALC_H
#define BACKEND_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define IS_UN_SIGN(value) (value == '+' || value == '-')
#define IS_BI_SIGN(value) (value == '*' || value == '/' || value == '^')
#define IS_TRIGONOMETRIC_SIGN(value) (value != NULL && (*value)->priority == 4)
#define IS_ALGEBRAIC_SIGN(value) \
  (value != NULL && (*value)->priority != 0 && (*value)->priority != 4)
#define IS_NUMBER(value) \
  (value != NULL && (*value)->priority == 0 && (*value)->type == s21_num)
#define IS_X(value) \
  (value != NULL && (*value)->priority == 0 && (*value)->type == s21_x)

// проверка строки
int bracket_checking(char *str);
int validating_string(char *old_str, char *new_str);
int checking_environment_of_number(char *str, int i);
int elements_checking(char *str);
int checking_dot(char *str, int i);
int checking_x(char *str, int i);
int checking_mod(char *str, int *i);
int checking_sign(char *str, int i);
int checking_sign_before_func(char *str, int i);
int checking_sin(char *str, int *i);
int checking_sqrt(char *str, int *i);
int checking_tan(char *str, int *i);
int checking_cos(char *str, int *i);
int checking_ln(char *str, int *i);
int checking_log(char *str, int *i);
int checking_a_trigonom(char *str, int *i);
int deleting_space(char *str, char *str1);
int checking_hooks(char *str, int i);
int checking_logs(char *str, int *i);
int checking_s(char *str, int *i);
int checking_trigonom(char *str, int *i);

//реализация стека
typedef struct el_t {
  double value;
  int priority;
  int type;
  struct el_t *next;
} Stack;

typedef enum operation {
  s21_num,
  s21_x,
  s21_open,
  s21_close,
  s21_plus,
  s21_minus,
  s21_mult,
  s21_div,
  s21_pow,
  s21_mod,
  s21_cos,
  s21_sin,
  s21_tan,
  s21_acos,
  s21_asin,
  s21_atan,
  s21_sqrt,
  s21_log,
  s21_ln,
  s21_un_plus,
  s21_un_minus
} operations;

void push(Stack **head, double value, int priority, int type);
int pop(Stack **head, double *value, int *priority, int *type);
int peek_priority(Stack **head, int *priority);
int peek_type(Stack **head, int *type);
int invers_stack(Stack **start_stack, Stack **end_stack);
void delete_stack(Stack **start);

// польская нотация
int parsing_str_to_stack(char *str, Stack **start_stack);
void reading_number(char *str, double *number, int *i, int *priotiry);
void reading_trigonometric_operation(char *str, char *operation, int *i);
int reading_algebra_operation(Stack **start_stack, Stack **operations_stack,
                              char *str, int *i);
int type_identification_of_trigonom(char *operation, int *type, int *priotiry);
int type_identification_of_algebra(char operation, int *type, int *priotiry);
int priority_conflict(Stack **start_stack, Stack **operations_stack,
                      int priority, int type);
int pop_expression_in_brackets(Stack **start_stack, Stack **operations_stack);

int calculating_result(Stack **end_stack, double *result, double X);
int calculating_algebraic(double *number_1, double *number_2, int type);
int calculating_trigonometric(double *number, int type);

int processing(char *string_to_calculate, double *result, double X);

double annuityСredit(double *sums, double *months, double *procents,
                     double *overpayment, double *totalSum);
double differentiatedСredit(double *sums, double *months, double *procents,
                            double *d);

#endif /* BACKEND_CALC_H */
