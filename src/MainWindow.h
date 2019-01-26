#pragma once

class DataInputWidget;

class MainWindow : public QMainWindow {
	public:
		MainWindow();

	private:
		void onInputChanged();
		void onShowHistoryBtnClick();
		void onSaveBtnClick();

	private:
		QPushButton* m_showHistoryBtn;
		QPushButton* m_saveBtn;
		QPushButton* m_resetBtn;
		DataInputWidget* m_dataInputWidget;
};
