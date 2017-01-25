#include "ParameterViewer.h"
#include "StringRegistry.h"
#include <sstream>
#include <iostream>

ParameterViewer::ParameterViewer(QWidget *parent) : QAbstractScrollArea(parent) {

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // buggy with GTK style, maximumViewportSize() doesn't take the border into account :(
	verticalScrollBar()->setSingleStep(20);
	setFocusPolicy(Qt::NoFocus);

	viewport()->setBackgroundRole(QPalette::Window);
	viewport()->setAutoFillBackground(true);
	viewport()->setMouseTracking(true);

	UpdateRange();

	loadTestParam();

	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChange()));}

ParameterViewer::~ParameterViewer() {}


void ParameterViewer::loadTestParam()
{
	m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);

	m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);m_parameters.EmplaceBack(StringRegistry::NewTag("Layer"),VData("Copper-top"),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("X"),VData(78.44),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Y"),VData(45.4156),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Radius"),VData(5.6),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Width"),VData(10),true,false,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Mirror"),VData(true),true,true,false);
	m_parameters.EmplaceBack(StringRegistry::NewTag("Angle"),VData(45),true,false,true);



	for(index_t i = 0 ; i < m_parameters.GetSize(); ++i) {
		QLineEdit *valuebox = new QLineEdit(viewport());
		if(m_parameters[i].m_mergeable){
			std::stringstream s;
			s << m_parameters[i].m_value;
			valuebox->setText(QString::fromStdString(s.str()));
		}
		else {
			valuebox->setText("...");
			if(m_parameters[i].m_expanded){
				ExpandParameter(i);
			}
		}
		this->AddWidget(i,valuebox);
	}

}

void ParameterViewer::OnFocusChange()
{
	QWidget *focuswidget = viewport()->focusWidget();
	if(focuswidget){ // widget can be distroyed
		// TODO check if widget is in parameterviewer
		QRect r = focuswidget->geometry();
		if(r.y() > viewport()->height()-r.height()-LAYOUT_HSPACING){ // scroll down
			verticalScrollBar()->setValue(verticalScrollBar()->value()+r.height()+LAYOUT_VSPACING);
		}
		if(r.y() < LAYOUT_VSPACING){ // scroll up
			verticalScrollBar()->setValue(verticalScrollBar()->value()-r.height()-LAYOUT_VSPACING);
		}
		if(r.y() < LAYOUT_VSPACING-r.height()){ // loop scroll down
			verticalScrollBar()->setValue(0);
		}
		if(r.y() > viewport()->height()-LAYOUT_HSPACING){ // loop scroll up
			verticalScrollBar()->setValue(viewport()->height()-r.height()-LAYOUT_HSPACING);
		}
		UpdateLayout();
	}
}

static QSize GetWidgetSize(QWidget* widget)
{
	QSize size = widget->sizeHint();
	if(!size.isValid())
		size = QSize(0, 0);
	QSize minimumsize = widget->minimumSize();
	if(!minimumsize.isValid())
		minimumsize = widget->minimumSizeHint();
	if(minimumsize.isValid())
		size.expandedTo(minimumsize);
	QSize maximumsize = widget->maximumSize();
	if(maximumsize.isValid())
		size.boundedTo(maximumsize);
	return size;
}

index_t ParameterViewer::GetWidgetCount()
{
	return m_widgets.size();
}

QWidget* ParameterViewer::GetWidget(index_t index)
{
	assert(index < m_widgets.size());
	return m_widgets[index];
}

void ParameterViewer::AddWidget(index_t index, QWidget* widget)
{
	assert(index <= m_widgets.size());
	assert(widget->parent() == viewport());

	widget->setAutoFillBackground(true);
	widget->setBackgroundRole(QPalette::Window);
	if(widget->focusPolicy() == Qt::NoFocus)
		widget->setFocusPolicy(Qt::ClickFocus);
	widget->show();

	m_widgets.insert(m_widgets.begin() + index, widget);
	UpdateFocusChain();
	UpdateRange();
	UpdateLayout();

}

void ParameterViewer::RemoveWidget(index_t index)
{
	assert(index < m_widgets.size());

	delete m_widgets[index];
	m_widgets.erase(m_widgets.begin() + index);
	UpdateFocusChain();
	UpdateRange();
	UpdateLayout();

}

void ParameterViewer::MoveWidget(index_t from, index_t to)
{
	assert(from < m_widgets.size());
	assert(to < m_widgets.size());

	QWidget *widget = m_widgets[from];
	m_widgets.erase(m_widgets.begin() + from);
	m_widgets.insert(m_widgets.begin() + to, widget);
	UpdateFocusChain();
	UpdateLayout();

}

void ParameterViewer::MakeVisible(QWidget* widget)
{
	assert(viewport()->isAncestorOf(widget));
	QRect widget_rect(widget->mapTo(viewport(), QPoint(0, verticalScrollBar()->value())), widget->size());
	QRect visible_rect(QPoint(0, verticalScrollBar()->value()), viewport()->size());
	if(widget_rect.height() > visible_rect.height()) {
		if(widget_rect.top() > visible_rect.top()) {
			verticalScrollBar()->setValue(widget_rect.top());
		} else if(widget_rect.bottom() < visible_rect.bottom()) {
			verticalScrollBar()->setValue(visible_rect.top() + widget_rect.bottom() - visible_rect.bottom());
		}
	} else {
		if(widget_rect.top() < visible_rect.top()) {
			verticalScrollBar()->setValue(widget_rect.top());
		} else if(widget_rect.bottom() > visible_rect.bottom()) {
			verticalScrollBar()->setValue(visible_rect.top() + widget_rect.bottom() - visible_rect.bottom());
		}
	}
}

bool ParameterViewer::viewportEvent(QEvent* event)
{
	switch(event->type()) {
		case QEvent::LayoutRequest: {
			UpdateRange();
			UpdateLayout();
			event->accept();
			return true;
		}
		default: return QAbstractScrollArea::viewportEvent(event);
	}
}

void ParameterViewer::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);
	UpdateRange();
	UpdateLayout();
}

void ParameterViewer::scrollContentsBy(int dx, int dy)
{
	if(dx == 0 && dy == 0)
		return;
	UpdateLayout();
}

bool ParameterViewer::focusNextPrevChild(bool next) {
	return QWidget::focusNextPrevChild(next); //TODO// remove?
}

void ParameterViewer::paintEvent(QPaintEvent *event)
{
	UNUSED(event);
	QPainter painter(viewport());

	int y = -verticalScrollBar()->value();

	for(index_t i = 0; i < m_widgets.size(); ++i)
	{
		QSize size = GetWidgetSize(m_widgets[i]);

		QStyleOptionButton opt;

		if(m_parameters[i].m_mergeable) {
			opt.state = QStyle::State_Item | QStyle::State_Active | QStyle::State_Enabled;
		}
		else {
			if(m_parameters[i].m_expanded){
				opt.state = QStyle::State_Item | QStyle::State_Children | QStyle::State_Open | QStyle::State_Active | QStyle::State_Enabled;
			}
			else{
				opt.state = QStyle::State_Item | QStyle::State_Children | QStyle::State_Active | QStyle::State_Enabled;
			}
		}
		if(i < m_widgets.size()-1){
			opt.state |= QStyle::State_Sibling;
		}

		if(m_current_index == i && m_current_subindex == INDEX_NONE && m_hover){
			opt.state |= QStyle::State_MouseOver;
		}
		else {
			opt.state &= ~QStyle::State_MouseOver;
		}

		QIcon select_icon = QIcon::fromTheme("document-open");
		QIcon deselect_icon = QIcon::fromTheme("document-save");


		opt.rect = QRect(0,y-LAYOUT_VSPACING/2,LAYOUT_FOLDBUTTONWIDTH,size.height()+LAYOUT_VSPACING);
		style()->drawPrimitive(QStyle::PE_IndicatorBranch, &opt, &painter, viewport());
		painter.drawText(QRect(LAYOUT_FOLDBUTTONWIDTH+LAYOUT_HSPACING,y,LAYOUT_LABELWIDTH-LAYOUT_FOLDBUTTONWIDTH+LAYOUT_HSPACING,size.height()),Qt::AlignLeft|Qt::AlignVCenter|Qt::TextSingleLine,QString::fromStdString(StringRegistry::GetString(m_parameters[i].m_name)));
		y += size.height()+LAYOUT_VSPACING;

		if(!m_parameters[i].m_mergeable && m_parameters[i].m_expanded){
			for(index_t j = 0; j < m_parameters[i].m_subparameters.size(); ++j){
				if(i < m_widgets.size()-1){
					QStyleOptionButton opt_sub;
					opt.state = QStyle::State_Active | QStyle::State_Enabled | QStyle::State_Sibling;
					opt.rect = QRect(0,y-LAYOUT_VSPACING/2,LAYOUT_FOLDBUTTONWIDTH,size.height()+LAYOUT_VSPACING);
					style()->drawPrimitive(QStyle::PE_IndicatorBranch, &opt, &painter, viewport());
				}
				select_icon.paint(&painter,LAYOUT_FOLDBUTTONWIDTH+LAYOUT_HSPACING,y,LAYOUT_SUBPARAMBUTTONWIDTH,size.height());
				deselect_icon.paint(&painter,LAYOUT_FOLDBUTTONWIDTH+2*LAYOUT_HSPACING+LAYOUT_SUBPARAMBUTTONWIDTH,y,LAYOUT_SUBPARAMBUTTONWIDTH,size.height());
				painter.drawText(QRect(LAYOUT_FOLDBUTTONWIDTH+3*LAYOUT_HSPACING+2*LAYOUT_SUBPARAMBUTTONWIDTH,y,LAYOUT_LABELWIDTH-LAYOUT_FOLDBUTTONWIDTH+LAYOUT_HSPACING,size.height()),Qt::AlignLeft|Qt::AlignVCenter|Qt::TextSingleLine,QString::fromStdString("(" + std::to_string(m_parameters[i].m_subparameters[j].m_num_shapes) + ")"));
				y += size.height()+LAYOUT_VSPACING;
			}
		}

	}

}

void ParameterViewer::mousePressEvent(QMouseEvent *event)
{
	positionToIndex(event->pos());
	if(m_current_index != INDEX_NONE){
		if(event->pos().x() < LAYOUT_FOLDBUTTONWIDTH){
			if(!m_parameters[m_current_index].m_mergeable){
				if(m_parameters[m_current_index].m_expanded){
					UnexpandParameter(m_current_index);
				}
				else{
					ExpandParameter(m_current_index);

				}
			}
		}
	}
}

void ParameterViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
	positionToIndex(event->pos());
	if(m_current_index != INDEX_NONE){
		if(event->pos().x() > LAYOUT_FOLDBUTTONWIDTH && event->pos().x() < LAYOUT_FOLDBUTTONWIDTH+LAYOUT_HSPACING+LAYOUT_LABELWIDTH){
			if(!m_parameters[m_current_index].m_mergeable){
				if(m_parameters[m_current_index].m_expanded){
					UnexpandParameter(m_current_index);
				}
				else{
					ExpandParameter(m_current_index);
				}
			}
		}
	}
}

void ParameterViewer::mouseMoveEvent(QMouseEvent *event)
{
	if(event->pos().x() < LAYOUT_FOLDBUTTONWIDTH+LAYOUT_HSPACING+LAYOUT_LABELWIDTH){
		m_hover = true;
		positionToIndex(event->pos());
	}
	else{
		m_hover = false;
	}
	viewport()->update();
}

void ParameterViewer::leaveEvent(QEvent *event)
{
	UNUSED(event);
	m_current_index = INDEX_NONE;
	m_current_subindex = INDEX_NONE;
	m_hover = false;
	viewport()->update();
}

void ParameterViewer::UpdateFocusChain()
{
	QWidget *current_widget;
	QWidget *next_widget;

	for(index_t i = 0; i < m_widgets.size()-1; ++i) {

		current_widget = m_widgets[i];
		if(!m_parameters[i].m_mergeable && m_parameters[i].m_expanded){
			next_widget = m_parameters[i].m_subparameters[0].m_widget;
			setTabOrder(current_widget,next_widget);

			for(index_t j = 1; j < m_parameters[i].m_subparameters.size(); ++j){
				current_widget = next_widget;
				next_widget = m_parameters[i].m_subparameters[j].m_widget;
				setTabOrder(current_widget,next_widget);
			}
			current_widget = m_parameters[i].m_subparameters[m_parameters[i].m_subparameters.size()].m_widget;
		}
		else{
			next_widget = m_widgets[i+1];
			setTabOrder(current_widget,next_widget);
		}
	}
}

void ParameterViewer::UpdateRange() {
	int height = LAYOUT_VSPACING;
	for(index_t i = 0; i < m_widgets.size(); ++i) {
		QSize size = GetWidgetSize(m_widgets[i]);
		height += size.height() + LAYOUT_VSPACING;

		if(!m_parameters[i].m_mergeable && m_parameters[i].m_expanded){
			for(index_t j = 0; j < m_parameters[i].m_subparameters.size(); ++j){
				QSize size = GetWidgetSize(m_parameters[i].m_subparameters[j].m_widget);
				height += size.height()+LAYOUT_VSPACING;
			}
		}

	}
	verticalScrollBar()->setPageStep(viewport()->height());
	verticalScrollBar()->setRange(0, std::max(0, height - LAYOUT_VSPACING - viewport()->height()));
}

void ParameterViewer::UpdateLayout() {




	int y = -verticalScrollBar()->value();

	y = y + LAYOUT_VSPACING;
	for(index_t i = 0; i < m_widgets.size(); ++i)
	{
		QSize size = GetWidgetSize(m_widgets[i]);

		m_widgets[i]->setGeometry(LAYOUT_LABELWIDTH+LAYOUT_FOLDBUTTONWIDTH+2*LAYOUT_HSPACING, y, viewport()->width()-LAYOUT_LABELWIDTH-LAYOUT_FOLDBUTTONWIDTH-3*LAYOUT_HSPACING, size.height());
		m_widgets[i]->setContentsMargins(0,0,0,0);
		y += size.height()+LAYOUT_VSPACING;

		if(!m_parameters[i].m_mergeable && m_parameters[i].m_expanded){
			for(index_t j = 0; j < m_parameters[i].m_subparameters.size(); ++j){
				QSize size = GetWidgetSize(m_parameters[i].m_subparameters[j].m_widget);

				m_parameters[i].m_subparameters[j].m_widget->setGeometry(LAYOUT_LABELWIDTH+LAYOUT_FOLDBUTTONWIDTH+2*LAYOUT_HSPACING, y, viewport()->width()-LAYOUT_LABELWIDTH-LAYOUT_FOLDBUTTONWIDTH-3*LAYOUT_HSPACING, size.height());
				m_parameters[i].m_subparameters[j].m_widget->setContentsMargins(0,0,0,0);
				y += size.height()+LAYOUT_VSPACING;
			}
		}
	}

	viewport()->update();
}

void ParameterViewer::positionToIndex(const QPoint &pos)
{
	m_current_index = INDEX_NONE;
	m_current_subindex = INDEX_NONE;
	int y = -verticalScrollBar()->value();

	y = y + LAYOUT_VSPACING/2;
	index_t i = 0;
	while(i < m_widgets.size() && m_current_index == INDEX_NONE)
	{
		QSize size = GetWidgetSize(m_widgets[i]);
		y += size.height()+LAYOUT_VSPACING;

		if(pos.y() < y){
			m_current_index = i;
			break;
		}

		if(!m_parameters[i].m_mergeable && m_parameters[i].m_expanded){
			for(index_t j = 0; j < m_parameters[i].m_subparameters.size(); ++j){
				QSize size = GetWidgetSize(m_parameters[i].m_subparameters[j].m_widget);
				y += size.height()+LAYOUT_VSPACING;

				if(pos.y() < y){
					m_current_index = i;
					m_current_subindex = y;
					break;
				}
			}
		}

		++i;
	}
}

void ParameterViewer::ExpandParameter(index_t index)
{
	m_parameters[index].m_expanded = true;

	// TODO replace with shape search
	QLineEdit *widget = new QLineEdit(viewport());
	widget->setText("fgdfg");
	widget->setAutoFillBackground(true);
	widget->setBackgroundRole(QPalette::Window);
	if(widget->focusPolicy() == Qt::NoFocus)
		widget->setFocusPolicy(Qt::ClickFocus);
	widget->show();
	m_parameters[index].m_subparameters.emplace_back(1,widget);

	QLineEdit *widget2 = new QLineEdit(viewport());
	widget2->setText("x");
	widget2->setAutoFillBackground(true);
	widget2->setBackgroundRole(QPalette::Window);
	if(widget2->focusPolicy() == Qt::NoFocus)
		widget2->setFocusPolicy(Qt::ClickFocus);
	widget2->show();
	m_parameters[index].m_subparameters.emplace_back(3,widget2);

	UpdateLayout();
	UpdateFocusChain();
	UpdateRange();
}

void ParameterViewer::UnexpandParameter(index_t index)
{
	m_parameters[index].m_expanded = false;
	for(index_t i = 0; i < m_parameters[index].m_subparameters.size(); ++i) {
		m_parameters[index].m_subparameters[i].m_widget->deleteLater();
	}
	m_parameters[index].m_subparameters.clear();

	UpdateLayout();
	UpdateFocusChain();
	UpdateRange();
}

