
#include "switchwidget.h"


CSwitchWidget::CSwitchWidget(QWidget *parent): QWidget(parent)
{
	m_pressstyle	= GRAPH_PRESSSTYLE_SYSTEM1;

	//渐进色
	m_offbkcolor1		= QColor(133, 133, 133);	//分开背景色1
	m_offbkcolor2		= QColor(99, 99, 99);		//分开背景色2
	
	//渐进色
	m_onbkcolor1		= QColor(91, 137, 14);		//闭合背景色1
	m_onbkcolor2		= QColor(71,103,8);			//闭合背景色2
	
	m_slidecolor1		= QColor(252, 252, 252);	
	m_slidecolor2		= QColor(224, 224, 224);
	
	m_textcolor			= QColor(255, 255, 255);
	m_textfont			= QFont(QString::fromLocal8Bit("宋体"), 10);

	m_offname			= QString::fromLocal8Bit("分");
	m_onname			= QString::fromLocal8Bit("合");

	m_state				= 0;
}

CSwitchWidget::~CSwitchWidget()
{

}

void CSwitchWidget::mousePressEvent(QMouseEvent * event)
{
	QPoint	cursorpos = event->pos();
	int		x = cursorpos.x();
	int		y = cursorpos.y();
	
	if (event->button() == Qt::LeftButton) {
		if (x < width() / 2.0) emit StateChanged(1);
		else emit StateChanged(0);
	}
	
	repaint();
	
	QWidget::mousePressEvent(event);
}

void CSwitchWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QRect widgetrect(0, 0, width(), height());
	DrawPressStyle(&painter, widgetrect, m_state);

	//QPalette pa;
	//QBrush brush(Qt::NoBrush);
	//qDrawShadePanel(&painter, 0, 0, width(), height(), pa, TRUE, 2,  &brush); 
}

void CSwitchWidget::DrawPressStyle(QPainter *painter, QRect &rect, uchar state)
{
	if (painter == NULL) return;

	DrawPressBkGround(painter, rect, state);	//绘制背景

	DrawPressText(painter, rect, state);		//绘制文字

	DrawPressSlide(painter, rect, state);		//绘制滑块
}

void CSwitchWidget::DrawPressBkGround(QPainter *painter, QRect &rect, uchar state)
{
	QBrush		oldbrush = painter->brush();
	QPen		oldpen   = painter->pen();		
	painter->save();

	int panestyle = GetPressStyle();

	int	x1 = rect.left(); int y1 = rect.top();
	int	x2 = rect.right(); int y2 = rect.bottom();
	int width = rect.width(); int height = rect.height();
	
	if (panestyle == GRAPH_PRESSSTYLE_SYSTEM1) {		//矩形背景、方形滑块
		if (state > 0) {		//投入状态
			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_onbkcolor1);
			linGrad.setColorAt(1, m_onbkcolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);

			painter->drawRoundedRect(rect, 5.0, 5.0);
		}
		else {					//退出状态
			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_offbkcolor1);
			linGrad.setColorAt(1, m_offbkcolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);
	
			painter->drawRoundedRect(rect, 5.0, 5.0);
		}

		//画立体阴影......
		painter->setBrush(Qt::NoBrush);
		QPen tmppen(Qt::darkGray);
		tmppen.setWidth(2.0);
		painter->setPen(tmppen);
		painter->drawRoundedRect(rect, 5.0, 5.0);
	}
	else if (panestyle == GRAPH_PRESSSTYLE_SYSTEM2) {	//圆角矩形背景、圆形滑块
		//path
		QPainterPath path;

		path.moveTo(x1 + height / 2.0, y1);
		path.arcTo(QRectF(x1, y1, height, height), 90, 180);
		path.lineTo(x2 - height / 2.0, y2);
		path.arcTo(QRectF(x2 - height, y1, height, height), 270, 180);
		path.lineTo(x1 + height / 2.0, y1);

		QPainterPath pathrect;
		pathrect.moveTo(rect.left(), rect.top());
		pathrect.lineTo(rect.left(), rect.bottom());
		pathrect.lineTo(rect.right(), rect.bottom());
		pathrect.lineTo(rect.right(), rect.top());
		pathrect.lineTo(rect.left(), rect.top());

		QPainterPath interpath = path.intersected(pathrect);

		if (state > 0) {		//投入状态
			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_onbkcolor1);
			linGrad.setColorAt(1, m_onbkcolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);
			painter->drawPath(interpath);
		}
		else {					//退出状态
			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_offbkcolor1);
			linGrad.setColorAt(1, m_offbkcolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);
			painter->drawPath(interpath);
		}

		//画立体阴影......
		painter->setBrush(Qt::NoBrush);
		painter->setPen(QColor(0, 0, 0, 255));
		painter->drawPath(interpath);
	}

	painter->restore();
	painter->setPen(oldpen);
	painter->setBrush(oldbrush);
}

void CSwitchWidget::DrawPressText(QPainter *painter, QRect &rect, uchar state)
{
	QBrush oldbrush = painter->brush();
	QPen	  oldpen   = painter->pen();		
	painter->save();
	
	
	int	x1 = rect.left(); int y1 = rect.top();
	int	x2 = rect.right(); int y2 = rect.bottom();
	int width = rect.width(); int height = rect.height();

	QPen tmppen(m_textcolor);

	if (state > 0) {		//投入状态
		painter->setFont(m_textfont);
		painter->setPen(tmppen);
		painter->drawText((int)(x1 + width / 2.0), y1, (int)(width / 2.0), height, Qt::AlignCenter, m_onname);
	}
	else {					//退出状态
		painter->setFont(m_textfont);
		painter->setPen(tmppen);
		painter->drawText(x1, y1, (int)(width / 2.0), height, Qt::AlignCenter, m_offname);
	}

	painter->restore();
	painter->setPen(oldpen);
	painter->setBrush(oldbrush);
}

void CSwitchWidget::DrawPressSlide(QPainter *painter, QRect &rect, uchar state)
{
	QBrush oldbrush = painter->brush();
	QPen	  oldpen   = painter->pen();		
	painter->save();
	
	int panestyle = GetPressStyle();
	
	int	x1 = rect.left(); int y1 = rect.top();
	int	x2 = rect.right(); int y2 = rect.bottom();
	int width = rect.width(); int height = rect.height();

	QRect sliderect;

	if (panestyle == GRAPH_PRESSSTYLE_SYSTEM1) {		//矩形背景、方形滑块
		if (state > 0) {		//投入状态
			sliderect.setLeft(rect.left() + 2); 
			sliderect.setTop(rect.top() + 2);
			sliderect.setWidth((int)(rect.width() / 2.0 - 4));
			sliderect.setHeight(rect.height() - 4);

			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_slidecolor1);
			linGrad.setColorAt(1, m_slidecolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);

			painter->drawRoundedRect(sliderect, 5.0, 5.0);
		}
		else {					//退出状态
			sliderect.setLeft(rect.right() - (int)(rect.width() / 2.0) + 2); 
			sliderect.setTop(rect.top() + 2);
			sliderect.setWidth((int)(rect.width() / 2.0 - 4));
			sliderect.setHeight(rect.height() - 4);

			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_slidecolor1);
			linGrad.setColorAt(1, m_slidecolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);
			
			painter->drawRoundedRect(sliderect, 5.0, 5.0);
		}

		//画立体阴影......
		painter->setBrush(Qt::NoBrush);
		painter->setPen(QColor(0, 0, 0, 255));
		painter->drawRoundedRect(sliderect, 5.0, 5.0);

		//画纹理
		painter->setPen(QColor(54, 54, 54));
		painter->drawLine(sliderect.left() + sliderect.width() / 2.0,	  sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0, sliderect.bottom() - sliderect.height() / 4.0 - 2);
		painter->drawLine(sliderect.left() + sliderect.width() / 2.0 - 5, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 - 5, sliderect.bottom() - sliderect.height() / 4.0 - 2);
		painter->drawLine(sliderect.left() + sliderect.width() / 2.0 + 5, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 + 5, sliderect.bottom() - sliderect.height() / 4.0 - 2);

		painter->setPen(QColor(134, 134, 134));
		painter->drawLine(sliderect.left() + sliderect.width() / 2.0 + 1,	  sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 + 1, sliderect.bottom() - sliderect.height() / 4.0 - 2);
		painter->drawLine(sliderect.left() + sliderect.width() / 2.0 - 5 + 1, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 - 5 + 1, sliderect.bottom() - sliderect.height() / 4.0 - 2);
		painter->drawLine(sliderect.left() + sliderect.width() / 2.0 + 5 + 1, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 + 5 + 1, sliderect.bottom() - sliderect.height() / 4.0 - 2);
	}
	else if (panestyle == GRAPH_PRESSSTYLE_SYSTEM2) {	//圆角矩形背景、圆形滑块
		
		QRect rrect;

		if (state > 0) {		//投入状态
			sliderect.setLeft(rect.left() + 2); 
			sliderect.setTop(rect.top() + 2);
			sliderect.setWidth(rect.height() - 4 );
			sliderect.setHeight(rect.height() - 4);

			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_slidecolor1);
			linGrad.setColorAt(1, m_slidecolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);

			rrect = sliderect.intersected(rect);
			
			painter->drawEllipse(rrect);
		}
		else {					//退出状态
			sliderect.setLeft(rect.right() -  rect.height() + 4 - 2); 
			sliderect.setTop(rect.top() + 2);
			sliderect.setWidth(rect.height() - 4 );
			sliderect.setHeight(rect.height() - 4);
			
			painter->setPen(Qt::NoPen);
			QLinearGradient linGrad(rect.left(), rect.top(), rect.left(), rect.bottom());
			linGrad.setColorAt(0, m_slidecolor1);
			linGrad.setColorAt(1, m_slidecolor2);
			linGrad.setSpread(QGradient::PadSpread);
			painter->setBrush(linGrad);

			rrect = sliderect.intersected(rect);
			painter->drawEllipse(rrect);
		}

		//画立体阴影......
		painter->setBrush(Qt::NoBrush);
		painter->setPen(QColor(0, 0, 0, 160));
		painter->drawEllipse(rrect);
	}
	
	painter->restore();
	painter->setPen(oldpen);
	painter->setBrush(oldbrush);
}