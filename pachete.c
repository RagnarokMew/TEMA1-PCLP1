#include<stdio.h>

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
  unsigned char prioritate; //pt a salva spatiu (in cerinta nu -sa specificat tipul)
  float greutate;
  char* mesaj;
  int codificareMesaj;
} pachet;

int main()
{
  return 0;
}
