	.686p
	ifdef ??version
	if    ??version GT 500H
	.mmx
	endif
	endif
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "D:\projects\mku\common\windows\Winport32.cpp"
	?debug	T "D:\projects\mku\common\windows\Winport32.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
$$BNAMES	ends
$$BROWSE	segment byte public use32 'DEBSYM'
$$BROWSE	ends
$$BROWFILE	segment byte public use32 'DEBSYM'
$$BROWFILE	ends
 ?debug  C FB0C0100600000
DGROUP	group	_BSS,_DATA
_TEXT	segment dword public use32 'CODE'
@InstallDriver$qpvpxct2	segment virtual
	align	2
@@InstallDriver$qpvpxct2	proc	near
?live16385@0:
	?debug L 68
@1:
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 80
	push      0
	push      0
	push      0
	push      0
	push      0
	mov       eax,dword ptr [ebp+16]
	push      eax
	push      1
	push      2
	push      1
	push      983551
	mov       edx,dword ptr [ebp+12]
	push      edx
	mov       ecx,dword ptr [ebp+12]
	push      ecx
	mov       eax,dword ptr [ebp+8]
	push      eax
	call      @CreateServiceA
	mov       dword ptr [ebp-4],eax
	?debug L 94
	cmp       dword ptr [ebp-4],0
	jne       short @2
	?debug L 95
	xor       eax,eax
@5:
	pop       ecx
	pop       ebp
	ret 
	?debug L 97
@2:
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @CloseServiceHandle
	?debug L 99
	mov       eax,1
	?debug L 100
@4:
@3:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@InstallDriver$qpvpxct2	endp
@InstallDriver$qpvpxct2	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	db	2
	db	0
	db	0
	db	0
	dw	70
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch1
	dd	?patch2
	dd	?patch3
	df	@@InstallDriver$qpvpxct2
	dw	0
	dw	4096
	dw	0
	dw	1
	dw	0
	dw	0
	dw	0
	db	23
	db	64
	db	73
	db	110
	db	115
	db	116
	db	97
	db	108
	db	108
	db	68
	db	114
	db	105
	db	118
	db	101
	db	114
	db	36
	db	113
	db	112
	db	118
	db	112
	db	120
	db	99
	db	116
	db	50
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	2
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4097
	dw	0
	dw	3
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	4097
	dw	0
	dw	4
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	5
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@5-@@InstallDriver$qpvpxct2
	dw	3
?patch1	equ	@4-@@InstallDriver$qpvpxct2+3
?patch2	equ	0
?patch3	equ	@4-@@InstallDriver$qpvpxct2
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@StartDriver$qpvpxc	segment virtual
	align	2
@@StartDriver$qpvpxc	proc	near
?live16386@0:
	?debug L 110
@6:
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 115
	push      983551
	mov       eax,dword ptr [ebp+12]
	push      eax
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @OpenServiceA
	mov       dword ptr [ebp-4],eax
	?debug L 119
	cmp       dword ptr [ebp-4],0
	jne       short @7
	?debug L 120
	xor       eax,eax
	jmp       short @8
	?debug L 122
@7:
	push      0
	push      0
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @StartServiceA
	test      eax,eax
	jne       short @9
	call      @GetLastError
	cmp       eax,1056
	je        short @9
	xor       ecx,ecx
	jmp       short @10
@9:
	mov       ecx,1
@10:
	mov       dword ptr [ebp-8],ecx
	?debug L 125
	mov       eax,dword ptr [ebp-4]
	push      eax
	call      @CloseServiceHandle
	?debug L 127
	mov       eax,dword ptr [ebp-8]
	?debug L 128
@11:
@8:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@StartDriver$qpvpxc	endp
@StartDriver$qpvpxc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	66
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch4
	dd	?patch5
	dd	?patch6
	df	@@StartDriver$qpvpxc
	dw	0
	dw	4100
	dw	0
	dw	6
	dw	0
	dw	0
	dw	0
	db	19
	db	64
	db	83
	db	116
	db	97
	db	114
	db	116
	db	68
	db	114
	db	105
	db	118
	db	101
	db	114
	db	36
	db	113
	db	112
	db	118
	db	112
	db	120
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	7
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4097
	dw	0
	dw	8
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	116
	dw	0
	dw	9
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	10
	dw	0
	dw	0
	dw	0
?patch4	equ	@11-@@StartDriver$qpvpxc+4
?patch5	equ	0
?patch6	equ	@11-@@StartDriver$qpvpxc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@OpenDevice$qpxcppv	segment virtual
	align	2
@@OpenDevice$qpxcppv	proc	near
?live16387@0:
	?debug L 139
@12:
	push      ebp
	mov       ebp,esp
	add       esp,-68
	?debug L 160
	mov       eax,dword ptr [ebp+8]
	push      eax
	push      offset s@
	lea       edx,dword ptr [ebp-68]
	push      edx
	call      @_wsprintfA
	add       esp,12
	?debug L 162
	lea       ecx,dword ptr [ebp-68]
	push      0
	push      128
	push      3
	push      0
	push      0
	push      -1073741824
	push      ecx
	call      @CreateFileA
	mov       dword ptr [ebp-4],eax
	?debug L 170
	cmp       dword ptr [ebp-4],-1
	jne       short @13
	?debug L 171
	xor       eax,eax
	jmp       short @14
	?debug L 174
@13:
	cmp       dword ptr [ebp+12],0
	je        short @15
	?debug L 175
	mov       edx,dword ptr [ebp-4]
	mov       ecx,dword ptr [ebp+12]
	mov       dword ptr [ecx],edx
	jmp       short @16
	?debug L 177
@15:
	mov       eax,dword ptr [ebp-4]
	push      eax
	call      @CloseHandle
	?debug L 179
@16:
	mov       eax,1
	?debug L 180
@17:
@14:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@OpenDevice$qpxcppv	endp
@OpenDevice$qpxcppv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	66
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch7
	dd	?patch8
	dd	?patch9
	df	@@OpenDevice$qpxcppv
	dw	0
	dw	4102
	dw	0
	dw	11
	dw	0
	dw	0
	dw	0
	db	19
	db	64
	db	79
	db	112
	db	101
	db	110
	db	68
	db	101
	db	118
	db	105
	db	99
	db	101
	db	36
	db	113
	db	112
	db	120
	db	99
	db	112
	db	112
	db	118
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4097
	dw	0
	dw	12
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4103
	dw	0
	dw	13
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	14
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65468
	dw	65535
	dw	4105
	dw	0
	dw	15
	dw	0
	dw	0
	dw	0
?patch7	equ	@17-@@OpenDevice$qpxcppv+4
?patch8	equ	0
?patch9	equ	@17-@@OpenDevice$qpxcppv
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@StopDriver$qpvpxc	segment virtual
	align	2
@@StopDriver$qpvpxc	proc	near
?live16388@0:
	?debug L 191
@18:
	push      ebp
	mov       ebp,esp
	add       esp,-36
	?debug L 197
	push      983551
	mov       eax,dword ptr [ebp+12]
	push      eax
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @OpenServiceA
	mov       dword ptr [ebp-4],eax
	?debug L 198
	cmp       dword ptr [ebp-4],0
	jne       short @19
	?debug L 199
	xor       eax,eax
	jmp       short @20
	?debug L 201
@19:
	lea       edx,dword ptr [ebp-36]
	push      edx
	push      1
	mov       ecx,dword ptr [ebp-4]
	push      ecx
	call      @ControlService
	mov       dword ptr [ebp-8],eax
	?debug L 203
	mov       eax,dword ptr [ebp-4]
	push      eax
	call      @CloseServiceHandle
	?debug L 205
	mov       eax,dword ptr [ebp-8]
	?debug L 206
@21:
@20:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@StopDriver$qpvpxc	endp
@StopDriver$qpvpxc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	65
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch10
	dd	?patch11
	dd	?patch12
	df	@@StopDriver$qpvpxc
	dw	0
	dw	4106
	dw	0
	dw	16
	dw	0
	dw	0
	dw	0
	db	18
	db	64
	db	83
	db	116
	db	111
	db	112
	db	68
	db	114
	db	105
	db	118
	db	101
	db	114
	db	36
	db	113
	db	112
	db	118
	db	112
	db	120
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	17
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4097
	dw	0
	dw	18
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65500
	dw	65535
	dw	65535
	dw	65535
	dw	19
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	116
	dw	0
	dw	20
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	21
	dw	0
	dw	0
	dw	0
?patch10	equ	@21-@@StopDriver$qpvpxc+4
?patch11	equ	0
?patch12	equ	@21-@@StopDriver$qpvpxc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@RemoveDriver$qpvpxc	segment virtual
	align	2
@@RemoveDriver$qpvpxc	proc	near
?live16389@0:
	?debug L 216
@22:
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 221
	push      983551
	mov       eax,dword ptr [ebp+12]
	push      eax
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @OpenServiceA
	mov       dword ptr [ebp-4],eax
	?debug L 226
	cmp       dword ptr [ebp-4],0
	jne       short @23
	?debug L 227
	xor       eax,eax
	jmp       short @24
	?debug L 229
@23:
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @DeleteService
	mov       dword ptr [ebp-8],eax
	?debug L 231
	mov       ecx,dword ptr [ebp-4]
	push      ecx
	call      @CloseServiceHandle
	?debug L 233
	mov       eax,dword ptr [ebp-8]
	?debug L 234
@25:
@24:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@RemoveDriver$qpvpxc	endp
@RemoveDriver$qpvpxc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	67
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch13
	dd	?patch14
	dd	?patch15
	df	@@RemoveDriver$qpvpxc
	dw	0
	dw	4108
	dw	0
	dw	22
	dw	0
	dw	0
	dw	0
	db	20
	db	64
	db	82
	db	101
	db	109
	db	111
	db	118
	db	101
	db	68
	db	114
	db	105
	db	118
	db	101
	db	114
	db	36
	db	113
	db	112
	db	118
	db	112
	db	120
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	23
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4097
	dw	0
	dw	24
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	116
	dw	0
	dw	25
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	26
	dw	0
	dw	0
	dw	0
?patch13	equ	@25-@@RemoveDriver$qpvpxc+4
?patch14	equ	0
?patch15	equ	@25-@@RemoveDriver$qpvpxc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@UnloadDeviceDriver$qpxc	segment virtual
	align	2
@@UnloadDeviceDriver$qpxc	proc	near
?live16390@0:
	?debug L 244
@26:
	push      ebp
	mov       ebp,esp
	push      ecx
	?debug L 248
	push      983103
	push      0
	push      0
	call      @OpenSCManagerA
	mov       dword ptr [ebp-4],eax
	?debug L 253
	mov       eax,dword ptr [ebp+8]
	push      eax
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @@StopDriver$qpvpxc
	add       esp,8
	?debug L 254
	mov       ecx,dword ptr [ebp+8]
	push      ecx
	mov       eax,dword ptr [ebp-4]
	push      eax
	call      @@RemoveDriver$qpvpxc
	add       esp,8
	?debug L 256
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @CloseServiceHandle
	?debug L 258
	mov       eax,1
	?debug L 259
@28:
@27:
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@UnloadDeviceDriver$qpxc	endp
@UnloadDeviceDriver$qpxc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	71
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch16
	dd	?patch17
	dd	?patch18
	df	@@UnloadDeviceDriver$qpxc
	dw	0
	dw	4110
	dw	0
	dw	27
	dw	0
	dw	0
	dw	0
	db	24
	db	64
	db	85
	db	110
	db	108
	db	111
	db	97
	db	100
	db	68
	db	101
	db	118
	db	105
	db	99
	db	101
	db	68
	db	114
	db	105
	db	118
	db	101
	db	114
	db	36
	db	113
	db	112
	db	120
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4097
	dw	0
	dw	28
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	29
	dw	0
	dw	0
	dw	0
?patch16	equ	@28-@@UnloadDeviceDriver$qpxc+3
?patch17	equ	0
?patch18	equ	@28-@@UnloadDeviceDriver$qpxc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@LoadDeviceDriver$qpxct1ppv	segment virtual
	align	2
@@LoadDeviceDriver$qpxct1ppv	proc	near
?live16391@0:
	?debug L 271
@29:
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 276
	push      983103
	push      0
	push      0
	call      @OpenSCManagerA
	mov       dword ptr [ebp-4],eax
	?debug L 279
	mov       eax,dword ptr [ebp+8]
	push      eax
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @@RemoveDriver$qpvpxc
	add       esp,8
	?debug L 282
	mov       ecx,dword ptr [ebp+12]
	push      ecx
	mov       eax,dword ptr [ebp+8]
	push      eax
	mov       edx,dword ptr [ebp-4]
	push      edx
	call      @@InstallDriver$qpvpxct2
	add       esp,12
	?debug L 285
	mov       ecx,dword ptr [ebp+8]
	push      ecx
	mov       eax,dword ptr [ebp-4]
	push      eax
	call      @@StartDriver$qpvpxc
	add       esp,8
	?debug L 288
	mov       edx,dword ptr [ebp+16]
	push      edx
	mov       ecx,dword ptr [ebp+8]
	push      ecx
	call      @@OpenDevice$qpxcppv
	add       esp,8
	mov       dword ptr [ebp-8],eax
	?debug L 290
	mov       eax,dword ptr [ebp-4]
	push      eax
	call      @CloseServiceHandle
	?debug L 292
	mov       eax,dword ptr [ebp-8]
	?debug L 293
@31:
@30:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@LoadDeviceDriver$qpxct1ppv	endp
@LoadDeviceDriver$qpxct1ppv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	74
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch19
	dd	?patch20
	dd	?patch21
	df	@@LoadDeviceDriver$qpxct1ppv
	dw	0
	dw	4112
	dw	0
	dw	30
	dw	0
	dw	0
	dw	0
	db	27
	db	64
	db	76
	db	111
	db	97
	db	100
	db	68
	db	101
	db	118
	db	105
	db	99
	db	101
	db	68
	db	114
	db	105
	db	118
	db	101
	db	114
	db	36
	db	113
	db	112
	db	120
	db	99
	db	116
	db	49
	db	112
	db	112
	db	118
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4097
	dw	0
	dw	31
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	4097
	dw	0
	dw	32
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	4103
	dw	0
	dw	33
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	116
	dw	0
	dw	34
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1027
	dw	0
	dw	35
	dw	0
	dw	0
	dw	0
?patch19	equ	@31-@@LoadDeviceDriver$qpxct1ppv+4
?patch20	equ	0
?patch21	equ	@31-@@LoadDeviceDriver$qpxct1ppv
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@GetPortVal$quspuluc	segment virtual
	align	2
@@TWinPort@GetPortVal$quspuluc	proc	near
?live16392@0:
	?debug L 295
@32:
	push      ebp
	mov       ebp,esp
	add       esp,-16
	?debug L 300
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	je        short @34
	?debug L 302
	mov       dx,word ptr [ebp+12]
	?debug L 305
	lea       eax,dword ptr [ebp-4]
	?debug L 302
	mov       word ptr [ebp-16],dx
	?debug L 305
	lea       edx,dword ptr [ebp-16]
	?debug L 303
	mov       cl,byte ptr [ebp+20]
	mov       byte ptr [ebp-8],cl
	?debug L 305
	push      0
	push      eax
	push      12
	push      edx
	lea       ecx,dword ptr [ebp-16]
	push      12
	push      ecx
	push      -2146426804
	mov       eax,dword ptr [ebp+8]
	mov       edx,dword ptr [eax+4]
	push      edx
	call      @DeviceIoControl
	test      eax,eax
	jne       short @35
	?debug L 308
	xor       eax,eax
	jmp       short @36
	?debug L 310
@35:
	mov       edx,dword ptr [ebp+16]
	mov       ecx,dword ptr [ebp-12]
	mov       dword ptr [edx],ecx
	?debug L 313
@34:
	mov       al,1
	?debug L 314
@38:
@36:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@GetPortVal$quspuluc	endp
@TWinPort@GetPortVal$quspuluc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	76
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch22
	dd	?patch23
	dd	?patch24
	df	@@TWinPort@GetPortVal$quspuluc
	dw	0
	dw	4116
	dw	0
	dw	55
	dw	0
	dw	0
	dw	0
	db	29
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	71
	db	101
	db	116
	db	80
	db	111
	db	114
	db	116
	db	86
	db	97
	db	108
	db	36
	db	113
	db	117
	db	115
	db	112
	db	117
	db	108
	db	117
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	56
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	57
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	1058
	dw	0
	dw	58
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	20
	dw	0
	dw	32
	dw	0
	dw	59
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65520
	dw	65535
	dw	4169
	dw	0
	dw	64
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	34
	dw	0
	dw	65
	dw	0
	dw	0
	dw	0
?patch22	equ	@38-@@TWinPort@GetPortVal$quspuluc+4
?patch23	equ	0
?patch24	equ	@38-@@TWinPort@GetPortVal$quspuluc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@SetPortVal$qusuluc	segment virtual
	align	2
@@TWinPort@SetPortVal$qusuluc	proc	near
?live16393@0:
	?debug L 316
@39:
	push      ebp
	mov       ebp,esp
	add       esp,-16
	?debug L 321
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	je        short @40
	?debug L 323
	mov       dx,word ptr [ebp+12]
	mov       word ptr [ebp-16],dx
	?debug L 327
	lea       edx,dword ptr [ebp-4]
	?debug L 324
	mov       ecx,dword ptr [ebp+16]
	mov       dword ptr [ebp-12],ecx
	?debug L 327
	lea       ecx,dword ptr [ebp-16]
	?debug L 325
	mov       al,byte ptr [ebp+20]
	mov       byte ptr [ebp-8],al
	?debug L 327
	push      0
	push      edx
	push      0
	push      0
	push      12
	push      ecx
	push      -2146426808
	mov       eax,dword ptr [ebp+8]
	mov       edx,dword ptr [eax+4]
	push      edx
	call      @DeviceIoControl
	test      eax,eax
	jne       short @41
	?debug L 329
	xor       eax,eax
	jmp       short @42
	?debug L 332
@41:
@40:
	mov       al,1
	?debug L 333
@43:
@42:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@SetPortVal$qusuluc	endp
@TWinPort@SetPortVal$qusuluc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	75
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch25
	dd	?patch26
	dd	?patch27
	df	@@TWinPort@SetPortVal$qusuluc
	dw	0
	dw	4171
	dw	0
	dw	66
	dw	0
	dw	0
	dw	0
	db	28
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	83
	db	101
	db	116
	db	80
	db	111
	db	114
	db	116
	db	86
	db	97
	db	108
	db	36
	db	113
	db	117
	db	115
	db	117
	db	108
	db	117
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	67
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	68
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	34
	dw	0
	dw	69
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	20
	dw	0
	dw	32
	dw	0
	dw	70
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65520
	dw	65535
	dw	4169
	dw	0
	dw	71
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	34
	dw	0
	dw	72
	dw	0
	dw	0
	dw	0
?patch25	equ	@43-@@TWinPort@SetPortVal$qusuluc+4
?patch26	equ	0
?patch27	equ	@43-@@TWinPort@SetPortVal$qusuluc
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_DATA	segment dword public use32 'DATA'
@_$DCJC$@TWinPort@$bctr$qv	segment virtual
	align	2
@@_$DCJC$@TWinPort@$bctr$qv	label	dword
	dd	@@$xt$p8TWinPort
	dd	5
	dd	8
	dd	0
@_$DCJC$@TWinPort@$bctr$qv	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTKC$@TWinPort@$bctr$qv	segment virtual
	align	2
@@_$ECTKC$@TWinPort@$bctr$qv	label	dword
	dd	0
	dd	-36
	dw	0
	dw	5
	dd	0
	dd	@@_$DCJC$@TWinPort@$bctr$qv
@_$ECTKC$@TWinPort@$bctr$qv	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@$bctr$qv	segment virtual
	align	2
@@TWinPort@$bctr$qv	proc	near
?live16394@0:
	?debug L 335
@44:
	push      ebp
	mov       ebp,esp
	add       esp,-184
	mov       eax,offset @@_$ECTKC$@TWinPort@$bctr$qv
	call      @__InitExceptBlockLDTC
	?debug L 336
	mov       word ptr [ebp-20],8
	?debug L 338
	push      148
	push      0
	lea       edx,dword ptr [ebp-184]
	push      edx
	call      @_memset
	?debug L 339
	mov       dword ptr [ebp-184],148
	?debug L 340
	mov       ecx,dword ptr [ebp+8]
	?debug L 338
	add       esp,12
	?debug L 341
	lea       eax,dword ptr [ebp-184]
	?debug L 340
	mov       byte ptr [ecx],0
	?debug L 341
	push      eax
	call      @GetVersionExA
	test      eax,eax
	je        short @45
	?debug L 342
	cmp       dword ptr [ebp-168],2
	sete      dl
	and       edx,1
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx],dl
	?debug L 344
@45:
	mov       eax,dword ptr [ebp+8]
	mov       byte ptr [eax+8],0
	?debug L 345
	mov       edx,dword ptr [ebp+8]
	xor       ecx,ecx
	mov       dword ptr [edx+4],ecx
	?debug L 347
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	je        short @46
	?debug L 349
	mov       edx,dword ptr [ebp+8]
	add       edx,4
	push      edx
	push      offset s@+7
	call      @@OpenDevice$qpxcppv
	add       esp,8
	test      eax,eax
	sete      cl
	and       ecx,1
	mov       eax,dword ptr [ebp+8]
	mov       byte ptr [eax+8],cl
	?debug L 351
@46:
	mov       edx,dword ptr [ebp-36]
	mov       dword ptr fs:[0],edx
	mov       eax,dword ptr [ebp+8]
	?debug L 351
@48:
@47:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@$bctr$qv	endp
@TWinPort@$bctr$qv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	65
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch28
	dd	?patch29
	dd	?patch30
	df	@@TWinPort@$bctr$qv
	dw	0
	dw	4173
	dw	0
	dw	73
	dw	0
	dw	0
	dw	0
	db	18
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	36
	db	98
	db	99
	db	116
	db	114
	db	36
	db	113
	db	118
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	74
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65352
	dw	65535
	dw	65534
	dw	65535
	dw	75
	dw	0
	dw	0
	dw	0
?patch28	equ	@48-@@TWinPort@$bctr$qv+4
?patch29	equ	0
?patch30	equ	@48-@@TWinPort@$bctr$qv
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@$bdtr$qv	segment virtual
	align	2
@@TWinPort@$bdtr$qv	proc	near
?live16398@0:
	?debug L 353
@49:
	push      ebp
	mov       ebp,esp
	cmp       dword ptr [ebp+8],0
	je        short @50
	?debug L 355
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	je        short @51
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	je        short @51
	?debug L 356
	mov       ecx,dword ptr [ebp+8]
	mov       eax,dword ptr [ecx+4]
	push      eax
	call      @CloseHandle
@51:
	test      byte ptr [ebp+12],1
	je        short @52
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @$bdele$qpv
	pop       ecx
	?debug L 357
@52:
@50:
@53:
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@$bdtr$qv	endp
@TWinPort@$bdtr$qv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	65
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch31
	dd	?patch32
	dd	?patch33
	df	@@TWinPort@$bdtr$qv
	dw	0
	dw	4175
	dw	0
	dw	76
	dw	0
	dw	0
	dw	0
	db	18
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	36
	db	98
	db	100
	db	116
	db	114
	db	36
	db	113
	db	118
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	77
	dw	0
	dw	0
	dw	0
?patch31	equ	@53-@@TWinPort@$bdtr$qv+2
?patch32	equ	0
?patch33	equ	@53-@@TWinPort@$bdtr$qv
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@ReadByte$qus	segment virtual
	align	2
@@TWinPort@ReadByte$qus	proc	near
?live16399@0:
	?debug L 359
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 361
@54:
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @55
	?debug L 365
@56:
	mov	 dx, word ptr word ptr [ebp+12]
	?debug L 366
	in	 al, dx
	?debug L 367
	mov	 byte ptr byte ptr [ebp-1],al
	?debug L 370
	mov       al,byte ptr [ebp-1]
	jmp       short @57
	?debug L 374
@58:
@55:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	je        short @60
	push      1
	lea       ecx,dword ptr [ebp-8]
	push      ecx
	mov       ax,word ptr [ebp+12]
	push      eax
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @@TWinPort@GetPortVal$quspuluc
	add       esp,16
	test      al,al
	jne       short @59
	?debug L 376
@60:
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx+8],1
	?debug L 377
	xor       eax,eax
	jmp       short @57
	?debug L 380
@59:
	mov       edx,dword ptr [ebp+8]
	mov       byte ptr [edx+8],0
	?debug L 381
	mov       al,byte ptr [ebp-8]
	?debug L 382
@61:
@57:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@ReadByte$qus	endp
@TWinPort@ReadByte$qus	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	69
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch34
	dd	?patch35
	dd	?patch36
	df	@@TWinPort@ReadByte$qus
	dw	0
	dw	4177
	dw	0
	dw	78
	dw	0
	dw	0
	dw	0
	db	22
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	82
	db	101
	db	97
	db	100
	db	66
	db	121
	db	116
	db	101
	db	36
	db	113
	db	117
	db	115
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	79
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	80
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	34
	dw	0
	dw	81
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch37
	df	@56
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65535
	dw	65535
	dw	32
	dw	0
	dw	82
	dw	0
	dw	0
	dw	0
?patch37	equ	@58-@56
	dw	2
	dw	6
?patch34	equ	@61-@@TWinPort@ReadByte$qus+4
?patch35	equ	0
?patch36	equ	@61-@@TWinPort@ReadByte$qus
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@ReadWord$qus	segment virtual
	align	2
@@TWinPort@ReadWord$qus	proc	near
?live16400@0:
	?debug L 384
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 386
@62:
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @63
	?debug L 390
@64:
	mov	 dx, word ptr word ptr [ebp+12]
	?debug L 391
	in	 ax,dx
	?debug L 392
	mov	 word ptr word ptr [ebp-2],ax
	?debug L 394
	mov       ax,word ptr [ebp-2]
	jmp       short @65
	?debug L 398
@66:
@63:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	je        short @68
	push      2
	lea       ecx,dword ptr [ebp-8]
	push      ecx
	mov       ax,word ptr [ebp+12]
	push      eax
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @@TWinPort@GetPortVal$quspuluc
	add       esp,16
	test      al,al
	jne       short @67
	?debug L 400
@68:
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx+8],1
	?debug L 401
	xor       eax,eax
	jmp       short @65
	?debug L 404
@67:
	mov       edx,dword ptr [ebp+8]
	mov       byte ptr [edx+8],0
	?debug L 406
	mov       ax,word ptr [ebp-8]
	?debug L 407
@69:
@65:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@ReadWord$qus	endp
@TWinPort@ReadWord$qus	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	69
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch38
	dd	?patch39
	dd	?patch40
	df	@@TWinPort@ReadWord$qus
	dw	0
	dw	4179
	dw	0
	dw	83
	dw	0
	dw	0
	dw	0
	db	22
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	82
	db	101
	db	97
	db	100
	db	87
	db	111
	db	114
	db	100
	db	36
	db	113
	db	117
	db	115
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	84
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	85
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	34
	dw	0
	dw	86
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch41
	df	@64
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65534
	dw	65535
	dw	33
	dw	0
	dw	87
	dw	0
	dw	0
	dw	0
?patch41	equ	@66-@64
	dw	2
	dw	6
?patch38	equ	@69-@@TWinPort@ReadWord$qus+4
?patch39	equ	0
?patch40	equ	@69-@@TWinPort@ReadWord$qus
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@ReadDWord$qus	segment virtual
	align	2
@@TWinPort@ReadDWord$qus	proc	near
?live16401@0:
	?debug L 409
	push      ebp
	mov       ebp,esp
	add       esp,-8
	?debug L 411
@70:
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @71
	?debug L 415
@72:
	mov	 dx, word ptr word ptr [ebp+12]
	?debug L 416
	in	 eax,dx
	?debug L 417
	mov	 dword ptr dword ptr [ebp-4],eax
	?debug L 419
	mov       eax,dword ptr [ebp-4]
	jmp       short @73
	?debug L 423
@74:
@71:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	je        short @76
	push      4
	lea       ecx,dword ptr [ebp-8]
	push      ecx
	mov       ax,word ptr [ebp+12]
	push      eax
	mov       edx,dword ptr [ebp+8]
	push      edx
	call      @@TWinPort@GetPortVal$quspuluc
	add       esp,16
	test      al,al
	jne       short @75
	?debug L 425
@76:
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx+8],1
	?debug L 426
	xor       eax,eax
	jmp       short @73
	?debug L 429
@75:
	mov       edx,dword ptr [ebp+8]
	mov       byte ptr [edx+8],0
	?debug L 431
	mov       eax,dword ptr [ebp-8]
	?debug L 432
@77:
@73:
	pop       ecx
	pop       ecx
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@ReadDWord$qus	endp
@TWinPort@ReadDWord$qus	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	70
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch42
	dd	?patch43
	dd	?patch44
	df	@@TWinPort@ReadDWord$qus
	dw	0
	dw	4181
	dw	0
	dw	88
	dw	0
	dw	0
	dw	0
	db	23
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	82
	db	101
	db	97
	db	100
	db	68
	db	87
	db	111
	db	114
	db	100
	db	36
	db	113
	db	117
	db	115
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	89
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	90
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65528
	dw	65535
	dw	34
	dw	0
	dw	91
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch45
	df	@72
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	34
	dw	0
	dw	92
	dw	0
	dw	0
	dw	0
?patch45	equ	@74-@72
	dw	2
	dw	6
?patch42	equ	@77-@@TWinPort@ReadDWord$qus+4
?patch43	equ	0
?patch44	equ	@77-@@TWinPort@ReadDWord$qus
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@WriteByte$qusuc	segment virtual
	align	2
@@TWinPort@WriteByte$qusuc	proc	near
?live16402@0:
	?debug L 434
	push      ebp
	mov       ebp,esp
	?debug L 436
@78:
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @79
	?debug L 439
	mov	 dx, word ptr word ptr [ebp+12]
	?debug L 440
	mov	 al, byte ptr byte ptr [ebp+16]
	?debug L 441
	out	 dx,al
	?debug L 443
@83:
	pop       ebp
	ret 
	?debug L 446
@79:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	jne       short @81
	?debug L 448
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx+8],1
	?debug L 449
@84:
	pop       ebp
	ret 
	?debug L 452
@81:
	push      1
	xor       eax,eax
	mov       al,byte ptr [ebp+16]
	push      eax
	mov       dx,word ptr [ebp+12]
	push      edx
	mov       ecx,dword ptr [ebp+8]
	push      ecx
	call      @@TWinPort@SetPortVal$qusuluc
	add       esp,16
	and       eax,255
	cmp       eax,1
	mov       ecx,dword ptr [ebp+8]
	sbb       edx,edx
	neg       edx
	mov       byte ptr [ecx+8],dl
	?debug L 453
@82:
@80:
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@WriteByte$qusuc	endp
@TWinPort@WriteByte$qusuc	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	72
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch46
	dd	?patch47
	dd	?patch48
	df	@@TWinPort@WriteByte$qusuc
	dw	0
	dw	4183
	dw	0
	dw	93
	dw	0
	dw	0
	dw	0
	db	25
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	87
	db	114
	db	105
	db	116
	db	101
	db	66
	db	121
	db	116
	db	101
	db	36
	db	113
	db	117
	db	115
	db	117
	db	99
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	94
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	95
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	32
	dw	0
	dw	96
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@84-@@TWinPort@WriteByte$qusuc
	dw	2
	dw	8
	dw	530
	dd	@83-@@TWinPort@WriteByte$qusuc
	dw	2
?patch46	equ	@82-@@TWinPort@WriteByte$qusuc+2
?patch47	equ	0
?patch48	equ	@82-@@TWinPort@WriteByte$qusuc
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@WriteWord$qusus	segment virtual
	align	2
@@TWinPort@WriteWord$qusus	proc	near
?live16403@0:
	?debug L 455
	push      ebp
	mov       ebp,esp
	?debug L 457
@85:
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @86
	?debug L 460
	mov	 dx, word ptr word ptr [ebp+12]
	?debug L 461
	mov	 ax, word ptr word ptr [ebp+16]
	?debug L 462
	out	 dx,ax
	?debug L 464
@90:
	pop       ebp
	ret 
	?debug L 467
@86:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	jne       short @88
	?debug L 469
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx+8],1
	?debug L 470
@91:
	pop       ebp
	ret 
	?debug L 473
@88:
	push      2
	movzx     eax,word ptr [ebp+16]
	push      eax
	mov       dx,word ptr [ebp+12]
	push      edx
	mov       ecx,dword ptr [ebp+8]
	push      ecx
	call      @@TWinPort@SetPortVal$qusuluc
	add       esp,16
	and       eax,255
	cmp       eax,1
	mov       ecx,dword ptr [ebp+8]
	sbb       edx,edx
	neg       edx
	mov       byte ptr [ecx+8],dl
	?debug L 474
@89:
@87:
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@WriteWord$qusus	endp
@TWinPort@WriteWord$qusus	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	72
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch49
	dd	?patch50
	dd	?patch51
	df	@@TWinPort@WriteWord$qusus
	dw	0
	dw	4185
	dw	0
	dw	97
	dw	0
	dw	0
	dw	0
	db	25
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	87
	db	114
	db	105
	db	116
	db	101
	db	87
	db	111
	db	114
	db	100
	db	36
	db	113
	db	117
	db	115
	db	117
	db	115
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	98
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	99
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	33
	dw	0
	dw	100
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@91-@@TWinPort@WriteWord$qusus
	dw	2
	dw	8
	dw	530
	dd	@90-@@TWinPort@WriteWord$qusus
	dw	2
?patch49	equ	@89-@@TWinPort@WriteWord$qusus+2
?patch50	equ	0
?patch51	equ	@89-@@TWinPort@WriteWord$qusus
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@WriteDWord$qusul	segment virtual
	align	2
@@TWinPort@WriteDWord$qusul	proc	near
?live16404@0:
	?debug L 476
	push      ebp
	mov       ebp,esp
	?debug L 478
@92:
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @93
	?debug L 481
	mov	 dx, word ptr word ptr [ebp+12]
	?debug L 482
	mov	 eax, dword ptr dword ptr [ebp+16]
	?debug L 483
	out	 dx,eax
	?debug L 485
@97:
	pop       ebp
	ret 
	?debug L 488
@93:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	jne       short @95
	?debug L 490
	mov       ecx,dword ptr [ebp+8]
	mov       byte ptr [ecx+8],1
	?debug L 491
@98:
	pop       ebp
	ret 
	?debug L 494
@95:
	push      4
	mov       eax,dword ptr [ebp+16]
	push      eax
	mov       dx,word ptr [ebp+12]
	push      edx
	mov       ecx,dword ptr [ebp+8]
	push      ecx
	call      @@TWinPort@SetPortVal$qusuluc
	add       esp,16
	and       eax,255
	cmp       eax,1
	mov       ecx,dword ptr [ebp+8]
	sbb       edx,edx
	neg       edx
	mov       byte ptr [ecx+8],dl
	?debug L 495
@96:
@94:
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@WriteDWord$qusul	endp
@TWinPort@WriteDWord$qusul	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	73
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch52
	dd	?patch53
	dd	?patch54
	df	@@TWinPort@WriteDWord$qusul
	dw	0
	dw	4187
	dw	0
	dw	101
	dw	0
	dw	0
	dw	0
	db	26
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	87
	db	114
	db	105
	db	116
	db	101
	db	68
	db	87
	db	111
	db	114
	db	100
	db	36
	db	113
	db	117
	db	115
	db	117
	db	108
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	102
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	33
	dw	0
	dw	103
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	34
	dw	0
	dw	104
	dw	0
	dw	0
	dw	0
	dw	8
	dw	530
	dd	@98-@@TWinPort@WriteDWord$qusul
	dw	2
	dw	8
	dw	530
	dd	@97-@@TWinPort@WriteDWord$qusul
	dw	2
?patch52	equ	@96-@@TWinPort@WriteDWord$qusul+2
?patch53	equ	0
?patch54	equ	@96-@@TWinPort@WriteDWord$qusul
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@ErrorMessage$qpci	segment virtual
	align	2
@@TWinPort@ErrorMessage$qpci	proc	near
?live16405@0:
	?debug L 497
@99:
	push      ebp
	mov       ebp,esp
	?debug L 499
	push      0
	mov       eax,dword ptr [ebp+16]
	push      eax
	mov       edx,dword ptr [ebp+12]
	push      edx
	push      1024
	call      @GetLastError
	push      eax
	push      0
	push      4096
	call      @FormatMessageA
	?debug L 507
@100:
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@ErrorMessage$qpci	endp
@TWinPort@ErrorMessage$qpci	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	74
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch55
	dd	?patch56
	dd	?patch57
	df	@@TWinPort@ErrorMessage$qpci
	dw	0
	dw	4189
	dw	0
	dw	105
	dw	0
	dw	0
	dw	0
	db	27
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	69
	db	114
	db	114
	db	111
	db	114
	db	77
	db	101
	db	115
	db	115
	db	97
	db	103
	db	101
	db	36
	db	113
	db	112
	db	99
	db	105
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	106
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1136
	dw	0
	dw	107
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	116
	dw	0
	dw	108
	dw	0
	dw	0
	dw	0
?patch55	equ	@100-@@TWinPort@ErrorMessage$qpci+2
?patch56	equ	0
?patch57	equ	@100-@@TWinPort@ErrorMessage$qpci
	dw	2
	dw	6
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@Install$qv	segment virtual
	align	2
@@TWinPort@Install$qv	proc	near
?live16406@0:
	?debug L 509
@101:
	push      ebp
	mov       ebp,esp
	add       esp,-524
	?debug L 511
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @102
	?debug L 512
	mov       al,1
	jmp       @103
	?debug L 514
@102:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	je        short @104
	?debug L 515
	mov       ecx,dword ptr [ebp+8]
	mov       eax,dword ptr [ecx+4]
	push      eax
	call      @CloseHandle
	?debug L 517
@104:
	mov       edx,dword ptr [ebp+8]
	xor       ecx,ecx
	?debug L 523
	lea       eax,dword ptr [ebp-264]
	?debug L 517
	mov       dword ptr [edx+4],ecx
	?debug L 523
	push      260
	push      eax
	push      0
	call      @GetModuleHandleA
	push      eax
	call      @GetModuleFileNameA
	test      eax,eax
	jne       short @105
	?debug L 525
	xor       eax,eax
	jmp       @103
	?debug L 528
@105:
	push      92
	lea       edx,dword ptr [ebp-264]
	push      edx
	call      @@std@strrchr$qpci
	add       esp,8
	mov       dword ptr [ebp-4],eax
	?debug L 530
	cmp       dword ptr [ebp-4],0
	je        short @106
	?debug L 531
	mov       ecx,dword ptr [ebp-4]
	mov       byte ptr [ecx+1],0
	jmp       short @107
	?debug L 534
@106:
	xor       eax,eax
	jmp       @103
	?debug L 537
@107:
	push      offset s@+13
	lea       edx,dword ptr [ebp-264]
	push      edx
	call      @_strcat
	add       esp,8
	?debug L 539
	push      260
	lea       ecx,dword ptr [ebp-524]
	push      ecx
	call      @GetSystemDirectoryA
	test      eax,eax
	jne       short @108
	?debug L 541
	xor       eax,eax
	jmp       short @103
	?debug L 544
@108:
	push      offset s@+23
	lea       edx,dword ptr [ebp-524]
	push      edx
	call      @_strcat
	add       esp,8
	?debug L 546
	push      offset s@+7
	call      @@UnloadDeviceDriver$qpxc
	pop       ecx
	?debug L 547
	push      0
	lea       ecx,dword ptr [ebp-524]
	push      ecx
	lea       eax,dword ptr [ebp-264]
	push      eax
	call      @CopyFileA
	test      eax,eax
	jne       short @109
	?debug L 549
	xor       eax,eax
	jmp       short @103
	?debug L 552
@109:
	mov       edx,dword ptr [ebp+8]
	xor       ecx,ecx
	mov       dword ptr [edx+4],ecx
	?debug L 553
	lea       edx,dword ptr [ebp-264]
	mov       eax,dword ptr [ebp+8]
	add       eax,4
	push      eax
	push      edx
	push      offset s@+7
	call      @@LoadDeviceDriver$qpxct1ppv
	add       esp,12
	test      eax,eax
	jne       short @110
	?debug L 554
	xor       eax,eax
	jmp       short @103
	?debug L 556
@110:
	mov       edx,dword ptr [ebp+8]
	?debug L 557
	mov       al,1
	?debug L 556
	mov       byte ptr [edx+8],0
	?debug L 558
@111:
@103:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@Install$qv	endp
@TWinPort@Install$qv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	67
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch58
	dd	?patch59
	dd	?patch60
	df	@@TWinPort@Install$qv
	dw	0
	dw	4191
	dw	0
	dw	109
	dw	0
	dw	0
	dw	0
	db	20
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	73
	db	110
	db	115
	db	116
	db	97
	db	108
	db	108
	db	36
	db	113
	db	118
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	110
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	1136
	dw	0
	dw	111
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65012
	dw	65535
	dw	4193
	dw	0
	dw	112
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65272
	dw	65535
	dw	4194
	dw	0
	dw	113
	dw	0
	dw	0
	dw	0
?patch58	equ	@111-@@TWinPort@Install$qv+4
?patch59	equ	0
?patch60	equ	@111-@@TWinPort@Install$qv
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@TWinPort@Remove$qv	segment virtual
	align	2
@@TWinPort@Remove$qv	proc	near
?live16407@0:
	?debug L 560
@112:
	push      ebp
	mov       ebp,esp
	add       esp,-260
	?debug L 562
	mov       eax,dword ptr [ebp+8]
	cmp       byte ptr [eax],0
	jne       short @113
	?debug L 563
	mov       al,1
	jmp       short @114
	?debug L 565
@113:
	mov       edx,dword ptr [ebp+8]
	cmp       dword ptr [edx+4],0
	je        short @115
	?debug L 566
	mov       ecx,dword ptr [ebp+8]
	mov       eax,dword ptr [ecx+4]
	push      eax
	call      @CloseHandle
	?debug L 568
@115:
	mov       edx,dword ptr [ebp+8]
	xor       ecx,ecx
	mov       dword ptr [edx+4],ecx
	?debug L 571
	push      260
	lea       eax,dword ptr [ebp-260]
	push      eax
	call      @GetSystemDirectoryA
	test      eax,eax
	jne       short @116
	?debug L 573
	xor       eax,eax
	jmp       short @114
	?debug L 576
@116:
	push      offset s@+23
	lea       edx,dword ptr [ebp-260]
	push      edx
	call      @_strcat
	add       esp,8
	?debug L 578
	push      offset s@+7
	call      @@UnloadDeviceDriver$qpxc
	pop       ecx
	test      eax,eax
	jne       short @117
	?debug L 580
	xor       eax,eax
	jmp       short @114
	?debug L 583
@117:
	lea       edx,dword ptr [ebp-260]
	push      edx
	call      @DeleteFileA
	?debug L 584
	mov       al,1
	?debug L 585
@118:
@114:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@TWinPort@Remove$qv	endp
@TWinPort@Remove$qv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	66
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch61
	dd	?patch62
	dd	?patch63
	df	@@TWinPort@Remove$qv
	dw	0
	dw	4195
	dw	0
	dw	114
	dw	0
	dw	0
	dw	0
	db	19
	db	64
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	64
	db	82
	db	101
	db	109
	db	111
	db	118
	db	101
	db	36
	db	113
	db	118
	dw	18
	dw	512
	dw	8
	dw	0
	dw	4117
	dw	0
	dw	115
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65276
	dw	65535
	dw	4197
	dw	0
	dw	116
	dw	0
	dw	0
	dw	0
?patch61	equ	@118-@@TWinPort@Remove$qv+4
?patch62	equ	0
?patch63	equ	@118-@@TWinPort@Remove$qv
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p8TWinPort	segment virtual
	align	2
@@$xt$p8TWinPort	label	dword
	dd	4
	dw	16
	dw	12
	dd	@@$xt$8TWinPort
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	32
	db	42
	db	0
@$xt$p8TWinPort	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$8TWinPort	segment virtual
	align	2
@@$xt$8TWinPort	label	byte
	dd	12
	dw	3
	dw	48
	dd	-1
	dd	3
	dw	60
	dw	64
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@@TWinPort@$bdtr$qv
	dw	1
	dw	68
	db	84
	db	87
	db	105
	db	110
	db	80
	db	111
	db	114
	db	116
	db	0
	db	0
	db	0
	db	0
	dd	0
	dd	0
	dd	0
@$xt$8TWinPort	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	;	s@+0:
	db	"\\.\%s",0
	;	s@+7:
	db	"WINIO",0
	;	s@+13:
	db	"winio.sys",0
	;	s@+23:
	db	"\Drivers\winio.sys",0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
@CreateServiceA equ CreateServiceA
 extrn   CreateServiceA:near
@CloseServiceHandle equ CloseServiceHandle
 extrn   CloseServiceHandle:near
@OpenServiceA equ OpenServiceA
 extrn   OpenServiceA:near
@StartServiceA equ StartServiceA
 extrn   StartServiceA:near
@GetLastError equ GetLastError
 extrn   GetLastError:near
@_wsprintfA equ _wsprintfA
 extrn   _wsprintfA:near
@CreateFileA equ CreateFileA
 extrn   CreateFileA:near
@CloseHandle equ CloseHandle
 extrn   CloseHandle:near
@ControlService equ ControlService
 extrn   ControlService:near
@DeleteService equ DeleteService
 extrn   DeleteService:near
@OpenSCManagerA equ OpenSCManagerA
 extrn   OpenSCManagerA:near
@DeviceIoControl equ DeviceIoControl
 extrn   DeviceIoControl:near
@_memset equ _memset
 extrn   _memset:near
@GetVersionExA equ GetVersionExA
 extrn   GetVersionExA:near
 extrn   __Exception_list:dword
 extrn   @__InitExceptBlockLDTC:near
 extrn   @$bdele$qpv:near
@FormatMessageA equ FormatMessageA
 extrn   FormatMessageA:near
@GetModuleFileNameA equ GetModuleFileNameA
 extrn   GetModuleFileNameA:near
@GetModuleHandleA equ GetModuleHandleA
 extrn   GetModuleHandleA:near
@@std@strrchr$qpci equ @std@strrchr$qpci
 extrn   @std@strrchr$qpci:near
@_strcat equ _strcat
 extrn   _strcat:near
@GetSystemDirectoryA equ GetSystemDirectoryA
 extrn   GetSystemDirectoryA:near
@CopyFileA equ CopyFileA
 extrn   CopyFileA:near
@DeleteFileA equ DeleteFileA
 extrn   DeleteFileA:near
 ?debug  C FB0A57696E706F7274333200
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F757569642E6C6962
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	?patch64
	dw	37
	dw	117
	dw	0
	dw	0
	dw	0
	dw	0
?patch64	equ	12
	dw	16
	dw	4
	dw	4115
	dw	0
	dw	1
	dw	118
	dw	0
	dw	0
	dw	0
	dw	16
	dw	4
	dw	4169
	dw	0
	dw	1
	dw	119
	dw	0
	dw	0
	dw	0
	dw	?patch65
	dw	38
	dw	238
	dw	120
	dw	0
	dw	121
	dw	0
	dw	122
	dw	0
	dw	123
	dw	0
	dw	124
	dw	0
	dw	125
	dw	0
	dw	126
	dw	0
	dw	127
	dw	0
	dw	128
	dw	0
	dw	129
	dw	0
	dw	130
	dw	0
	dw	131
	dw	0
	dw	132
	dw	0
	dw	133
	dw	0
	dw	134
	dw	0
	dw	135
	dw	0
	dw	136
	dw	0
	dw	137
	dw	0
	dw	138
	dw	0
	dw	139
	dw	0
	dw	140
	dw	0
	dw	141
	dw	0
	dw	142
	dw	0
	dw	143
	dw	0
	dw	144
	dw	0
	dw	145
	dw	0
	dw	146
	dw	0
	dw	147
	dw	0
	dw	148
	dw	0
	dw	149
	dw	0
	dw	150
	dw	0
	dw	151
	dw	0
	dw	152
	dw	0
	dw	153
	dw	0
	dw	154
	dw	0
	dw	155
	dw	0
	dw	156
	dw	0
	dw	157
	dw	0
	dw	158
	dw	0
	dw	159
	dw	0
	dw	160
	dw	0
	dw	161
	dw	0
	dw	162
	dw	0
	dw	163
	dw	0
	dw	164
	dw	0
	dw	165
	dw	0
	dw	166
	dw	0
	dw	167
	dw	0
	dw	168
	dw	0
	dw	169
	dw	0
	dw	170
	dw	0
	dw	171
	dw	0
	dw	172
	dw	0
	dw	173
	dw	0
	dw	174
	dw	0
	dw	175
	dw	0
	dw	176
	dw	0
	dw	177
	dw	0
	dw	178
	dw	0
	dw	179
	dw	0
	dw	180
	dw	0
	dw	181
	dw	0
	dw	182
	dw	0
	dw	183
	dw	0
	dw	184
	dw	0
	dw	185
	dw	0
	dw	186
	dw	0
	dw	187
	dw	0
	dw	188
	dw	0
	dw	189
	dw	0
	dw	190
	dw	0
	dw	191
	dw	0
	dw	192
	dw	0
	dw	193
	dw	0
	dw	194
	dw	0
	dw	195
	dw	0
	dw	196
	dw	0
	dw	197
	dw	0
	dw	198
	dw	0
	dw	199
	dw	0
	dw	200
	dw	0
	dw	201
	dw	0
	dw	202
	dw	0
	dw	203
	dw	0
	dw	204
	dw	0
	dw	205
	dw	0
	dw	206
	dw	0
	dw	207
	dw	0
	dw	208
	dw	0
	dw	209
	dw	0
	dw	210
	dw	0
	dw	211
	dw	0
	dw	212
	dw	0
	dw	213
	dw	0
	dw	214
	dw	0
	dw	215
	dw	0
	dw	216
	dw	0
	dw	217
	dw	0
	dw	218
	dw	0
	dw	219
	dw	0
	dw	220
	dw	0
	dw	221
	dw	0
	dw	222
	dw	0
	dw	223
	dw	0
	dw	224
	dw	0
	dw	225
	dw	0
	dw	226
	dw	0
	dw	227
	dw	0
	dw	228
	dw	0
	dw	229
	dw	0
	dw	230
	dw	0
	dw	231
	dw	0
	dw	232
	dw	0
	dw	233
	dw	0
	dw	234
	dw	0
	dw	235
	dw	0
	dw	236
	dw	0
	dw	237
	dw	0
	dw	238
	dw	0
	dw	239
	dw	0
	dw	240
	dw	0
	dw	241
	dw	0
	dw	242
	dw	0
	dw	243
	dw	0
	dw	244
	dw	0
	dw	245
	dw	0
	dw	246
	dw	0
	dw	247
	dw	0
	dw	248
	dw	0
	dw	249
	dw	0
	dw	250
	dw	0
	dw	251
	dw	0
	dw	252
	dw	0
	dw	253
	dw	0
	dw	254
	dw	0
	dw	255
	dw	0
	dw	256
	dw	0
	dw	257
	dw	0
	dw	258
	dw	0
	dw	259
	dw	0
	dw	260
	dw	0
	dw	261
	dw	0
	dw	262
	dw	0
	dw	263
	dw	0
	dw	264
	dw	0
	dw	265
	dw	0
	dw	266
	dw	0
	dw	267
	dw	0
	dw	268
	dw	0
	dw	269
	dw	0
	dw	270
	dw	0
	dw	271
	dw	0
	dw	272
	dw	0
	dw	273
	dw	0
	dw	274
	dw	0
	dw	275
	dw	0
	dw	276
	dw	0
	dw	277
	dw	0
	dw	278
	dw	0
	dw	279
	dw	0
	dw	280
	dw	0
	dw	281
	dw	0
	dw	282
	dw	0
	dw	283
	dw	0
	dw	284
	dw	0
	dw	285
	dw	0
	dw	286
	dw	0
	dw	287
	dw	0
	dw	288
	dw	0
	dw	289
	dw	0
	dw	290
	dw	0
	dw	291
	dw	0
	dw	292
	dw	0
	dw	293
	dw	0
	dw	294
	dw	0
	dw	295
	dw	0
	dw	296
	dw	0
	dw	297
	dw	0
	dw	298
	dw	0
	dw	299
	dw	0
	dw	300
	dw	0
	dw	301
	dw	0
	dw	302
	dw	0
	dw	303
	dw	0
	dw	304
	dw	0
	dw	305
	dw	0
	dw	306
	dw	0
	dw	307
	dw	0
	dw	308
	dw	0
	dw	309
	dw	0
	dw	310
	dw	0
	dw	311
	dw	0
	dw	312
	dw	0
	dw	313
	dw	0
	dw	314
	dw	0
	dw	315
	dw	0
	dw	316
	dw	0
	dw	317
	dw	0
	dw	318
	dw	0
	dw	319
	dw	0
	dw	320
	dw	0
	dw	321
	dw	0
	dw	322
	dw	0
	dw	323
	dw	0
	dw	324
	dw	0
	dw	325
	dw	0
	dw	326
	dw	0
	dw	327
	dw	0
	dw	328
	dw	0
	dw	329
	dw	0
	dw	330
	dw	0
	dw	331
	dw	0
	dw	332
	dw	0
	dw	333
	dw	0
	dw	334
	dw	0
	dw	335
	dw	0
	dw	336
	dw	0
	dw	337
	dw	0
	dw	338
	dw	0
	dw	339
	dw	0
	dw	340
	dw	0
	dw	341
	dw	0
	dw	342
	dw	0
	dw	343
	dw	0
	dw	344
	dw	0
	dw	345
	dw	0
	dw	346
	dw	0
	dw	347
	dw	0
	dw	348
	dw	0
	dw	349
	dw	0
	dw	350
	dw	0
	dw	351
	dw	0
	dw	352
	dw	0
	dw	353
	dw	0
	dw	354
	dw	0
	dw	355
	dw	0
	dw	356
	dw	0
	dw	357
	dw	0
?patch65	equ	956
	dw	?patch66
	dw	1
	db	6
	db	1
	db	0
	db	24
	db	9
	db	66
	db	67
	db	67
	db	51
	db	50
	db	32
	db	53
	db	46
	db	53
?patch66	equ	16
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
	db        2,0,0,0,14,0,8,0,116,0,0,0,0,0,3,0
	db        3,16,0,0,8,0,2,0,10,0,2,16,0,0,8,0
	db        1,0,1,0,112,0,0,0,16,0,1,2,3,0,3,4
	db        0,0,1,16,0,0,1,16,0,0,14,0,8,0,116,0
	db        0,0,0,0,2,0,5,16,0,0,12,0,1,2,2,0
	db        3,4,0,0,1,16,0,0,14,0,8,0,116,0,0,0
	db        0,0,2,0,8,16,0,0,8,0,2,0,10,0,3,4
	db        0,0,12,0,1,2,2,0,1,16,0,0,7,16,0,0
	db        18,0,3,0,112,0,0,0,17,0,0,0,0,0,0,0
	db        64,0,64,0,14,0,8,0,116,0,0,0,0,0,2,0
	db        11,16,0,0,12,0,1,2,2,0,3,4,0,0,1,16
	db        0,0,14,0,8,0,116,0,0,0,0,0,2,0,13,16
	db        0,0,12,0,1,2,2,0,3,4,0,0,1,16,0,0
	db        14,0,8,0,116,0,0,0,0,0,1,0,15,16,0,0
	db        8,0,1,2,1,0,1,16,0,0,14,0,8,0,116,0
	db        0,0,0,0,3,0,17,16,0,0,16,0,1,2,3,0
	db        1,16,0,0,1,16,0,0,7,16,0,0,26,0,9,0
	db        48,0,0,0,19,16,0,0,21,16,0,0,0,0,3,0
	db        72,16,0,0,0,0,0,0,28,0,4,0,18,0,71,16
	db        0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0
	db        36,0,0,0,12,0,26,0,9,0,48,0,0,0,19,16
	db        0,0,21,16,0,0,0,0,3,0,22,16,0,0,0,0
	db        0,0,8,0,2,0,10,4,19,16,0,0,16,0,1,2
	db        3,0,33,0,0,0,34,4,0,0,32,0,0,0,26,0
	db        9,0,48,0,0,0,19,16,0,0,21,16,0,0,0,0
	db        3,0,24,16,0,0,0,0,0,0,16,0,1,2,3,0
	db        33,0,0,0,34,0,0,0,32,0,0,0,26,0,9,0
	db        26,16,0,0,19,16,0,0,21,16,0,0,0,0,0,0
	db        27,16,0,0,0,0,0,0,8,0,2,0,10,0,19,16
	db        0,0,4,0,1,2,0,0,26,0,9,0,26,16,0,0
	db        19,16,0,0,21,16,0,0,0,0,1,0,31,16,0,0
	db        0,0,0,0,8,0,2,0,42,0,30,16,0,0,8,0
	db        1,0,1,0,19,16,0,0,8,0,1,2,1,0,29,16
	db        0,0,26,0,9,0,3,0,0,0,19,16,0,0,21,16
	db        0,0,0,0,0,0,33,16,0,0,0,0,0,0,4,0
	db        1,2,0,0,26,0,9,0,48,0,0,0,19,16,0,0
	db        21,16,0,0,0,0,0,0,35,16,0,0,0,0,0,0
	db        4,0,1,2,0,0,26,0,9,0,48,0,0,0,19,16
	db        0,0,21,16,0,0,0,0,0,0,37,16,0,0,0,0
	db        0,0,4,0,1,2,0,0,26,0,9,0,48,0,0,0
	db        19,16,0,0,21,16,0,0,0,0,0,0,39,16,0,0
	db        0,0,0,0,4,0,1,2,0,0,26,0,9,0,32,0
	db        0,0,19,16,0,0,21,16,0,0,0,0,1,0,41,16
	db        0,0,0,0,0,0,8,0,1,2,1,0,33,0,0,0
	db        26,0,9,0,33,0,0,0,19,16,0,0,21,16,0,0
	db        0,0,1,0,43,16,0,0,0,0,0,0,8,0,1,2
	db        1,0,33,0,0,0,26,0,9,0,34,0,0,0,19,16
	db        0,0,21,16,0,0,0,0,1,0,45,16,0,0,0,0
	db        0,0,8,0,1,2,1,0,33,0,0,0,26,0,9,0
	db        3,0,0,0,19,16,0,0,21,16,0,0,0,0,2,0
	db        47,16,0,0,0,0,0,0,12,0,1,2,2,0,33,0
	db        0,0,32,0,0,0,26,0,9,0,3,0,0,0,19,16
	db        0,0,21,16,0,0,0,0,2,0,49,16,0,0,0,0
	db        0,0,12,0,1,2,2,0,33,0,0,0,33,0,0,0
	db        26,0,9,0,3,0,0,0,19,16,0,0,21,16,0,0
	db        0,0,2,0,51,16,0,0,0,0,0,0,12,0,1,2
	db        2,0,33,0,0,0,34,0,0,0,26,0,9,0,48,0
	db        0,0,19,16,0,0,21,16,0,0,0,0,0,0,53,16
	db        0,0,0,0,0,0,4,0,1,2,0,0,26,0,9,0
	db        3,0,0,0,19,16,0,0,21,16,0,0,0,0,2,0
	db        55,16,0,0,0,0,0,0,12,0,1,2,2,0,112,4
	db        0,0,116,0,0,0,12,0,7,2,2,0,20,16,0,0
	db        0,0,0,0,12,0,7,2,2,0,23,16,0,0,0,0
	db        0,0,22,0,7,2,3,4,25,16,0,0,0,0,0,0
	db        35,20,28,16,0,0,0,0,0,0,12,0,7,2,3,8
	db        32,16,0,0,0,0,0,0,12,0,7,2,3,0,34,16
	db        0,0,0,0,0,0,12,0,7,2,3,0,36,16,0,0
	db        0,0,0,0,12,0,7,2,3,0,38,16,0,0,0,0
	db        0,0,12,0,7,2,3,0,40,16,0,0,0,0,0,0
	db        12,0,7,2,3,0,42,16,0,0,0,0,0,0,12,0
	db        7,2,3,0,44,16,0,0,0,0,0,0,12,0,7,2
	db        3,0,46,16,0,0,0,0,0,0,12,0,7,2,3,0
	db        48,16,0,0,0,0,0,0,12,0,7,2,3,0,50,16
	db        0,0,0,0,0,0,12,0,7,2,3,0,52,16,0,0
	db        0,0,0,0,12,0,7,2,3,0,54,16,0,0,0,0
	db        0,0,242,0,4,2,6,4,48,0,0,0,2,0,37,0
	db        0,0,0,0,0,0,0,0,242,241,6,4,3,4,0,0
	db        2,0,38,0,0,0,0,0,0,0,4,0,242,241,6,4
	db        48,0,0,0,2,0,39,0,0,0,0,0,0,0,8,0
	db        242,241,8,4,1,0,56,16,0,0,40,0,0,0,8,4
	db        1,0,57,16,0,0,41,0,0,0,8,4,2,0,58,16
	db        0,0,42,0,0,0,8,4,1,0,59,16,0,0,43,0
	db        0,0,8,4,1,0,60,16,0,0,44,0,0,0,8,4
	db        1,0,61,16,0,0,45,0,0,0,8,4,1,0,62,16
	db        0,0,46,0,0,0,8,4,1,0,63,16,0,0,47,0
	db        0,0,8,4,1,0,64,16,0,0,48,0,0,0,8,4
	db        1,0,65,16,0,0,49,0,0,0,8,4,1,0,66,16
	db        0,0,50,0,0,0,8,4,1,0,67,16,0,0,51,0
	db        0,0,8,4,1,0,68,16,0,0,52,0,0,0,8,4
	db        1,0,69,16,0,0,53,0,0,0,8,4,1,0,70,16
	db        0,0,54,0,0,0,16,0,1,2,3,0,33,0,0,0
	db        34,4,0,0,32,0,0,0,28,0,5,0,3,0,74,16
	db        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db        60,0,0,0,12,0,60,0,4,2,6,4,33,0,0,0
	db        3,0,61,0,0,0,0,0,0,0,0,0,242,241,6,4
	db        34,0,0,0,3,0,62,0,0,0,0,0,0,0,4,0
	db        242,241,6,4,32,0,0,0,3,0,63,0,0,0,0,0
	db        0,0,8,0,26,0,9,0,48,0,0,0,19,16,0,0
	db        21,16,0,0,0,0,3,0,76,16,0,0,0,0,0,0
	db        16,0,1,2,3,0,33,0,0,0,34,0,0,0,32,0
	db        0,0,26,0,9,0,26,16,0,0,19,16,0,0,21,16
	db        0,0,0,0,0,0,78,16,0,0,0,0,0,0,4,0
	db        1,2,0,0,26,0,9,0,3,0,0,0,19,16,0,0
	db        21,16,0,0,0,0,0,0,80,16,0,0,0,0,0,0
	db        4,0,1,2,0,0,26,0,9,0,32,0,0,0,19,16
	db        0,0,21,16,0,0,0,0,1,0,82,16,0,0,0,0
	db        0,0,8,0,1,2,1,0,33,0,0,0,26,0,9,0
	db        33,0,0,0,19,16,0,0,21,16,0,0,0,0,1,0
	db        84,16,0,0,0,0,0,0,8,0,1,2,1,0,33,0
	db        0,0,26,0,9,0,34,0,0,0,19,16,0,0,21,16
	db        0,0,0,0,1,0,86,16,0,0,0,0,0,0,8,0
	db        1,2,1,0,33,0,0,0,26,0,9,0,3,0,0,0
	db        19,16,0,0,21,16,0,0,0,0,2,0,88,16,0,0
	db        0,0,0,0,12,0,1,2,2,0,33,0,0,0,32,0
	db        0,0,26,0,9,0,3,0,0,0,19,16,0,0,21,16
	db        0,0,0,0,2,0,90,16,0,0,0,0,0,0,12,0
	db        1,2,2,0,33,0,0,0,33,0,0,0,26,0,9,0
	db        3,0,0,0,19,16,0,0,21,16,0,0,0,0,2,0
	db        92,16,0,0,0,0,0,0,12,0,1,2,2,0,33,0
	db        0,0,34,0,0,0,26,0,9,0,3,0,0,0,19,16
	db        0,0,21,16,0,0,0,0,2,0,94,16,0,0,0,0
	db        0,0,12,0,1,2,2,0,112,4,0,0,116,0,0,0
	db        26,0,9,0,48,0,0,0,19,16,0,0,21,16,0,0
	db        0,0,0,0,96,16,0,0,0,0,0,0,4,0,1,2
	db        0,0,18,0,3,0,112,0,0,0,17,0,0,0,0,0
	db        0,0,4,1,4,1,18,0,3,0,112,0,0,0,17,0
	db        0,0,0,0,0,0,4,1,4,1,26,0,9,0,48,0
	db        0,0,19,16,0,0,21,16,0,0,0,0,0,0,100,16
	db        0,0,0,0,0,0,4,0,1,2,0,0,18,0,3,0
	db        112,0,0,0,17,0,0,0,0,0,0,0,4,1,4,1
	db        14,0,8,0,3,4,0,0,7,0,13,0,103,16,0,0
	db        56,0,1,2,13,0,3,4,0,0,1,16,0,0,1,16
	db        0,0,34,0,0,0,34,0,0,0,34,0,0,0,34,0
	db        0,0,1,16,0,0,1,16,0,0,34,4,0,0,1,16
	db        0,0,1,16,0,0,1,16,0,0,14,0,8,0,116,0
	db        0,0,7,0,1,0,105,16,0,0,8,0,1,2,1,0
	db        3,4,0,0,14,0,8,0,3,4,0,0,7,0,3,0
	db        107,16,0,0,16,0,1,2,3,0,3,4,0,0,1,16
	db        0,0,34,0,0,0,14,0,8,0,116,0,0,0,7,0
	db        3,0,110,16,0,0,8,0,2,0,10,0,1,16,0,0
	db        16,0,1,2,3,0,3,4,0,0,34,0,0,0,109,16
	db        0,0,14,0,8,0,34,0,0,0,7,0,0,0,112,16
	db        0,0,4,0,1,2,0,0,14,0,8,0,116,0,0,0
	db        64,0,3,0,114,16,0,0,16,0,1,2,3,0,112,4
	db        0,0,1,16,0,0,0,0,0,0,14,0,8,0,3,4
	db        0,0,7,0,7,0,116,16,0,0,32,0,1,2,7,0
	db        1,16,0,0,34,0,0,0,34,0,0,0,253,255,255,255
	db        34,0,0,0,34,0,0,0,3,4,0,0,14,0,8,0
	db        116,0,0,0,7,0,1,0,118,16,0,0,8,0,1,2
	db        1,0,3,4,0,0,14,0,8,0,116,0,0,0,7,0
	db        3,0,120,16,0,0,16,0,1,2,3,0,3,4,0,0
	db        34,0,0,0,252,255,255,255,14,0,8,0,116,0,0,0
	db        7,0,1,0,122,16,0,0,8,0,1,2,1,0,3,4
	db        0,0,14,0,8,0,3,4,0,0,7,0,3,0,124,16
	db        0,0,16,0,1,2,3,0,1,16,0,0,1,16,0,0
	db        34,0,0,0,14,0,8,0,116,0,0,0,7,0,8,0
	db        126,16,0,0,36,0,1,2,8,0,3,4,0,0,34,0
	db        0,0,3,4,0,0,34,0,0,0,3,4,0,0,34,0
	db        0,0,34,4,0,0,251,255,255,255,14,0,8,0,3,4
	db        0,0,0,0,3,0,128,16,0,0,16,0,1,2,3,0
	db        3,4,0,0,116,0,0,0,117,0,0,0,14,0,8,0
	db        116,0,0,0,7,0,1,0,130,16,0,0,8,0,1,2
	db        1,0,250,255,255,255,8,0,2,0,10,2,3,0,0,0
	db        14,0,8,0,3,0,0,0,4,0,1,0,133,16,0,0
	db        8,0,1,2,1,0,3,4,0,0,14,0,8,0,3,0
	db        0,0,0,0,1,0,135,16,0,0,8,0,1,2,1,0
	db        3,4,0,0,14,0,8,0,34,0,0,0,7,0,7,0
	db        139,16,0,0,8,0,2,0,10,0,138,16,0,0,8,0
	db        1,0,1,0,3,0,0,0,32,0,1,2,7,0,34,0
	db        0,0,137,16,0,0,34,0,0,0,34,0,0,0,112,4
	db        0,0,34,0,0,0,7,16,0,0,14,0,8,0,34,0
	db        0,0,7,0,3,0,141,16,0,0,16,0,1,2,3,0
	db        3,4,0,0,112,4,0,0,34,0,0,0,14,0,8,0
	db        3,4,0,0,7,0,1,0,143,16,0,0,8,0,1,2
	db        1,0,1,16,0,0,14,0,8,0,112,4,0,0,0,0
	db        2,0,145,16,0,0,12,0,1,2,2,0,112,4,0,0
	db        116,0,0,0,14,0,8,0,112,4,0,0,0,0,2,0
	db        147,16,0,0,12,0,1,2,2,0,112,4,0,0,1,16
	db        0,0,14,0,8,0,117,0,0,0,7,0,2,0,149,16
	db        0,0,12,0,1,2,2,0,112,4,0,0,117,0,0,0
	db        14,0,8,0,116,0,0,0,7,0,3,0,151,16,0,0
	db        16,0,1,2,3,0,1,16,0,0,1,16,0,0,116,0
	db        0,0,14,0,8,0,116,0,0,0,7,0,1,0,153,16
	db        0,0,8,0,1,2,1,0,1,16,0,0
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
	db	13,'InstallDriver'
	db	12,'SchSCManager'
	db	10,'DriverName'
	db	10,'ServiceExe'
	db	10,'schService'
	db	11,'StartDriver'
	db	12,'SchSCManager'
	db	10,'DriverName'
	db	3,'ret'
	db	10,'schService'
	db	10,'OpenDevice'
	db	10,'DriverName'
	db	9,'lphDevice'
	db	7,'hDevice'
	db	18,'completeDeviceName'
	db	10,'StopDriver'
	db	12,'SchSCManager'
	db	10,'DriverName'
	db	13,'serviceStatus'
	db	3,'ret'
	db	10,'schService'
	db	12,'RemoveDriver'
	db	12,'SchSCManager'
	db	10,'DriverName'
	db	3,'ret'
	db	10,'schService'
	db	18,'UnloadDeviceDriver'
	db	4,'Name'
	db	12,'schSCManager'
	db	16,'LoadDeviceDriver'
	db	4,'Name'
	db	4,'Path'
	db	9,'lphDevice'
	db	4,'okay'
	db	12,'schSCManager'
	db	8,'TWinPort'
	db	5,'WinNT'
	db	7,'hDriver'
	db	5,'error'
	db	10,'GetPortVal'
	db	10,'SetPortVal'
	db	18,'@TWinPort@$bctr$qv'
	db	18,'@TWinPort@$bdtr$qv'
	db	9,'Installed'
	db	7,'Install'
	db	6,'Remove'
	db	8,'ReadByte'
	db	8,'ReadWord'
	db	9,'ReadDWord'
	db	9,'WriteByte'
	db	9,'WriteWord'
	db	10,'WriteDWord'
	db	5,'Error'
	db	12,'ErrorMessage'
	db	20,'@TWinPort@GetPortVal'
	db	4,'this'
	db	9,'wPortAddr'
	db	10,'pdwPortVal'
	db	5,'bSize'
	db	15,'tagPort32Struct'
	db	9,'wPortAddr'
	db	9,'dwPortVal'
	db	5,'bSize'
	db	12,'Port32Struct'
	db	15,'dwBytesReturned'
	db	20,'@TWinPort@SetPortVal'
	db	4,'this'
	db	9,'wPortAddr'
	db	9,'dwPortVal'
	db	5,'bSize'
	db	12,'Port32Struct'
	db	15,'dwBytesReturned'
	db	18,'@TWinPort@$bctr$qv'
	db	4,'this'
	db	4,'info'
	db	18,'@TWinPort@$bdtr$qv'
	db	4,'this'
	db	18,'@TWinPort@ReadByte'
	db	4,'this'
	db	3,'adr'
	db	3,'val'
	db	1,'b'
	db	18,'@TWinPort@ReadWord'
	db	4,'this'
	db	3,'adr'
	db	3,'val'
	db	1,'w'
	db	19,'@TWinPort@ReadDWord'
	db	4,'this'
	db	3,'adr'
	db	3,'val'
	db	1,'w'
	db	19,'@TWinPort@WriteByte'
	db	4,'this'
	db	3,'adr'
	db	4,'data'
	db	19,'@TWinPort@WriteWord'
	db	4,'this'
	db	3,'adr'
	db	4,'data'
	db	20,'@TWinPort@WriteDWord'
	db	4,'this'
	db	3,'adr'
	db	4,'data'
	db	22,'@TWinPort@ErrorMessage'
	db	4,'this'
	db	6,'buffer'
	db	6,'maxlen'
	db	17,'@TWinPort@Install'
	db	4,'this'
	db	8,'pszSlash'
	db	7,'DstPath'
	db	7,'SrcPath'
	db	16,'@TWinPort@Remove'
	db	4,'this'
	db	7,'DstPath'
	db	3,'std'
	db	8,'TWinPort'
	db	15,'tagPort32Struct'
	db	5,'_rotr'
	db	5,'_rotl'
	db	6,'_crotr'
	db	6,'_lrotr'
	db	6,'_lrotl'
	db	6,'_crotl'
	db	3,'abs'
	db	6,'wctomb'
	db	7,'wcstoul'
	db	8,'wcstombs'
	db	6,'wcstol'
	db	6,'wcstod'
	db	5,'ultoa'
	db	4,'time'
	db	6,'system'
	db	4,'swab'
	db	7,'strtoul'
	db	6,'strtol'
	db	6,'strtod'
	db	5,'srand'
	db	7,'realloc'
	db	4,'rand'
	db	6,'putenv'
	db	6,'perror'
	db	6,'mbtowc'
	db	8,'mbstowcs'
	db	5,'mblen'
	db	13,'_seterrormode'
	db	26,'@std@%max$T1%$qrxT1t1$rxT1'
	db	26,'@std@%min$T1%$qrxT1t1$rxT1'
	db	17,'@std@randomize$qv'
	db	14,'@std@random$qi'
	db	4,'ltoa'
	db	4,'gcvt'
	db	4,'fcvt'
	db	4,'ecvt'
	db	6,'malloc'
	db	4,'ldiv'
	db	4,'labs'
	db	4,'itoa'
	db	6,'getenv'
	db	4,'free'
	db	4,'exit'
	db	3,'div'
	db	6,'calloc'
	db	4,'atol'
	db	4,'atoi'
	db	4,'atof'
	db	6,'atexit'
	db	5,'abort'
	db	6,'_wtold'
	db	5,'_wtol'
	db	5,'_wtoi'
	db	5,'_wtof'
	db	8,'_wsystem'
	db	11,'_wsplitpath'
	db	11,'_wsearchstr'
	db	11,'_wsearchenv'
	db	8,'_wputenv'
	db	8,'_wperror'
	db	10,'_wmakepath'
	db	8,'_wgetenv'
	db	10,'_wfullpath'
	db	8,'_wcstold'
	db	8,'_strtold'
	db	10,'_splitpath'
	db	10,'_searchstr'
	db	10,'_searchenv'
	db	9,'_makepath'
	db	7,'_wtoi64'
	db	8,'_ui64tow'
	db	8,'_ui64toa'
	db	7,'_i64tow'
	db	7,'_i64toa'
	db	7,'_atoi64'
	db	5,'_ltow'
	db	5,'_ltoa'
	db	6,'_lrand'
	db	5,'_itow'
	db	6,'_ultow'
	db	5,'_gcvt'
	db	5,'_fcvt'
	db	9,'_fullpath'
	db	5,'_exit'
	db	6,'_atold'
	db	5,'_ecvt'
	db	7,'__errno'
	db	10,'__doserrno'
	db	5,'qsort'
	db	7,'lsearch'
	db	5,'lfind'
	db	7,'bsearch'
	db	7,'wcsxfrm'
	db	6,'wcstok'
	db	6,'wcsstr'
	db	6,'wcsspn'
	db	7,'wcsrchr'
	db	7,'wcspcpy'
	db	7,'wcspbrk'
	db	7,'wcsncpy'
	db	7,'wcsncmp'
	db	7,'wcsncat'
	db	6,'wcslen'
	db	7,'wcscspn'
	db	6,'wcscpy'
	db	7,'wcscoll'
	db	6,'wcscmp'
	db	6,'wcschr'
	db	6,'wcscat'
	db	6,'strtok'
	db	18,'@std@strstr$qpxct1'
	db	18,'@std@strstr$qpcpxc'
	db	6,'strspn'
	db	19,'@std@strpbrk$qpxct1'
	db	19,'@std@strpbrk$qpcpxc'
	db	8,'strerror'
	db	7,'strcspn'
	db	18,'@std@strrchr$qpxci'
	db	17,'@std@strrchr$qpci'
	db	7,'strncpy'
	db	7,'strncmp'
	db	7,'strncat'
	db	6,'strlen'
	db	17,'@std@strchr$qpxci'
	db	16,'@std@strchr$qpci'
	db	6,'strcat'
	db	6,'strset'
	db	6,'stpcpy'
	db	7,'strnset'
	db	7,'_wcsset'
	db	7,'_wcsrev'
	db	8,'_wcspcpy'
	db	8,'_wcsnset'
	db	10,'_wcsnicoll'
	db	9,'_wcsnicmp'
	db	9,'_wcsncoll'
	db	9,'_wcsicoll'
	db	8,'_wcsicmp'
	db	7,'_wcsdup'
	db	10,'_strnicoll'
	db	9,'_strncoll'
	db	9,'_stricoll'
	db	9,'_strerror'
	db	9,'_lwcsxfrm'
	db	8,'_lwcsupr'
	db	11,'_lwcsnicoll'
	db	10,'_lwcsncoll'
	db	8,'_lwcslwr'
	db	10,'_lwcsicoll'
	db	9,'_lwcscoll'
	db	9,'_lstrxfrm'
	db	11,'_lstrnicoll'
	db	10,'_lstrncoll'
	db	10,'_lstricoll'
	db	9,'_lstrcoll'
	db	6,'strrev'
	db	8,'strnicmp'
	db	7,'stricmp'
	db	6,'strdup'
	db	7,'_stpcpy'
	db	8,'_lstrupr'
	db	8,'_lstrlwr'
	db	12,'_lwsetlocale'
	db	11,'_wsetlocale'
	db	12,'_llocaleconv'
	db	10,'localeconv'
	db	11,'_lsetlocale'
	db	10,'_ltowlower'
	db	10,'_ltowupper'
	db	8,'towupper'
	db	8,'towlower'
	db	9,'_ltoupper'
	db	7,'toupper'
	db	9,'_ltolower'
	db	7,'tolower'
	db	8,'iswascii'
	db	9,'iswxdigit'
	db	8,'iswupper'
	db	8,'iswspace'
	db	8,'iswpunct'
	db	8,'iswprint'
	db	8,'iswlower'
	db	8,'iswgraph'
	db	8,'iswdigit'
	db	8,'iswcntrl'
	db	8,'iswalpha'
	db	8,'iswalnum'
	db	7,'isascii'
	db	8,'isxdigit'
	db	7,'isupper'
	db	7,'isspace'
	db	7,'ispunct'
	db	7,'isprint'
	db	7,'islower'
	db	7,'isgraph'
	db	7,'isdigit'
	db	7,'iscntrl'
	db	7,'isalpha'
	db	7,'isalnum'
	db	6,'memset'
	db	6,'memcpy'
	db	6,'memcmp'
	db	19,'@std@memchr$qpxviui'
	db	18,'@std@memchr$qpviui'
	db	7,'memmove'
	db	7,'memicmp'
	db	7,'memccpy'
	db	8,'_wmemset'
	db	8,'_wmemcpy'
	db	21,'@std@_wmemchr$qpxviui'
	db	20,'@std@_wmemchr$qpviui'
	db	10,'__threadid'
	db	14,'@std@ptrdiff_t'
	db	11,'@std@size_t'
	db	11,'@std@wint_t'
	db	13,'@std@wctype_t'
	db	12,'@std@va_list'
	db	9,'_chartype'
	db	6,'_lower'
	db	6,'_upper'
	db	5,'lconv'
	db	5,'_argc'
	db	5,'_argv'
	db	12,'__mb_cur_max'
	db	16,'_cmdline_escapes'
	db	8,'_environ'
	db	9,'_fileinfo'
	db	6,'_fmode'
	db	8,'_osmajor'
	db	8,'_osminor'
	db	7,'_osmode'
	db	10,'_osversion'
	db	12,'_sys_errlist'
	db	9,'_sys_nerr'
	db	9,'_wenviron'
	db	13,'@std@atexit_t'
	db	10,'@std@div_t'
	db	11,'@std@ldiv_t'
$$BNAMES	ends
	?debug	D "D:\projects\mku\common\windows\WinPort32.h" 12102 29257
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\WINIOCTL.H" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\imm.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mcx.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsvc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\commdlg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oleauto.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\propidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oaidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\msxml.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\servprov.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oleidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\urlmon.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\cguid.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\unknwn.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\search.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdlib.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objbase.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ole2.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\prsht.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winspool.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsmcrd.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winioctl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnsip.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcndr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wtypes.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winscard.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winefs.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wincrypt.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\qos.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsock2.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winperf.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\shellapi.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcasync.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnterr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnsi.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcdcep.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcdce.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\windows.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\nb30.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mmsystem.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\lzexpand.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dlgs.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ddeml.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dde.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\cderr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnetwk.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winreg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winver.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wincon.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnls.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\tvout.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winuser.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack1.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wingdi.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winerror.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winbase.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack8.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack2.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\poppack.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack4.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_loc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\locale.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_str.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\string.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\guiddef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\basetsd.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mbctype.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ctype.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnt.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\windef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdarg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\excpt.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_null.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_defs.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_stddef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mem.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\WINDOWS.H" 10303 10240
	?debug	D "D:\projects\mku\common\windows\Winport32.cpp" 11965 26754
 ?debug  C FB062A633A5C50524F4752417E315C626F726C616E645C434255494C447E315C6C69625C76636C35302E23303425D60F00DB4E9B31
 ?debug  C FB0510235F534552564943455F535441545553
 ?debug  C FB0510235F4F5356455253494F4E494E464F41
 ?debug  C FB0516232A5F53454355524954595F41545452494255544553
 ?debug  C FB0511232A5F534552564943455F535441545553
 ?debug  C FB050D232A5F4F5645524C4150504544
 ?debug  C FB0511232A5F4F5356455253494F4E494E464F41
	end
