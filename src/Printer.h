#ifndef __WONTON_KERNEL_PRINTER_H_INCLUDED__
#define __WONTON_KERNEL_PRINTER_H_INCLUDED__

#include <base/type.h>
#include <base/getSingleInstance.h>

namespace kernel {

/**
 * XXX This class is ugly, find a new model to implement the log system
 * XXX Make all methods thread-safe
 */
class Printer {
	friend Printer& base::getSingleInstance<Printer>();
private:
	Printer();

public:
	Printer& operator << (char data);
	Printer& operator << (const char* string);

	Printer& operator << (short data) {
		printInteger(data);
		return *this;
	}

	Printer& operator << (bool b) {
		if (b) {
			operator << ("true");
		} else {
			operator << ("false");
		}
		return *this;
	}

	Printer& operator << (int data) {
		printInteger(data);
		return *this;
	}

	Printer& operator << (long data) {
		printInteger(data);
		return *this;
	}

	Printer& operator << (unsigned short data) {
		printUnsigned(data);
		return *this;
	}

	Printer& operator << (unsigned int data) {
		printUnsigned(data);
		return *this;
	}

	Printer& operator << (unsigned long data) {
		printUnsigned(data);
		return *this;
	}

	Printer& operator << (void* pointer) {
		printUnsigned((base::Address)pointer);
		return *this;
	}

	void scroll();

private:
	base::U16* buffer;
	int x;
	int y;

	template<typename Int>
	void printInteger(Int data) {
		if (data < 0) {
			operator << ('-');
			printInteger(-data);
		} else {
			if (data >= 10) {
				printInteger(data / 10);
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
};

}

#endif

