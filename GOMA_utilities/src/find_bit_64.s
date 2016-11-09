#find_bit_64.s
#
.section .data

.section .text

.global find_bit_64 

.type find_bit_64, @function
find_bit_64:

 bsfq   (%rdi), %rbx         # Busca el índice del bit menos significativo 
 jz     is_zero              # Si es cero retorna uno
 
 btcq   %rbx, (%rdi)         # Sino pone el bit a cero
 movq   %rbx, (%rsi)         # Almacena el resultado en el segundo parámetro 
 movq   $0x0, %rax           # Y retorna cero
 jmp    end_find_bit_64
 
is_zero: 
 movq   $0x1, %rax           # Retorna 1
 
end_find_bit_64:
 ret
