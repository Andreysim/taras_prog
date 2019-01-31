#pragma once

class EvalValue {
	public:
		constexpr EvalValue() : m_value(0.0) {}
		constexpr EvalValue(double value) : m_value(value) {}

		constexpr double value() const { return m_value; }
		operator double() const noexcept { return m_value; }

		bool isGood() const noexcept;
		bool isNeutral() const noexcept;
		bool isBad() const noexcept;

	private:
		double m_value;
};
