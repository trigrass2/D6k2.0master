#ifndef SYSTEMOUTPUTVIEW_H
#define SYSTEMOUTPUTVIEW_H

#include <QTableView>

class CSystemOutputView : public QTableView
{
	Q_OBJECT

public:
	CSystemOutputView(QWidget *parent);
	~CSystemOutputView();

protected:
	void resizeEvent(QResizeEvent *event);

private:
	
};

#endif // SYSTEMOUTPUTVIEW_H
