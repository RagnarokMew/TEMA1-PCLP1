#include<stdio.h>
#include<stdlib.h>
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
  int prioritate;
  float greutate;
  char* mesaj;
  int codificareMesaj;
} pachet;

typedef struct {
  int id;
  int nrPachete;
  int distribuite[50];
} postas;

void readInput(int* nrC, int* nrP, cartier** cartiere, pachet** pachete);

void freeAll(int nrC, int nrP, cartier* cartiere, pachet* pachete);

void outputCerinta1(int nrC, cartier* cartiere, int nrP, pachet* pachete);

void processAddress(pachet* target);

int main()
{
  //alegerea taskului selectat
  int task;
  scanf("%d", &task);

  //Declarare + citire input
  pachet* pachete;
  cartier* cartiere;
  int nrP, nrC;
  readInput(&nrC, &nrP, &cartiere, &pachete);

  //selectarea cerintei / taskului
  switch(task) {
    case 1:
      //!TODO
      outputCerinta1(nrC, cartiere, nrP, pachete);
      break;
    case 2:
      //!TODO
      break;
    case 3:
      //!TODO
      break;
    case 4:
      //!TODO
      break;
    case 5:
      //!TODO
      break;
    case 6:
      //!TODO
      break;
    case 7:
      //!TODO
      break;
    default:
      printf("No such task.");
      break;
  }

  freeAll(nrC, nrP, cartiere, pachete);
  return 0;
}

// Cerinta 1.1: citeste datele de intrare
void readInput(int* nrC, int* nrP, cartier** cartiere, pachet** pachete) {
  // Citire cartiere
  scanf("%d", nrC);
  *cartiere = (cartier*)malloc(*nrC * sizeof(cartier));
  for(int i = 0; i < *nrC; i++) {
    (*cartiere)[i].id = i;
    char buff[1024];
    scanf("%s", buff);
    (*cartiere)[i].nume = (char*)malloc(strlen(buff) + 1);
    strcpy((*cartiere)[i].nume, buff);
  }

  //Citire pachete
  scanf("%d", nrP);
  *pachete = (pachet*)malloc(*nrP * sizeof(pachet));
  for(int i = 0; i < *nrP; i++) {
    (*pachete)[i].id = i;
    for(int j = 0; j < 18; j++)
      scanf("%d", &(*pachete)[i].adresa[j]);
    scanf("%d", &(*pachete)[i].prioritate);
    scanf("%f", &(*pachete)[i].greutate);
    char buff[1024];
    fgets(buff, 1024, stdin);
    buff[strlen(buff)-1]= '\0';
    (*pachete)[i].mesaj = (char*)malloc(strlen(buff)+1);
    strcpy((*pachete)[i].mesaj,buff);

    //seteaza defaultul pt valori pt a putea fi modificate mai tarziu
    (*pachete)[i].strada = 0;
    (*pachete)[i].idCartier = 0;
    (*pachete)[i].numar = 0;
  }
}

// Elibereaza memoria alocata dinamic structurilor
void freeAll(int nrC, int nrP, cartier* cartiere, pachet* pachete) {
  for(int i = 0; i < nrC; i++)
    free(cartiere[i].nume);
  free(cartiere);

  for(int i = 0; i < nrP; i++)
    free(pachete[i].mesaj);
  free(pachete);
}

void outputCerinta1(int nrC, cartier* cartiere, int nrP, pachet* pachete) {
  for(int i = 0; i < nrC; i++)
    printf("%d %s\n", cartiere[i].id, cartiere[i].nume);

  for(int i = 0; i < nrP; i++) {
    printf("%d\n", pachete[i].id);
    for(int j = 0; j < 18; j++)
      printf("%d ",pachete[i].adresa[j]);
    printf("\n%.3f\n",pachete[i].greutate);
    printf("%s\n",pachete[i].mesaj);
  }
}

void processAddress(pachet* target) {
  // extract idCartier
  int pow = 1;
  for(int i = 4; i >= 0; i--) {
    target->idCartier+=pow*target->adresa[i];
    pow*=2;
  }

  // extract strada
  pow = 1;
  for(int i = 9; i >= 5; i++) {
    target->strada+=target->adresa[i];
    pow*=2;
  }

  // extract numar
  pow = 1;
  for(int i = 17; i >= 10; i++) {
    target->numar+=target->adresa[i];
    pow*=2;
  }
}
