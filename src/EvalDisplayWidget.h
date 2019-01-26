#pragma once

class EvalDisplayWidget : public QWidget {
	public:
		EvalDisplayWidget(QWidget* parent = nullptr);
		void setLabelText(const QString& text);
		void setValue(double val);
		void clear();

	private:
		QLabel* m_label;
		QLabel* m_valueLabel;
		QLabel* m_smileLabel;
};
