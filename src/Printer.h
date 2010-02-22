#ifndef KERNEL_PRINTER_H_INCLUDED
#define KERNEL_PRINTER_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include <sexy/IS_SIGNED.h>
#include <sexy/IS_INTEGER.h>
#include <sexy/IS_STRING.h>
#include <sexy/IS_POINTER.h>
#include <sexy/IS_ENUM.h>

namespace kernel {

/**
 * XXX This class is ugly, find a new model to implement the log system
 * XXX Make all methods thread-safe
 */
class Printer {
	friend Printer& getSingleInstance<Printer>();
	Printer();
	Printer(const Printer&);
	const Printer& operator=(const Printer&);

	template<typename Integer>
	class UnsignedIntegerPrinter {
	public:
		static Printer& print(Integer data, Printer& printer) {
			char tmp[sizeof(Integer) * 2 + 1] = {0};
			for (unsigned i = 0; i < sizeof(Integer) * 2; ++i,
					data >>= 4) {
				char c = data & 0x0f;
				if (c < 10) {
					tmp[sizeof(Integer) * 2 - i - 1] = '0' + c;
				} else {
					tmp[sizeof(Integer) * 2 - i - 1] = 'A' + c - 10;
				}
			}
			return printer << (tmp);
		}
	};

	template<typename Integer>
	class SignedIntegerPrinter {
	public:
		/**
		 * XXX Optimize
		 */
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

	template<typename Integer>
	class EnumPrinter {
	public:
		static Printer& print(Integer data, Printer& printer) {
			return UnsignedIntegerPrinter<U64>::print((U64)data, printer);
		}
	};

	template<typename String>
	class StringPrinter {
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

	template<typename Pointer>
	class PointerPrinter {
	public:
		static Printer& print(Pointer pointer, Printer& printer) {
			return printer << (Address)pointer;
		}
	};

	template<typename T>
	class NullPrinter {
	public:
		static Printer& print(const T&, Printer& printer) {
			return printer;
		}
	};
public:
	template<typename T>
	Printer& operator << (const T& data) {
		typedef typename TYPE_SELECTOR<IS_INTEGER<T>::value,
							typename TYPE_SELECTOR<IS_SIGNED<T>::value,
								SignedIntegerPrinter<T>,
								UnsignedIntegerPrinter<T>
							>::Type,
							typename TYPE_SELECTOR<IS_STRING<T>::value,
								StringPrinter<T>,
								typename TYPE_SELECTOR<IS_POINTER<T>::value,
									PointerPrinter<T>,
									typename TYPE_SELECTOR<IS_ENUM<T>::value,
										EnumPrinter<T>,
										NullPrinter<T>
									>::Type
								>::Type
							>::Type
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

} /* namespace kernel */

#endif /* KERNEL_PRINTER_H_INCLUDED */

