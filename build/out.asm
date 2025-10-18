	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"r3clib.addc5735-cgu.0"
	.def	_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17h71814a0963b01d65E;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17h71814a0963b01d65E
	.p2align	4, 0x90
_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17h71814a0963b01d65E:
.seh_proc _ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17h71814a0963b01d65E
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	rcx
	#APP
	#NO_APP
	nop
	add	rsp, 40
	ret
	.seh_endproc

	.def	_ZN3std2rt10lang_start17hf1db9f1ca3fe9af2E;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN3std2rt10lang_start17hf1db9f1ca3fe9af2E
	.globl	_ZN3std2rt10lang_start17hf1db9f1ca3fe9af2E
	.p2align	4, 0x90
_ZN3std2rt10lang_start17hf1db9f1ca3fe9af2E:
.seh_proc _ZN3std2rt10lang_start17hf1db9f1ca3fe9af2E
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	rax, r8
	mov	r8, rdx
	mov	qword ptr [rsp + 48], rcx
	mov	byte ptr [rsp + 32], r9b
	lea	rdx, [rip + __unnamed_1]
	lea	rcx, [rsp + 48]
	mov	r9, rax
	call	_ZN3std2rt19lang_start_internal17h9b461f8940399158E
	nop
	add	rsp, 56
	ret
	.seh_endproc

	.def	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h0ddb4740e49dcbe7E;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h0ddb4740e49dcbe7E
	.p2align	4, 0x90
_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h0ddb4740e49dcbe7E:
.seh_proc _ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h0ddb4740e49dcbe7E
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	rcx, qword ptr [rcx]
	call	_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17h71814a0963b01d65E
	xor	eax, eax
	add	rsp, 40
	ret
	.seh_endproc

	.def	_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17hdc3595f6fa9237f6E;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17hdc3595f6fa9237f6E
	.p2align	4, 0x90
_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17hdc3595f6fa9237f6E:
.seh_proc _ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17hdc3595f6fa9237f6E
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	rcx, qword ptr [rcx]
	call	_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17h71814a0963b01d65E
	xor	eax, eax
	add	rsp, 40
	ret
	.seh_endproc

	.def	_ZN4core3ptr42drop_in_place$LT$alloc..string..String$GT$17h865e2c17f2a9678fE;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN4core3ptr42drop_in_place$LT$alloc..string..String$GT$17h865e2c17f2a9678fE
	.p2align	4, 0x90
_ZN4core3ptr42drop_in_place$LT$alloc..string..String$GT$17h865e2c17f2a9678fE:
	test	rdx, rdx
	je	.LBB4_1
	mov	r8, rdx
	not	r8
	shr	r8, 63
	jmp	__rust_dealloc
.LBB4_1:
	ret

	.def	_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17h719ecb3a7474fe3aE;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17h719ecb3a7474fe3aE
	.p2align	4, 0x90
_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17h719ecb3a7474fe3aE:
	ret

	.def	_ZN5alloc7raw_vec11finish_grow17h40ccabc9dbf39553E;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN5alloc7raw_vec11finish_grow17h40ccabc9dbf39553E
	.p2align	4, 0x90
_ZN5alloc7raw_vec11finish_grow17h40ccabc9dbf39553E:
.seh_proc _ZN5alloc7raw_vec11finish_grow17h40ccabc9dbf39553E
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	rdi, rdx
	mov	rsi, rcx
	test	r8, r8
	je	.LBB6_5
	cmp	qword ptr [r9 + 16], 0
	je	.LBB6_3
	mov	rdx, qword ptr [r9 + 8]
	test	rdx, rdx
	je	.LBB6_3
	mov	rcx, qword ptr [r9]
	mov	r8d, 1
	mov	r9, rdi
	call	__rust_realloc
	test	rax, rax
	jne	.LBB6_11
	jmp	.LBB6_12
.LBB6_3:
	test	rdi, rdi
	je	.LBB6_4
	mov	edx, 1
	mov	rcx, rdi
	call	__rust_alloc
	test	rax, rax
	jne	.LBB6_11
.LBB6_12:
	mov	qword ptr [rsi + 8], rdi
	mov	qword ptr [rsi + 16], 1
	jmp	.LBB6_6
.LBB6_5:
	mov	qword ptr [rsi + 8], rdi
	mov	qword ptr [rsi + 16], 0
.LBB6_6:
	mov	eax, 1
	jmp	.LBB6_7
.LBB6_4:
	mov	eax, 1
	xor	edi, edi
.LBB6_11:
	mov	qword ptr [rsi + 8], rax
	mov	qword ptr [rsi + 16], rdi
	xor	eax, eax
.LBB6_7:
	mov	qword ptr [rsi], rax
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret
	.seh_endproc

	.def	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E;
	.scl	3;
	.type	32;
	.endef
	.section	.text$unlikely,"xr",one_only,_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
	.p2align	4, 0x90
_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E:
.seh_proc _ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	add	rdx, r8
	jb	.LBB7_10
	mov	rsi, rcx
	mov	rax, qword ptr [rcx + 8]
	lea	rcx, [rax + rax]
	cmp	rcx, rdx
	cmova	rdx, rcx
	cmp	rdx, 9
	mov	edi, 8
	cmovae	rdi, rdx
	mov	r8, rdi
	not	r8
	shr	r8, 63
	test	rax, rax
	je	.LBB7_3
	mov	rcx, qword ptr [rsi]
	mov	rdx, rax
	not	rdx
	shr	rdx, 63
	mov	qword ptr [rsp + 40], rcx
	mov	qword ptr [rsp + 48], rax
	mov	qword ptr [rsp + 56], rdx
	jmp	.LBB7_4
.LBB7_3:
	mov	qword ptr [rsp + 56], 0
.LBB7_4:
	lea	rcx, [rsp + 64]
	lea	r9, [rsp + 40]
	mov	rdx, rdi
	call	_ZN5alloc7raw_vec11finish_grow17h40ccabc9dbf39553E
	cmp	qword ptr [rsp + 64], 0
	mov	rcx, qword ptr [rsp + 72]
	je	.LBB7_5
	mov	rdx, qword ptr [rsp + 80]
	movabs	rax, -9223372036854775807
	cmp	rdx, rax
	je	.LBB7_6
	test	rdx, rdx
	jne	.LBB7_9
.LBB7_10:
	call	_ZN5alloc7raw_vec17capacity_overflow17hb17ce8869088e46bE
	ud2
.LBB7_5:
	mov	qword ptr [rsi], rcx
	mov	qword ptr [rsi + 8], rdi
.LBB7_6:
	add	rsp, 88
	pop	rdi
	pop	rsi
	ret
.LBB7_9:
	call	_ZN5alloc5alloc18handle_alloc_error17hd3d81f1df5d3c2aaE
	ud2
	.seh_endproc

	.def	_ZN60_$LT$alloc..string..String$u20$as$u20$core..fmt..Display$GT$3fmt17h540b1d46c2ce115aE;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN60_$LT$alloc..string..String$u20$as$u20$core..fmt..Display$GT$3fmt17h540b1d46c2ce115aE
	.p2align	4, 0x90
_ZN60_$LT$alloc..string..String$u20$as$u20$core..fmt..Display$GT$3fmt17h540b1d46c2ce115aE:
	mov	r8, rdx
	mov	rax, qword ptr [rcx]
	mov	rdx, qword ptr [rcx + 16]
	mov	rcx, rax
	jmp	_ZN42_$LT$str$u20$as$u20$core..fmt..Display$GT$3fmt17h55073f896b824303E

	.def	_ZN6r3clib4main17h34bfa8a4f0a92926E;
	.scl	3;
	.type	32;
	.endef
	.section	.text,"xr",one_only,_ZN6r3clib4main17h34bfa8a4f0a92926E
	.p2align	4, 0x90
_ZN6r3clib4main17h34bfa8a4f0a92926E:
.Lfunc_begin0:
.seh_proc _ZN6r3clib4main17h34bfa8a4f0a92926E
	.seh_handler __CxxFrameHandler3, @unwind, @except
	push	rbp
	.seh_pushreg rbp
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	push	rbx
	.seh_pushreg rbx
	sub	rsp, 200
	.seh_stackalloc 200
	lea	rbp, [rsp + 128]
	.seh_setframe rbp, 128
	movaps	xmmword ptr [rbp + 48], xmm9
	.seh_savexmm xmm9, 176
	movaps	xmmword ptr [rbp + 32], xmm8
	.seh_savexmm xmm8, 160
	movaps	xmmword ptr [rbp + 16], xmm7
	.seh_savexmm xmm7, 144
	movaps	xmmword ptr [rbp], xmm6
	.seh_savexmm xmm6, 128
	.seh_endprologue
	mov	qword ptr [rbp - 8], -2
	lea	rax, [rip + __unnamed_2]
	mov	qword ptr [rbp - 80], rax
	mov	qword ptr [rbp - 72], 1
	mov	qword ptr [rbp - 64], 0
	lea	rax, [rip + __unnamed_3]
	mov	qword ptr [rbp - 48], rax
	mov	qword ptr [rbp - 40], 0
	lea	rcx, [rbp - 80]
	call	_ZN3std2io5stdio6_print17hf9f676e81421b601E
	mov	qword ptr [rbp - 32], 1
	xorps	xmm0, xmm0
	movups	xmmword ptr [rbp - 24], xmm0
.Ltmp0:
	lea	rbx, [rbp - 32]
	mov	r8d, 53
	mov	rcx, rbx
	xor	edx, edx
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp1:
	mov	rax, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
	movups	xmm0, xmmword ptr [rip + __unnamed_4+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_4+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_4]
	movups	xmmword ptr [rax + rdx], xmm0
	movabs	rcx, 755232724714877984
	mov	qword ptr [rax + rdx + 45], rcx
	add	rdx, 53
	mov	qword ptr [rbp - 16], rdx
	mov	rsi, qword ptr [rbp - 24]
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 51
	ja	.LBB9_4
.Ltmp2:
	lea	rcx, [rbp - 32]
	mov	r8d, 52
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp3:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_4:
	movups	xmm0, xmmword ptr [rip + __unnamed_5+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_5+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_5]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	dword ptr [rax + rdx + 48], 171666532
	add	rdx, 52
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 48
	ja	.LBB9_7
.Ltmp4:
	lea	rcx, [rbp - 32]
	mov	r8d, 49
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp5:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_7:
	movups	xmm0, xmmword ptr [rip + __unnamed_6+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_6+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_6]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	byte ptr [rax + rdx + 48], 10
	add	rdx, 49
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 15
	ja	.LBB9_10
.Ltmp6:
	lea	rcx, [rbp - 32]
	mov	r8d, 16
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp7:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_10:
	movups	xmm0, xmmword ptr [rip + __unnamed_7]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 16
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 59
	ja	.LBB9_13
.Ltmp8:
	lea	rcx, [rbp - 32]
	mov	r8d, 60
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp9:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_13:
	movups	xmm0, xmmword ptr [rip + __unnamed_8+44]
	movups	xmmword ptr [rax + rdx + 44], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_8+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_8+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_8]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 60
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 13
	ja	.LBB9_16
.Ltmp10:
	lea	rcx, [rbp - 32]
	mov	r8d, 14
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp11:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_16:
	movabs	rcx, 737294510419174944
	mov	qword ptr [rax + rdx + 6], rcx
	movabs	rcx, 7359003228999279986
	mov	qword ptr [rax + rdx], rcx
	add	rdx, 14
	mov	qword ptr [rbp - 16], rdx
	sub	rsi, rdx
	cmp	rsi, 1
	ja	.LBB9_19
.Ltmp12:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp13:
	mov	rax, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_19:
	mov	word ptr [rax + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	rax, qword ptr [rbp - 24]
	mov	rcx, rax
	sub	rcx, rdx
	cmp	rcx, 12
	ja	.LBB9_22
.Ltmp14:
	lea	rcx, [rbp - 32]
	mov	r8d, 13
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp15:
	mov	rax, qword ptr [rbp - 24]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_22:
	mov	rcx, qword ptr [rbp - 32]
	movabs	rsi, 737294519111000174
	mov	qword ptr [rcx + rdx + 5], rsi
	movabs	rsi, 8367809545530271090
	mov	qword ptr [rcx + rdx], rsi
	add	rdx, 13
	mov	qword ptr [rbp - 16], rdx
	sub	rax, rdx
	cmp	rax, 1
	ja	.LBB9_25
.Ltmp16:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp17:
	mov	rcx, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_25:
	mov	word ptr [rcx + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	rsi, qword ptr [rbp - 24]
	mov	rax, rsi
	sub	rax, rdx
	cmp	rax, 33
	ja	.LBB9_28
.Ltmp18:
	lea	rcx, [rbp - 32]
	mov	r8d, 34
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp19:
	mov	rsi, qword ptr [rbp - 24]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_28:
	mov	rax, qword ptr [rbp - 32]
	movups	xmm0, xmmword ptr [rip + __unnamed_9+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_9]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 32], 2683
	add	rdx, 34
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 66
	ja	.LBB9_31
.Ltmp20:
	lea	rcx, [rbp - 32]
	mov	r8d, 67
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp21:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_31:
	movups	xmm8, xmmword ptr [rip + __unnamed_10+48]
	movups	xmmword ptr [rax + rdx + 48], xmm8
	movups	xmm9, xmmword ptr [rip + __unnamed_10+32]
	movups	xmmword ptr [rax + rdx + 32], xmm9
	movups	xmm6, xmmword ptr [rip + __unnamed_10+16]
	movups	xmmword ptr [rax + rdx + 16], xmm6
	movups	xmm7, xmmword ptr [rip + __unnamed_10]
	movups	xmmword ptr [rax + rdx], xmm7
	mov	dword ptr [rax + rdx + 63], 171647598
	add	rdx, 67
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 59
	ja	.LBB9_34
.Ltmp22:
	lea	rcx, [rbp - 32]
	mov	r8d, 60
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp23:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_34:
	movups	xmm0, xmmword ptr [rip + __unnamed_11+44]
	movups	xmmword ptr [rax + rdx + 44], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_11+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_11+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_11]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 60
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 66
	ja	.LBB9_37
.Ltmp24:
	lea	rcx, [rbp - 32]
	mov	r8d, 67
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp25:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_37:
	movups	xmmword ptr [rax + rdx + 48], xmm8
	movups	xmmword ptr [rax + rdx + 32], xmm9
	movups	xmmword ptr [rax + rdx + 16], xmm6
	movups	xmmword ptr [rax + rdx], xmm7
	mov	dword ptr [rax + rdx + 63], 171647598
	add	rdx, 67
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 15
	ja	.LBB9_40
.Ltmp26:
	lea	rcx, [rbp - 32]
	mov	r8d, 16
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp27:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_40:
	movups	xmm0, xmmword ptr [rip + __unnamed_12]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 16
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 54
	ja	.LBB9_43
.Ltmp28:
	lea	rcx, [rbp - 32]
	mov	r8d, 55
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp29:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_43:
	movups	xmm0, xmmword ptr [rip + __unnamed_13+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_13+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_13]
	movups	xmmword ptr [rax + rdx], xmm0
	movabs	rcx, 737220821394533934
	mov	qword ptr [rax + rdx + 47], rcx
	add	rdx, 55
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rsi
	sub	rcx, rdx
	cmp	rcx, 9
	ja	.LBB9_46
.Ltmp30:
	lea	rcx, [rbp - 32]
	mov	r8d, 10
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp31:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rsi, qword ptr [rbp - 24]
.LBB9_46:
	movabs	rcx, 3539950744989099378
	mov	qword ptr [rax + rdx], rcx
	mov	word ptr [rax + rdx + 8], 2619
	add	rdx, 10
	mov	qword ptr [rbp - 16], rdx
	sub	rsi, rdx
	cmp	rsi, 1
	ja	.LBB9_49
.Ltmp32:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp33:
	mov	rax, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_49:
	mov	word ptr [rax + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	rdi, qword ptr [rbp - 24]
	mov	rax, rdi
	sub	rax, rdx
	cmp	rax, 22
	ja	.LBB9_52
.Ltmp34:
	lea	rcx, [rbp - 32]
	mov	r8d, 23
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp35:
	mov	rdi, qword ptr [rbp - 24]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_52:
	mov	rax, qword ptr [rbp - 32]
	movups	xmm0, xmmword ptr [rip + __unnamed_14]
	movups	xmmword ptr [rax + rdx], xmm0
	movabs	rsi, 737285430574475122
	mov	qword ptr [rax + rdx + 15], rsi
	add	rdx, 23
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 25
	ja	.LBB9_55
.Ltmp36:
	lea	rcx, [rbp - 32]
	mov	r8d, 26
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp37:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_55:
	movups	xmm0, xmmword ptr [rip + __unnamed_15+10]
	movups	xmmword ptr [rax + rdx + 10], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_15]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 26
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 30
	ja	.LBB9_58
.Ltmp38:
	lea	rcx, [rbp - 32]
	mov	r8d, 31
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp39:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_58:
	movups	xmm0, xmmword ptr [rip + __unnamed_16+15]
	movups	xmmword ptr [rax + rdx + 15], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_16]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 31
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 29
	ja	.LBB9_61
.Ltmp40:
	lea	rcx, [rbp - 32]
	mov	r8d, 30
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp41:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_61:
	movups	xmm0, xmmword ptr [rip + __unnamed_17+14]
	movups	xmmword ptr [rax + rdx + 14], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_17]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 30
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 38
	ja	.LBB9_64
.Ltmp42:
	lea	rcx, [rbp - 32]
	mov	r8d, 39
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp43:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_64:
	movups	xmm0, xmmword ptr [rip + __unnamed_18+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_18]
	movups	xmmword ptr [rax + rdx], xmm0
	movabs	rcx, 737220843237433961
	mov	qword ptr [rax + rdx + 31], rcx
	add	rdx, 39
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 33
	ja	.LBB9_67
.Ltmp44:
	lea	rcx, [rbp - 32]
	mov	r8d, 34
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp45:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_67:
	movups	xmm0, xmmword ptr [rip + __unnamed_19+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_19]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 32], 2619
	add	rdx, 34
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 33
	ja	.LBB9_70
.Ltmp46:
	lea	rcx, [rbp - 32]
	mov	r8d, 34
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp47:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_70:
	movups	xmm0, xmmword ptr [rip + __unnamed_20+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_20]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 32], 2619
	add	rdx, 34
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 33
	ja	.LBB9_73
.Ltmp48:
	lea	rcx, [rbp - 32]
	mov	r8d, 34
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp49:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_73:
	movups	xmm0, xmmword ptr [rip + __unnamed_21+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_21]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 32], 2619
	add	rdx, 34
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 28
	ja	.LBB9_76
.Ltmp50:
	lea	rcx, [rbp - 32]
	mov	r8d, 29
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp51:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_76:
	movups	xmm0, xmmword ptr [rip + __unnamed_22+13]
	movups	xmmword ptr [rax + rdx + 13], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_22]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 29
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 32
	ja	.LBB9_79
.Ltmp52:
	lea	rcx, [rbp - 32]
	mov	r8d, 33
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp53:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_79:
	movups	xmm0, xmmword ptr [rip + __unnamed_23+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_23]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	byte ptr [rax + rdx + 32], 10
	add	rdx, 33
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 34
	ja	.LBB9_82
.Ltmp54:
	lea	rcx, [rbp - 32]
	mov	r8d, 35
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp55:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_82:
	movups	xmm0, xmmword ptr [rip + __unnamed_24+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_24]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	dword ptr [rax + rdx + 31], 171649314
	add	rdx, 35
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 32
	ja	.LBB9_85
.Ltmp56:
	lea	rcx, [rbp - 32]
	mov	r8d, 33
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp57:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_85:
	movups	xmm0, xmmword ptr [rip + __unnamed_25+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_25]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	byte ptr [rax + rdx + 32], 10
	add	rdx, 33
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 42
	ja	.LBB9_88
.Ltmp58:
	lea	rcx, [rbp - 32]
	mov	r8d, 43
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp59:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_88:
	movups	xmm0, xmmword ptr [rip + __unnamed_26+27]
	movups	xmmword ptr [rax + rdx + 27], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_26+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_26]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 43
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 54
	ja	.LBB9_91
.Ltmp60:
	lea	rcx, [rbp - 32]
	mov	r8d, 55
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp61:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_91:
	movups	xmm0, xmmword ptr [rip + __unnamed_27+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_27+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_27]
	movups	xmmword ptr [rax + rdx], xmm0
	movabs	rcx, 737236979366917492
	mov	qword ptr [rax + rdx + 47], rcx
	add	rdx, 55
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 16
	ja	.LBB9_94
.Ltmp62:
	lea	rcx, [rbp - 32]
	mov	r8d, 17
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp63:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_94:
	movups	xmm0, xmmword ptr [rip + __unnamed_28]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	byte ptr [rax + rdx + 16], 10
	add	rdx, 17
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 51
	ja	.LBB9_97
.Ltmp64:
	lea	rcx, [rbp - 32]
	mov	r8d, 52
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp65:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_97:
	movups	xmm0, xmmword ptr [rip + __unnamed_29+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_29+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_29]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	dword ptr [rax + rdx + 48], 170008627
	add	rdx, 52
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 42
	ja	.LBB9_100
.Ltmp66:
	lea	rcx, [rbp - 32]
	mov	r8d, 43
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp67:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_100:
	movups	xmm0, xmmword ptr [rip + __unnamed_30+27]
	movups	xmmword ptr [rax + rdx + 27], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_30+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_30]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 43
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 30
	ja	.LBB9_103
.Ltmp68:
	lea	rcx, [rbp - 32]
	mov	r8d, 31
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp69:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_103:
	movups	xmm0, xmmword ptr [rip + __unnamed_31+15]
	movups	xmmword ptr [rax + rdx + 15], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_31]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 31
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 50
	ja	.LBB9_106
.Ltmp70:
	lea	rcx, [rbp - 32]
	mov	r8d, 51
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp71:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_106:
	movups	xmm0, xmmword ptr [rip + __unnamed_32+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_32+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_32]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	dword ptr [rax + rdx + 47], 171651360
	add	rdx, 51
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 17
	ja	.LBB9_109
.Ltmp72:
	lea	rcx, [rbp - 32]
	mov	r8d, 18
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp73:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_109:
	movups	xmm0, xmmword ptr [rip + __unnamed_33]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 16], 2621
	add	rdx, 18
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 46
	ja	.LBB9_112
.Ltmp74:
	lea	rcx, [rbp - 32]
	mov	r8d, 47
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp75:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_112:
	movups	xmm0, xmmword ptr [rip + __unnamed_34+31]
	movups	xmmword ptr [rax + rdx + 31], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_34+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_34]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 47
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 50
	ja	.LBB9_115
.Ltmp76:
	lea	rcx, [rbp - 32]
	mov	r8d, 51
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp77:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_115:
	movups	xmm0, xmmword ptr [rip + __unnamed_35+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_35+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_35]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	dword ptr [rax + rdx + 47], 171651360
	add	rdx, 51
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 17
	ja	.LBB9_118
.Ltmp78:
	lea	rcx, [rbp - 32]
	mov	r8d, 18
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp79:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_118:
	movups	xmm0, xmmword ptr [rip + __unnamed_36]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 16], 2621
	add	rdx, 18
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 61
	ja	.LBB9_121
.Ltmp80:
	lea	rcx, [rbp - 32]
	mov	r8d, 62
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp81:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_121:
	movups	xmm0, xmmword ptr [rip + __unnamed_37+46]
	movups	xmmword ptr [rax + rdx + 46], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_37+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_37+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_37]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 62
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 44
	ja	.LBB9_124
.Ltmp82:
	lea	rcx, [rbp - 32]
	mov	r8d, 45
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp83:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_124:
	movups	xmm0, xmmword ptr [rip + __unnamed_38+29]
	movups	xmmword ptr [rax + rdx + 29], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_38+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_38]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 45
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 45
	ja	.LBB9_127
.Ltmp84:
	lea	rcx, [rbp - 32]
	mov	r8d, 46
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp85:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_127:
	movups	xmm0, xmmword ptr [rip + __unnamed_39+30]
	movups	xmmword ptr [rax + rdx + 30], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_39+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_39]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 46
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 24
	ja	.LBB9_130
.Ltmp86:
	lea	rcx, [rbp - 32]
	mov	r8d, 25
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp87:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_130:
	movups	xmm0, xmmword ptr [rip + __unnamed_40+9]
	movups	xmmword ptr [rax + rdx + 9], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_40]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 25
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 66
	ja	.LBB9_133
.Ltmp88:
	lea	rcx, [rbp - 32]
	mov	r8d, 67
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp89:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_133:
	movups	xmmword ptr [rax + rdx + 48], xmm8
	movups	xmmword ptr [rax + rdx + 32], xmm9
	movups	xmmword ptr [rax + rdx + 16], xmm6
	movups	xmmword ptr [rax + rdx], xmm7
	mov	dword ptr [rax + rdx + 63], 171647598
	add	rdx, 67
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 61
	ja	.LBB9_136
.Ltmp90:
	lea	rcx, [rbp - 32]
	mov	r8d, 62
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp91:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_136:
	movups	xmm0, xmmword ptr [rip + __unnamed_41+46]
	movups	xmmword ptr [rax + rdx + 46], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_41+32]
	movups	xmmword ptr [rax + rdx + 32], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_41+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_41]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 62
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 66
	ja	.LBB9_139
.Ltmp92:
	lea	rcx, [rbp - 32]
	mov	r8d, 67
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp93:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_139:
	movups	xmmword ptr [rax + rdx + 48], xmm8
	movups	xmmword ptr [rax + rdx + 32], xmm9
	movups	xmmword ptr [rax + rdx + 16], xmm6
	movups	xmmword ptr [rax + rdx], xmm7
	mov	dword ptr [rax + rdx + 63], 171647598
	add	rdx, 67
	mov	qword ptr [rbp - 16], rdx
	sub	rdi, rdx
	cmp	rdi, 1
	ja	.LBB9_142
.Ltmp94:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp95:
	mov	rax, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_142:
	mov	word ptr [rax + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	rax, qword ptr [rbp - 24]
	sub	rax, rdx
	cmp	rax, 1
	ja	.LBB9_145
.Ltmp96:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp97:
	mov	rdx, qword ptr [rbp - 16]
.LBB9_145:
	mov	rax, qword ptr [rbp - 32]
	mov	word ptr [rax + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	rdi, qword ptr [rbp - 24]
	mov	rax, rdi
	sub	rax, rdx
	cmp	rax, 15
	ja	.LBB9_148
.Ltmp98:
	lea	rcx, [rbp - 32]
	mov	r8d, 16
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp99:
	mov	rdi, qword ptr [rbp - 24]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_148:
	mov	rax, qword ptr [rbp - 32]
	movups	xmm0, xmmword ptr [rip + __unnamed_42]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 16
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 28
	ja	.LBB9_151
.Ltmp100:
	lea	rcx, [rbp - 32]
	mov	r8d, 29
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp101:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_151:
	movups	xmm0, xmmword ptr [rip + __unnamed_43+13]
	movups	xmmword ptr [rax + rdx + 13], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_43]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 29
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 17
	ja	.LBB9_154
.Ltmp102:
	lea	rcx, [rbp - 32]
	mov	r8d, 18
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp103:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_154:
	movups	xmm0, xmmword ptr [rip + __unnamed_44]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 16], 2619
	add	rdx, 18
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 30
	ja	.LBB9_157
.Ltmp104:
	lea	rcx, [rbp - 32]
	mov	r8d, 31
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp105:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_157:
	movups	xmm0, xmmword ptr [rip + __unnamed_45+15]
	movups	xmmword ptr [rax + rdx + 15], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_45]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 31
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 30
	ja	.LBB9_160
.Ltmp106:
	lea	rcx, [rbp - 32]
	mov	r8d, 31
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp107:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_160:
	movups	xmm0, xmmword ptr [rip + __unnamed_46+15]
	movups	xmmword ptr [rax + rdx + 15], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_46]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 31
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 26
	ja	.LBB9_163
.Ltmp108:
	lea	rcx, [rbp - 32]
	mov	r8d, 27
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp109:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_163:
	movups	xmm0, xmmword ptr [rip + __unnamed_47+11]
	movups	xmmword ptr [rax + rdx + 11], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_47]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 27
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 24
	ja	.LBB9_166
.Ltmp110:
	lea	rcx, [rbp - 32]
	mov	r8d, 25
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp111:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_166:
	movups	xmm0, xmmword ptr [rip + __unnamed_48+9]
	movups	xmmword ptr [rax + rdx + 9], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_48]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 25
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 29
	ja	.LBB9_169
.Ltmp112:
	lea	rcx, [rbp - 32]
	mov	r8d, 30
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp113:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_169:
	movups	xmm0, xmmword ptr [rip + __unnamed_49+14]
	movups	xmmword ptr [rax + rdx + 14], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_49]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 30
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 28
	ja	.LBB9_172
.Ltmp114:
	lea	rcx, [rbp - 32]
	mov	r8d, 29
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp115:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_172:
	movups	xmm0, xmmword ptr [rip + __unnamed_50+13]
	movups	xmmword ptr [rax + rdx + 13], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_50]
	movups	xmmword ptr [rax + rdx], xmm0
	add	rdx, 29
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 33
	ja	.LBB9_175
.Ltmp116:
	lea	rcx, [rbp - 32]
	mov	r8d, 34
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp117:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_175:
	movups	xmm0, xmmword ptr [rip + __unnamed_51+16]
	movups	xmmword ptr [rax + rdx + 16], xmm0
	movups	xmm0, xmmword ptr [rip + __unnamed_51]
	movups	xmmword ptr [rax + rdx], xmm0
	mov	word ptr [rax + rdx + 32], 2619
	add	rdx, 34
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 22
	ja	.LBB9_178
.Ltmp118:
	lea	rcx, [rbp - 32]
	mov	r8d, 23
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp119:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_178:
	movups	xmm0, xmmword ptr [rip + __unnamed_52]
	movups	xmmword ptr [rax + rdx], xmm0
	movabs	rcx, 737220821397762659
	mov	qword ptr [rax + rdx + 15], rcx
	add	rdx, 23
	mov	qword ptr [rbp - 16], rdx
	mov	rcx, rdi
	sub	rcx, rdx
	cmp	rcx, 12
	ja	.LBB9_181
.Ltmp120:
	lea	rcx, [rbp - 32]
	mov	r8d, 13
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp121:
	mov	rdx, qword ptr [rbp - 16]
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 24]
.LBB9_181:
	movabs	rcx, 737294446045110382
	mov	qword ptr [rax + rdx + 5], rcx
	movabs	rcx, 7142830446885496178
	mov	qword ptr [rax + rdx], rcx
	add	rdx, 13
	mov	qword ptr [rbp - 16], rdx
	sub	rdi, rdx
	cmp	rdi, 1
	ja	.LBB9_184
.Ltmp122:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp123:
	mov	rax, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 16]
.LBB9_184:
	mov	word ptr [rax + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	rax, qword ptr [rbp - 24]
	sub	rax, rdx
	cmp	rax, 1
	ja	.LBB9_187
.Ltmp124:
	lea	rcx, [rbp - 32]
	mov	r8d, 2
	call	_ZN5alloc7raw_vec19RawVec$LT$T$C$A$GT$7reserve21do_reserve_and_handle17hf115987b973856d8E
.Ltmp125:
	mov	rdx, qword ptr [rbp - 16]
.LBB9_187:
	mov	rax, qword ptr [rbp - 32]
	mov	word ptr [rax + rdx], 2685
	add	rdx, 2
	mov	qword ptr [rbp - 16], rdx
	mov	qword ptr [rbp - 96], rbx
	lea	rax, [rip + _ZN60_$LT$alloc..string..String$u20$as$u20$core..fmt..Display$GT$3fmt17h540b1d46c2ce115aE]
	mov	qword ptr [rbp - 88], rax
	lea	rax, [rip + __unnamed_53]
	mov	qword ptr [rbp - 80], rax
	mov	qword ptr [rbp - 72], 2
	mov	qword ptr [rbp - 64], 0
	lea	rax, [rbp - 96]
	mov	qword ptr [rbp - 48], rax
	mov	qword ptr [rbp - 40], 1
.Ltmp126:
	lea	rcx, [rbp - 80]
	call	_ZN3std2io5stdio6_print17hf9f676e81421b601E
.Ltmp127:
	mov	rdx, qword ptr [rbp - 24]
	test	rdx, rdx
	je	.LBB9_190
	mov	rcx, qword ptr [rbp - 32]
	mov	r8, rdx
	not	r8
	shr	r8, 63
	call	__rust_dealloc
.LBB9_190:
	movaps	xmm6, xmmword ptr [rbp]
	movaps	xmm7, xmmword ptr [rbp + 16]
	movaps	xmm8, xmmword ptr [rbp + 32]
	movaps	xmm9, xmmword ptr [rbp + 48]
	add	rsp, 200
	pop	rbx
	pop	rdi
	pop	rsi
	pop	rbp
	ret
	.seh_handlerdata
	.long	($cppxdata$_ZN6r3clib4main17h34bfa8a4f0a92926E)@IMGREL
	.section	.text,"xr",one_only,_ZN6r3clib4main17h34bfa8a4f0a92926E
	.seh_endproc
	.def	"?dtor$191@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA";
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90
"?dtor$191@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA":
.seh_proc "?dtor$191@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA"
.LBB9_191:
	mov	qword ptr [rsp + 16], rdx
	push	rbp
	.seh_pushreg rbp
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	push	rbx
	.seh_pushreg rbx
	sub	rsp, 104
	.seh_stackalloc 104
	lea	rbp, [rdx + 128]
	movaps	xmmword ptr [rsp + 32], xmm9
	.seh_savexmm xmm9, 32
	movaps	xmmword ptr [rsp + 48], xmm8
	.seh_savexmm xmm8, 48
	movaps	xmmword ptr [rsp + 64], xmm7
	.seh_savexmm xmm7, 64
	movaps	xmmword ptr [rsp + 80], xmm6
	.seh_savexmm xmm6, 80
	.seh_endprologue
	mov	rcx, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 24]
	call	_ZN4core3ptr42drop_in_place$LT$alloc..string..String$GT$17h865e2c17f2a9678fE
	movaps	xmm6, xmmword ptr [rsp + 80]
	movaps	xmm7, xmmword ptr [rsp + 64]
	movaps	xmm8, xmmword ptr [rsp + 48]
	movaps	xmm9, xmmword ptr [rsp + 32]
	add	rsp, 104
	pop	rbx
	pop	rdi
	pop	rsi
	pop	rbp
	ret
	.seh_handlerdata
	.section	.text,"xr",one_only,_ZN6r3clib4main17h34bfa8a4f0a92926E
	.seh_endproc
	.def	"?dtor$192@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA";
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90
"?dtor$192@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA":
.seh_proc "?dtor$192@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA"
.LBB9_192:
	mov	qword ptr [rsp + 16], rdx
	push	rbp
	.seh_pushreg rbp
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	push	rbx
	.seh_pushreg rbx
	sub	rsp, 104
	.seh_stackalloc 104
	lea	rbp, [rdx + 128]
	movaps	xmmword ptr [rsp + 32], xmm9
	.seh_savexmm xmm9, 32
	movaps	xmmword ptr [rsp + 48], xmm8
	.seh_savexmm xmm8, 48
	movaps	xmmword ptr [rsp + 64], xmm7
	.seh_savexmm xmm7, 64
	movaps	xmmword ptr [rsp + 80], xmm6
	.seh_savexmm xmm6, 80
	.seh_endprologue
	mov	rcx, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 24]
	call	_ZN4core3ptr42drop_in_place$LT$alloc..string..String$GT$17h865e2c17f2a9678fE
	movaps	xmm6, xmmword ptr [rsp + 80]
	movaps	xmm7, xmmword ptr [rsp + 64]
	movaps	xmm8, xmmword ptr [rsp + 48]
	movaps	xmm9, xmmword ptr [rsp + 32]
	add	rsp, 104
	pop	rbx
	pop	rdi
	pop	rsi
	pop	rbp
	ret
.Lfunc_end0:
	.seh_handlerdata
	.section	.text,"xr",one_only,_ZN6r3clib4main17h34bfa8a4f0a92926E
	.seh_endproc
	.section	.xdata,"dr",associative,_ZN6r3clib4main17h34bfa8a4f0a92926E
	.p2align	2
$cppxdata$_ZN6r3clib4main17h34bfa8a4f0a92926E:
	.long	429065506
	.long	2
	.long	($stateUnwindMap$_ZN6r3clib4main17h34bfa8a4f0a92926E)@IMGREL
	.long	0
	.long	0
	.long	4
	.long	($ip2state$_ZN6r3clib4main17h34bfa8a4f0a92926E)@IMGREL
	.long	120
	.long	0
	.long	1
$stateUnwindMap$_ZN6r3clib4main17h34bfa8a4f0a92926E:
	.long	-1
	.long	"?dtor$191@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA"@IMGREL
	.long	-1
	.long	"?dtor$192@?0?_ZN6r3clib4main17h34bfa8a4f0a92926E@4HA"@IMGREL
$ip2state$_ZN6r3clib4main17h34bfa8a4f0a92926E:
	.long	.Lfunc_begin0@IMGREL
	.long	-1
	.long	.Ltmp0@IMGREL+1
	.long	0
	.long	.Ltmp126@IMGREL+1
	.long	1
	.long	.Ltmp127@IMGREL+1
	.long	-1
	.section	.text,"xr",one_only,_ZN6r3clib4main17h34bfa8a4f0a92926E

	.def	main;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",one_only,main
	.globl	main
	.p2align	4, 0x90
main:
.seh_proc main
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	r9, rdx
	movsxd	r8, ecx
	lea	rax, [rip + _ZN6r3clib4main17h34bfa8a4f0a92926E]
	mov	qword ptr [rsp + 48], rax
	mov	byte ptr [rsp + 32], 2
	lea	rdx, [rip + __unnamed_1]
	lea	rcx, [rsp + 48]
	call	_ZN3std2rt19lang_start_internal17h9b461f8940399158E
	nop
	add	rsp, 56
	ret
	.seh_endproc

	.section	.rdata,"dr",one_only,__unnamed_1
	.p2align	3
__unnamed_1:
	.quad	_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17h719ecb3a7474fe3aE
	.asciz	"\b\000\000\000\000\000\000\000\b\000\000\000\000\000\000"
	.quad	_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17hdc3595f6fa9237f6E
	.quad	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h0ddb4740e49dcbe7E
	.quad	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h0ddb4740e49dcbe7E

	.section	.rdata,"dr",one_only,__unnamed_3
	.p2align	3
__unnamed_3:

	.section	.rdata,"dr",one_only,__unnamed_4
__unnamed_4:
	.ascii	"bool run_cmd(const string& cmd, const string& tag) {\n"

	.section	.rdata,"dr",one_only,__unnamed_5
__unnamed_5:
	.ascii	"cout << \"[BOOT] \" << tag << \" \342\206\222 \" << cmd << endl;\n"

	.section	.rdata,"dr",one_only,__unnamed_6
__unnamed_6:
	.ascii	"let mut ret = system(cmd.c_str()); // i32 \354\266\224\354\240\225\n"

	.section	.rdata,"dr",one_only,__unnamed_7
__unnamed_7:
	.ascii	"if ret != 0 { {\n"

	.section	.rdata,"dr",one_only,__unnamed_8
__unnamed_8:
	.ascii	"cerr << \"[ERR] \342\235\214 \" << tag << \" failed (\" << ret << \")\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_54
__unnamed_54:
	.ascii	"return false;\n"

	.section	.rdata,"dr",one_only,__unnamed_55
__unnamed_55:
	.ascii	"return true;\n"

	.section	.rdata,"dr",one_only,__unnamed_9
__unnamed_9:
	.ascii	"fn main(int argc, char* argv[]) {\n"

	.section	.rdata,"dr",one_only,__unnamed_10
__unnamed_10:
	.ascii	"cout << \"=====================================================\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_11
__unnamed_11:
	.ascii	"cout << \"[r3c] Rust LTS transpiler + bootstrap pipeline\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_12
__unnamed_12:
	.ascii	"if argc < 2 { {\n"

	.section	.rdata,"dr",one_only,__unnamed_13
__unnamed_13:
	.ascii	"cerr << \"Usage: r3c.exe --transpile-all <files...>\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_56
__unnamed_56:
	.ascii	"return 1;\n"

	.section	.rdata,"dr",one_only,__unnamed_14
__unnamed_14:
	.ascii	"string mode = argv[1];\n"

	.section	.rdata,"dr",one_only,__unnamed_15
__unnamed_15:
	.ascii	"vector<string> cpp_files;\n"

	.section	.rdata,"dr",one_only,__unnamed_16
__unnamed_16:
	.ascii	"for (int i = 2; i < argc; ++i)\n"

	.section	.rdata,"dr",one_only,__unnamed_17
__unnamed_17:
	.ascii	"cpp_files.push_back(argv[i]);\n"

	.section	.rdata,"dr",one_only,__unnamed_18
__unnamed_18:
	.ascii	"string rust_out = \"rustlib/r3clib.rs\";\n"

	.section	.rdata,"dr",one_only,__unnamed_19
__unnamed_19:
	.ascii	"string asm_out = \"build/out.asm\";\n"

	.section	.rdata,"dr",one_only,__unnamed_20
__unnamed_20:
	.ascii	"string obj_out = \"build/out.obj\";\n"

	.section	.rdata,"dr",one_only,__unnamed_21
__unnamed_21:
	.ascii	"string exe_out = \"build/out.exe\";\n"

	.section	.rdata,"dr",one_only,__unnamed_22
__unnamed_22:
	.ascii	"string rust_ver = \"+1.65.0\";\n"

	.section	.rdata,"dr",one_only,__unnamed_23
__unnamed_23:
	.ascii	"fs::create_directories(\"build\");\n"

	.section	.rdata,"dr",one_only,__unnamed_24
__unnamed_24:
	.ascii	"fs::create_directories(\"rustlib\");\n"

	.section	.rdata,"dr",one_only,__unnamed_25
__unnamed_25:
	.ascii	"if mode == \"--transpile-all\" { {\n"

	.section	.rdata,"dr",one_only,__unnamed_26
__unnamed_26:
	.ascii	"cout << \"[STEP] Transpiling to Rust...\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_27
__unnamed_27:
	.ascii	"if !transpile_to_rust(cpp_files, rust_out) { return 1;\n"

	.section	.rdata,"dr",one_only,__unnamed_28
__unnamed_28:
	.ascii	"string cmd_asm =\n"

	.section	.rdata,"dr",one_only,__unnamed_29
__unnamed_29:
	.ascii	"\"rustc \" + rust_ver + \" --emit asm -C opt-level=3 \"\n"

	.section	.rdata,"dr",one_only,__unnamed_30
__unnamed_30:
	.ascii	"\"-C llvm-args=\\\"--x86-asm-syntax=intel\\\" \"\n"

	.section	.rdata,"dr",one_only,__unnamed_31
__unnamed_31:
	.ascii	"+ rust_out + \" -o \" + asm_out;\n"

	.section	.rdata,"dr",one_only,__unnamed_32
__unnamed_32:
	.ascii	"if !run_cmd(cmd_asm, \"rustc emit asm\") { return 1;\n"

	.section	.rdata,"dr",one_only,__unnamed_33
__unnamed_33:
	.ascii	"string cmd_nasm =\n"

	.section	.rdata,"dr",one_only,__unnamed_34
__unnamed_34:
	.ascii	"\"nasm -f win64 \" + asm_out + \" -o \" + obj_out;\n"

	.section	.rdata,"dr",one_only,__unnamed_35
__unnamed_35:
	.ascii	"if !run_cmd(cmd_nasm, \"NASM assemble\") { return 1;\n"

	.section	.rdata,"dr",one_only,__unnamed_36
__unnamed_36:
	.ascii	"string cmd_link =\n"

	.section	.rdata,"dr",one_only,__unnamed_37
__unnamed_37:
	.ascii	"\"gcc \" + obj_out + \" -o \" + exe_out + \" -lkernel32 -luser32\";\n"

	.section	.rdata,"dr",one_only,__unnamed_38
__unnamed_38:
	.ascii	"if !run_cmd(cmd_link, \"Linking\") { return 1;\n"

	.section	.rdata,"dr",one_only,__unnamed_39
__unnamed_39:
	.ascii	"cout << \"[STEP] Running self-built exe...\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_40
__unnamed_40:
	.ascii	"system(exe_out.c_str());\n"

	.section	.rdata,"dr",one_only,__unnamed_41
__unnamed_41:
	.ascii	"cout << \"[SUCCESS] \342\234\205 r3c transpile+bootstrap completed.\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_42
__unnamed_42:
	.ascii	"namespace r3c {\n"

	.section	.rdata,"dr",one_only,__unnamed_43
__unnamed_43:
	.ascii	"std::string injectStdLib() {\n"

	.section	.rdata,"dr",one_only,__unnamed_44
__unnamed_44:
	.ascii	"std::string code;\n"

	.section	.rdata,"dr",one_only,__unnamed_45
__unnamed_45:
	.ascii	"code += \"%macro r3_print 1\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_46
__unnamed_46:
	.ascii	"code += \"    lea rcx, [%1]\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_47
__unnamed_47:
	.ascii	"code += \"    call puts\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_48
__unnamed_48:
	.ascii	"code += \"%endmacro\\n\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_49
__unnamed_49:
	.ascii	"code += \"%macro r3_exit 1\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_50
__unnamed_50:
	.ascii	"code += \"    mov rcx, %1\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_51
__unnamed_51:
	.ascii	"code += \"    call ExitProcess\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_52
__unnamed_52:
	.ascii	"code += \"%endmacro\\n\";\n"

	.section	.rdata,"dr",one_only,__unnamed_57
__unnamed_57:
	.ascii	"return code;\n"

	.section	.rdata,"dr",one_only,__unnamed_58
__unnamed_58:
	.ascii	"[BOOT] Rust LTS bootstrap successful!\n"

	.section	.rdata,"dr",one_only,__unnamed_2
	.p2align	3
__unnamed_2:
	.quad	__unnamed_58
	.asciz	"&\000\000\000\000\000\000"

	.section	.rdata,"dr",one_only,__unnamed_59
__unnamed_59:
	.byte	10

	.section	.rdata,"dr",one_only,__unnamed_53
	.p2align	3
__unnamed_53:
	.quad	__unnamed_3
	.zero	8
	.quad	__unnamed_59
	.asciz	"\001\000\000\000\000\000\000"

