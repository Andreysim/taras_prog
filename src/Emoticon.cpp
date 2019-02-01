#include "pch.h"
#include "Emoticon.h"

Emoticon::Emoticon(QWidget* parent)
		: QWidget(parent) {
	const QFontMetrics fm(font());
	const int sz = fm.height() * 2;
	setMinimumHeight(sz);
	setMinimumWidth(32);
}

void Emoticon::setIconFromVal(EvalValue val) {
	if (val.isGood()) {
		m_icon = QIcon(":/ok.png");
	} else if (val.isBad()) {
		m_icon = QIcon(":/bad.png");
	} else {
		m_icon = QIcon(":/neutral.png");
	}
	update();
}

void Emoticon::clear() {
	m_icon = QIcon();
	update();
}

void Emoticon::paintEvent(QPaintEvent* /*event*/) {
	if (!m_icon.isNull()) {
		QPainter p(this);
		p.fillRect(rect(), Qt::transparent);
		QRect rc = rect();
		if (rc.width() < rc.height()) {
			rc.translate(0, (rc.height() - rc.width()) / 2);
			rc.setHeight(rc.width());
		} else if (rc.height() < rc.width()) {
			rc.translate((rc.width() - rc.height()) / 2, 0);
			rc.setWidth(rc.height());
		}
		m_icon.paint(&p, rc);
	}
}
