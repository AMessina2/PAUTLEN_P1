segment .data
segment .bss
  __esp resd 1
segment .text
 global main
 extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
 extern print_endofline, print_blank, print_string
 extern alfa_malloc, alfa_free, ld_float
main:
mov dword [__esp], esp
	push dword 6
	push dword 5
pop dword eax
pop dword ebx
add eax, ebx
mov edx, 10
jg masdediez0
push dword 1
call print_int
jmp fin0
masdediez0:
push dword 0
call print_int
fin0:
	add esp, 4
	push dword 4
	push dword 4
pop dword eax
pop dword ebx
add eax, ebx
mov edx, 10
jg masdediez1
push dword 1
call print_int
jmp fin1
masdediez1:
push dword 0
call print_int
fin1:
	add esp, 4
mov dword esp, [__esp]
ret
