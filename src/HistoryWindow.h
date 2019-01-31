#pragma once

#include "Data.h"
#include "FilterOptions.h"

class MainWindow;
class FiltersWidget;
class HistoryWidget;

class HistoryWindow : public QMainWindow {
	public:
		HistoryWindow(QVector<Data>* history, MainWindow* mainWindow);

	private:
		void onHistoryDataAppend(const Data& data);
		void onFiltersUpdated(FilterOptionFlags filterOptions);
		void onSaveHistoryActionTriggered();
		bool isPassed(const Data& data, FilterOptionFlags filterOptions);
		QByteArray historyToText() const;
		QByteArray historyToJson() const;
		static void saveDataToFile(const QString& filePath, const QByteArray& data);

	private:
		QVector<Data>* const m_history;
		FiltersWidget* m_filtersWidget;
		QScrollArea* m_historyArea;
		QList<HistoryWidget*> m_widgets;
};
