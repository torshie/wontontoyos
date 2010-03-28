#ifndef PANGU_CREATE_PAGE_MAP_H_INCLUDED
#define PANGU_CREATE_PAGE_MAP_H_INCLUDED

#include "mm/PagePointer.h"

namespace pangu {

kernel::PagePointer<4>* createPageMap();

} // namespace kernel

#endif // PANGU_CREATE_PAGE_MAP_H_INCLUDED
