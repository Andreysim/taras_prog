#include "pch.h"
#include "MainWindow.h"
#include "DataInputWidget.h"
#include "ResultWidget.h"
#include "StringUtil.h"
#include "HistoryWindow.h"

MainWindow::MainWindow()
		: m_showHistoryBtn (new QPushButton(QStringLiteral("HISTORY"), this))
		, m_saveBtn        (new QPushButton(QStringLiteral("SAVE"), this))
		, m_resetBtn       (new QPushButton(QStringLiteral("RESET"), this))
		, m_saveStatusLabel(new QLabel(this))
		, m_dataInputWidget(new DataInputWidget(this)) {

	loadHistory();

	m_saveBtn->setEnabled(false);

	QGridLayout* btnsLout = new QGridLayout;
	btnsLout->setAlignment(Qt::AlignRight);
	btnsLout->addWidget(m_showHistoryBtn, 0, 0);
	btnsLout->addWidget(m_saveBtn, 0, 1);
	btnsLout->addWidget(m_resetBtn, 0, 2);
	btnsLout->addWidget(m_saveStatusLabel, 1, 1, Qt::AlignHCenter);

	QVBoxLayout* lout = new QVBoxLayout;
	lout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
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
		m_showHistoryBtn, &QPushButton::clicked,
		this, &MainWindow::onShowHistoryBtnClick
	);
	connect(
		m_resetBtn, &QPushButton::clicked,
		this, &MainWindow::onResetBtnClick
	);
	connect(
		m_saveBtn, &QPushButton::clicked,
		this, &MainWindow::onSaveBtnClick
	);
}

void MainWindow::loadHistory() {
	QFile file("history.data");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, "Error", "Failed to open history file for read");
		return;
	}
	bool isFileCorrupted = false;
	const QString content = file.readAll();
	for (const QStringRef& line : content.splitRef('\n', QString::SkipEmptyParts)) {
		const QVector<QStringRef> vals = line.split(' ', QString::SkipEmptyParts);
		if (vals.size() == 3) {
			bool ok = true;
			double a;
			double b;
			qint64 timestamp;
			if (StringUtil::strCvt(vals[0], &a)
				&& StringUtil::strCvt(vals[1], &b)
				&& StringUtil::strCvt(vals[2], &timestamp)) {
				m_history.append({a, b, timestamp});
			} else {
				isFileCorrupted = true;
			}
		} else {
			isFileCorrupted = true;
		}
	}
	if (isFileCorrupted) {
		QMessageBox::warning(this, "Warning", "History file was corrupted.");
	}
}

Data MainWindow::getData() const {
	double a;
	double b;
	if (StringUtil::strCvt(m_dataInputWidget->valueA(), &a)
		&& StringUtil::strCvt(m_dataInputWidget->valueB(), &b)) {
		return Data(a, b);
	}
	return Data();
}

void MainWindow::updateResultText(const Data& data) const {
	const QString pattern = QStringLiteral("<span style=\"color: %1\"><b>%2</b></span>");
	const QString resultText = data.resultText();
	const QString color = (data.isGoodData() ? "green" : "red");
	m_dataInputWidget->resultWidget()->setResult(pattern.arg(color, resultText));
}

void MainWindow::onInputChanged() {
	const Data data = getData();
	if (data.isValid()) {
		ResultWidget* const resultWidget = m_dataInputWidget->resultWidget();
		resultWidget->setValue(ResultWidget::V11, data.v11());
		resultWidget->setValue(ResultWidget::V12, data.v12());
		resultWidget->setValue(ResultWidget::V21, data.v21());
		resultWidget->setValue(ResultWidget::V22, data.v22());
		updateResultText(data);
		m_saveBtn->setEnabled(true);
	} else {
		m_dataInputWidget->clearEvals();
		m_saveBtn->setEnabled(false);
	}
	m_saveStatusLabel->clear();
}

void MainWindow::onShowHistoryBtnClick() {
	HistoryWindow* const histWnd = new HistoryWindow(&m_history, this);
	connect(histWnd, &QObject::destroyed, this, &MainWindow::onHistoryDialogDestroyed);
	histWnd->show();
	m_historyDialogs.append(histWnd);
}

void MainWindow::onSaveBtnClick() {
	const Data data = getData();
	if (data.isValid()) {
		QFile file("history.data");
		if (!file.open(QIODevice::Append)) {
			QMessageBox::critical(this, "Error", "Failed to open history file for write");
			return;
		}
		const qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
		QTextStream ss(&file);
		ss.setRealNumberPrecision(3);
		ss.setRealNumberNotation(QTextStream::FixedNotation);
		ss << data.a() << ' ' << data.b() << ' ' << timestamp << '\n';
		file.close();

		if (ss.status() == QTextStream::Status::Ok) {
			m_history.append({data.a(), data.b(), timestamp});
			m_saveStatusLabel->setText("<span style=\"color: green\">Saved</span>");
		} else {
			m_saveStatusLabel->setText("<span style=\"color: red\">Faild</span>");
		}
	}
}

void MainWindow::onResetBtnClick() {
	m_dataInputWidget->reset();
	m_saveBtn->setEnabled(false);
	m_saveStatusLabel->clear();
}

void MainWindow::onHistoryDialogDestroyed(QObject * dialog) {
	for (int i = 0; i < m_historyDialogs.size(); ++i) {
		if (m_historyDialogs[i] == dialog) {
			m_historyDialogs.remove(i);
			return;
		}
	}
}
