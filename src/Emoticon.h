#pragma once

#include "EvalValue.h"

class Emoticon : public QWidget {
	public:
		Emoticon(QWidget* parent);
		void setIconFromVal(EvalValue val);
		void clear();

	protected:
		void paintEvent(QPaintEvent* event) override;

	private:
		QIcon m_icon;
};
