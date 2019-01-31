#include "pch.h"
#include "HistoryWindow.h"
#include "FiltersWidget.h"
#include "HistoryWidget.h"
#include "MainWindow.h"

HistoryWindow::HistoryWindow(QVector<Data>* history, MainWindow* mainWindow)
		: QMainWindow(mainWindow)
		, m_history(history)
		, m_filtersWidget(new FiltersWidget(this))
		, m_historyArea(new QScrollArea(this)) {

	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle("History");

	QMenuBar* const menuBar = new QMenuBar(this);
	setMenuBar(menuBar);
	QAction* const saveHistoryAction = new QAction("Save History", menuBar);
	menuBar->addAction(saveHistoryAction);
	connect(saveHistoryAction, &QAction::triggered, this, &HistoryWindow::onSaveHistoryActionTriggered);

	QVBoxLayout* const histLout = new QVBoxLayout;
	histLout->setAlignment(Qt::AlignTop);
	for (const Data& data : *m_history) {
		HistoryWidget* const w = new HistoryWidget(data, this);
		m_widgets.append(w);
		histLout->addWidget(w);
	}

	QWidget* const w = new QWidget(m_historyArea);
	w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
	w->setLayout(histLout);
	m_historyArea->setWidget(w);
	m_historyArea->setWidgetResizable(true);

	QVBoxLayout* lout = new QVBoxLayout;
	lout->setAlignment(Qt::AlignTop);
	lout->addWidget(m_filtersWidget);
	lout->addWidget(m_historyArea);

	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(lout);
	setCentralWidget(centralWidget);

	connect(mainWindow, &MainWindow::historyDataAppended, this, &HistoryWindow::onHistoryDataAppend);
	connect(m_filtersWidget, &FiltersWidget::filterChanged, this, &HistoryWindow::onFiltersUpdated);
}

void HistoryWindow::onHistoryDataAppend(const Data& data) {
	QVBoxLayout* const lout = (QVBoxLayout*) m_historyArea->widget()->layout();
	HistoryWidget* const w = new HistoryWidget(data, this);
	const bool visible = isPassed(data, m_filtersWidget->currentFilterOptions());
	w->setVisible(visible);
	m_widgets.append(w);
	lout->addWidget(w);
}

void HistoryWindow::onFiltersUpdated(FilterOptionFlags filterOptions) {
	for (int i = 0, n = m_widgets.size(); i < n; ++i) {
		m_widgets[i]->setVisible(
			isPassed((*m_history)[i], filterOptions)
		);
	}
}

void HistoryWindow::onSaveHistoryActionTriggered() {
	QStringList filters = {
		"TXT (*.txt)",
		"JSON (*.json)"
	};

	QString filter;
	QString file = QFileDialog::getSaveFileName(this, "Save History", "history.txt", filters.join(";;"), &filter);
	QByteArray data;
	switch (filters.indexOf(filter)) {
		case 0:
			data = historyToText();
			break;
		case 1:
			data = historyToJson();
			break;
		default:
			QMessageBox::critical(this, "Error", "History wasn't saved");
			break;
	}

	saveDataToFile(file, data);
}

bool HistoryWindow::isPassed(const Data& data, FilterOptionFlags filterOptions) {
	if (filterOptions == FilterOption::None) {
		return true;
	}
	const bool dataIsOk = data.isGoodData();
	const double diff = data.b() - data.a();
	if ((filterOptions & FilterOption::Ok) && !dataIsOk) {
		return false;
	}
	if ((filterOptions & FilterOption::NotOk) && dataIsOk) {
		return false;
	}
	if ((filterOptions & FilterOption::ABLesser2) && !(data.a() < 2 && data.b() < 2)) {
		return false;
	}
	if ((filterOptions & FilterOption::ABGreater2) && !(data.a() > 2 && data.b() > 2)) {
		return false;
	}
	if ((filterOptions & FilterOption::DiffFrom06To1) && !(0.6 <= diff && diff < 1.0)) {
		return false;
	}
	if ((filterOptions & FilterOption::DiffFrom1To2) && !(1.0 <= diff && diff < 2.0)) {
		return false;
	}
	if ((filterOptions & FilterOption::DiffFrom2To3) && !(2.0 <= diff && diff < 3.0)) {
		return false;
	}
	if ((filterOptions & FilterOption::DiffFrom3To4) && !(3.0 <= diff && diff < 4.0)) {
		return false;
	}
	return true;
}

QByteArray HistoryWindow::historyToText() const {
	QString sb;
	QTextStream ss(&sb);
	ss.setFieldAlignment(QTextStream::AlignLeft);
	ss.setRealNumberNotation(QTextStream::FixedNotation);
	for (int i = 0; i < m_widgets.size(); ++i) {
		if (m_widgets[i]->isVisible()) {
			const Data& data = (*m_history)[i];
			const QDateTime dt = QDateTime::fromMSecsSinceEpoch(data.timestamp());
			ss
				<< "\n+----------+----------------+------------------+------------------+\n|          | A = "

				<< qSetRealNumberPrecision(3)
				<< qSetFieldWidth(10) << data.a() << qSetFieldWidth(0)

				<< qSetRealNumberPrecision(1)
				<< " | V11 = "
				<< qSetFieldWidth(10) << data.v11() << qSetFieldWidth(0)
				<< " | V12 = "
				<< qSetFieldWidth(10) << data.v12() << qSetFieldWidth(0)

				<< " |\n| "
				<< dt.toString("dd.MM.yy")
				<< " +----------------+------------------+------------------+\n| "
				<< dt.toString("HH:mm:ss")
				<< " | B = "

				<< qSetRealNumberPrecision(3)
				<< qSetFieldWidth(10) << data.b() << qSetFieldWidth(0)

				<< qSetRealNumberPrecision(1)
				<< " | V21 = "
				<< qSetFieldWidth(10) << data.v21() << qSetFieldWidth(0)
				<< " | V22 = "
				<< qSetFieldWidth(10) << data.v22() << qSetFieldWidth(0)

				<< " |\n|          +----------------+------------------+------------------+\n|          | Result: "

				<< qSetFieldWidth(44) << data.resultText() << qSetFieldWidth(0)

				<< " |\n+----------+------------------------------------------------------+\n";
		}
	}
	return sb.toUtf8();
}

QByteArray HistoryWindow::historyToJson() const {
	QJsonArray arr;
	for (int i = 0; i < m_widgets.size(); ++i) {
		if (m_widgets[i]->isVisible()) {
			const Data& data = (*m_history)[i];

			QJsonObject dataValsObj;
			dataValsObj.insert("A", data.a());
			dataValsObj.insert("B", data.b());

			QJsonObject valsObj;
			valsObj.insert("V11", data.v11().value());
			valsObj.insert("V12", data.v12().value());
			valsObj.insert("V21", data.v21().value());
			valsObj.insert("V22", data.v22().value());

			QJsonObject dataObj;
			dataObj.insert("Data", dataValsObj);
			dataObj.insert("Values", valsObj);
			dataObj.insert("Result", data.resultText());

			arr.append(dataObj);
		}
	}

	QJsonDocument doc(arr);
	return doc.toJson(QJsonDocument::Indented);
}

void HistoryWindow::saveDataToFile(const QString& filePath, const QByteArray& data) {
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly) || file.write(data) == -1) {
		QMessageBox::critical(Q_NULLPTR, "Error", "Failed to write file: " + filePath);
	}
}
