#include "pch.h"
#include "MainWindow.h"
#include "DataInputWidget.h"
#include "Data.h"
MainWindow::MainWindow()
		: m_showHistoryBtn (new QPushButton(QStringLiteral("HISTORY"), this))
		, m_saveBtn        (new QPushButton(QStringLiteral("SAVE"), this))
		, m_resetBtn       (new QPushButton(QStringLiteral("RESET"), this))
		, m_dataInputWidget(new DataInputWidget(this)) {

	QHBoxLayout* btnsLout = new QHBoxLayout;
	btnsLout->setAlignment(Qt::AlignRight);
	btnsLout->addWidget(m_showHistoryBtn);
	btnsLout->addWidget(m_saveBtn);
	btnsLout->addWidget(m_resetBtn);

	QVBoxLayout* lout = new QVBoxLayout;
	lout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	lout->setSpacing(20);
	lout->addLayout(btnsLout);
	lout->addWidget(m_dataInputWidget, 0, Qt::AlignLeft);

	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(lout);

	setCentralWidget(centralWidget);

	connect(
		m_dataInputWidget, &DataInputWidget::dataInputChanged,
		this, &MainWindow::onInputChanged
	);
	connect(
		m_resetBtn, &QPushButton::clicked,
		m_dataInputWidget, &DataInputWidget::reset
	);
}

void MainWindow::onInputChanged() {
	Data data(
		m_dataInputWidget->valueA().toDouble(),
		m_dataInputWidget->valueB().toDouble()
	);
	if (data.isValid()) {
		m_dataInputWidget->setVal(0, data.v11());
		m_dataInputWidget->setVal(1, data.v12());
		m_dataInputWidget->setVal(2, data.v21());
		m_dataInputWidget->setVal(3, data.v22());

		QString result;
		if (data.isGoodData()) {
			result = "GOOD";
			if (data.isFirstColumnGood()) {
				result += " (first column)";
			} else {
				result += " (second column)";
			}
		} else {
			result = "BAD";
		}
		m_dataInputWidget->setResult(result);
	} else {
		m_dataInputWidget->clearEvals();
	}
}

void MainWindow::onShowHistoryBtnClick() {

}

void MainWindow::onSaveBtnClick() {

}
