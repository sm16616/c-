#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"

// TODO: upgrade the run function, adding functions to support it.

struct state {
    int X;
    int xprevious;
    int Y;
    int yprevious;
    bool pause;
    bool pen;
    int length;
    int opcodeExtended;
    int ExtendedByte;
    int ExtendedNegative;
    int colour;
};
typedef struct state State;

void COL(State *s) {
  s->colour = s->ExtendedByte;
}

void opcode0 (State *s, int32_t operand) {
  s->xprevious = s->X;
  s->X = s->X + operand;
}

void opcode0extended (State *s) {
  s->xprevious = s->X;
  s->X = s->X + s->ExtendedNegative;
}

void opcode1 (State *s, int32_t operand, display *d) {
  s->yprevious = s->Y;
  s->Y = s->Y + operand;

  if (s->pen) {
    if (s->colour == 255) {
      line(d, s->xprevious, s->yprevious, s->X, s->Y);
    }
    else {
      cline(d, s->X, s->Y, s->xprevious, s->yprevious, s->colour);
    }
  } s->xprevious = s->X;
}

void opcode1extended (State *s, display *d) {
  s->yprevious = s->Y;
  s->Y = s->Y + s->ExtendedNegative;

  if (s->pen) {
    if (s->colour == 255) {
      line(d, s->xprevious, s->yprevious, s->X, s->Y);
    }
    else {
      cline(d, s->X, s->Y, s->xprevious, s->yprevious, s->colour);
    }
  }  s->xprevious = s->X;
}

void opcode2 (State *s, display *d) {
  pause(d, s->ExtendedByte);
}

void opcode3 (State *s) {
  s->pen = !s->pen;
}

void extractExtended (State *s, FILE *in, display *d, char b) {
  s->ExtendedByte = 0;

  if (s->length == 3) {
    s->length = 4;
  }
  for (int i = 0; i < s->length; ++i) {
    b = fgetc(in);
    s->ExtendedByte = (s->ExtendedByte << 8) + ((b) & 0xFF);
  }

  if (s->length == 1 && s->ExtendedByte > 127) {
    s->ExtendedNegative = s-> ExtendedByte - 256;
  }

  if (s->length == 2 && s->ExtendedByte > 32767) {
    s->ExtendedNegative = s-> ExtendedByte - 65536;
  }

  else {
    s->ExtendedNegative = s->ExtendedByte;
  }

switch (s->opcodeExtended) {
case 0:
opcode0extended(s);
break;
case 1:
opcode1extended(s, d);
break;
case 2:
opcode2(s, d);
break;
case 3:
opcode3(s);
break;
case 4:
clear(d);
break;
case 5:
key(d);
break;
case 6:
COL(s);
break;
default:
break;
}
}

void extract(char b, int opcode, int operand, State *s, display *d, FILE *in) {
  opcode = (b >> 6) & 0x03;
  operand = ((b) & 0x3F);
  int Operand = operand;
  s->length = (b >> 4) & 0x03;
  s->opcodeExtended = (b & (0x07));

  if (operand > 32) {
    operand = operand - 64;
  }
  switch (opcode) {
  case 0:
  opcode0(s, operand);
  break;
  case 1:
  opcode1(s, operand, d);
  break;
  case 2:
  s->ExtendedByte = Operand;
  opcode2(s,d);
  break;
  case 3:
  extractExtended(s, in, d, b);
  break;
  default:
  break;
}
}

void interpret(FILE *in, display *d) {
  State sdata = {0,0,0,0,false,false,0,0,0,0,255};
  State *s = &sdata;
  int opcode = 0;
  int operand = 0;
  unsigned char b = fgetc(in);
  while (! feof(in)) {
    extract(b, opcode, operand, s, d, in);
    //printf("%02x\n", b);
    b = fgetc(in);
  }
}


// Read sketch instructions from the given file.  If test is NULL, display the
// result in a graphics window, else check the graphics calls made.

void run(char *filename, char *test[]) {
    FILE *in = fopen(filename, "rb");
    if (in == NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }
    display *d = newDisplay(filename, 200, 200, test);
    interpret(in, d);
    end(d);
    fclose(in);
}

// ----------------------------------------------------------------------------
// Nothing below this point needs to be changed.
// ----------------------------------------------------------------------------

// Forward declaration of test data.
char **lineTest, **squareTest, **boxTest, **oxoTest, **diagTest, **crossTest,
     **clearTest, **keyTest, **pausesTest, **fieldTest, **lawnTest;

void testSketches() {
    // Stage 1
    run("line.sketch", lineTest);
    run("square.sketch", squareTest);
    run("box.sketch", boxTest);
    run("oxo.sketch", oxoTest);

    // Stage 2
    run("diag.sketch", diagTest);
    run("cross.sketch", crossTest);

    // Stage 3
    run("clear.sketch", clearTest);
    run("key.sketch", keyTest);

    // Stage 4
    run("pauses.sketch", pausesTest);
    run("field.sketch", fieldTest);
    run("lawn.sketch", lawnTest);
}

int main(int n, char *args[n]) {
    if (n == 1) testSketches();
    else if (n == 2) run(args[1], NULL);
    else {
        fprintf(stderr, "Usage: sketch [file.sketch]");
        exit(1);
    }
}

// Each test is a series of calls, stored in a variable-length array of strings,
// with a NULL terminator.

// The calls that should be made for line.sketch.
char **lineTest = (char *[]) {
    "line(d,30,30,60,30)", NULL
};

// The calls that should be made for square.sketch.
char **squareTest = (char *[]) {
    "line(d,30,30,60,30)","line(d,60,30,60,60)",
    "line(d,60,60,30,60)","line(d,30,60,30,30)", NULL
};

// The calls that should be made for box.sketch.
char **boxTest = (char *[]) {
    "line(d,30,30,32,30)", "pause(d,10)", "line(d,32,30,34,30)", "pause(d,10)",
    "line(d,34,30,36,30)", "pause(d,10)", "line(d,36,30,38,30)", "pause(d,10)",
    "line(d,38,30,40,30)", "pause(d,10)", "line(d,40,30,42,30)", "pause(d,10)",
    "line(d,42,30,44,30)", "pause(d,10)", "line(d,44,30,46,30)", "pause(d,10)",
    "line(d,46,30,48,30)", "pause(d,10)", "line(d,48,30,50,30)", "pause(d,10)",
    "line(d,50,30,52,30)", "pause(d,10)", "line(d,52,30,54,30)", "pause(d,10)",
    "line(d,54,30,56,30)", "pause(d,10)", "line(d,56,30,58,30)", "pause(d,10)",
    "line(d,58,30,60,30)", "pause(d,10)", "line(d,60,30,60,32)", "pause(d,10)",
    "line(d,60,32,60,34)", "pause(d,10)", "line(d,60,34,60,36)", "pause(d,10)",
    "line(d,60,36,60,38)", "pause(d,10)", "line(d,60,38,60,40)", "pause(d,10)",
    "line(d,60,40,60,42)", "pause(d,10)", "line(d,60,42,60,44)", "pause(d,10)",
    "line(d,60,44,60,46)", "pause(d,10)", "line(d,60,46,60,48)", "pause(d,10)",
    "line(d,60,48,60,50)", "pause(d,10)", "line(d,60,50,60,52)", "pause(d,10)",
    "line(d,60,52,60,54)", "pause(d,10)", "line(d,60,54,60,56)", "pause(d,10)",
    "line(d,60,56,60,58)", "pause(d,10)", "line(d,60,58,60,60)", "pause(d,10)",
    "line(d,60,60,58,60)", "pause(d,10)", "line(d,58,60,56,60)", "pause(d,10)",
    "line(d,56,60,54,60)", "pause(d,10)", "line(d,54,60,52,60)", "pause(d,10)",
    "line(d,52,60,50,60)", "pause(d,10)", "line(d,50,60,48,60)", "pause(d,10)",
    "line(d,48,60,46,60)", "pause(d,10)", "line(d,46,60,44,60)", "pause(d,10)",
    "line(d,44,60,42,60)", "pause(d,10)", "line(d,42,60,40,60)", "pause(d,10)",
    "line(d,40,60,38,60)", "pause(d,10)", "line(d,38,60,36,60)", "pause(d,10)",
    "line(d,36,60,34,60)", "pause(d,10)", "line(d,34,60,32,60)", "pause(d,10)",
    "line(d,32,60,30,60)", "pause(d,10)", "line(d,30,60,30,58)", "pause(d,10)",
    "line(d,30,58,30,56)", "pause(d,10)", "line(d,30,56,30,54)", "pause(d,10)",
    "line(d,30,54,30,52)", "pause(d,10)", "line(d,30,52,30,50)", "pause(d,10)",
    "line(d,30,50,30,48)", "pause(d,10)", "line(d,30,48,30,46)", "pause(d,10)",
    "line(d,30,46,30,44)", "pause(d,10)", "line(d,30,44,30,42)", "pause(d,10)",
    "line(d,30,42,30,40)", "pause(d,10)", "line(d,30,40,30,38)", "pause(d,10)",
    "line(d,30,38,30,36)", "pause(d,10)", "line(d,30,36,30,34)", "pause(d,10)",
    "line(d,30,34,30,32)", "pause(d,10)", "line(d,30,32,30,30)", "pause(d,10)",
    NULL
};

// The calls that should be made for box.sketch.
char **oxoTest = (char *[]) {
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,30,40,60,40)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,30,50,60,50)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,40,30,40,60)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,50,30,50,60)", NULL
};

// The calls that should be made for diag.sketch.
char **diagTest = (char *[]) {
    "line(d,30,30,60,60)", NULL
};

// The calls that should be made for cross.sketch.
char **crossTest = (char *[]) {
    "line(d,30,30,60,60)", "line(d,60,30,30,60)", NULL
};

// The calls that should be made for clear.sketch.
char **clearTest = (char *[]) {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
    "line(d,50,30,50,60)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "clear(d)", "line(d,30,30,60,60)",
    "line(d,60,30,30,60)", NULL
};

// The calls that should be made for key.sketch.
char **keyTest = (char *[]) {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
    "line(d,50,30,50,60)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "key(d)", "clear(d)", "line(d,30,30,60,60)",
    "line(d,60,30,30,60)", NULL
};

// The calls that should be made for diag.sketch.
char **pausesTest = (char *[]) {
    "pause(d,0)", "pause(d,0)", "pause(d,127)", "pause(d,128)", "pause(d,300)",
    "pause(d,0)", "pause(d,71469)", NULL
};

// The calls that should be made for field.sketch.
char **fieldTest = (char *[]) {
    "line(d,30,30,170,30)", "line(d,170,30,170,170)",
    "line(d,170,170,30,170)", "line(d,30,170,30,30)", NULL
};

// The calls that should be made for field.sketch.
char **lawnTest = (char *[]) {
    "cline(d,30,30,170,30,16711935)", "cline(d,170,30,170,170,16711935)",
    "cline(d,170,170,30,170,16711935)", "cline(d,30,170,30,30,16711935)",
    NULL
};
