#ifndef __SWITCHWIDGET_H__
#define __SWITCHWIDGET_H__

#include <QtGui>

typedef  unsigned char		uchar;
#define		GRAPH_PRESSSTYLE_SYSTEM1	0
#define		GRAPH_PRESSSTYLE_SYSTEM2	1

class CSwitchWidget: public QWidget
{
	Q_OBJECT
private:
	uchar 			m_pressstyle;		//开关风格
	QColor			m_offbkcolor1;		
	QColor			m_offbkcolor2;
	QColor			m_onbkcolor1;
	QColor			m_onbkcolor2;
	QColor			m_slidecolor1;
	QColor			m_slidecolor2;
	QColor			m_textcolor;
	QFont			m_textfont;

	QString			m_offname;
	QString			m_onname;
	uchar			m_state;

public:
	//设置属性接口
	//开关风格
	uchar			GetPressStyle()								{ return m_pressstyle;					};
	void			SetPressStyle(uchar style)					{ m_pressstyle = style;					};
	
	//关闭背景颜色1
	QColor			GetPressOffBkColor1()						{ return  m_offbkcolor1;				};
	void			SetPressOffBkColor1(QColor color)			{ m_offbkcolor1 = color;				};
	
	//关闭背景颜色2
	QColor			GetPressOffBkColor2()						{ return  m_offbkcolor2;				};
	void			SetPressOffBkColor2(QColor color)			{ m_offbkcolor2 = color;				};
	
	//合上背景颜色1
	QColor			GetPressOnBkColor1()						{ return  m_onbkcolor1;					};
	void			SetPressOnBkColor1(QColor color)			{ m_onbkcolor1 = color;					};
	
	//合上背景颜色2
	QColor			GetPressOnBkColor2()						{ return  m_onbkcolor2;					};
	void			SetPressOnBkColor2(QColor color)			{ m_onbkcolor2 = color;					};
	
	//滑块颜色1
	QColor			GetPressSlideColor1()						{ return  m_slidecolor1;				};
	void			SetPressSlideColor1(QColor color)			{ m_slidecolor1 = color;				};
	
	//滑块颜色2
	QColor			GetPressSlideColor2()						{ return  m_slidecolor2;				};
	void			SetPressSlideColor2(QColor color)			{ m_slidecolor2 = color;				};
	
	//文字颜色
	QColor			GetPressTextColor()							{ return  m_textcolor;					};
	void			SetPressTextColor(QColor color)				{ m_textcolor = color;					};
	
	//文字字体
	QFont			GetPressTextFont()							{ return m_textfont;					};
	void			SetPressTextFont(QFont font)				{ m_textfont = font;					};

	//开关分状态文字描述
	QString			GetOffName()								{ return  m_offname;					};
	void			SetOffName(QString name)					{ m_offname = name;						};

	//开关合状态文字描述
	QString			GetOnName()									{ return  m_onname;						};
	void			SetOnName(QString name)						{ m_onname = name;						};

	//设置开关状态
	uchar			GetSwitchState()							{ return m_state;						};
	void			SetSwitchState(uchar state)					{ m_state = state;	repaint();			};

public:
	CSwitchWidget(QWidget *parent = 0);
	~CSwitchWidget();
	
signals: 
	void			StateChanged(int state);
	
protected:	
	virtual void	mousePressEvent(QMouseEvent * event);
	virtual void	paintEvent(QPaintEvent *event);

protected:	
	void			DrawPressStyle(QPainter *painter, QRect &rect, uchar state);	
	void			DrawPressBkGround(QPainter *painter, QRect &rect, uchar state);	
	void			DrawPressText(QPainter *painter, QRect &rect, uchar state);	
	void			DrawPressSlide(QPainter *painter, QRect &rect, uchar state);
};

#endif