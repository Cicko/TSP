#reset_bit_64.s
#
.section .data

.section .text

.global reset_bit_64 

.type reset_bit_64, @function
reset_bit_64:

# pushq  %rax
 pushq  %rbx
# pushq  %rcx
# pushq  %rdx

 movq   %rsi, %rax           # Introduce posición en el acumulador
 movq   $0, %rdx
 movq   $64, %r8             # Almacena el divisor
 divq   %r8                  # Computar base y desplazamiento resto en dx
                             # cociente en ax

 leaq   (%rdi, %rax, 8), %rbx   # Calcula la posición dentro del array
 movq   (%rbx), %rcx         # Carga la posición en el registro cx

 btrq   %rdx, %rcx           # Establece a uno el bit seleccionado

 movq   %rcx, (%rbx)         # Almacena la palabra modificada en su posición

# popq %rdx
# popq %rcx
popq %rbx
# popq %rax

 ret



