/***************************************************************************************
 * Copyright (c) 2014-2024 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expr[128];
  word_t old_val;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP *new_wp() {
  if (free_ == NULL) {
    panic("No more free watchpoints");
  }
  WP *wp = free_;
  free_ = free_->next;

  wp->next = head;
  head = wp;

  return wp;
}

void free_wp(WP *wp) {
  if (head == NULL || wp == NULL)
    return;

  if (head == wp) {
    head = wp->next;
  } else {
    WP *prev = head;
    while (prev->next != NULL && prev->next != wp) {
      prev = prev->next;
    }
    if (prev->next == wp) {
      prev->next = wp->next;
    } else {
      // wp not found in head list
      return;
    }
  }

  wp->next = free_;
  free_ = wp;
}

void list_watchpoints() {
  if (head == NULL) {
    printf("No watchpoints.\n");
    return;
  }
  printf("Num     Type           Disp Enb Address          What\n");
  for (WP *wp = head; wp != NULL; wp = wp->next) {
    printf("%-2d      watchpoint     keep y                    %s\n", wp->NO,
           wp->expr);
  }
}

bool check_watchpoints() {
  bool changed = false;
  for (WP *wp = head; wp != NULL; wp = wp->next) {
    bool success;
    word_t new_val = expr(wp->expr, &success);
    if (success) {
      if (new_val != wp->old_val) {
        printf("Watchpoint %d: %s\n", wp->NO, wp->expr);
        printf("Old value = %u (0x%x)\n", wp->old_val, wp->old_val);
        printf("New value = %u (0x%x)\n", new_val, new_val);
        wp->old_val = new_val;
        changed = true;
      }
    }
  }
  return changed;
}

void delete_watchpoint(int no) {
  for (WP *wp = head; wp != NULL; wp = wp->next) {
    if (wp->NO == no) {
      free_wp(wp);
      printf("Watchpoint %d deleted\n", no);
      return;
    }
  }
  printf("Watchpoint %d not found\n", no);
}

int set_watchpoint(char *e) {
  WP *wp = new_wp();
  strncpy(wp->expr, e, 128); // Safe copy
  wp->expr[127] = '\0';

  bool success;
  wp->old_val = expr(wp->expr, &success);
  if (!success) {
    free_wp(wp);
    return -1;
  }
  return wp->NO;
}
