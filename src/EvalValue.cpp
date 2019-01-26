#include "pch.h"
#include "EvalValue.h"

bool EvalValue::isGood() const noexcept {
	return m_value >= 84.0;
}

bool EvalValue::isNeutral() const noexcept {
	return !isBad() && !isGood();
}

bool EvalValue::isBad() const noexcept {
	return m_value <= 76.0;
}
