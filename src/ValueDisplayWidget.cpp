#include "pch.h"
#include "ValueDisplayWidget.h"
#include "Emoticon.h"

ValueDisplayWidget::ValueDisplayWidget(QWidget* parent)
		: QWidget(parent)
		, m_label         (new QLabel(this))
		, m_valueLabel    (new QLabel(this))
		, m_emoticonWidget(new Emoticon(this)) {

	const QFontMetrics fm(font());
	const int w = fm.width("0000000");
	m_valueLabel->setMinimumWidth(w);

	QHBoxLayout* lout = new QHBoxLayout;
	lout->setMargin(5);
	lout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	lout->addWidget(m_label);
	lout->addWidget(m_valueLabel);
	lout->addWidget(m_emoticonWidget);

	setLayout(lout);
}
void ValueDisplayWidget::setLabelText(const QString& text) {
	m_label->setText(text);
}

void ValueDisplayWidget::setValue(EvalValue val) {
	m_valueLabel->setText(QString::number(val, 'f', 1));
	m_emoticonWidget->setIconFromVal(val);
}

void ValueDisplayWidget::clear() {
	m_valueLabel->clear();
	m_emoticonWidget->clear();
}

void ValueDisplayWidget::paintEvent(QPaintEvent * event) {
	//QPainter p(this);
	//p.drawRect(m_label->geometry());
	//p.drawRect(m_valueLabel->geometry());
	//p.drawRect(m_emoticonWidget->geometry());
}
