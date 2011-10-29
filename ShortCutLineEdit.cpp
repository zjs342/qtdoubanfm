#include "ShortCutLineEdit.h"
#include <QKeySequence>
#include <QPushButton>
#include <QKeyEvent>

//namespace TWUtils {
//namespace UI {

ShortCutLineEdit::ShortCutLineEdit( QWidget* parent ) :
	QLineEdit( parent ),
	b_keyIsValid( true ),
	b_showButton( false )
{
	setObjectName( "ShortCutLineEdit" );
	//                m_btn.setParent( this );
	//                m_btn.hide();
	//                m_btn.setCursor( Qt::ArrowCursor );
	//                connect( &m_btn, SIGNAL( clicked() ), this, SLOT( clearText() ) );
	//                setButtonVisible(true,tr("清除快捷键"));

	ensurePolished();
	//                updateButtonPosition();
}

void ShortCutLineEdit::setText( const QString& s )
{
	QByteArray ss = s.toAscii().toPercentEncoding();
	ss.replace( "%E1%9F%80", "" );
	QString sss = QByteArray::fromPercentEncoding( ss );
	sss.replace( "Meta", "Win" );
	QLineEdit::setText( sss );
	//                if( b_showButton )
	//                        m_btn.setVisible( !s.isEmpty() );
}

QString ShortCutLineEdit::text() const
{
	QString s = QLineEdit::text();
	s.replace( "Win", "Meta" );
	return s;
}

void ShortCutLineEdit::clearText()
{
	s_storedKey = "";
	QLineEdit::setText( "" );
	b_keyIsValid = false;
	setFocus();
	//                m_btn.hide();
}

void ShortCutLineEdit::resizeEvent( QResizeEvent* )
{
	//                updateButtonPosition();
}

void ShortCutLineEdit::keyPressEvent( QKeyEvent* e )
{
	e->accept();
	if( b_keyIsValid )
	{
		s_storedKey = text();
	}

	// 后退键清除快捷键
	if( e->key() == Qt::Key_Backspace )
	{
		setText( "" );
		s_storedKey = "";
		b_keyIsValid = false;
		return;
	}

	int modifiers = e->modifiers();
	int key = e->key() & ( ~Qt::Key_Control ) & ( ~Qt::Key_Meta )
		& ( ~Qt::Key_Alt ) & ( ~Qt::Key_Shift );
	/*int key = e->key() & ~(Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier);*/
	QKeySequence keyseq( e->key() | ( e->modifiers()&( ~Qt::KeypadModifier ) ) );
	setText( keyseq );
	if( modifiers == 0 || key == 0 )
	{
		// 如果没有modifier，或者只有modifier，这个快捷键不能用。
		b_keyIsValid = false;
		return;
	}

	b_keyIsValid = true;
}

void ShortCutLineEdit::keyReleaseEvent( QKeyEvent* )
{
	if( !b_keyIsValid )
		setText( s_storedKey );
}

/*        void ShortCutLineEdit::setButtonVisible( bool show, const QString& toolTip )
	  {
	  b_showButton = show;
	  m_btn.setToolTip( toolTip );
	  if( show )
	  m_btn.setVisible( !text().isEmpty() );
	  else
	  m_btn.hide();
	  }

	  void ShortCutLineEdit::updateButtonPosition()
	  {
	  int x = width() - m_btn.width() - 2;
	  int y = ( height() - m_btn.height() ) / 2;
	  m_btn.move( x, y );
	  setTextMargins( 0, 0, width() - x, 0 );
	  }
 */
//}
//} // namespace TWUtils
