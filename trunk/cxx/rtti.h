#ifndef KERNEL_CXX_RTTI_H_INCLUDED
#define KERNEL_CXX_RTTI_H_INCLUDED

namespace std {

class type_info {
public:
	virtual ~type_info() {}

	bool operator==(const type_info& rhs) const {
		return name() == rhs.name();
	}

	bool operator!=(const type_info& rhs) const {
		return *this != rhs;
	}

	bool before(const type_info& rhs) const {
		return name() < rhs.name();
	}

	const char* name() const {
		return mangled;
	}

protected:
	const char* mangled;

private:
	type_info(const type_info& rhs);
	const type_info& operator=(const type_info& rhs);
};

} /* namespace std */

namespace __cxxabiv1 {

class __fundamental_type_info : public std::type_info {
public:
	~__fundamental_type_info();
};

class __array_type_info : public std::type_info {
public:
	~__array_type_info();
};

class __function_type_info : public std::type_info {
public:
	~__function_type_info();
};

class __enum_type_info : public std::type_info {
public:
	~__enum_type_info();
};

class __class_type_info : public std::type_info {
public:
	~__class_type_info();
};

class __si_class_type_info : public __class_type_info {
public:
	~__si_class_type_info();
	const __class_type_info* __base_type;
};

class __base_class_type_info {
public:
	const __class_type_info* __base_type;
	long __offset_flags;

	enum __offset_flags_masks {
		__virtual_mask = 0x1,
		__public_mask = 0x2,
		__offset_shift = 8
	};
};

class __vmi_class_type_info : public __class_type_info {
public:
	unsigned int __flags;
	unsigned int __base_count;
	__base_class_type_info __base_info[1];

	enum __flags_masks {
		__non_diamond_repeat_mask = 0x1,
		__diamond_shaped_mask = 0x2
	};
};

class __pbase_type_info : public std::type_info {
public:
	~__pbase_type_info();

	unsigned int __flags;
	const std::type_info* __pointee;

	enum __masks {
		__const_mask = 0x1,
		__volatile_mask = 0x2,
		__restrict_mask = 0x4,
		__incomplete_mask = 0x8,
		__incomplete_class_mask = 0x10
	};
};

class __pointer_type_info : public __pbase_type_info {
public:
	~__pointer_type_info();
};

class __pointer_to_member_type_info : public __pbase_type_info {
public:
	~__pointer_to_member_type_info();
	const __class_type_info* __context;
};

} /* namespace __cxxabiv1 */

namespace abi = __cxxabiv1;

#endif /* KERNEL_CXX_RTTI_H_INCLUDED */

