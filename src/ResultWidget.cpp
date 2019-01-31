#include "pch.h"
#include "ResultWidget.h"
#include "ValueDisplayWidget.h"

static const QString resultPattern = QStringLiteral("Result: %1");

ResultWidget::ResultWidget(QWidget * parent)
		: QWidget(parent)
		, m_result(new QLabel(this)) {
	m_valsWidgets[0] = new ValueDisplayWidget(this);
	m_valsWidgets[1] = new ValueDisplayWidget(this);
	m_valsWidgets[2] = new ValueDisplayWidget(this);
	m_valsWidgets[3] = new ValueDisplayWidget(this);

	m_valsWidgets[0]->setLabelText("V11 =");
	m_valsWidgets[1]->setLabelText("V12 =");
	m_valsWidgets[2]->setLabelText("V21 =");
	m_valsWidgets[3]->setLabelText("V22 =");

	m_result->setMargin(5);
	m_result->setText(resultPattern.arg(QString()));

	QGridLayout* lout = new QGridLayout;
	lout->setSpacing(0);
	lout->addWidget(m_valsWidgets[0], 0, 0);
	lout->addWidget(m_valsWidgets[1], 0, 1);
	lout->addWidget(m_valsWidgets[2], 1, 0);
	lout->addWidget(m_valsWidgets[3], 1, 1);
	lout->addWidget(m_result, 2, 0, 1, 2);

	setLayout(lout);
}

void ResultWidget::setValue(TargetValue targetValue, EvalValue value) {
	switch (targetValue) {
		case V11:
		case V12:
		case V21:
		case V22:
			m_valsWidgets[targetValue]->setValue(value);
			break;
	}
}

void ResultWidget::setResult(const QString& result) {
	m_result->setText(resultPattern.arg(result));
}

void ResultWidget::clear() {
	m_valsWidgets[0]->clear();
	m_valsWidgets[1]->clear();
	m_valsWidgets[2]->clear();
	m_valsWidgets[3]->clear();
	m_result->setText(resultPattern.arg(QString()));
}

void ResultWidget::paintEvent(QPaintEvent* event) {
	QPainter p(this);

	p.drawRect(m_valsWidgets[0]->geometry());
	p.drawRect(m_valsWidgets[1]->geometry());
	p.drawRect(m_valsWidgets[2]->geometry());
	p.drawRect(m_valsWidgets[3]->geometry());
	p.drawRect(m_result->geometry());

	const int y1 = m_valsWidgets[0]->geometry().y();
	const int y2 = m_valsWidgets[2]->geometry().bottom();

	QHBoxLayout* v1xLayout = (QHBoxLayout*) m_valsWidgets[0]->layout();
	int x =
		m_valsWidgets[0]->geometry().x()
		+ v1xLayout->itemAt(2)->geometry().x()
		- v1xLayout->spacing() / 2;
	p.drawLine(x, y1, x, y2);

	v1xLayout = (QHBoxLayout*) m_valsWidgets[1]->layout();
	x =
		m_valsWidgets[1]->geometry().x()
		+ v1xLayout->itemAt(2)->geometry().x()
		- v1xLayout->spacing() / 2;
	p.drawLine(x, y1, x, y2);
}
