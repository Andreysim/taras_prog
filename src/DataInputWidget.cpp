#include "pch.h"
#include "DataInputWidget.h"
#include "ResultWidget.h"

DataInputWidget::DataInputWidget(QWidget* parent)
		: QWidget       (parent)
		, m_aLabel      (new QLabel(QStringLiteral("A ="), this))
		, m_bLabel      (new QLabel(QStringLiteral("B ="), this))
		, m_aInput      (new QLineEdit(this))
		, m_bInput      (new QLineEdit(this))
		, m_resultWidget(new ResultWidget(this)) {

	const QFontMetrics fm(font());
	const int inpWidth = fm.width("00000000");
	m_aInput->setFixedWidth(inpWidth);
	m_bInput->setFixedWidth(inpWidth);

	QGridLayout* inpLout = new QGridLayout;
	inpLout->setAlignment(Qt::AlignTop);
	inpLout->addWidget(m_aLabel, 0, 0);
	inpLout->addWidget(m_aInput, 0, 1);
	inpLout->addWidget(m_bLabel, 1, 0);
	inpLout->addWidget(m_bInput, 1, 1);

	QWidget* w = new QWidget(this);
	w->setLayout(inpLout);

	QHBoxLayout* lout = new QHBoxLayout;
	lout->setSpacing(20);
	lout->addWidget(w);
	lout->addWidget(m_resultWidget);

	setLayout(lout);

	connect(m_aInput, &QLineEdit::textEdited, this, &DataInputWidget::dataInputChanged);
	connect(m_bInput, &QLineEdit::textEdited, this, &DataInputWidget::dataInputChanged);
}

QString DataInputWidget::valueA() const {
	return m_aInput->text();
}

QString DataInputWidget::valueB() const {
	return m_bInput->text();
}

void DataInputWidget::reset() {
	m_aInput->clear();
	m_bInput->clear();
	clearEvals();
}

void DataInputWidget::clearEvals() {
	m_resultWidget->clear();
}
