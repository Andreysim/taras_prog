#pragma once

#include "EvalValue.h"

class Data {
	public:
		Data() noexcept;
		Data(double a, double b) noexcept;
		Data(double a, double b, qint64 timestamp) noexcept;

	public:
		double a() const noexcept { return m_a; }
		double b() const noexcept { return m_a; }
		qint64 timestamp() const noexcept { return m_timestamp; }
		EvalValue v11() const noexcept;
		EvalValue v12() const noexcept;
		EvalValue v21() const noexcept;
		EvalValue v22() const noexcept;
		bool isValid() const noexcept;
		bool isGoodData() const noexcept;
		bool isFirstColumnGood() const noexcept;
		bool isSecondColumnGood() const noexcept;
		QString resultText() const;
		QString resultHtml() const;

	private:
		double m_a;
		double m_b;
		qint64 m_timestamp;
};
