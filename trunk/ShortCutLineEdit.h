#ifndef SHORTCUTLINEEDIT_H
#define SHORTCUTLINEEDIT_H

//#include "../utils_global.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
//namespace TWUtils {
//namespace UI {

        class ShortCutLineEdit : public QLineEdit
	{
		Q_OBJECT
		public:
			explicit ShortCutLineEdit( QWidget* parent = 0 );
//			void setButtonVisible( bool show , const QString& toolTip = QString::null );

			void setText( const QString& );
			QString text() const;
		signals:
			void buttonClicked();
		public slots:
			void clearText();

		protected:
			void resizeEvent( QResizeEvent* );
			void keyPressEvent( QKeyEvent* );
			void keyReleaseEvent( QKeyEvent* );

		private:
			bool    b_keyIsValid;
			bool    b_showButton;
			QString	s_storedKey;
//			QPushButton m_btn;
//			void updateButtonPosition();

        };
//} // namespace UI
//} // namespace TWUtils

#endif // LIB_UTILS_SHORTCUTLINEEDIT_H
