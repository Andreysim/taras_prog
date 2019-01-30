#include "pch.h"
#include "StringUtil.h"

bool StringUtil::strCvt(const QString& str, double* dest) {
	return strCvt(&str, dest);
}

bool StringUtil::strCvt(const QString& str, qint64* dest) {
	return strCvt(&str, dest);
}

bool StringUtil::strCvt(const QStringRef& str, double* dest) {
	bool ok = true;
	*dest = str.toDouble(&ok);
	return ok;
}

bool StringUtil::strCvt(const QStringRef& str, qint64* dest) {
	bool ok = true;
	*dest = str.toLongLong(&ok);
	return ok;
}
