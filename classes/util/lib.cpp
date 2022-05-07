#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

extern "C" {
void imprimei(int i) { cout << i << endl; }

void imprimer(double r) { cout << r << endl; }

void imprimec(char *c) { cout << c << endl; }

void emite() { cout.flush(); }

char *lc() {
  char *result = new char[2];
  result[1] = '\0';
  if (cin >> result[0])
    return result;
  else {
    result[0] = '\0';
    return result;
  }
}

int li() {
  int inteiro;
  cin >> inteiro;
  return inteiro;
}

double lr() {
  double real;
  cin >> real;
  return real;
}

int ordem(char *c) {
  if (*c > 127 || *c < 0)
    return -1;
  else
    return (int)*c;
}

char *chr(int i) {
  if (i > 127 || i < 0)
    exit(-1);
  char *cadeia = new char[2];
  cadeia[0] = (char)(i);
  cadeia[1] = '\0';
  return cadeia;
}

int tamanho(char *c) { return strlen(c); }

char *subcadeia(char *c, int i, int n) {
  char *result = new char[n + 1];
  memcpy(result, c + i, n);
  result[n] = '\0';
  return result;
}

char *concatene(char *c1, char *c2) {
  auto len1 = strlen(c1), len2 = strlen(c2);
  auto len = len1 + len2;
  char *result = new char[len + 1];
  memcpy(result, c1, len1);
  memcpy(result + len1, c2, len2);
  result[len] = '\0';
  return result;
}

int inverter(int i) { return i == 0; }

void termine(int i) { exit(i); }

int gere_inteiro() { return rand(); }

double gere_real() {
  double f = (double)rand() / RAND_MAX;
  return numeric_limits<double>::min() +
         f * (numeric_limits<double>::max() - numeric_limits<double>::min());
}
}
