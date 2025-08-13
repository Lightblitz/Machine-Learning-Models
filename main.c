#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "linalg.h"


/*
// run_linear_regression takes the matrix X to solve for s = (X^TX)^-1X^Ty
char* run_linear_regression(const struct matrix* X, const struct matrix* Y, const int num_points) {
    for (int i = 0; i < num_points; i++) {
        
    }
} */


int main() {
    struct quest q = { 0 };
  quest_init(&q);  
  char cmd[30];
  while(1) {
    char subject[3] = "";
    int number = 0;
    char title[128] = "";
    int capacity = 0;
    char name[32] = "";
    int id = 0;
    int res = scanf(" %30c", &cmd);

    if (cmd == 'q' || res != 1) {
        break;
    }
    if (cmd == 'help') {
        printf("Here are the list of commands available for this library:");
    }


    /*if (cmd == 'q' || res != 1) {
      break;
    }
    if (cmd == 'c') {
      if (scanf("%s %d %d %127[^\n]\n", subject, &number, &capacity, title) != 4) {
        break;
      }
      quest_create_course(&q, subject, number, title, capacity);
    } else if (cmd == 'p') {
      if (scanf("%s %d", subject, &number) != 2) {
        break;
      }
      quest_print_course(&q, subject, number);
    } else if (cmd == 's') {
      if (scanf(" %31[^\n]\n", name) != 1) {
        break;
      }
      quest_register_student(&q, name);
    } else if (cmd == 'P') {
      if (scanf("%d", &id) != 1) {
        break;
      }
      quest_print_student(&q, id);
    } else if (cmd == 'e') {
      if (scanf("%d %s %d", &id, subject, &number) != 3) {
        break;
      }
      quest_enroll(&q, id, subject, number);
    } else if (cmd == 'd') {
      if (scanf("%d %s %d", &id, subject, &number) != 3) {
        break;
      }
      quest_drop(&q, id, subject, number);
    } else if (cmd == 'g') {
      if (scanf("%s %d", subject, &number) != 2) {
        break;
      }
      int ids[32] = { 0 };
      int grades[32] = { 0 };
      int i = 0;
      for (; i < 32; i++) {
        char num[1024];
        if (scanf("%s", num) != 1) {
          break;
        }
        if (strcmp(num, "end") == 0) {
          break;
        }
        if (sscanf(num, "%d", &ids[i]) != 1) {
          i = -1;
          break;
        }
        if (scanf("%d", &grades[i]) != 1) {
          i = -1;
          break;
        }
      }
      if (i == -1) {
        break;
      }
      quest_submit_grades(&q, subject, number, ids, grades, i);
    }
    else {
      break;
    }*/
  }
}