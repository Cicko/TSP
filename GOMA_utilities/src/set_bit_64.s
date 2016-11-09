#set_bit_64.s
#
.section .data

.section .text

.global set_bit_64 

.type set_bit_64, @function
set_bit_64:


 andq   $0 , %rax               # Inicializa el acumulador       
 movb   %sil, %al                # Introduce posición a comprobar en el acumulador 
 shrb   $6 , %al                # Divide por 64 el acumulador para establecer la posición en ax el cociente

 leaq   (%rdi, %rax, 8), %rcx   # Calcula la posición dentro del array

 movb   %sil, %al                # Introduce nuevamente posición a comprobar en el acumulador para calcular el desplazamiento
 andb   $0x3f, %al              # Calcula el resto de la división por 64 eliminando a partir del sexto bit

 btsq   %rax, (%rcx)           # Establece a uno el bit seleccionado

 ret



