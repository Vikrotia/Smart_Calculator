#include "backend_calc.h"
int processing(char *string_to_calculate, double *result, double X) {
  int status = OK;
  Stack *start_stack = NULL;
  Stack *end_stack = NULL;
  char str1[256];
  status = validating_string(string_to_calculate, str1);
  if (status) {
    status = parsing_str_to_stack(str1, &start_stack);
    if (status) invers_stack(&start_stack, &end_stack);
    if (status) {
      status = calculating_result(&end_stack, result, X);
    }
  }
  delete_stack(&start_stack);
  delete_stack(&end_stack);
  return status;
}

int validating_string(char *old_str, char *new_str) {
  int status = OK;
  if (strlen(old_str) > 255)
    status = ERROR;
  else {
    deleting_space(old_str, new_str);
    if (!bracket_checking(new_str)) status = ERROR;
    if (!elements_checking(new_str)) status = ERROR;
  }
  return status;
}

int deleting_space(char *str, char *str1) {
  int size = strlen(str);
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (str[i] != ' ') {
      str1[j] = str[i];
      j++;
    }
  }
  str1[j] = '\0';
  return 0;
}

int bracket_checking(char *str) {
  int status = OK;
  int open = 0, close = 0;
  int size = strlen(str);
  for (int i = 0; i < size && status; i++) {
    if (str[i] == '(') {
      open++;
      if (str[i + 1] == ')') status = ERROR;
    }
    if (str[i] == ')') {
      close++;
      if (close > open) status = ERROR;
    }
  }
  if (open != close) status = ERROR;
  return status;
}

int elements_checking(char *str) {
  int status = OK;
  int size = strlen(str);
  int x = 0;
  for (int i = 0; i < size && status; i++) {
    if ((str[i] >= '0' && str[i] <= '9')) {
      if (!checking_environment_of_number(str, i)) status = ERROR;
    } else if (str[i] == '.') {
      if (!checking_dot(str, i)) status = ERROR;
    } else if (str[i] == 'X' || str[i] == 'x') {
      if (!checking_x(str, i))
        status = ERROR;
      else
        x = 1;
    } else if (str[i] == 'm') {
      if (!checking_mod(str, &i)) status = ERROR;
    } else if (IS_UN_SIGN(str[i]) || IS_BI_SIGN(str[i]) || str[i] == '%') {
      if (!checking_sign(str, i)) status = ERROR;
    } else if (str[i] == 's') {
      if (!checking_s(str, &i)) status = ERROR;
    } else if (str[i] == 't' || str[i] == 'c') {
      if (!checking_trigonom(str, &i)) status = ERROR;
    } else if (str[i] == 'l') {
      if (!checking_logs(str, &i)) status = ERROR;
    } else if (str[i] == 'a') {
      if (!checking_a_trigonom(str, &i)) status = ERROR;
    } else if (str[i] == '(' || str[i] == ')') {
      if (!checking_hooks(str, i)) status = ERROR;
    } else
      status = ERROR;
  }
  if (size < 2 && x == 0) {
    status = ERROR;
  }
  return status;
}

int checking_hooks(char *str, int i) {
  int status = OK;
  int size = strlen(str);
  if (i == 0 && str[i] == ')') status = ERROR;
  if (i == size - 1 && str[i] == '(') status = ERROR;
  return status;
}

int checking_environment_of_number(char *str, int i) {
  int status = OK;
  if (i != 0) {
    if (str[i - 1] == ')') status = ERROR;
  }
  if (str[i + 1] == '(') status = ERROR;
  if (str[i + 1] == 'c' || str[i + 1] == 's' || str[i + 1] == 't' ||
      str[i + 1] == 'a' || str[i + 1] == 'l')
    status = ERROR;
  return status;
}

int checking_dot(char *str, int i) {
  int status = OK;
  if (i != 0) {
    if (str[i - 1] < '0' || str[i - 1] > '9' || str[i + 1] < '0' ||
        str[i + 1] > '9') {
      status = ERROR;
    }
  } else
    status = ERROR;
  return status;
}

int checking_x(char *str, int i) {
  int status = OK;
  if (i != 0) {
    if ((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i - 1] == ')' ||
        str[i - 1] == '.')
      status = ERROR;
  }
  if ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '(' ||
      str[i + 1] == '.')
    status = ERROR;
  if (str[i + 1] == 'c' || str[i + 1] == 's' || str[i + 1] == 't' ||
      str[i + 1] == 'a' || str[i + 1] == 'l')
    status = ERROR;
  return status;
}

int checking_mod(char *str, int *i) {
  int status = OK;
  int size = strlen(str);
  if (((*i) + 3) < size) {
    if ((*i) != 0) {
      if (str[(*i) - 1] == '(' || str[(*i) + 3] == ')') status = ERROR;
    }
    if (str[(*i) + 1] != 'o' || str[(*i) + 2] != 'd') status = ERROR;
    if (str[(*i) + 3] == 'm' || str[(*i) - 1] == 'd') status = ERROR;
    if (IS_UN_SIGN(str[(*i) - 1]) || IS_BI_SIGN(str[(*i) - 1])) status = ERROR;
    if (IS_UN_SIGN(str[(*i) + 3]) || IS_BI_SIGN(str[(*i) + 3])) status = ERROR;
  } else
    status = ERROR;
  if (status) *i = (*i) + 2;
  return status;
}

int checking_sign(char *str, int i) {
  int status = OK;
  if (str[i + 1] == ')') status = ERROR;
  if (i != 0) {
    if (IS_BI_SIGN(str[i - 1]) || IS_BI_SIGN(str[i + 1]) ||
        IS_UN_SIGN(str[i - 1]) || IS_UN_SIGN(str[i + 1]))
      status = ERROR;
    if (str[i - 1] == 'd' || str[i + 1] == 'm') status = ERROR;
  } else {
    if (IS_BI_SIGN(str[i + 1]) || IS_UN_SIGN(str[i + 1]) || str[i + 1] == 'm')
      status = ERROR;
    if ((i == 0 || str[i - 1] == '(') && IS_BI_SIGN(str[i])) status = ERROR;
  }
  return status;
}

int checking_sign_before_func(char *str, int i) {
  int status = OK;
  if (i != 0 && str[i - 1] != '(' && str[i - 1] != 'd') {
    if (!IS_UN_SIGN(str[i - 1]) && !IS_BI_SIGN(str[i - 1])) status = ERROR;
  }
  return status;
}

int checking_s(char *str, int *i) {
  int status = OK;
  if (!checking_sign_before_func(str, *i)) status = ERROR;
  if (strncmp(&str[*i], "sin(", 4)) {
    if (strncmp(&str[*i], "sqrt(", 5))
      status = ERROR;
    else
      *i = *i + 4;
  } else
    *i = *i + 3;
  return status;
}

int checking_logs(char *str, int *i) {
  int status = OK;
  if (!checking_sign_before_func(str, *i)) status = ERROR;
  if (strncmp(&str[*i], "log(", 4)) {
    if (strncmp(&str[*i], "ln(", 3))
      status = ERROR;
    else
      *i = *i + 2;
  } else
    *i = *i + 3;
  return status;
}

int checking_a_trigonom(char *str, int *i) {
  int status = OK;
  if (!checking_sign_before_func(str, *i)) status = ERROR;
  if (strncmp(&str[*i], "acos(", 5) && strncmp(&str[*i], "asin(", 5) &&
      strncmp(&str[*i], "atan(", 5))
    status = ERROR;
  if (status) *i = *i + 4;
  return status;
}

int checking_trigonom(char *str, int *i) {
  int status = OK;
  if (!checking_sign_before_func(str, *i)) status = ERROR;
  if (strncmp(&str[*i], "cos(", 4) && strncmp(&str[*i], "tan(", 4))
    status = ERROR;
  if (status) *i = *i + 3;
  return status;
}

void push(Stack **head, double value, int priority, int type) {
  Stack *tmp = (Stack *)malloc(sizeof(Stack));
  if (tmp != NULL) {
    tmp->value = value;
    tmp->priority = priority;
    tmp->type = type;
    tmp->next = (*head);
    (*head) = tmp;
  }
}
int pop(Stack **head, double *value, int *priority, int *type) {
  Stack *prev = NULL;
  int status = OK;
  if (*head == NULL) status = ERROR;
  if (status) {
    prev = (*head);
    *value = prev->value;
    *priority = prev->priority;
    *type = prev->type;
    (*head) = (*head)->next;
    free(prev);
  }
  return status;
}

int peek_priority(Stack **head, int *priority) {
  int status = OK;
  if (*head == NULL) status = ERROR;
  if (status) *priority = (*head)->priority;
  return status;
}
int peek_type(Stack **head, int *type) {
  int status = OK;
  if (*head == NULL) status = ERROR;
  if (status) *type = (*head)->type;
  return status;
}

void delete_stack(Stack **start) {
  Stack *prev = NULL;
  int error = 1;
  if (*start == NULL) error = 0;
  if (error) {
    while ((*start)->next) {
      prev = (*start);
      (*start) = (*start)->next;
      free(prev);
    }
    free(*start);
  }
}

int parsing_str_to_stack(char *str, Stack **start_stack) {
  int status = OK;
  int priority = 0;
  Stack *operations_stack = NULL;
  int size = strlen(str);
  for (int i = 0; i < size; i++) {
    if (isdigit((str[i])) || str[i] == '.') {
      double number = 0.0;
      reading_number(str, &number, &i, &priority);
      push(start_stack, number, priority, s21_num);
    } else if (str[i] == 'x' || str[i] == 'X')
      push(start_stack, 0.0, 0, s21_x);
    else if (isalpha(str[i]) && str[i] != 'x' && str[i] != 'X') {
      char operation[50] = {0};
      int type = 0;
      reading_trigonometric_operation(str, operation, &i);
      type_identification_of_trigonom(operation, &type, &priority);
      if (!priority_conflict(start_stack, &operations_stack, priority, type))
        status = ERROR;
    } else if (IS_UN_SIGN(str[i]) || IS_BI_SIGN(str[i]) || str[i] == '%') {
      if (!reading_algebra_operation(start_stack, &operations_stack, str, &i))
        status = ERROR;
    } else if (str[i] == '(')
      push(&operations_stack, 0.0, 0, s21_open);
    else if (str[i] == ')')
      pop_expression_in_brackets(start_stack, &operations_stack);
  }
  if (*start_stack == NULL) status = ERROR;
  if (status) invers_stack(&operations_stack, start_stack);
  return status;
}

void reading_number(char *str, double *number, int *i, int *priotiry) {
  char str_of_number[100] = {0};
  int number_digit = 0;
  int point = 1;
  while (isdigit(str[*i]) || (str[*i] == '.' && point)) {
    if (str[*i] == '.') point = 0;
    str_of_number[number_digit] = str[*i];
    number_digit++;
    *i = *i + 1;
  }
  *i = *i - 1;
  *number = atof(str_of_number);
  *priotiry = 0;
}

void reading_trigonometric_operation(char *str, char *operation, int *i) {
  int number_char = 0;
  while (isalpha(str[*i])) {
    operation[number_char] = str[*i];
    number_char++;
    *i = *i + 1;
  }
  *i = *i - 1;
}
int type_identification_of_trigonom(char *operation, int *type, int *priotiry) {
  int status = OK;
  if (!strncmp(operation, "sin", 3))
    *type = s21_sin;
  else if (!strncmp(operation, "cos", 3))
    *type = s21_cos;
  else if (!strncmp(operation, "tan", 3))
    *type = s21_tan;
  else if (!strncmp(operation, "acos", 4))
    *type = s21_acos;
  else if (!strncmp(operation, "asin", 4))
    *type = s21_asin;
  else if (!strncmp(operation, "atan", 4))
    *type = s21_atan;
  else if (!strncmp(operation, "sqrt", 4))
    *type = s21_sqrt;
  else if (!strncmp(operation, "ln", 2))
    *type = s21_ln;
  else if (!strncmp(operation, "log", 3))
    *type = s21_log;
  else if (!strncmp(operation, "mod", 3))
    *type = s21_mod;
  else
    status = ERROR;
  *priotiry = 4;
  if (*type == s21_mod) *priotiry = 2;
  return status;
}
int priority_conflict(Stack **start_stack, Stack **operations_stack,
                      int priority, int type) {
  int status = OK;
  int priority_previous_operation = 0;
  if (peek_priority(operations_stack, &priority_previous_operation)) {
    double value = 0.0;
    int priority1 = 0;
    int type_prev = 0;
    int type_pop = 0;
    peek_type(operations_stack, &type_prev);
    if (priority <= priority_previous_operation) {
      while (priority <= priority_previous_operation &&
             *operations_stack != NULL &&
             !(type_prev == s21_pow && type == s21_pow) && status) {
        pop(operations_stack, &value, &priority1, &type_pop);
        if (*start_stack == NULL)
          status = ERROR;
        else {
          push(start_stack, value, priority1, type_pop);
          peek_priority(operations_stack, &priority_previous_operation);
          peek_type(operations_stack, &type_prev);
        }
      }
      push(operations_stack, 0.0, priority, type);
    } else if (priority > priority_previous_operation) {
      push(operations_stack, 0.0, priority, type);
    }
  } else
    push(operations_stack, 0.0, priority, type);
  return status;
}

int reading_algebra_operation(Stack **start_stack, Stack **operations_stack,
                              char *str, int *i) {
  int status = OK;
  if (str[*i] == '-' && (*i - 1) < 0) {
    *i = *i + 1;
    double number = 0.0;
    int priority = 0;
    reading_number(str, &number, i, &priority);
    number *= (-1);
    push(start_stack, number, priority, s21_num);
  } else if (str[*i] == '-' &&
             (IS_UN_SIGN(str[*i - 1]) || IS_BI_SIGN(str[*i - 1]) ||
              str[*i - 1] == '(')) {
    *i = *i + 1;
    double number = 0.0;
    int priority = 0;
    reading_number(str, &number, i, &priority);
    number *= (-1);
    push(start_stack, number, priority, s21_num);
  } else {
    int type = 0;
    int priority = 0;
    type_identification_of_algebra(str[*i], &type, &priority);
    if (!priority_conflict(start_stack, operations_stack, priority, type))
      status = ERROR;
  }
  return status;
}

int type_identification_of_algebra(char operation, int *type, int *priotiry) {
  if (operation == '-') {
    *type = s21_minus;
    *priotiry = 1;
  } else if (operation == '+') {
    *type = s21_plus;
    *priotiry = 1;
  } else if (operation == '*') {
    *type = s21_mult;
    *priotiry = 2;
  } else if (operation == '/') {
    *type = s21_div;
    *priotiry = 2;
  } else if (operation == '^') {
    *type = s21_pow;
    *priotiry = 3;
  } else if (operation == '%') {
    *type = s21_mod;
    *priotiry = 2;
  }
  return 0;
}

int pop_expression_in_brackets(Stack **start_stack, Stack **operations_stack) {
  int status = OK;
  double value = 0.0;
  int priority = 0;
  int type = (*operations_stack)->type;
  while (type != s21_open) {
    pop(operations_stack, &value, &priority, &type);
    push(start_stack, value, priority, type);
    type = (*operations_stack)->type;
  }
  if (type == s21_open && *operations_stack != NULL)
    pop(operations_stack, &value, &priority, &type);
  return status;
}

int invers_stack(Stack **start_stack, Stack **end_stack) {
  double value = 0.0;
  int priority = 0;
  int type = 0;
  while (pop(start_stack, &value, &priority, &type))
    push(end_stack, value, priority, type);
  return 0;
}

int calculating_result(Stack **end_stack, double *result, double X) {
  int status = OK;
  double value = 0.0;
  int priority = 0;
  int type = 0;
  double numbers[10] = {0};
  int i = 0;
  while (*end_stack != NULL && status) {
    if (IS_NUMBER(end_stack)) {
      pop(end_stack, &value, &priority, &type);
      numbers[i] = value;
      i++;
    } else if (IS_ALGEBRAIC_SIGN(end_stack)) {
      i = i - 2;
      if (i < 0) {
        status = ERROR;
      } else {
        pop(end_stack, &value, &priority, &type);
        if (!calculating_algebraic(&numbers[i], &numbers[i + 1], type))
          status = ERROR;
        i++;
      }
    } else if (IS_TRIGONOMETRIC_SIGN(end_stack)) {
      pop(end_stack, &value, &priority, &type);
      i--;
      if (!calculating_trigonometric(&numbers[i], type)) status = ERROR;
      i++;
    } else if (IS_X(end_stack)) {
      pop(end_stack, &value, &priority, &type);
      numbers[i] = X;
      i++;
    } else
      status = ERROR;
  }
  if (numbers[1] != 0.0) {
    status = ERROR;
    numbers[0] = 0.0;
  } else
    *result = numbers[0];
  if (!status) *result = 0.0;
  return status;
}

int calculating_trigonometric(double *number, int type) {
  int status = OK;
  if (type == s21_sin)
    *number = sin(*number);
  else if (type == s21_cos)
    *number = cos(*number);
  else if (type == s21_tan)
    *number = tan(*number);
  else if (type == s21_asin) {
    if (*number < -1 || *number > 1)
      status = ERROR;
    else
      *number = asin(*number);
  } else if (type == s21_acos) {
    if (*number < -1 || *number > 1)
      status = ERROR;
    else
      *number = acos(*number);
  } else if (type == s21_atan)
    *number = atan(*number);
  else if (type == s21_sqrt) {
    if (*number < 0)
      status = ERROR;
    else
      *number = sqrt(*number);
  } else if (type == s21_ln) {
    if (*number <= 0)
      status = ERROR;
    else
      *number = log(*number);
  } else if (type == s21_log) {
    if (*number <= 0)
      status = ERROR;
    else
      *number = log10(*number);
  } else
    status = ERROR;
  return status;
}

int calculating_algebraic(double *number_1, double *number_2, int type) {
  int status = OK;
  if (type == s21_plus)
    *number_1 = *number_1 + (*number_2);
  else if (type == s21_minus)
    *number_1 = *number_1 - (*number_2);
  else if (type == s21_mult)
    *number_1 = *number_1 * (*number_2);
  else if (type == s21_div) {
    if (*number_2 == 0.0)
      status = ERROR;
    else {
      *number_1 = *number_1 / (*number_2);
    }
  } else if (type == s21_pow)
    *number_1 = pow(*number_1, (*number_2));
  else if (type == s21_mod)
    if (*number_2 == 0.0)
      status = ERROR;
    else {
      *number_1 = fmod(*number_1, *number_2);
    }
  else
    status = ERROR;
  if (status) *number_2 = 0.0;
  return status;
}

double annuityСredit(double *sums, double *months, double *procents,
                     double *overpayment, double *totalSum) {
  double PMT = *sums * (*procents * (pow(1 + (*procents), *months) /
                                     (pow(1 + (*procents), *months) - 1)));
  *totalSum = PMT * *months;
  *overpayment = *totalSum - *sums;
  return PMT;
}

double differentiatedСredit(double *sums, double *months, double *procents,
                            double *d) {
  double PMT = (*d) + ((*sums) - (*d) * ((*months) - 1)) * (*procents);
  return PMT;
}
