#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int one;
  int two;
} Pair;

Pair best_ll = { 0, 0 };
Pair best_ur = { -1, -1 };
int best_area = 0;

int *c; /* Cache */
Pair *s; /* Stack */
int top = 0; /* Top of stack */

void push(int a, int b) {
  s[top].one = a;
  s[top].two = b;
  ++top;
}

void pop(int *a, int *b) {
  --top;
  *a = s[top].one;
  *b = s[top].two;
}


int M, N; /* Dimension of input; M is length of a row. */

void update_cache() {
  int m;
  char b;
  for (m = 0; m!=M; ++m) {
    scanf(" %c", &b);
    fprintf(stderr, " %c", b);
    if (b=='0') {
      c[m] = 0;
    } else { ++c[m]; }
  }
  fprintf(stderr, "\n");
}


int main() {
  int m, n;
  scanf("%d %d", &M, &N);
  fprintf(stderr, "Reading %dx%d array (1 row == %d elements)\n", M, N, M);
  c = (int*)malloc((M+1)*sizeof(int));
  s = (Pair*)malloc((M+1)*sizeof(Pair));
  for (m = 0; m!=M+1; ++m) { c[m] = s[m].one = s[m].two = 0; }
  /* Main algorithm: */
  for (n = 0; n!=N; ++n) {
    int open_width = 0;
    update_cache();
    for (m = 0; m!=M+1; ++m) {
      if (c[m]>open_width) { /* Open new rectangle? */
        push(m, open_width);
        open_width = c[m];
      } else /* "else" optional here */
      if (c[m]<open_width) { /* Close rectangle(s)? */
        int m0, w0, area;
        do {
          pop(&m0, &w0);
          area = open_width*(m-m0);
          if (area>best_area) {
            best_area = area;
            best_ll.one = m0; best_ll.two = n;
            best_ur.one = m-1; best_ur.two = n-open_width+1;
          }
          open_width = w0;
        } while (c[m]<open_width);
        open_width = c[m];
        if (open_width!=0) {
          push(m0, w0);
        }
      }
    }
  }
  fprintf(stderr, "The maximal rectangle has area %d.\n", best_area);
  fprintf(stderr, "Location: [col=%d, row=%d] to [col=%d, row=%d]\n",
                  best_ll.one+1, best_ll.two+1, best_ur.one+1, best_ur.two+1);
  return 0;
}