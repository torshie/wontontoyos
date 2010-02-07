#ifndef KERNEL_PRINTER_H_INCLUDED
#define KERNEL_PRINTER_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include <sexy/IS_SIGNED.h>

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
				printer << ('-');
				print(-data, printer);
			} else {
				if (data >= 10) {
					print(data / 10, printer);
					data %= 10;
				}
				printer << ((char)('0' + data));
			}
			return printer;
		}
	};
public:
	Printer& operator << (char data);

	Printer& operator << (char* string) {
		operator << ((const char*)(string));
		return *this;
	}

	Printer& operator << (const char* string);

	Printer& operator << (bool b) {
		if (b) {
			operator << ("true");
		} else {
			operator << ("false");
		}
		return *this;
	}

	template<typename Integer>
	Printer& operator << (Integer data) {
		typedef typename TYPE_SELECTOR<IS_SIGNED<Integer>::value,
							SignedIntegerPrinter<Integer>,
							UnsignedIntegerPrinter<Integer>
						>::Type IntegerPrinter;
		return IntegerPrinter::print(data, *this);
	}

	template<typename T>
	Printer& operator << (T* pointer) {
		return *this << (Address)pointer;
	}

	template<typename T>
	Printer& operator << (const T* pointer) {
		return *this << (Address)pointer;
	}

private:
	U16* buffer;
	int x;
	int y;

	void scroll();
};

} /* namespace kernel */

#endif /* KERNEL_PRINTER_H_INCLUDED */

