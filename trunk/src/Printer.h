#ifndef KERNEL_PRINTER_H_INCLUDED
#define KERNEL_PRINTER_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include <sexy/IS_SIGNED.h>
#include <sexy/IS_INTEGER.h>
#include <sexy/IS_STRING.h>
#include <sexy/IS_POINTER.h>
#include <sexy/IS_ENUM.h>
#include <sexy/IS_UNSIGNED.h>
#include <sexy/IS_ARRAY_OF.h>
#include <sexy/TYPE_SELECTOR.h>
#include <sexy/NAKED.h>
#include <kernel/abi.h>

namespace kernel {

// XXX Make all methods thread-safe
// XXX Printer cannot print wchar_t
class Printer {
	friend Printer& getSingleInstance<Printer>();
	friend class Message;

#ifndef __X86_32__
	Printer(U16* base = (U16*)(KERNEL_VIRTUAL_BASE + 0xb8000));
#else
public:
	Printer(U16* base = (U16*)(0xb8000));
private:
#endif

	Printer(const Printer&);
	const Printer& operator=(const Printer&);

	template<typename Integer> class UnsignedIntegerPrinter {
	public:
		static Printer& print(Integer data, Printer& printer) {
			enum {
				BUFFER_SIZE = sizeof(Integer) * 2 + 1
			};
			char tmp[BUFFER_SIZE] = {0};
			for (unsigned int i = 0; i < sizeof(Integer) * 2; ++i,
					data >>= 4) {
				char c = data & 0x0f;
				if (c < 10) {
					tmp[sizeof(Integer) * 2 - i - 1] = '0' + c;
				} else {
					tmp[sizeof(Integer) * 2 - i - 1] = 'A' + c - 10;
				}
			}
			for (unsigned int i = 0; i < BUFFER_SIZE; ++i) {
				if (tmp[i] == 0) {
					break;
				}
				if (i % 4 == 0 && i != 0) {
					printer.printChar('-');
				}
				printer.printChar(tmp[i]);
			}
			return printer;
		}
	};

	template<typename Integer> class SignedIntegerPrinter {
	public:
		// XXX Optimize
		static Printer& print(Integer data, Printer& printer) {
			if (data < 0) {
				printer.printChar('-');
				print(-data, printer);
			} else {
				if (data >= 10) {
					print(data / 10, printer);
					data %= 10;
				}
				printer.printChar('0' + data);
			}
			return printer;
		}
	};

	template<typename Integer> class EnumPrinter {
	public:
		static Printer& print(Integer data, Printer& printer) {
			return UnsignedIntegerPrinter<U64>::print((U64)data, printer);
		}
	};

	template<typename String> class StringPrinter {
	public:
		static Printer& print(const String& data, Printer& printer) {
			if (data == 0) {
				return printer;
			}

			for (const char* p = data; *p; ++p) {
				printer.printChar(*p);
			}
			return printer;
		}
	};

	template<typename Char> class CharPrinter {
	public:
		static Printer& print(Char c, Printer& printer) {
			printer.printChar(c);
			return printer;
		}
	};

	template<typename CharArray, unsigned int N = sizeof(CharArray)> class CharArrayPrinter {
	public:
		static Printer& print(const char array[N], Printer& printer) {
			for (unsigned int i = 0; array[i] && i < N; ++i) {
				printer.printChar(array[i]);
			}
			return printer;
		}
	};

	template<typename Pointer> class PointerPrinter {
	public:
		static Printer& print(Pointer pointer, Printer& printer) {
			return printer << (Address)pointer;
		}
	};

	template<typename Boolean> class BooleanPrinter {
	public:
		static Printer& print(Boolean b, Printer& printer) {
			return printer << (b ? "true" : "false");
		}
	};

	template<typename T> class NullPrinter {
	public:
		static Printer& print(const T&, Printer& printer) {
			printer << "(null printer)";
			return printer;
		}
	};

	template<typename T> Printer& operator << (const T& data) {
		typedef typename NAKED<T>::Type Naked;
		typedef typename TYPE_SELECTOR<
			SAME_TYPE<Naked, char>::value, CharPrinter<T>,
			SAME_TYPE<Naked, bool>::value, BooleanPrinter<T>,
			IS_SIGNED<Naked>::value, SignedIntegerPrinter<T>,
			IS_UNSIGNED<Naked>::value, UnsignedIntegerPrinter<T>,
			IS_ARRAY_OF<Naked, char>::value, CharArrayPrinter<T>,
			IS_STRING<Naked>::value, StringPrinter<T>,
			IS_POINTER<Naked>::value, PointerPrinter<T>,
			IS_ENUM<Naked>::value, EnumPrinter<T>,
			true, NullPrinter<T>
		>::Type CompetentPrinter;

		return CompetentPrinter::print(data, *this);
	}

private:
	enum {
		COLOR = 0x0700,
		WIDTH = 80,
		HEIGHT = 25
	};

	U16* buffer;
	int x;
	int y;

	Printer& printChar(char data);
	void scroll();
};

} // namespace kernel

#endif // KERNEL_PRINTER_H_INCLUDED

