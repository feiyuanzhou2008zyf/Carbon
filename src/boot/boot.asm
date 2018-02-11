%define SWITCH_USE_CHS_READ_SECTOR_TO_MEMORY
MEMORY_ADDR_BOOT_CODE_ORG_ENTRY equ 0x7c00
MEMORY_ADDR_LOADER_MODULE equ 0x7e00
MEMORY_ADDR_STACK_TOP equ 0x7c00
MEMORY_ADDR_SECTOR_NEED_COPY_TO_DEST equ MEMORY_ADDR_LOADER_MODULE
CNT_PARTITION_ENTRY equ 4
BYTE_FLAG_PARTITION_ACTIVE equ 0x80
LEN_PARTITION_ENTRY equ 0x10
PARTITION_TYPE_FAT32_WITH_CHS_ADDRESSING equ 0x0b
PARTITION_TYPE_FAT32_WITH_LBA equ 0x0c
BIT_VALID_PARTITION_SET equ 00000001b
BIT_VALID_PARTITION_CLR equ 11111110b
bits 16
org MEMORY_ADDR_BOOT_CODE_ORG_ENTRY
	cli
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,MEMORY_ADDR_STACK_TOP
	mov byte[byte_status],al
	mov byte[byte_udisk_sn],al
	mov word[word_disk_head_number],ax
	mov word[word_disk_sector_number],ax
	sti
	cld
	mov si,sp
	mov [byte_udisk_sn],dl
	mov si,str_start_boot_from_usb_device
	call fn_disp_str
	mov si,addr_partition_table
	xor ax,ax
	mov cx,CNT_PARTITION_ENTRY
label_verify_partition_entry_do_once:
	test byte [si],BYTE_FLAG_PARTITION_ACTIVE
	jz label_verify_partition_entry_next
	inc ax
	mov bp,si
label_verify_partition_entry_next:
	add si,LEN_PARTITION_ENTRY
	loop label_verify_partition_entry_do_once
	dec ax
	jz label_proc_valid_partition_table
	mov si,str_invalid_partition_table
	jmp label_show_msg_and_loop_dead
label_proc_valid_partition_table:
	pusha
	mov dl,[byte_udisk_sn]
	mov ah,41h
	mov bx,55AAh
	int 13h
	jb short not_support_int_13h_extensions
	cmp bx,0AA55h
	jnz not_support_int_13h_extensions
	test cl,1
	jz not_support_int_13h_extensions
	%ifdef SWITCH_USE_CHS_READ_SECTOR_TO_MEMORY
		jmp not_support_int_13h_extensions
	%else
		mov al,[byte_status]
		or al,BIT_VALID_PARTITION_SET
		mov byte[byte_status],al
		jmp label_read_sectors_into_memory
	%endif
not_support_int_13h_extensions:
	mov dl,[byte_udisk_sn]
	mov di,0
	mov ah,8
	stc
	int 13h
	jb label_cant_get_chs
	and ah,ah
	jnz label_cant_get_chs
	mov al,dh
	inc al
	jz label_cant_get_chs
	jmp label_save_chs
label_cant_get_chs:
	mov si,str_error_cant_get_chs
	call label_show_msg_and_loop_dead
label_save_chs:
	mov [word_disk_head_number],ax
	mov [word_disk_sector_number],cx
label_read_sectors_into_memory:
	popa
	xor cx,cx
	mov ax,[bp + 8]
	mov dx,[bp + 0Ah]
	mov bx,MEMORY_ADDR_SECTOR_NEED_COPY_TO_DEST
	call fn_read_sectors_into_memory
	jnb ok_proc_read_sectors_into_memory
retry_proc_read_sectors_into_memory:
	cmp byte [bp + 4],PARTITION_TYPE_FAT32_WITH_CHS_ADDRESSING
	jnz loc_B3
	cmp byte [bp + 4],PARTITION_TYPE_FAT32_WITH_LBA
	jz loc_B3
	jmp err_loading_operating_system
loc_B3:
	inc cx
	add ax,6
	adc dx,0
	call fn_read_sectors_into_memory
	jnb ok_proc_read_sectors_into_memory
err_loading_operating_system:	
	mov si,str_err_loading_operating_system
	jmp label_show_msg_and_loop_dead
ok_proc_read_sectors_into_memory:	
	mov ax,[ds:7DFEh]
	cmp ax,0AA55h
	jz ok_boot_signature
	or cx,cx
	jz retry_proc_read_sectors_into_memory
	jmp err_loading_operating_system
ok_boot_signature:
	mov dl,[byte_udisk_sn]
	mov si,bp
	cli
	jne MEMORY_ADDR_SECTOR_NEED_COPY_TO_DEST
label_show_msg_and_loop_dead:
	call fn_disp_str
	jmp $
fn_disp_str:
	lodsb
	and al,al
	jz fn_disp_str_end
	mov ah,0Eh
	mov bx,7
	int 10h
	jmp fn_disp_str
fn_disp_str_end:
	ret
fn_read_sectors_into_memory:
	push di
	mov di,5
fn_read_sectors_into_memory_retry:
	pusha
	xor cx,cx
	push cx
	push cx
	push dx
	push ax
	push cx
	push bx
	inc cx
	push cx
	push 0010h
	mov si,sp
	test byte[byte_status],BIT_VALID_PARTITION_SET
	jz label_read_disk_to_memory_by_chs
	mov ah,0x42
	mov dl,[byte_udisk_sn]	
	jmp label_read_disk_to_memory_by_int_13h
label_read_disk_to_memory_by_chs:
	div word [word_disk_sector_number]
	inc dx
	mov cx,dx
	xor dx,dx
	div word [word_disk_head_number]
	mov ch,al
	shr ax,2
	and al,0C0h
	or cl,al
	mov dh,dl
	mov dl,[byte_udisk_sn]
	mov ax,201h
label_read_disk_to_memory_by_int_13h:
	int 13h
	lea sp,[si + 10h]
	popa
	jb fn_read_sectors_into_memory_end
	cmp ah,0x00
	jz fn_read_sectors_into_memory_ok
	dec di
	pusha
	xor ah,ah
	mov dl,[byte_udisk_sn]
	int 13h
	popa
	jmp label_read_sectors_into_memory_retry
fn_read_sectors_into_memory_ok:	
	clc
dn_read_sectors_into_memory_end:
	pop di
	ret
str_start_boot_from_usb_device:
	db 0x0d,0x0a,"Booting...",0x0d,0x0a,0
str_invalid_partition_table:
	db 0x0d,0x0a,"Invalid partition table",0x0d,0x0a,0
str_mbr_code_execute_over:
	db "MBR end execute",0x0d,0x0a,0
str_err_loading_operating_system:
	db "Error loading operating system",0x0d,0x0a,0
str_error_cant_get_chs:
	db "Can't get CHS",0x0d,0x0a,0
byte_status:
	db 0xcd
byte_udisk_sn:
	db 0xcd
word_disk_head_number:
	dw 0xcdcd
word_disk_sector_number:
	dw 0xcdcd
times 512 - ($ - $$) - 2 - (16 * 4) db 0
addr_partition_table:
	db 0x80,0x00,0x02,0x00,0x0c,0xfe,0xff,0xaf,0x01,0x00,0x00,0x00,0xff,0x3f,0xe7,0x00  
    db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  
    db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  
    db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
addr_word_boot_signature:
	db 0x55,0xaa