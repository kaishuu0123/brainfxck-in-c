#include <stdio.h>
#include <stdlib.h>

int p, r;
char data[30000], src_buffer[30000], b, *s = src_buffer;

void interpret(char *c) {
  char *d;

  r++;
  while (*c) {
    switch(*c++) {
    case '<':
      p--;
      break;
    case '>':
      p++;
      break;
    case '+':
      data[p]++;
      break;
    case '-':
      data[p]--;
      break;
    case '.':
      putchar(data[p]);
      fflush(stdout);
      break;
    case ',':
      data[p] = getchar();
      fflush(stdout);
      break;
    case '[':
      for (b = 1, d = c; b && *c; c++) {
        b += *c == '[';
        b -= *c == ']';
      }

      if (!b) {
        c[-1] = 0;
        while (data[p])
          interpret(d);
        c[-1] = ']';
        break;
      }
    case ']':
      puts("Unblaced brakets"), exit(0);
      break;
    default:
      /* NOTHING DONE */
      break;
    }

    if (p < 0 || p > 100)
      puts("Range error"), exit(0);
  }
  r--;
}

int main(int argc, char *argv[]) {
  FILE *f;

  if (argc <= 1) {
    printf("%s [brainfxck source]\n", argv[0]);
    exit(1);
  }

  if ((f = fopen(argv[1], "r"))) {
    while ((b = getc(f)) > 0)
      *s++ = b;
    *s = 0;
    interpret(src_buffer);
  }

  return 0;
}
