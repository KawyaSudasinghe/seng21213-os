[BITS 32]
global ctx_switch

; void ctx_switch(uint32_t *old_esp, uint32_t new_esp);
ctx_switch:
    ; 1. Save general registers and flags of current process
    pusha
    pushf

    ; 2. Retrieve arguments from original stack position
    mov eax, [esp + 40]    ; pointer to old_esp
    mov ecx, [esp + 44]    ; new_esp value

    ; 3. Store current ESP into old process PCB
    mov [eax], esp

    ; 4. Switch to new process stack
    mov esp, ecx

    ; 5. Restore registers and flags of new process
    popf
    popa
    ret
