#include "pch.h"
#include "Data.h"

Data::Data() noexcept : Data(0.0, 0.0, 0) {}

Data::Data(double a, double b) noexcept : Data(a, b, 0) {}

Data::Data(double a, double b, qint64 timestamp) noexcept
		: m_a(a)
		, m_b(b)
		, m_timestamp(timestamp) {}

EvalValue Data::v11() const noexcept {
	return 3 * 20 * m_a;
}

EvalValue Data::v12() const noexcept {
	return 2 * 20 * m_a;
}

EvalValue Data::v21() const noexcept {
	return 1 * 20 * m_b;
}

EvalValue Data::v22() const noexcept {
	return 2 * 20 * m_b;
}

bool Data::isValid() const noexcept {
	return !(m_a < 1.0 || m_b < 1.0);
}

bool Data::isGoodData() const noexcept {
	int goodCount = 0;
	if (v11().isGood()) {
		++goodCount;
	}
	if (v12().isGood()) {
		++goodCount;
	}
	if (v21().isGood()) {
		++goodCount;
	}
	if (v22().isGood()) {
		++goodCount;
	}
	return goodCount >= 3;
}

bool Data::isFirstColumnGood() const noexcept {
	return v11().isGood() && v21().isGood();
}

bool Data::isSecondColumnGood() const noexcept {
	return v12().isGood() && v22().isGood();
}

QString Data::resultText() const {
	QString result;
	if (isGoodData()) {
		result = "GOOD";
		if (isFirstColumnGood()) {
			result += " (first column)";
		} else {
			result += " (second column)";
		}
	} else {
		result = "BAD";
	}
	return result;
}

QString Data::resultHtml() const {
	static const QString pattern = QStringLiteral("<span style=\"color: %1\"><b>%2</b></span>");
	const QString resultText = this->resultText();
	const QString color = (isGoodData() ? QStringLiteral("green") : QStringLiteral("red"));
	return pattern.arg(color, resultText);
}
