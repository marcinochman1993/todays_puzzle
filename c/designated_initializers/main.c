/* gcc main.c -std=c99 */
#include <stdio.h>

#define TAB_SIZE 10

typedef struct PersonS
{
  int id;
  int age;
  int height;
  int weight;
} Person;


void printPerson(Person* person)
{
  printf("Id: %d, Age: %d, height: %d cm, weight: %d kg\n", person->id,
         person->age, person->height,
         person->weight);
}

void printTab(int* tab, int size)
{
  if(size <= 0)
    return;

  printf("[");
  for(int i = 0; i < size - 1; ++i)
  {
    printf("%d, ", tab[i]);
  }

  printf("%d]\n", tab[size - 1]);
}

int main(int argc, char *argv[argc])
{
  Person person = {.age = 30, .height = 170, .weight = 75};

  printPerson(&person);

  int tab[TAB_SIZE] = {[5] = 10, [3] = 20};

  printTab(tab, TAB_SIZE);

  return 0;
}
