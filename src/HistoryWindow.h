#pragma once

#include "Data.h"
#include "FilterOptions.h"

class FiltersWidget;
class HistoryWidget;

class HistoryWindow : public QMainWindow {
	public:
		HistoryWindow(QVector<Data>* history, QWidget* parent = Q_NULLPTR);

	private:
		void onFiltersUpdated(FilterOptionFlags filterOptions);
		void onSaveHistoryActionTriggered();
		bool isPassed(const Data& data, FilterOptionFlags filterOptions);

	private:
		QVector<Data>* const m_history;
		FiltersWidget* m_filtersWidget;
		QList<HistoryWidget*> m_widgets;
};
