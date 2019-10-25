#include "alfa.h"
void escribir_subseccion_data(FILE *fpasm)
{
  fprintf(fpasm, "segment .data\n");
}
void escribir_cabecera_bss(FILE *fpasm)
{
  fprintf(fpasm, "segment .bss\n  __esp resd 1\n");
}
void escribir_inicio_main(FILE *fpasm)
{
  fprintf(fpasm, "main:\n");
  fprintf(fpasm, "mov dword [__esp], esp\n");
}
void escribir_fin(FILE *fpasm)
{
  fprintf(fpasm, "mov dword esp, [__esp]\n");
  fprintf(fpasm, "ret\n");
}
void escribir_segmento_codigo(FILE *fpasm)
{
  fprintf(fpasm, "segment .text\n");
  fprintf(fpasm, " global main\n");
  fprintf(fpasm, " extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
  fprintf(fpasm, " extern print_endofline, print_blank, print_string\n");
  fprintf(fpasm, " extern alfa_malloc, alfa_free, ld_float\n");
}
void uno_si_mayor_de_10(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop dword eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop dword ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "add eax, ebx\n");
  fprintf(fpasm, "mov edx, 10\n");
  fprintf(fpasm, "jg masdediez%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "call print_int\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "masdediez%d:\n", etiqueta);
  fprintf(fpasm, "push dword 0\n");
  fprintf(fpasm, "call print_int\n");
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void declarar_variable(FILE *fpasm, char *nombre, int tipo, int tamano)
{
  fprintf(fpasm, "_%s resd %d \n", nombre, tamano);
}

void escribir_operando(FILE *fpasm, char *nombre, int es_variable)
{
  if (es_variable)
  {
    fprintf(fpasm, "mov eax, _%s\n", nombre);
  }
  else
  {
    fprintf(fpasm, "mov eax, %s\n", nombre);
  }
  fprintf(fpasm, "push dword eax\n");
}

void asignar(FILE *fpasm, char *nombre, int es_variable)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable)
  {
    fprintf(fpasm, "mov _%s, [eax]\n", nombre);
  }
  else
  {
    fprintf(fpasm, "mov _%s, eax\n", nombre);
  }
}

void sumar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "add eax, ebx\n");
  fprintf(fpasm, "push eax\n");
}

void restar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "sub eax, ebx\n");
  fprintf(fpasm, "push eax\n");
}

void multiplicar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "imul ebx\n");
  fprintf(fpasm, "push eax\n");
}

void dividir(FILE *fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cdq\n");
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "idiv ebx\n");
  fprintf(fpasm, "push eax\n");
}

void o(FILE *fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "or eax, ebx\n");
  fprintf(fpasm, "push eax\n");
}

void y(FILE *fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_2)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "and eax, ebx\n");
  fprintf(fpasm, "push eax\n");
}

void no(FILE *fpasm, int es_variable_1, int cuantos_no)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "mov ebx, 0\n");
  fprintf(fpasm, "inicio_%d:\n", cuantos_no);
  fprintf(fpasm, "cmp eax[ebx], 0\n");
  fprintf(fpasm, "je cambiaA1_%d\n", cuantos_no);
  fprintf(fpasm, "mov eax[ebx], 0\n");
  fprintf(fpasm, "j fin_%d\n", cuantos_no);
  fprintf(fpasm, "cambiaA1_%d:\n", cuantos_no);
  fprintf(fpasm, "mov eax[ebx], 1\n");
  fprintf(fpasm, "fin_%d:\n", cuantos_no);
  fprintf(fpasm, "inc ebx\n");
  fprintf(fpasm, "cmp ebx, 32\n");
  fprintf(fpasm, "jne inicio_%d\n", cuantos_no);
  fprintf(fpasm, "push eax\n");
}

void igual(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "mov ecx, 1\n");
  fprintf(fpasm, "cmp eax, ebx\n");
  fprintf(fpasm, "je igual%d\n", etiqueta);
  fprintf(fpasm, "mov ecx, 0\n");
  fprintf(fpasm, "igual%d: \n", etiqueta);
  fprintf(fpasm, "push ecx\n");
}

void distinto(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "mov ecx, 0\n");
  fprintf(fpasm, "cmp eax, ebx\n");
  fprintf(fpasm, "je distinto%d\n", etiqueta);
  fprintf(fpasm, "mov ecx, 1\n");
  fprintf(fpasm, "distinto%d: \n", etiqueta);
  fprintf(fpasm, "push ecx\n");
}

void menor_igual(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "mov ecx, 1\n");
  fprintf(fpasm, "cmp eax, ebx\n");
  fprintf(fpasm, "jle menorIgual%d\n", etiqueta);
  fprintf(fpasm, "mov ecx, 0\n");
  fprintf(fpasm, "menorIgual%d: \n", etiqueta);
  fprintf(fpasm, "push ecx\n");
}

void mayor_igual(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "mov ecx, 1\n");
  fprintf(fpasm, "cmp eax, ebx\n");
  fprintf(fpasm, "jge mayorIgual%d\n", etiqueta);
  fprintf(fpasm, "mov ecx, 0\n");
  fprintf(fpasm, "mayorIgual%d: \n", etiqueta);
  fprintf(fpasm, "push ecx\n");
}

void mayor(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "mov ecx, 1\n");
  fprintf(fpasm, "cmp eax, ebx\n");
  fprintf(fpasm, "jg mayor%d\n", etiqueta);
  fprintf(fpasm, "mov ecx, 0\n");
  fprintf(fpasm, "mayor%d: \n", etiqueta);
  fprintf(fpasm, "push ecx\n");
}

void menor(FILE *fpasm, int es_variable_1, int es_variable_2, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "pop ebx\n");
  if (es_variable_1)
  {
    fprintf(fpasm, "mov ebx, [ebx]\n");
  }
  fprintf(fpasm, "mov ecx, 1\n");
  fprintf(fpasm, "cmp eax, ebx\n");
  fprintf(fpasm, "jl menor%d\n", etiqueta);
  fprintf(fpasm, "mov ecx, 0\n");
  fprintf(fpasm, "menor%d: \n", etiqueta);
  fprintf(fpasm, "push ecx\n");
}

void leer(FILE *fpasm, char *nombre, int tipo)
{
  fprintf(fpasm, "push dword %s\n", nombre);
  if (tipo == 1)
  {
    fprintf(fpasm, "call scan_boolean\n");
  }
  else
  {
    fprintf(fpasm, "call scan_int\n");
  }
  fprintf(fpasm, "add esp, 4\n");
}

void escribir(FILE *fpasm, int es_variable, int tipo)
{
  fprintf(fpasm, "pop eax\n");
  if (es_variable)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "push dword eax\n");
  if (tipo == 1)
  {
    fprintf(fpasm, "call print_boolean\n");
  }
  else
  {
    fprintf(fpasm, "call print_int\n");
  }
  fprintf(fpasm, "add esp, 4\n");
}