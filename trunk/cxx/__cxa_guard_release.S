.section .text
.global __cxa_guard_release
__cxa_guard_release:
	movb $1, (%rdi)
	ret
