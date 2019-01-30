#pragma once

class ResultWidget;

class DataInputWidget : public QWidget {

	Q_OBJECT

	public:
		DataInputWidget(QWidget* parent = nullptr);

	public:
		ResultWidget* resultWidget() const {return m_resultWidget;}
		QString valueA() const;
		QString valueB() const;
		void reset();
		void clearEvals();

	signals:
		void dataInputChanged();

	protected:
		void paintEvent(QPaintEvent* event) override;

	private:
		QLabel* m_aLabel;
		QLabel* m_bLabel;
		QLineEdit* m_aInput;
		QLineEdit* m_bInput;
		ResultWidget* m_resultWidget;

};
