#pragma once

#include <QFlags>

enum class FilterOption : unsigned int {
	None          = 0x00,
	Ok            = 0x01,
	NotOk         = 0x02,
	ABLesser2     = 0x04,
	ABGreater2    = 0x08,
	DiffFrom06To1 = 0x10,
	DiffFrom1To2  = 0x20,
	DiffFrom2To3  = 0x40,
	DiffFrom3To4  = 0x80
};

typedef QFlags<FilterOption> FilterOptionFlags;
//Q_DECLARE_FLAGS(FilterOptionFlags, FilterOptions);

Q_DECL_CONSTEXPR inline bool operator == (FilterOptionFlags f1, FilterOptionFlags f2) {
	return (FilterOptionFlags::Int) f1 == (FilterOptionFlags::Int) f2;
}

Q_DECL_CONSTEXPR inline bool operator != (FilterOptionFlags f1, FilterOptionFlags f2) {
	return !(f1 == f2);
}
