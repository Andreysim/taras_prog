#pragma once

#include "ResultWidget.h"

class Data;

class HistoryWidget : public ResultWidget {
	public:
		HistoryWidget(const Data& data, QWidget* parent);
		void setA(double val);
		void setB(double val);
		void setDate(qint64 timestamp);

	protected:
		void paintEvent(QPaintEvent* event) override;

	private:
		QLabel* m_aLabel;
		QLabel* m_bLabel;
		QLabel* m_dateLabel;
};
