#include "pch.h"
#include "EvalDisplayWidget.h"

EvalDisplayWidget::EvalDisplayWidget(QWidget* parent)
		: QWidget(parent)
		, m_label     (new QLabel(this))
		, m_valueLabel(new QLabel(this))
		, m_smileLabel(new QLabel(this)) {

	QHBoxLayout* lout = new QHBoxLayout;
	lout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	lout->addWidget(m_label);
	lout->addWidget(m_valueLabel);
	lout->addWidget(m_smileLabel);

	setLayout(lout);
}
void EvalDisplayWidget::setLabelText(const QString& text) {
	m_label->setText(text);
}

void EvalDisplayWidget::setValue(double val) {
	m_valueLabel->setText(QString::number(val, 'f', 1));
}

void EvalDisplayWidget::clear() {
	m_valueLabel->clear();
	m_smileLabel->clear();
}
