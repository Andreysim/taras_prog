#pragma once

#include "EvalValue.h"

class ValueDisplayWidget;

class ResultWidget : public QWidget {
	public:
		enum TargetValue { V11, V12, V21, V22 };

	public:
		ResultWidget(QWidget* parent);
		void setValue(TargetValue targetValue, EvalValue value);
		void setResult(const QString& result);
		void clear();

	protected:
		void paintEvent(QPaintEvent* event) override;

	protected:
		ValueDisplayWidget* m_valsWidgets[4];
		QLabel* m_result;
};
