	.file	"cwf.c"
	.section	.rodata
.LC0:
	.string	"Cache-Control"
.LC1:
	.string	"Connection"
.LC2:
	.string	"Date"
.LC3:
	.string	"Pragma"
.LC4:
	.string	"Trailer"
.LC5:
	.string	"Transfer-Encoding"
.LC6:
	.string	"Upgrade"
.LC7:
	.string	"Via"
.LC8:
	.string	"Warning"
.LC9:
	.string	"Accept"
.LC10:
	.string	"Accept-Charset"
.LC11:
	.string	"Accept-Encoding"
.LC12:
	.string	"Accept-Language"
.LC13:
	.string	"Authorization"
.LC14:
	.string	"Expect"
.LC15:
	.string	"From"
.LC16:
	.string	"Host"
.LC17:
	.string	"If-Match"
.LC18:
	.string	"If-Modified-Since"
.LC19:
	.string	"If-None-Match"
.LC20:
	.string	"If-Range"
.LC21:
	.string	"If-Unmodified-Since"
.LC22:
	.string	"Max-Forwards"
.LC23:
	.string	"Proxy-Authorization"
.LC24:
	.string	"Range"
.LC25:
	.string	"Referer"
.LC26:
	.string	"TE"
.LC27:
	.string	"User-Agent"
.LC28:
	.string	"Allow"
.LC29:
	.string	"Content-Encoding"
.LC30:
	.string	"Content-Language"
.LC31:
	.string	"Content-Length"
.LC32:
	.string	"Content-Location"
.LC33:
	.string	"Content-MD5"
.LC34:
	.string	"Content-Range"
.LC35:
	.string	"Content-Type"
.LC36:
	.string	"Expires"
.LC37:
	.string	"Last-Modified"
.LC38:
	.string	"extension-header"
.LC39:
	.string	"Accept-Ranges"
.LC40:
	.string	"Age"
.LC41:
	.string	"ETag"
.LC42:
	.string	"Location"
.LC43:
	.string	"Proxy-Authenticate"
.LC44:
	.string	"Retry-After"
.LC45:
	.string	"Server"
.LC46:
	.string	"Vary"
.LC47:
	.string	"WWW-Authenticate"
	.data
	.align 64
	.type	header_fields, @object
	.size	header_fields, 384
header_fields:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC8
	.quad	.LC9
	.quad	.LC10
	.quad	.LC11
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.quad	.LC18
	.quad	.LC19
	.quad	.LC20
	.quad	.LC21
	.quad	.LC22
	.quad	.LC23
	.quad	.LC24
	.quad	.LC25
	.quad	.LC26
	.quad	.LC27
	.quad	.LC28
	.quad	.LC29
	.quad	.LC30
	.quad	.LC31
	.quad	.LC32
	.quad	.LC33
	.quad	.LC34
	.quad	.LC35
	.quad	.LC36
	.quad	.LC37
	.quad	.LC38
	.quad	.LC39
	.quad	.LC40
	.quad	.LC41
	.quad	.LC42
	.quad	.LC43
	.quad	.LC44
	.quad	.LC45
	.quad	.LC46
	.quad	.LC47
	.globl	clients
	.bss
	.align 8
	.type	clients, @object
	.size	clients, 8
clients:
	.zero	8
	.globl	nclients
	.data
	.align 4
	.type	nclients, @object
	.size	nclients, 4
nclients:
	.long	10
	.section	.rodata
.LC48:
	.string	"ERROR opening socket"
.LC49:
	.string	"ERROR setting reuseaddr"
.LC50:
	.string	"ERROR on binding"
.LC51:
	.string	"selecting..."
.LC52:
	.string	"ERROR select"
.LC53:
	.string	"new client available"
.LC54:
	.string	"ERROR accepting"
.LC55:
	.string	"ERROR finding client"
.LC56:
	.string	"ERROR on read"
.LC57:
	.string	"ERROR parsing buffer"
	.align 8
.LC58:
	.string	"method: %s\npath: %s\nversion: %d.%d\n"
.LC59:
	.string	"OK"
.LC60:
	.string	"text/plain"
.LC61:
	.string	"404"
.LC62:
	.string	"not found"
.LC63:
	.string	"%d"
.LC64:
	.string	"error responding"
	.text
	.globl	CWF_start
	.type	CWF_start, @function
CWF_start:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$2856, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -2856(%rbp)
	movl	%esi, -2860(%rbp)
	movl	$0, -44(%rbp)
	movl	$0, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket
	movl	%eax, -48(%rbp)
	cmpl	$0, -48(%rbp)
	jns	.L2
	movl	$.LC48, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L34
.L2:
	leaq	-384(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	bzero
	movw	$2, -384(%rbp)
	movl	$0, -380(%rbp)
	movl	-2860(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	htons
	movw	%ax, -382(%rbp)
	movl	$1, -1428(%rbp)
	leaq	-1428(%rbp), %rdx
	movl	-48(%rbp), %eax
	movl	$4, %r8d
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	setsockopt
	testl	%eax, %eax
	jns	.L4
	movl	$.LC49, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L34
.L4:
	leaq	-384(%rbp), %rcx
	movl	-48(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	bind
	testl	%eax, %eax
	jns	.L5
	movl	$.LC50, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L34
.L5:
	movl	-48(%rbp), %eax
	movl	$10, %esi
	movl	%eax, %edi
	call	listen
	movl	$0, %eax
	movl	$16, %ecx
	leaq	-224(%rbp), %rdx
	movq	%rdx, %rdi
#APP
# 58 "cwf.c" 1
	cld; rep; stosq
# 0 "" 2
#NO_APP
	movl	%edi, %eax
	movl	%ecx, %edx
	movl	%edx, -52(%rbp)
	movl	%eax, -56(%rbp)
	movl	$0, %eax
	movl	$16, %ecx
	leaq	-352(%rbp), %rdx
	movq	%rdx, %rdi
#APP
# 59 "cwf.c" 1
	cld; rep; stosq
# 0 "" 2
#NO_APP
	movl	%edi, %eax
	movl	%ecx, %edx
	movl	%edx, -60(%rbp)
	movl	%eax, -64(%rbp)
	movl	-48(%rbp), %eax
	leal	63(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$6, %eax
	movl	%eax, %esi
	movslq	%esi, %rax
	movq	-224(%rbp,%rax,8), %rdi
	movl	-48(%rbp), %eax
	cltd
	shrl	$26, %edx
	addl	%edx, %eax
	andl	$63, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	salq	%cl, %rdx
	movq	%rdx, %rax
	orq	%rax, %rdi
	movq	%rdi, %rdx
	movslq	%esi, %rax
	movq	%rdx, -224(%rbp,%rax,8)
	movl	-48(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	$24, %esi
	movl	$10, %edi
	call	calloc
	movq	%rax, clients(%rip)
.L33:
	movq	-224(%rbp), %rax
	movq	%rax, -352(%rbp)
	movq	-216(%rbp), %rax
	movq	%rax, -344(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -336(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -328(%rbp)
	movq	-192(%rbp), %rax
	movq	%rax, -320(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -312(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -304(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -296(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -288(%rbp)
	movq	-152(%rbp), %rax
	movq	%rax, -280(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-128(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -240(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -232(%rbp)
	movl	$.LC51, %edi
	call	puts
	movl	-20(%rbp), %eax
	leal	1(%rax), %edi
	leaq	-352(%rbp), %rax
	movl	$0, %r8d
	movl	$0, %ecx
	movl	$0, %edx
	movq	%rax, %rsi
	call	select
	movl	%eax, -24(%rbp)
	cmpl	$-1, -24(%rbp)
	jne	.L6
	movl	$.LC52, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L34
.L6:
	movl	$0, -28(%rbp)
	jmp	.L7
.L32:
	movl	-28(%rbp), %eax
	leal	63(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$6, %eax
	cltq
	movq	-352(%rbp,%rax,8), %rsi
	movl	-28(%rbp), %eax
	cltd
	shrl	$26, %edx
	addl	%edx, %eax
	andl	$63, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	salq	%cl, %rdx
	movq	%rdx, %rax
	andq	%rsi, %rax
	testq	%rax, %rax
	je	.L8
	subl	$1, -24(%rbp)
	movl	-28(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jne	.L9
	movl	$.LC53, %edi
	call	puts
	movl	$16, -356(%rbp)
	leaq	-356(%rbp), %rdx
	leaq	-400(%rbp), %rcx
	movl	-48(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	accept
	movl	%eax, -32(%rbp)
	cmpl	$0, -32(%rbp)
	jns	.L10
	movl	$.LC54, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L34
.L10:
	movl	-32(%rbp), %eax
	leal	63(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$6, %eax
	movl	%eax, %esi
	movslq	%esi, %rax
	movq	-224(%rbp,%rax,8), %rdi
	movl	-32(%rbp), %eax
	cltd
	shrl	$26, %edx
	addl	%edx, %eax
	andl	$63, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	salq	%cl, %rdx
	movq	%rdx, %rax
	orq	%rax, %rdi
	movq	%rdi, %rdx
	movslq	%esi, %rax
	movq	%rdx, -224(%rbp,%rax,8)
	movl	$0, -36(%rbp)
	jmp	.L11
.L14:
	movq	clients(%rip), %rax
	movl	-36(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L12
	jmp	.L13
.L12:
	addl	$1, -36(%rbp)
.L11:
	movl	nclients(%rip), %eax
	cmpl	%eax, -36(%rbp)
	jl	.L14
.L13:
	movl	nclients(%rip), %eax
	cmpl	%eax, -36(%rbp)
	jne	.L15
	movl	nclients(%rip), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	clients(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	%rax, clients(%rip)
	movl	nclients(%rip), %eax
	cltq
	movq	clients(%rip), %rdx
	movl	nclients(%rip), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$0, %esi
	movq	%rcx, %rdi
	call	memset
	movl	nclients(%rip), %eax
	addl	%eax, %eax
	movl	%eax, nclients(%rip)
.L15:
	movl	$24, %esi
	movl	$1, %edi
	call	calloc
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movl	-32(%rbp), %edx
	movl	%edx, (%rax)
	movq	-72(%rbp), %rax
	movl	$0, 16(%rax)
	movq	clients(%rip), %rax
	movl	-36(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	movq	-72(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jle	.L16
	movl	-32(%rbp), %eax
	movl	%eax, -20(%rbp)
	jmp	.L8
.L16:
	jmp	.L8
.L9:
	movl	$0, -40(%rbp)
	jmp	.L17
.L20:
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L18
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	cmpl	-28(%rbp), %eax
	jne	.L18
	jmp	.L19
.L18:
	addl	$1, -40(%rbp)
.L17:
	movl	nclients(%rip), %eax
	cmpl	%eax, -40(%rbp)
	jl	.L20
.L19:
	movl	nclients(%rip), %eax
	cmpl	%eax, -40(%rbp)
	jne	.L21
	movl	$.LC55, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L34
.L21:
	leaq	-1424(%rbp), %rcx
	movl	-28(%rbp), %eax
	movl	$1024, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -76(%rbp)
	cmpl	$0, -76(%rbp)
	jg	.L22
	movl	$.LC56, %edi
	call	puts
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-28(%rbp), %eax
	leal	63(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$6, %eax
	movl	%eax, %esi
	movslq	%esi, %rax
	movq	-224(%rbp,%rax,8), %rdi
	movl	-28(%rbp), %eax
	cltd
	shrl	$26, %edx
	addl	%edx, %eax
	andl	$63, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	salq	%cl, %rdx
	movq	%rdx, %rax
	notq	%rax
	andq	%rax, %rdi
	movq	%rdi, %rdx
	movslq	%esi, %rax
	movq	%rdx, -224(%rbp,%rax,8)
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free_client
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	$0, (%rax)
	jmp	.L8
.L22:
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rbx
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	16(%rax), %edx
	movl	-76(%rbp), %eax
	addl	%edx, %eax
	addl	$3, %eax
	movslq	%eax, %rdx
	movq	clients(%rip), %rax
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc
	movq	%rax, 8(%rbx)
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	clients(%rip), %rax
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	8(%rax), %rcx
	movq	clients(%rip), %rax
	movl	-40(%rbp), %esi
	movslq	%esi, %rsi
	salq	$3, %rsi
	addq	%rsi, %rax
	movq	(%rax), %rax
	movl	16(%rax), %eax
	cltq
	addq	%rax, %rcx
	leaq	-1424(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	clients(%rip), %rdx
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rdx
	movq	(%rdx), %rdx
	movl	16(%rdx), %ecx
	movl	-76(%rbp), %edx
	addl	%ecx, %edx
	movl	%edx, 16(%rax)
	leaq	-2416(%rbp), %rdx
	movl	$0, %eax
	movl	$118, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	16(%rax), %ecx
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	leaq	-2416(%rbp), %rdx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	parse_request
	movl	%eax, -80(%rbp)
	cmpl	$0, -80(%rbp)
	jns	.L24
	movl	$.LC57, %edi
	call	puts
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-28(%rbp), %eax
	leal	63(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$6, %eax
	movl	%eax, %esi
	movslq	%esi, %rax
	movq	-224(%rbp,%rax,8), %rdi
	movl	-28(%rbp), %eax
	cltd
	shrl	$26, %edx
	addl	%edx, %eax
	andl	$63, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	salq	%cl, %rdx
	movq	%rdx, %rax
	notq	%rax
	andq	%rax, %rdi
	movq	%rdi, %rdx
	movslq	%esi, %rax
	movq	%rdx, -224(%rbp,%rax,8)
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free_client
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	$0, (%rax)
	jmp	.L8
.L24:
	cmpl	$0, -80(%rbp)
	jne	.L25
	jmp	.L8
.L25:
	movl	-2412(%rbp), %ecx
	movl	-2416(%rbp), %eax
	leaq	-2416(%rbp), %rdx
	addq	$8, %rdx
	leaq	-2416(%rbp), %rsi
	addq	$520, %rsi
	movl	%ecx, %r8d
	movl	%eax, %ecx
	movl	$.LC58, %edi
	movl	$0, %eax
	call	printf
	leaq	-2848(%rbp), %rdx
	movl	$0, %eax
	movl	$54, %ecx
	movq	%rdx, %rdi
	rep stosq
	movl	$1, -2848(%rbp)
	movl	$1, -2844(%rbp)
	movl	$200, -2840(%rbp)
	movq	$.LC59, -2832(%rbp)
	leaq	-2848(%rbp), %rax
	addq	$408, %rax
	movl	$512, %esi
	movq	%rax, %rdi
	call	init_buffer
	movl	$.LC60, %edi
	call	strdup
	movq	%rax, %rdx
	leaq	-2848(%rbp), %rax
	addq	$24, %rax
	movl	$.LC35, %esi
	movq	%rax, %rdi
	call	set_header
	leaq	-2416(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-2856(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	get_route
	movq	%rax, -88(%rbp)
	cmpq	$0, -88(%rbp)
	je	.L26
	leaq	-2848(%rbp), %rcx
	leaq	-2416(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	jmp	.L27
.L26:
	movl	$.LC61, %edi
	call	puts
	movl	$404, -2840(%rbp)
	movq	$.LC62, -2832(%rbp)
	movabsq	$2338616625289506868, %rax
	movq	%rax, -1456(%rbp)
	movl	$1853189990, -1448(%rbp)
	movw	$100, -1444(%rbp)
	leaq	-1456(%rbp), %rax
	leaq	-2848(%rbp), %rdx
	addq	$408, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	append_bufferStr
.L27:
	movq	-2424(%rbp), %rax
	testq	%rax, %rax
	je	.L28
	movl	-2436(%rbp), %edx
	leaq	-1472(%rbp), %rax
	movl	$.LC63, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf
	leaq	-1472(%rbp), %rax
	movq	%rax, %rdi
	call	strdup
	movq	%rax, %rdx
	leaq	-2848(%rbp), %rax
	addq	$24, %rax
	movl	$.LC31, %esi
	movq	%rax, %rdi
	call	set_header
.L28:
	leaq	-1432(%rbp), %rdx
	leaq	-2848(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	gen_response
	movq	%rax, -96(%rbp)
	movl	-1432(%rbp), %eax
	movslq	%eax, %rdx
	movq	-96(%rbp), %rcx
	movl	-32(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write
	testq	%rax, %rax
	jns	.L29
	movl	$.LC64, %edi
	call	puts
.L29:
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	free
	leaq	-2848(%rbp), %rax
	addq	$24, %rax
	movq	%rax, %rdi
	call	free_header
	leaq	-2848(%rbp), %rax
	addq	$408, %rax
	movq	%rax, %rdi
	call	free_buffer
	leaq	-2416(%rbp), %rax
	addq	$536, %rax
	movq	%rax, %rdi
	call	free_header
	leaq	-2416(%rbp), %rax
	addq	$920, %rax
	movq	%rax, %rdi
	call	free_buffer
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L30
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	free
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	$0, 8(%rax)
.L30:
	movq	clients(%rip), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	$0, 16(%rax)
.L8:
	addl	$1, -28(%rbp)
.L7:
	movl	-28(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jg	.L31
	cmpl	$0, -24(%rbp)
	jg	.L32
.L31:
	jmp	.L33
.L34:
	addq	$2856, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	CWF_start, .-CWF_start
	.ident	"GCC: (GNU) 4.9.2 20141224 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
