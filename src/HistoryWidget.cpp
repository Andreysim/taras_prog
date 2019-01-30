#include "pch.h"
#include "HistoryWidget.h"
#include "ValueDisplayWidget.h"
#include "Data.h"

HistoryWidget::HistoryWidget(const Data& data, QWidget* parent)
		: ResultWidget(parent)
		, m_aLabel(new QLabel(this))
		, m_bLabel(new QLabel(this))
		, m_dateLabel(new QLabel(this)) {

	const QFontMetrics fm(font());
	const QMargins m(5, 0, 5, 0);
	const int w = fm.width("M = 000000") + m.left() + m.right();
	m_aLabel->setFixedWidth(w);
	m_bLabel->setFixedWidth(w);
	m_aLabel->setContentsMargins(m);
	m_bLabel->setContentsMargins(m);
	m_dateLabel->setContentsMargins(10, 0, 10, 0);

	delete layout();

	QGridLayout* lout = new QGridLayout;
	lout->setSpacing(0);
	lout->addWidget(m_dateLabel, 0, 0, 2, 1);
	lout->addWidget(m_aLabel, 0, 1);
	lout->addWidget(m_bLabel, 1, 1);
	lout->addWidget(m_valsWidgets[0], 0, 2);
	lout->addWidget(m_valsWidgets[1], 0, 3);
	lout->addWidget(m_valsWidgets[2], 1, 2);
	lout->addWidget(m_valsWidgets[3], 1, 3);
	lout->addWidget(m_result, 2, 2, 1, 2);
	setLayout(lout);

	setDate(data.timestamp());
	setA(data.a());
	setB(data.b());
	setValue(V11, data.v11());
	setValue(V12, data.v12());
	setValue(V21, data.v21());
	setValue(V22, data.v22());
	setResult(data.resultHtml());
}

void HistoryWidget::setA(double val) {
	m_aLabel->setText("A = " + QString::number(val, 'f', 3));
}

void HistoryWidget::setB(double val) {
	m_bLabel->setText("B = " + QString::number(val, 'f', 3));
}

void HistoryWidget::setDate(qint64 timestamp) {
	QDateTime dt = QDateTime::fromMSecsSinceEpoch(timestamp);
	m_dateLabel->setText("Date:\n" + dt.toString("dd.MM.yyyy\nHH:mm:ss"));
}

void HistoryWidget::paintEvent(QPaintEvent* event) {
	ResultWidget::paintEvent(event);

	QPainter p(this);
	p.drawRect(rect().adjusted(0, 0, -1, -1));
	p.drawRect(m_aLabel->geometry());
	p.drawRect(m_bLabel->geometry());
}
