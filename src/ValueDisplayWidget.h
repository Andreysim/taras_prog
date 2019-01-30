#pragma once

#include "EvalValue.h"

class ValueDisplayWidget : public QWidget {
	public:
		ValueDisplayWidget(QWidget* parent = nullptr);
		void setLabelText(const QString& text);
		void setValue(EvalValue val);
		void clear();

	private:
		QLabel* m_label;
		QLabel* m_valueLabel;
		QLabel* m_smileLabel;
};
