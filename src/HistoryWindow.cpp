#include "pch.h"
#include "HistoryWindow.h"
#include "FiltersWidget.h"
#include "HistoryWidget.h"

HistoryWindow::HistoryWindow(QVector<Data>* history, QWidget* parent)
		: QMainWindow(parent)
		, m_history(history)
		, m_filtersWidget(new FiltersWidget(this)) {

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

	QScrollArea* const histArea = new QScrollArea(this);
	QWidget* const w = new QWidget(histArea);
	w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
	w->setLayout(histLout);
	histArea->setWidget(w);
	histArea->setWidgetResizable(true);

	QVBoxLayout* lout = new QVBoxLayout;
	lout->setAlignment(Qt::AlignTop);
	lout->addWidget(m_filtersWidget);
	lout->addWidget(histArea);

	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(lout);
	setCentralWidget(centralWidget);

	connect(m_filtersWidget, &FiltersWidget::filterChanged, this, &HistoryWindow::onFiltersUpdated);
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
	const int filterInd = filters.indexOf(filter);
	if (filterInd == -1) {
		QMessageBox::critical(this, "Error", "History wasn't saved");
	} else {

	}
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
