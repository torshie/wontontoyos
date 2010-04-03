#ifndef KERNEL_DEFINE_H_INCLUDED
#define KERNEL_DEFINE_H_INCLUDED

#if defined(__X86_32__)
#	define DEFINE_LONG_LONG(a, b) DEFINE(a, b##ull)
#else
#	define DEFINE_LONG_LONG(a, b) DEFINE(a, b)
#endif

#if defined(__ASM__)
#	define DEFINE(a, b) .set a, b
#	define BEGIN_DEFINE(space)
#	define END_DEFINE()
#else
#	define DEFINE(a, b) a = b,
#	define BEGIN_DEFINE(space) namespace kernel { enum space {
#	define END_DEFINE() }; }
#endif

#endif /* KERNEL_DEFINE_H_INCLUDED */
