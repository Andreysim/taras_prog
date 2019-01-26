#pragma once

class EvalDisplayWidget;

class DataInputWidget : public QWidget {

	Q_OBJECT

	public:
		DataInputWidget(QWidget* parent = nullptr);

	public:
		QString valueA() const;
		QString valueB() const;
		void reset();
		void clearEvals();
		void setVal(int targetVal, double val);
		void setResult(const QString& resultStr);

	signals:
		void dataInputChanged();

	private:
		QLabel* m_aLabel;
		QLabel* m_bLabel;
		QLineEdit* m_aInput;
		QLineEdit* m_bInput;
		EvalDisplayWidget* m_valsWidgets[4];
		QLabel* m_resultLabel;
		QLabel* m_resultDisplayLabel;

};
