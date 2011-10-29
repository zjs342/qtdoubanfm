#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <QWidget>
#include <QSettings>
#include "qxtglobalshortcut/qxtglobalshortcut.h"
#include <QDebug>

namespace Ui {
	class Shortcut;
}

class Shortcut : public QWidget
{
	Q_OBJECT

	public:
		explicit Shortcut(QWidget *parent = 0);
		~Shortcut();
		QxtGlobalShortcut* m_next;
		QxtGlobalShortcut* m_like;
		QxtGlobalShortcut* m_dislike;
		QxtGlobalShortcut* m_min;
		QxtGlobalShortcut* m_play;
		QxtGlobalShortcut* m_down;
		//QxtGlobalShortcut* m_lrc;
		QxtGlobalShortcut* m_desktop;
		//QxtGlobalShortcut* m_list;
		QxtGlobalShortcut* m_close;
	private:
		Ui::Shortcut *ui;
		public slots:
			void init();
		void mcancel();
		void mshow();
};

#endif // SHORTCUT_H
