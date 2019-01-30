#include "pch.h"
#include "FiltersWidget.h"

FiltersWidget::FiltersWidget(QWidget* parent)
		: QWidget(parent)
		, m_currentFilters(FilterOption::None) {

	m_filterButtons[DropFiltersBtn]         = new QPushButton("X", this);
	m_filterButtons[FilterOkBtn]            = new QPushButton("GOOD", this);
	m_filterButtons[FilterNotOkBtn]         = new QPushButton("BAD", this);
	m_filterButtons[FilterABLesser2Btn]     = new QPushButton("A < 2\nB < 2", this);
	m_filterButtons[FilterABGreater2Btn]    = new QPushButton("A > 2\nB > 2", this);
	m_filterButtons[FilterDiffFrom06To1Btn] = new QPushButton("[0.6, 1)", this);
	m_filterButtons[FilterDiffFrom1To2Btn]  = new QPushButton("[1, 2)", this);
	m_filterButtons[FilterDiffFrom2To3Btn]  = new QPushButton("[2, 3)", this);
	m_filterButtons[FilterDiffFrom3To4Btn]  = new QPushButton("[3, 4)", this);

	for (int i = 1; i < Count; ++i) {
		QPushButton* const btn = m_filterButtons[i];
		btn->setCheckable(true);
		btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	}

	QGridLayout* lout = new QGridLayout;
	lout->addWidget(m_filterButtons[DropFiltersBtn]        , 0, 0, 2, 1);
	lout->addWidget(m_filterButtons[FilterOkBtn]           , 0, 1);
	lout->addWidget(m_filterButtons[FilterNotOkBtn]        , 1, 1);
	lout->addWidget(m_filterButtons[FilterABLesser2Btn]    , 0, 3);
	lout->addWidget(m_filterButtons[FilterABGreater2Btn]   , 1, 3);
	lout->addWidget(m_filterButtons[FilterDiffFrom06To1Btn], 0, 4);
	lout->addWidget(m_filterButtons[FilterDiffFrom1To2Btn] , 1, 4);
	lout->addWidget(m_filterButtons[FilterDiffFrom2To3Btn] , 0, 5);
	lout->addWidget(m_filterButtons[FilterDiffFrom3To4Btn] , 1, 5);

	lout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	lout->activate();

	const int h = m_filterButtons[FilterOkBtn]->height();
	m_filterButtons[DropFiltersBtn]->setFixedSize(h, h);

	setLayout(lout);

	connect(m_filterButtons[DropFiltersBtn]        , &QPushButton::clicked, this, &FiltersWidget::onDropFiltersBtnClicked);
	connect(m_filterButtons[FilterOkBtn]           , &QPushButton::clicked, this, &FiltersWidget::onFilterOkBtnClicked);
	connect(m_filterButtons[FilterNotOkBtn]        , &QPushButton::clicked, this, &FiltersWidget::onFilterNotOkBtnClicked);
	connect(m_filterButtons[FilterABLesser2Btn]    , &QPushButton::clicked, this, &FiltersWidget::onFilterABLesser2BtnClicked);
	connect(m_filterButtons[FilterABGreater2Btn]   , &QPushButton::clicked, this, &FiltersWidget::onFilterABGreater2BtnClicked);
	connect(m_filterButtons[FilterDiffFrom06To1Btn], &QPushButton::clicked, this, &FiltersWidget::onFilterDiffFrom06To1BtnClicked);
	connect(m_filterButtons[FilterDiffFrom1To2Btn] , &QPushButton::clicked, this, &FiltersWidget::onFilterDiffFrom1To2BtnClicked);
	connect(m_filterButtons[FilterDiffFrom2To3Btn] , &QPushButton::clicked, this, &FiltersWidget::onFilterDiffFrom2To3BtnClicked);
	connect(m_filterButtons[FilterDiffFrom3To4Btn] , &QPushButton::clicked, this, &FiltersWidget::onFilterDiffFrom3To4BtnClicked);
}

void FiltersWidget::setFilterOptions(FilterOptionFlags options, bool isSet) {
	const FilterOptionFlags oldFilterOptions = m_currentFilters;
	if (isSet) {
		m_currentFilters |= options;
	} else {
		m_currentFilters &= ~options;
	}
	if (m_currentFilters != oldFilterOptions) {
		emit filterChanged(m_currentFilters);
	}
}

void FiltersWidget::onDropFiltersBtnClicked() {
	for (int i = 0; i < Count; ++i) {
		m_filterButtons[i]->setChecked(false);
	}
	m_currentFilters = FilterOption::None;
	emit filterChanged(m_currentFilters);
}

void FiltersWidget::onFilterOkBtnClicked() {
	setFilterOptions(FilterOption::Ok, m_filterButtons[FilterOkBtn]->isChecked());
}

void FiltersWidget::onFilterNotOkBtnClicked() {
	setFilterOptions(FilterOption::NotOk, m_filterButtons[FilterNotOkBtn]->isChecked());
}

void FiltersWidget::onFilterABLesser2BtnClicked() {
	setFilterOptions(FilterOption::ABLesser2, m_filterButtons[FilterABLesser2Btn]->isChecked());
}

void FiltersWidget::onFilterABGreater2BtnClicked() {
	setFilterOptions(FilterOption::ABGreater2, m_filterButtons[FilterABGreater2Btn]->isChecked());
}

void FiltersWidget::onFilterDiffFrom06To1BtnClicked() {
	setFilterOptions(FilterOption::DiffFrom06To1, m_filterButtons[FilterDiffFrom06To1Btn]->isChecked());
}

void FiltersWidget::onFilterDiffFrom1To2BtnClicked() {
	setFilterOptions(FilterOption::DiffFrom1To2, m_filterButtons[FilterDiffFrom1To2Btn]->isChecked());
}

void FiltersWidget::onFilterDiffFrom2To3BtnClicked() {
	setFilterOptions(FilterOption::DiffFrom2To3, m_filterButtons[FilterDiffFrom2To3Btn]->isChecked());
}

void FiltersWidget::onFilterDiffFrom3To4BtnClicked() {
	setFilterOptions(FilterOption::DiffFrom3To4, m_filterButtons[FilterDiffFrom3To4Btn]->isChecked());
}
