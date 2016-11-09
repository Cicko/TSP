#test_bit_64.s
#
.section .data

.section .text

.global test_bit_64 

.type test_bit_64, @function
test_bit_64:

# pushq  %rcx
# pushq  %rcx
# pushq  %rdx
# pushq  %r8
 
 
 andq   $0 , %rax               # Inicializa el acumulador       
 movb   %sil, %al                # Introduce posición a comprobar en el acumulador 
 shrb   $6 , %al                # Divide por 64 el acumulador para establecer la posición en ax el cociente
 
 leaq   (%rdi, %rax, 8), %rcx   # Calcula la posición dentro del array
 
 movb   %sil, %al                # Introduce nuevamente posición a comprobar en el acumulador para calcular el desplazamiento
 andb   $0x3f, %al              # Calcula el resto de la división por 64 eliminando a partir del sexto bit

 btq    %rax, (%rcx)              # Pregunta por el bit en la posición indicada por ax dentro de cx

 jc    is_ok                   # Salta al final si el carry está a 1

 andw   $0, %ax                 # En caso contrario retorna cero 
 jmp is_end

is_ok:
 andw   $0, %ax                 # En caso contrario retorna cero 
 incb   %al                     # Establece a 1 el acumulador si 

is_end:

# popq %r8
# popq %rdx
# popq %rcx
# popq %rcx

 ret

