.section .text
/* XXX Change to C++ source and check correctness of this function */
.global __cxa_guard_release
__cxa_guard_release:
	movb $1, (%rdi)
	ret
