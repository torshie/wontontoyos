#ifndef KERNEL_DEFINE_H_INCLUDED
#define KERNEL_DEFINE_H_INCLUDED

#ifdef __ASM__
#define DEFINE(a, b) .set a, b
#define BEGIN_DEFINE(space)
#define END_DEFINE()
#else
#define DEFINE(a, b) a = b,
#define BEGIN_DEFINE(space) namespace space { enum {
#define END_DEFINE() }; }
#endif

#endif /* KERNEL_DEFINE_H_INCLUDED */
