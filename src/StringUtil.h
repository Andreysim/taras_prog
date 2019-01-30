#pragma once

class StringUtil {
		StringUtil() = delete;
	public:
		static bool strCvt(const QString& str, double* dest);
		static bool strCvt(const QString& str, qint64* dest);
		static bool strCvt(const QStringRef& str, double* dest);
		static bool strCvt(const QStringRef& str, qint64* dest);
};
