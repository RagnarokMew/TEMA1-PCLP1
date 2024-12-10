#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct {
  int id;
  char* nume;
} cartier;

typedef struct {
  int id;
  int adresa[18];
  int idCartier;
  int strada;
  int numar;
  unsigned char prioritate; //pt a salva spatiu (in cerinta nu s-a specificat tipul)
  float greutate;
  char* mesaj;
  int codificareMesaj;
} pachet;

typedef struct {
  int id;
  int nrPachete;
  int distribuite[50];
} postas;

int main()
{
  return 0;
}
