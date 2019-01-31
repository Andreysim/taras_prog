#pragma once

#include "Data.h"

class DataInputWidget;
class HistoryWindow;

class MainWindow : public QMainWindow {

	Q_OBJECT

	public:
		MainWindow();

	signals:
		void historyDataAppended(const Data& data);

	private:
		void loadHistory();
		Data getData() const;
		void updateResultText(const Data& data) const;
		void onInputChanged();
		void onShowHistoryBtnClick();
		void onSaveBtnClick();
		void onResetBtnClick();
		void onHistoryDialogDestroyed(QObject* dialog);

	private:
		QPushButton* m_showHistoryBtn;
		QPushButton* m_saveBtn;
		QPushButton* m_resetBtn;
		QLabel* m_saveStatusLabel;
		DataInputWidget* m_dataInputWidget;
		QVector<Data> m_history;
		QVector<HistoryWindow*> m_historyDialogs;
};
