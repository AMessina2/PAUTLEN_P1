#include "alfa.h"

void ifthenelse_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (exp_es_variable)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "je else_%d\n", etiqueta);
}

void ifthenelse_fin_then(FILE *fpasm, int etiqueta)
{
  fprintf(fpasm, "j finIfThenElse_%d\n", etiqueta);
  fprintf(fpasm, "else_%d: \n", etiqueta);
}

void ifthenelse_fin(FILE *fpasm, int etiqueta)
{
  fprintf(fpasm, "finIfThenElse_%d: \n", etiqueta);
}

void ifthen_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  if (exp_es_variable)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "je finIfThen_%d\n", etiqueta);
}

void ifthen_fin(FILE *fpasm, int etiqueta)
{
  fprintf(fpasm, "finIfThen_%d: \n", etiqueta);
}

void while_inicio(FILE *fpasm, int etiqueta)
{
  fprintf(fpasm, "whileInicio_%d: \n", etiqueta);
}

void while_exp_pila(FILE *fpasm, int exp_es_variable, int etiqueta)
{
  fprintf(fpasm, "pop eax\n");
  fprintf(fpasm, "push eax\n");
  if (exp_es_variable)
  {
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "je whileFin_%d\n", etiqueta);
}

void while_fin(FILE *fpasm, int etiqueta)
{
  fprintf(fpasm, "j whileInicio_%d: \n", etiqueta);
  fprintf(fpasm, "whileFin_%d: \n", etiqueta);
}
void escribir_elemento_vector(FILE *fpasm, char *nombre_vector,
                              int tam_max, int exp_es_direccion)
{
  fprintf(fpasm, "pop dword eax\n");
  if (exp_es_direccion)
  {
    fprintf(fpasm, "mov dword eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "jl near fin_indice_fuera_rango\n");
  fprintf(fpasm, "cmp eax, %d-1\n", tam_max);
  fprintf(fpasm, "jg near fin_indice_fuera_rango\n");
  fprintf(fpasm, "mov dword edx, %s\n", nombre_vector);
  fprintf(fpasm, "lea eax, [edx + eax*4]\n");
  fprintf(fpasm, "push dword eax\n");
}
void declararFuncion(FILE *fd_asm, char *nombre_funcion, int num_var_loc)
{
  fprintf(fd_asm, "%s\n", nombre_funcion);
  fprintf(fd_asm, "push ebp\n");
  fprintf(fd_asm, "mov ebp, esp\n");
  fprintf(fd_asm, "sub esp , 4*%d\n", num_var_loc);
}
void retornarFuncion(FILE *fd_asm, int es_variable)
{
  fprintf(fd_asm, "pop eax\n");
  if (es_variable)
  {
    fprintf(fd_asm, "mov dword eax, [eax]\n");
  }
  fprintf(fd_asm, "mov esp,ebp\n");
  fprintf(fd_asm, "pop ebp\n");
  fprintf(fd_asm, "ret\n");
}
void escribirParametro(FILE *fpasm, int pos_parametro, int num_total_parametros)
{
  int puntero = 4 * (1 + (num_total_parametros - pos_parametro));
  fprintf(fpasm, "lea eax, [ebp + %d]\n", puntero);
  fprintf(fpasm, "push dword eax\n");
}
void escribirVariableLocal(FILE *fpasm, int posicion_variable_local)
{
  int puntero = 4 * posicion_variable_local;
  fprintf(fpasm, "lea eax, [ebp - %d]\n", puntero);
  fprintf(fpasm, "push dword eax\n");
}
void asignarDestinoEnPila(FILE *fpasm, int es_variable)
{
  fprintf(fpasm, "pop dword ebx\n");
  fprintf(fpasm, "pop dword eax\n");
  if (es_variable)
  {
    fprintf(fpasm, "mov dword eax, [eax]\n");
  }
  fprintf(fpasm, "mov dword[ebx], eax\n");
}
void operandoEnPilaAArgumento(FILE *fd_asm, int es_variable)
{
  if (es_variable)
  {
    fprintf(fd_asm, "pop eax\n");
    fprintf(fd_asm, "mov eax, [eax]\n");
    fprintf(fd_asm, "push eax\n");
  }
}
void llamarFuncion(FILE *fd_asm, char *nombre_funcion, int num_argumentos)
{
  fprintf(fd_asm, "call %s\n", nombre_funcion);
  fprintf(fd_asm, "add esp, %d*4\n", num_argumentos);
  fprintf(fd_asm, "push dword eax\n");
}
void limpiarPila(FILE *fd_asm, int num_argumentos)
{
  fprintf(fd_asm, "sub esp , 4*%d\n", num_argumentos);
}