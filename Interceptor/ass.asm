extern on_enter:Proc

.code
;--------------------------------------------------------------------
; _penter procedure
;--------------------------------------------------------------------
	PUSHREGS	macro
		push	rax
		push	rcx
		push	rdx
		push	r8
		push	r9
		push	r10
		push	r11
	endm

	POPREGS	macro
		pop	r11
		pop	r10
		pop	r9
		pop	r8
		pop	rdx
		pop	rcx
		pop	rax
	endm

_penter proc
	push rax
	lahf
	; Store the volatile registers
	PUSHREGS
	sub rsp, 8+16
	movdqu xmmword ptr[rsp], xmm0
	sub rsp ,8
	sub  rsp,28h 

	; Get the return address of the function
	mov  rcx,rsp
	mov  rcx,qword ptr[rcx+136]
	;sub  rcx,5
	
	;call the function to get the name of the callee and caller	
	call on_enter

	add  rsp,28h
	add rsp, 8 
	movdqu xmm0, xmmword ptr[rsp]
	add rsp, 8+ 16
	;Restore the registers back by poping out
	POPREGS
	sahf
	pop rax
	
	ret

_penter endp
end