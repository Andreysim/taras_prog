#pragma once

#include "FilterOptions.h"

class FiltersWidget : public QWidget {

	Q_OBJECT

	private:
		enum Button {
			DropFiltersBtn,
			FilterOkBtn,
			FilterNotOkBtn,
			FilterABLesser2Btn,
			FilterABGreater2Btn,
			FilterDiffFrom06To1Btn,
			FilterDiffFrom1To2Btn,
			FilterDiffFrom2To3Btn,
			FilterDiffFrom3To4Btn,
			Count
		};

	public:
		FiltersWidget(QWidget* parent = Q_NULLPTR);

	public:
		FilterOptionFlags currentFilterOptions() const {return m_currentFilters;}

	signals:
		void filterChanged(FilterOptionFlags filterOptions);

	private:
		void setFilterOptions(FilterOptionFlags option, bool isSet);
		void onDropFiltersBtnClicked();
		void onFilterOkBtnClicked();
		void onFilterNotOkBtnClicked();
		void onFilterABLesser2BtnClicked();
		void onFilterABGreater2BtnClicked();
		void onFilterDiffFrom06To1BtnClicked();
		void onFilterDiffFrom1To2BtnClicked();
		void onFilterDiffFrom2To3BtnClicked();
		void onFilterDiffFrom3To4BtnClicked();

	private:
		QPushButton* m_filterButtons[Count];
		FilterOptionFlags m_currentFilters;
};
