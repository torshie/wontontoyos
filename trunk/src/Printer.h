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
private:
	Printer();

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
		if (IS_SIGNED<Integer>::value) {
			printSigned(data);
		} else {
			printUnsigned(data);
		}
		return *this;
	}

	Printer& operator << (const void* pointer) {
		printUnsigned((Address)pointer);
		return *this;
	}

private:
	U16* buffer;
	int x;
	int y;

	template<typename Int>
	void printSigned(Int data) {
		if (data < 0) {
			operator << ('-');
			printSigned(-data);
		} else {
			if (data >= 10) {
				printSigned(data / 10);
				data %= 10;
			}
			operator << ((char)('0' + data));
		}
	}

	template<typename Int>
	void printUnsigned(Int data) {
		char tmp[sizeof(Int) * 2 + 1] = {0};
		for (unsigned i = 0; i < sizeof(Int) * 2; ++i, data >>= 4) {
			char c = data & 0x0f;
			if (c < 10) {
				tmp[sizeof(Int) * 2 - i - 1] = '0' + c;
			} else {
				tmp[sizeof(Int) * 2 - i - 1] = 'A' + c - 10;
			}
		}
		operator << (tmp);
	}

	void scroll();

};

} /* namespace kernel */

#endif /* KERNEL_PRINTER_H_INCLUDED */

