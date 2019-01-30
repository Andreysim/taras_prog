#include "pch.h"
#include "ValueDisplayWidget.h"

ValueDisplayWidget::ValueDisplayWidget(QWidget* parent)
		: QWidget(parent)
		, m_label     (new QLabel(this))
		, m_valueLabel(new QLabel(this))
		, m_smileLabel(new QLabel(this)) {

	const QFontMetrics fm(font());
	const int w = fm.width("0000000");
	m_valueLabel->setMinimumWidth(w);

	QHBoxLayout* lout = new QHBoxLayout;
	lout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	lout->addWidget(m_label);
	lout->addWidget(m_valueLabel);
	lout->addWidget(m_smileLabel);

	setLayout(lout);
}
void ValueDisplayWidget::setLabelText(const QString& text) {
	m_label->setText(text);
}

void ValueDisplayWidget::setValue(EvalValue val) {
	m_valueLabel->setText(QString::number(val, 'f', 1));
}

void ValueDisplayWidget::clear() {
	m_valueLabel->clear();
	m_smileLabel->clear();
}
