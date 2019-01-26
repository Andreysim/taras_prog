#include "pch.h"
#include "DataInputWidget.h"
#include "EvalDisplayWidget.h"

DataInputWidget::DataInputWidget(QWidget* parent)
		: QWidget             (parent)
		, m_aLabel            (new QLabel(QStringLiteral("A ="), this))
		, m_bLabel            (new QLabel(QStringLiteral("B ="), this))
		, m_aInput            (new QLineEdit(this))
		, m_bInput            (new QLineEdit(this))
		, m_resultLabel       (new QLabel(QStringLiteral("Result:"), this))
		, m_resultDisplayLabel(new QLabel(this)) {

	m_valsWidgets[0] = new EvalDisplayWidget(this);
	m_valsWidgets[1] = new EvalDisplayWidget(this);
	m_valsWidgets[2] = new EvalDisplayWidget(this);
	m_valsWidgets[3] = new EvalDisplayWidget(this);

	m_valsWidgets[0]->setLabelText("V11 = 3 * A * 20 =");
	m_valsWidgets[1]->setLabelText("V12 = 2 * A * 20 =");
	m_valsWidgets[2]->setLabelText("V21 = 1 * B * 20 =");
	m_valsWidgets[3]->setLabelText("V22 = 2 * B * 20 =");

	QGridLayout* inpLout = new QGridLayout;
	inpLout->addWidget(m_aLabel, 0, 0);
	inpLout->addWidget(m_aInput, 0, 1);
	inpLout->addWidget(m_bLabel, 1, 0);
	inpLout->addWidget(m_bInput, 1, 1);

	QGridLayout* evalLout = new QGridLayout;
	evalLout->addWidget(m_valsWidgets[0], 0, 0);
	evalLout->addWidget(m_valsWidgets[1], 0, 1);
	evalLout->addWidget(m_valsWidgets[2], 1, 0);
	evalLout->addWidget(m_valsWidgets[3], 1, 1);

	QHBoxLayout* resLout = new QHBoxLayout;
	resLout->setAlignment(Qt::AlignVCenter);
	resLout->addWidget(m_resultLabel);
	resLout->addWidget(m_resultDisplayLabel);

	QGridLayout* lout = new QGridLayout;
	lout->addLayout(inpLout, 0, 0);
	lout->addLayout(evalLout, 0, 1);
	lout->addLayout(resLout, 1, 1, Qt::AlignLeft);

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
	m_valsWidgets[0]->clear();
	m_valsWidgets[1]->clear();
	m_valsWidgets[2]->clear();
	m_valsWidgets[3]->clear();
	m_resultDisplayLabel->clear();
}

void DataInputWidget::setVal(int targetVal, double val) {
	m_valsWidgets[targetVal]->setValue(val);
}

void DataInputWidget::setResult(const QString& resultStr) {
	m_resultDisplayLabel->setText(resultStr);
}
