﻿/*! @file
<PRE>
********************************************************************************
模块名       :	选择需要测的点
文件名       :	choosepointswgt.cpp
文件实现功能 :
作者         :  xingzhibing
版本         :  V1.00
--------------------------------------------------------------------------------
备注         : <其它说明>
--------------------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容

********************************************************************************
</PRE>
*  @brief
*  @author xingzhibing
*  @version 1.0
*  @date    2016.9.27
*/
#include <QTableWidget>
#include <QHBoxLayout>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include "choosepointswgt.h"
#include "dragtablewgt.h"
#include "datadefine.h"
#include "pointinfo.h"
#include "analysepointbin.h"
#include "virtualtablewgt.h"
#include "analogdragtablewgt.h"
#include "fcifile.h"
/*! \fn CChoosePointsWgt::CChoosePointsWgt(CPointInfo *pPointInfo, QWidget *parent)
*********************************************************************************************************
** \brief CChoosePointsWgt::CChoosePointsWgt(CPointInfo *pPointInfo, QWidget *parent)
** \details   构造函数
** \param 点信息 parent
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
CChoosePointsWgt::CChoosePointsWgt(CPointInfo *pPointInfo, QWidget *parent)
	: QWidget(parent),
	m_pDescTableWgt(new CDragTableWgt(this)),
	m_pSourceTableWgt(new CDragTableWgt(this)),
	m_pDoubleDescTableWgt(new CDragTableWgt(this)),
	m_pDoubleSourceTableWgt(new CDragTableWgt(this)),
	m_pAnalogDescTableWgt(new CAnalogDragTableWgt(this)),
	m_pAnalogSourceTableWgt(new CAnalogDragTableWgt(this)),
	m_pKwhDescTableWgt(new CDragTableWgt(this)),
	m_pKwhSourceTableWgt(new CDragTableWgt(this)),
	m_pControlDescTableWgt(new CDragTableWgt(this)),
	m_pControlSourceTableWgt(new CDragTableWgt(this)),
    m_pVirtualDescTableWgt(new CVirtualTableWgt(this)),
    m_pVirtualSourceTableWgt(new CDragTableWgt(this)),
	m_pTabWgt(new QTabWidget(this)),
    m_pCurrentPoints(new CAnalysePointBin(this))
{

	m_pPointInfo = pPointInfo;
	
	m_pDescTableWgt->SetDescTableWgt();
	m_pSourceTableWgt->SetSourceTableWgt();

	//双点
	m_pDoubleDescTableWgt->SetDescTableWgt();
	m_pDoubleSourceTableWgt->SetSourceTableWgt();

	m_pAnalogDescTableWgt->SetDescTableWgt();
	m_pAnalogSourceTableWgt->SetSourceTableWgt();

	m_pKwhDescTableWgt->SetDescTableWgt();
	m_pKwhSourceTableWgt->SetSourceTableWgt();

	m_pControlDescTableWgt->SetDescTableWgt();
	m_pControlSourceTableWgt->SetSourceTableWgt();

    //虚遥信
    m_pVirtualSourceTableWgt->SetSourceTableWgt();
    m_pVirtualDescTableWgt->SetDescTableWgt();

	//更新数据  信号  槽
	connect(m_pDescTableWgt, SIGNAL(Signal_UpdateTableInfo()), this, SLOT(Slot_UpdateBinaryPointData()));
	connect(m_pDoubleDescTableWgt, SIGNAL(Signal_UpdateTableInfo()), this, SLOT(Slot_UpdateDoubleBinaryPointData()));

	connect(m_pAnalogDescTableWgt, SIGNAL(Signal_UpdateTableInfo()), this, SLOT(Slot_UpdateAnalogPointData()));
	connect(m_pKwhDescTableWgt, SIGNAL(Signal_UpdateTableInfo()), this, SLOT(Slot_UpdateKwhPointData()));
	connect(m_pControlDescTableWgt, SIGNAL(Signal_UpdateTableInfo()), this, SLOT(Slot_UpdateControlPointData()));

	//更新选中状态
	connect(m_pDescTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pSourceTableWgt, SLOT(Slot_SetSelectedState(QList<unsigned int>)));

	connect(m_pDoubleDescTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pDoubleSourceTableWgt, SLOT(Slot_SetSelectedState(QList<unsigned int>)));

	connect(m_pAnalogDescTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pAnalogSourceTableWgt, SLOT(Slot_SetSelectedState(QList<unsigned int>)));
	connect(m_pKwhDescTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pKwhSourceTableWgt, SLOT(Slot_SetSelectedState(QList<unsigned int>)));
	connect(m_pControlDescTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pControlSourceTableWgt, SLOT(Slot_SetSelectedState(QList<unsigned int>)));
    //虚遥信
    connect(m_pVirtualDescTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pVirtualSourceTableWgt, SLOT(Slot_SetSelectedState(QList<unsigned int>)));

	//复原状态
	connect(m_pSourceTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pDescTableWgt, SLOT(Slot_setRecoverState(QList<unsigned int>)));

	connect(m_pDoubleSourceTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pDoubleDescTableWgt, SLOT(Slot_setRecoverState(QList<unsigned int>)));

	connect(m_pAnalogSourceTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pAnalogDescTableWgt, SLOT(Slot_setRecoverState(QList<unsigned int>)));
	connect(m_pKwhSourceTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pKwhDescTableWgt, SLOT(Slot_setRecoverState(QList<unsigned int>)));
	connect(m_pControlSourceTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pControlDescTableWgt, SLOT(Slot_setRecoverState(QList<unsigned int>)));
    //虚遥信
    connect(m_pVirtualSourceTableWgt, SIGNAL(Signal_ExistListID(QList<unsigned int>)), m_pVirtualDescTableWgt, SLOT(Slot_setRecoverState(QList<unsigned int>)));

	SetWgtLayout();
}

/*! \fn CChoosePointsWgt::SetWgtLayout()
*********************************************************************************************************
** \brief CChoosePointsWgt::SetWgtLayout()
** \details   设置页面布局
** \param 
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::SetWgtLayout()
{
	//创建wgt布局
	QHBoxLayout *pWgtLayout = new QHBoxLayout(this);
	pWgtLayout->addWidget(m_pTabWgt);
	//创建遥信widget
	QWidget *pBinaryWgt = new QWidget(this);
	QHBoxLayout *pBinayLayout = new QHBoxLayout(pBinaryWgt);

	pBinayLayout->addWidget(m_pDescTableWgt);
	pBinayLayout->addWidget(m_pSourceTableWgt);
	//创建双点遥信
	QWidget *pDoubleBinaryWgt = new QWidget(this);
	QHBoxLayout *pDoubleBinayLayout = new QHBoxLayout(pDoubleBinaryWgt);

	pDoubleBinayLayout->addWidget(m_pDoubleDescTableWgt);
	pDoubleBinayLayout->addWidget(m_pDoubleSourceTableWgt);

	//创建遥测widgets
	QWidget *pAnalogWgt = new QWidget(this);
	QHBoxLayout *pAnalogLayout = new QHBoxLayout(pAnalogWgt);

	pAnalogLayout->addWidget(m_pAnalogDescTableWgt);
	pAnalogLayout->addWidget(m_pAnalogSourceTableWgt);

	//创建遥脉widget
	QWidget *pKwhWgt = new QWidget(this);
	QHBoxLayout *pKwhLayout = new QHBoxLayout(pKwhWgt);

	pKwhLayout->addWidget(m_pKwhDescTableWgt);
	pKwhLayout->addWidget(m_pKwhSourceTableWgt);

	//创建遥控widget
	QWidget *pControlWgt = new QWidget(this);
	QHBoxLayout *pControlLayout = new QHBoxLayout(pControlWgt);

	pControlLayout->addWidget(m_pControlDescTableWgt);
	pControlLayout->addWidget(m_pControlSourceTableWgt);

    //创建虚遥信
    QWidget *pVirutalWgt = new QWidget(this);
    QHBoxLayout *pVirutallayout = new QHBoxLayout(pVirutalWgt);

    pVirutallayout->addWidget(m_pVirtualDescTableWgt);
    pVirutallayout->addWidget(m_pVirtualSourceTableWgt);

	m_pTabWgt->addTab(pBinaryWgt, tr("Binary Point"));
	m_pTabWgt->addTab(pDoubleBinaryWgt, QStringLiteral("双点遥信"));
	m_pTabWgt->addTab(pAnalogWgt, tr("Analog Point"));
	m_pTabWgt->addTab(pKwhWgt, tr("Kwh Point"));
	m_pTabWgt->addTab(pControlWgt, tr("Control Point"));
    m_pTabWgt->addTab(pVirutalWgt,tr("Virtual Binary"));
}

/*! \fn InitWgt(CRemotePonitTableAnalyse *pPointAnalyse)
*********************************************************************************************************
** \brief InitWgt(CRemotePonitTableAnalyse *pPointAnalyse)
** \details   初始化点表内容
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::InitWgt(CFciFile *pPointAnalyse)
{
	//清空数据
	m_pDescTableWgt->ClearAllData();
	m_pSourceTableWgt->ClearAllData();

	m_pDoubleDescTableWgt->ClearAllData();
	m_pDoubleSourceTableWgt->ClearAllData();

	m_pAnalogDescTableWgt->ClearAllData();
	m_pAnalogSourceTableWgt->ClearAllData();
	m_pKwhDescTableWgt->ClearAllData();
	m_pKwhSourceTableWgt->ClearAllData();
	m_pControlDescTableWgt->ClearAllData();
	m_pControlSourceTableWgt->ClearAllData();

    m_pVirtualSourceTableWgt->ClearAllData();
    m_pVirtualDescTableWgt->ClearAllData();

	m_pPointTableAnalyse = pPointAnalyse;

	if (!InsertDataToTable())
	{
		return;
	}

	Slot_UpdateBinaryPointData();
	Slot_UpdateAnalogPointData();
	Slot_UpdateKwhPointData();
	Slot_UpdateControlPointData();
}


/*! \fn Slot_UpdateBinaryPointData()
*********************************************************************************************************
** \brief Slot_UpdateBinaryPointData()
** \details   更新遥信测点
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::Slot_UpdateBinaryPointData()
{
	Q_ASSERT(m_pPointInfo);
	if (m_pPointInfo == NULL)
	{
		return;
	}

	m_pPointInfo->SetBinaryMap(m_pDescTableWgt->GetCurrentTableData());
}

void CChoosePointsWgt::Slot_UpdateDoubleBinaryPointData()
{
	Q_ASSERT(m_pPointInfo);
	if (m_pPointInfo == NULL)
	{
		return;
	}

	m_pPointInfo->SetDoubleBinaryMap(m_pDoubleDescTableWgt->GetCurrentTableData());

}

/*! \fn Slot_UpdateAnalogPointData()
*********************************************************************************************************
** \brief Slot_UpdateAnalogPointData()
** \details   更新遥测测点
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::Slot_UpdateAnalogPointData()
{
	Q_ASSERT(m_pPointInfo);
	if (m_pPointInfo == NULL)
	{
		return;
	}

	m_pPointInfo->SetAnalogMap(m_pAnalogDescTableWgt->GetCurrentTableData());
}

/*! \fn Slot_UpdateKwhPointData()
*********************************************************************************************************
** \brief Slot_UpdateKwhPointData()
** \details   更新遥脉测点信息
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::Slot_UpdateKwhPointData()
{
	Q_ASSERT(m_pPointInfo);
	if (m_pPointInfo == NULL)
	{
		return;
	}

	m_pPointInfo->SetKwhMap(m_pKwhDescTableWgt->GetCurrentTableData());
}

/*! \fn Slot_UpdateControlPointData()
*********************************************************************************************************
** \brief Slot_UpdateControlPointData()
** \details   更新遥控测点信息
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::Slot_UpdateControlPointData()
{
	Q_ASSERT(m_pPointInfo);
	if (m_pPointInfo == NULL)
	{
		return;
	}

	m_pPointInfo->SetControlMap(m_pControlDescTableWgt->GetCurrentTableData());
}

/*! \fn InsertDataToTable()
*********************************************************************************************************
** \brief InsertDataToTable()
** \details   往表格中插入数据
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
bool CChoosePointsWgt::InsertDataToTable()
{
	//清空数据
	m_pDescTableWgt->clearContents();
	m_pDescTableWgt->setRowCount(0);

	m_pDoubleDescTableWgt->clearContents();
	m_pDoubleDescTableWgt->setRowCount(0);

	m_pDoubleSourceTableWgt->clearContents();
	m_pDoubleSourceTableWgt->setRowCount(0);

	m_pSourceTableWgt->clearContents();
	m_pSourceTableWgt->setRowCount(0);

    m_pVirtualSourceTableWgt->clearContents();
    m_pVirtualSourceTableWgt->setRowCount(0);

    m_pVirtualDescTableWgt->clearContents();
    m_pVirtualDescTableWgt->setRowCount(0);

	m_pAnalogDescTableWgt->clearContents();
	m_pAnalogDescTableWgt->setRowCount(0);

	m_pAnalogSourceTableWgt->clearContents();
	m_pAnalogSourceTableWgt->setRowCount(0);

	m_pKwhDescTableWgt->clearContents();
	m_pKwhDescTableWgt->setRowCount(0);

	m_pKwhSourceTableWgt->clearContents();
	m_pKwhSourceTableWgt->setRowCount(0);

	m_pControlDescTableWgt->clearContents();
	m_pControlDescTableWgt->setRowCount(0);

	m_pControlSourceTableWgt->clearContents();
	m_pControlSourceTableWgt->setRowCount(0);

	if (!GetBinaryPoints())
	{
		return false;
	}

	if (!GetDoubleBinaryPoints())
	{
		return false;
	}

	if (!GetAnalogPoints())
	{
		return false;
	}

	if (!GetKwhPoints())
	{
		return false;
	}

	if (!GetControlPoints())
	{
		return false;
	}

	return true;
}

/*! \fn GetBinaryPoints()
*********************************************************************************************************
** \brief GetBinaryPoints()
** \details   获取遥信点表信息
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
bool CChoosePointsWgt::GetBinaryPoints()
{
	//获取遥信数据
	std::vector <RPT_DEF> lstBinaryRpt;
	bool bRet = m_pPointTableAnalyse->GetYXArryInfo(lstBinaryRpt);

	//填充数据  遥信
	for (int i = 0; i < lstBinaryRpt.size(); i++)
	{
		QTableWidgetItem *item0 = new QTableWidgetItem;
		item0->setText(QString::number(lstBinaryRpt.at(i)->OccNO));
		item0->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item1 = new QTableWidgetItem;
		item1->setText(lstBinaryRpt.at(i)->InnerAddr);
		item1->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item2 = new QTableWidgetItem;
		item2->setText(lstBinaryRpt.at(i)->Address);
		item2->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item3 = new QTableWidgetItem;
		item3->setText(lstBinaryRpt.at(i)->Desccription);
		item3->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item4 = new QTableWidgetItem;
		item4->setText(lstBinaryRpt.at(i)->Name);
		item4->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item41 = new QTableWidgetItem;

		m_pSourceTableWgt->insertRow(i);
		m_pSourceTableWgt->setItem(i, 0, item0);
		m_pSourceTableWgt->setItem(i, 1, item1);
		m_pSourceTableWgt->setItem(i, 2, item2);
		m_pSourceTableWgt->setItem(i, 3, item4);
		m_pSourceTableWgt->setItem(i, 4, item3);
		m_pSourceTableWgt->setItem(i, 5, item41);

        //虚遥信内容和遥信相同
        QTableWidgetItem *item5= new QTableWidgetItem;
        item5->setText(QString::number(lstBinaryRpt.at(i)->OccNO));
		item5->setTextAlignment(Qt::AlignLeft);

        QTableWidgetItem *item6 = new QTableWidgetItem;
        item6->setText(lstBinaryRpt.at(i)->Address);
		item6->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item7 = new QTableWidgetItem;
		item7->setText(lstBinaryRpt.at(i)->InnerAddr);
		item7->setTextAlignment(Qt::AlignLeft);

        QTableWidgetItem *item8 = new QTableWidgetItem;
        item8->setText(lstBinaryRpt.at(i)->Desccription);
		item8->setTextAlignment(Qt::AlignLeft);

        QTableWidgetItem *item9 = new QTableWidgetItem;
		item9->setText(lstBinaryRpt.at(i)->Name);
		item9->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item10 = new QTableWidgetItem;

        m_pVirtualSourceTableWgt->insertRow(i);
        m_pVirtualSourceTableWgt->setItem(i, 0, item5);
        m_pVirtualSourceTableWgt->setItem(i, 1, item6);
        m_pVirtualSourceTableWgt->setItem(i, 2, item7);
        m_pVirtualSourceTableWgt->setItem(i, 3, item9);
		m_pVirtualSourceTableWgt->setItem(i, 4, item8);
		m_pVirtualSourceTableWgt->setItem(i, 5, item10);
	}

	return true;
}

//双点遥信
bool CChoosePointsWgt::GetDoubleBinaryPoints()
{
	std::vector<RPT_DEF>lstBinaryRpt;
	bool bRet = m_pPointTableAnalyse->GetYXArryInfo(lstBinaryRpt);
	//填充数据  遥信
	for (int i = 0; i < lstBinaryRpt.size(); i++)
	{
		QTableWidgetItem *item0 = new QTableWidgetItem;
		item0->setText(QString::number(lstBinaryRpt.at(i)->OccNO));
		item0->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item1 = new QTableWidgetItem;
		item1->setText(lstBinaryRpt.at(i)->InnerAddr);
		item1->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item2 = new QTableWidgetItem;
		item2->setText(lstBinaryRpt.at(i)->Address);
		item2->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item3 = new QTableWidgetItem;
		item3->setText(lstBinaryRpt.at(i)->Name);
		item3->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item4 = new QTableWidgetItem;
		item4->setText(lstBinaryRpt.at(i)->Desccription);
		item4->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item5 = new QTableWidgetItem;

		m_pDoubleSourceTableWgt->insertRow(i);
		m_pDoubleSourceTableWgt->setItem(i, 0, item0);
		m_pDoubleSourceTableWgt->setItem(i, 1, item1);
		m_pDoubleSourceTableWgt->setItem(i, 2, item2);
		m_pDoubleSourceTableWgt->setItem(i, 3, item3);
		m_pDoubleSourceTableWgt->setItem(i, 4, item4);
		m_pDoubleSourceTableWgt->setItem(i, 5, item5);
	}

	return true;
}

/*! \fn GetAnalogPoints()
*********************************************************************************************************
** \brief GetAnalogPoints()
** \details   获取遥测点表信息
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
bool CChoosePointsWgt::GetAnalogPoints()
{
	//获取遥信数据
	std::vector<RPT_DEF>lstAnalogRpt;
	bool bRet = m_pPointTableAnalyse->GetYcArryInfo(lstAnalogRpt);
	//填充数据  遥信
	for (int i = 0; i < lstAnalogRpt.size(); i++)
	{
		QTableWidgetItem *item0 = new QTableWidgetItem;
		item0->setText(QString::number(lstAnalogRpt.at(i)->OccNO));
		item0->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item1 = new QTableWidgetItem;
		item1->setText(lstAnalogRpt.at(i)->InnerAddr);
		item1->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item2 = new QTableWidgetItem;
		item2->setText(lstAnalogRpt.at(i)->Address);
		item2->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item3 = new QTableWidgetItem;
		item3->setText(lstAnalogRpt.at(i)->Desccription);
		item3->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item4 = new QTableWidgetItem;
		item4->setText(lstAnalogRpt.at(i)->Name);
		item4->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item5 = new QTableWidgetItem;
		item5->setText(QString::number(lstAnalogRpt.at(i)->MinValue));
		item5->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item6 = new QTableWidgetItem;
		item6->setText(QString::number(lstAnalogRpt.at(i)->MaxValue));
		item6->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item7 = new QTableWidgetItem;
		item7->setText(QString::number(lstAnalogRpt.at(i)->KRate));
		item7->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item8 = new QTableWidgetItem;
		item8->setText(lstAnalogRpt.at(i)->Unit);
		item8->setTextAlignment(Qt::AlignLeft);

		m_pAnalogSourceTableWgt->insertRow(i);
		m_pAnalogSourceTableWgt->setItem(i, 0, item0);
		m_pAnalogSourceTableWgt->setItem(i, 1, item1);
		m_pAnalogSourceTableWgt->setItem(i, 2, item2);
		m_pAnalogSourceTableWgt->setItem(i, 3, item4);

		m_pAnalogSourceTableWgt->setItem(i, 4, item3);
		m_pAnalogSourceTableWgt->setItem(i, 5, item5);
		m_pAnalogSourceTableWgt->setItem(i, 6, item6);
		m_pAnalogSourceTableWgt->setItem(i, 7, item7);
		m_pAnalogSourceTableWgt->setItem(i, 8, item8);
	}

	return true;
}

/*! \fn GetKwhPoints()
*********************************************************************************************************
** \brief GetKwhPoints()
** \details   获取遥脉点表信息
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
bool CChoosePointsWgt::GetKwhPoints()
{
	return true;
}

/*! \fn GetControlPoints()
*********************************************************************************************************
** \brief GetControlPoints()
** \details   获取遥控点表信息
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
bool CChoosePointsWgt::GetControlPoints()
{
	//获取遥信数据
	std::vector <RPT_DEF > lstControlRpt;
	bool bRet = m_pPointTableAnalyse->GetYKArryInfo(lstControlRpt);
	//填充数据  遥信
	for (int i = 0; i < lstControlRpt.size(); i++)
	{
		QTableWidgetItem *item0 = new QTableWidgetItem;
		item0->setText(QString::number(lstControlRpt.at(i)->OccNO));
		item0->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item1 = new QTableWidgetItem;
		item1->setText(lstControlRpt.at(i)->InnerAddr);
		item1->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item2 = new QTableWidgetItem;
		item2->setText(lstControlRpt.at(i)->Address);
		item2->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item3 = new QTableWidgetItem;
		item3->setText(lstControlRpt.at(i)->Name);
		item3->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item4 = new QTableWidgetItem;
		item4->setText(lstControlRpt.at(i)->Desccription);
		item4->setTextAlignment(Qt::AlignLeft);

		QTableWidgetItem *item5 = new QTableWidgetItem;

		m_pControlSourceTableWgt->insertRow(i);
		m_pControlSourceTableWgt->setItem(i, 0, item0);
		m_pControlSourceTableWgt->setItem(i, 1, item1);
		m_pControlSourceTableWgt->setItem(i, 2, item2);
		m_pControlSourceTableWgt->setItem(i, 3, item3);
		m_pControlSourceTableWgt->setItem(i, 4, item4);
		m_pControlSourceTableWgt->setItem(i, 5, item5);
	}

	return true;
}

CChoosePointsWgt::~CChoosePointsWgt()
{
}

/*! \fn Slot_UpdateAllChoosePoints(const QString &strFilename)
*********************************************************************************************************
** \brief Slot_UpdateAllChoosePoints(const QString &strFilename)
** \details   更新所有的点
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::Slot_UpdateAllChoosePoints(const QString &strFilename)
{
	return;
    m_pCurrentPoints->InitData(strFilename);

    m_pDescTableWgt->clearContents();
    m_pDescTableWgt->setRowCount(0);

	m_pDoubleDescTableWgt->clearContents();
	m_pDoubleDescTableWgt->setRowCount(0);

    m_pAnalogDescTableWgt->clearContents();
    m_pAnalogDescTableWgt->setRowCount(0);

    m_pKwhDescTableWgt->clearContents();
    m_pKwhDescTableWgt->setRowCount(0);

    m_pControlDescTableWgt->clearContents();
    m_pControlDescTableWgt->setRowCount(0);


    Slot_UpdateBinaryPointData();
	//双点遥信
	Slot_UpdateDoubleBinaryPointData();
    Slot_UpdateAnalogPointData();
    Slot_UpdateKwhPointData();
    Slot_UpdateControlPointData();
    
}

/*! \fn UpdateToDesTables(RPT rptInfo, CDragTableWgt *pDesTableWgt)
*********************************************************************************************************
** \brief UpdateToDesTables(RPT rptInfo, CDragTableWgt *pDesTableWgt)
** \details   更新表中的值
** \param
** \return
** \author xingzhibing
** \date 2016年09月27日
** \note
********************************************************************************************************/
void CChoosePointsWgt::UpdateToDesTables(RPT rptInfo, CDragTableWgt *pDesTableWgt)
{
    if (pDesTableWgt == nullptr)
    {
        return;
    }

    int nRowCount = pDesTableWgt->rowCount();

    QTableWidgetItem *item0 = new QTableWidgetItem;

    item0->setText(QString::number(nRowCount));
        
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText(QString::number(rptInfo.OccNO));

    QTableWidgetItem *item2 = new QTableWidgetItem;  
    item2->setText(rptInfo.InnerAddr);

    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(rptInfo.Address);

    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setText(rptInfo.Desccription);

    pDesTableWgt->insertRow(nRowCount);
    pDesTableWgt->setItem(nRowCount, 0, item0);
    pDesTableWgt->setItem(nRowCount, 1, item1);
    pDesTableWgt->setItem(nRowCount, 2, item2);
    pDesTableWgt->setItem(nRowCount, 3, item3);
    pDesTableWgt->setItem(nRowCount, 4, item4);
}

void CChoosePointsWgt::UpdateAnalogToDesTables(RPT rptInfo, CAnalogDragTableWgt * pDesTableWgt)
{
	if (pDesTableWgt == nullptr)
	{
		return;
	}

	int nRowCount = pDesTableWgt->rowCount();

	QTableWidgetItem *item0 = new QTableWidgetItem;

	item0->setText(QString::number(nRowCount));

	QTableWidgetItem *item1 = new QTableWidgetItem;
	item1->setText(QString::number(rptInfo.OccNO ));

	QTableWidgetItem *item2 = new QTableWidgetItem;
	item2->setText(rptInfo.InnerAddr);

	QTableWidgetItem *item3 = new QTableWidgetItem;
	item3->setText(rptInfo.Address);

	QTableWidgetItem *item4 = new QTableWidgetItem;
	item4->setText(rptInfo.Desccription);

	QTableWidgetItem *item5 = new QTableWidgetItem;
	

	QTableWidgetItem *item6 = new QTableWidgetItem;
	

	QTableWidgetItem *item7 = new QTableWidgetItem;
	

	QTableWidgetItem *item8 = new QTableWidgetItem;
	

	QTableWidgetItem *item9 = new QTableWidgetItem;
	

	if (m_pCurrentPoints->GetDoorDatas().contains(rptInfo.OccNO))
	{
		item5->setText(QString::number(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].MinValue));
		item6->setText(QString::number(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].MaxValue));
		item7->setText(QString::number(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].KRate));
		item8->setText(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].Unit);
	}
	else
	{
		item5->setText(QString::number(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].MinValue));
		item6->setText(QString::number(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].MaxValue));
		item7->setText(QString::number(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].KRate));
		item8->setText(m_pCurrentPoints->GetDoorDatas()[rptInfo.OccNO].Unit);
	}

	pDesTableWgt->insertRow(nRowCount);
	pDesTableWgt->setItem(nRowCount, 0, item0);
	pDesTableWgt->setItem(nRowCount, 1, item1);
	pDesTableWgt->setItem(nRowCount, 2, item2);
	pDesTableWgt->setItem(nRowCount, 3, item3);
	pDesTableWgt->setItem(nRowCount, 4, item4);

	pDesTableWgt->setItem(nRowCount, 5, item5);
	pDesTableWgt->setItem(nRowCount, 6, item6);
	pDesTableWgt->setItem(nRowCount, 7, item7);
	pDesTableWgt->setItem(nRowCount, 8, item8);
	pDesTableWgt->setItem(nRowCount, 9, item9);

}

QMap<int, QString> CChoosePointsWgt::GetRemoteToDesc()
{
    QMap<int, QString> mapInfo;
    for (int i = 0; i < m_pDescTableWgt->rowCount(); i++)
    {
        mapInfo.insert(m_pDescTableWgt->item(i, 0)->text().toInt(), m_pDescTableWgt->item(i, 3)->text());
    }
    return mapInfo;
}

void CChoosePointsWgt::SetProjectPath(const QString &strPath)
{
    m_pVirtualDescTableWgt->SetSaveFileName(strPath);
}

void CChoosePointsWgt::SaveChooseBinFile(const QString &strFilename)
{
    if (strFilename.isEmpty())
    {
        return;
    }

    QFile file(strFilename);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Warning"), file.errorString());
        return;
    }

    //遥信
    for (int i = 0; i < m_pDescTableWgt->rowCount(); i++)
    {
		if (i == 0)
		{
			file.write("引用表类型=YX\n");
			file.write("引用表数目=" + QByteArray(QString::number(m_pDescTableWgt->rowCount()).toStdString().c_str()) + "\n");
		}


        int nDeviceNum = m_pDescTableWgt->item(i, 1)->text().toInt();
    
		file.write(QByteArray(QString::number(i+1).toStdString().c_str()) + "," + 
			QByteArray(QString::number(nDeviceNum).toStdString().c_str()) + QByteArray("\n"));
    }

	//双点遥信
	for (int i = 0; i < m_pDoubleDescTableWgt->rowCount(); i++)
	{
		if (i == 0)
		{
			file.write("引用表类型=DYX\n");
			file.write("引用表数目=" + QByteArray(QString::number(m_pDoubleDescTableWgt->rowCount()).toStdString().c_str()) + "\n");
		}


		int nDeviceNum = m_pDoubleDescTableWgt->item(i, 1)->text().toInt();
		// int nDeviceGroup = m_pPointTableAnalyse->GetBinaryIdGroup()[nDeviceNum].GroupNum;
		//nDeviceNum = m_pPointTableAnalyse->GetBinaryIdGroup()[nDeviceNum].NUM;


		file.write(QByteArray(QString::number(i + 1).toStdString().c_str()) + "," +
			QByteArray(QString::number(nDeviceNum).toStdString().c_str()) + QByteArray("\n"));
	}

    //遥测
    for (int i = 0; i < m_pAnalogDescTableWgt->rowCount(); i++)
    {
		if (i == 0)
		{
			file.write("引用表类型=YC\n");
			file.write("引用表数目=" + QByteArray(QString::number(m_pAnalogDescTableWgt->rowCount()).toStdString().c_str()) + "\n");
		}

		int nDeviceNum = m_pAnalogDescTableWgt->item(i, 1)->text().toInt();

		float fB = m_pAnalogDescTableWgt->item(i, 5)->text().toFloat();
		float fk = m_pAnalogDescTableWgt->item(i, 6)->text().toFloat();
		float fUp = m_pAnalogDescTableWgt->item(i, 7)->text().toFloat();
		float fDown = m_pAnalogDescTableWgt->item(i, 8)->text().toFloat();
		float fThreshold = m_pAnalogDescTableWgt->item(i, 9)->text().toFloat();

		file.write(QByteArray(QString::number(i + 1).toStdString().c_str()) + "," +
			QByteArray(QString::number(nDeviceNum).toStdString().c_str()) +  "," + 
			QByteArray(QString::number(fB).toStdString().c_str()) + "," +
			QByteArray(QString::number(fk).toStdString().c_str()) + "," +
			QByteArray(QString::number(fUp).toStdString().c_str()) + "," +
			QByteArray(QString::number(fDown).toStdString().c_str()) + "," +
			QByteArray(QString::number(fThreshold).toStdString().c_str()) + "\n");
	}

    //遥脉
    for (int i = 0; i < m_pKwhDescTableWgt->rowCount(); i++)
    {
		if (i == 0)
		{
			file.write("引用表类型=YM\n");
			file.write("引用表数目=" + QByteArray(QString::number(m_pKwhDescTableWgt->rowCount()).toStdString().c_str()) + QByteArray("\n"));
		}

		int nDeviceNum = m_pKwhDescTableWgt->item(i, 1)->text().toInt();

		file.write(QByteArray(QString::number(i + 1).toStdString().c_str()) + "," +
			QByteArray(QString::number(nDeviceNum).toStdString().c_str()) + "\n");
	}

    //遥控
    for (int i = 0; i < m_pControlDescTableWgt->rowCount(); i++)
    {
		if (i == 0)
		{
			file.write("引用表类型=YK\n");
			file.write("引用表数目=" + QByteArray(QString::number(m_pControlDescTableWgt->rowCount()).toStdString().c_str()) + QByteArray("\n"));
		}

		int nDeviceNum = m_pControlDescTableWgt->item(i, 1)->text().toInt();

		file.write(QByteArray(QString::number(i + 1).toStdString().c_str()) + "," +
			QByteArray(QString::number(nDeviceNum).toStdString().c_str()) + "\n");
	}

    file.close();
    QMessageBox::information(this, tr("Success"), tr("Save Success!"));
}
