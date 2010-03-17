.section .init
.global start
start:
	/* XXX Set RSP and other application registers before call main */
	call main
