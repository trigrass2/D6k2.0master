/*! @file meta_object.cpp
<PRE>
********************************************************************************
模块名       :  对本节点的所有tagname进行管理
文件名       :  meta_object.cpp
文件实现功能 :
作者         :  LiJin
版本         :  V1.00
--------------------------------------------------------------------------------
备注         :  tagname按类型存于共享内存中
--------------------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容

********************************************************************************
</PRE>
*  @brief
*  @author LiJin
*  @version 1.0
*  @date    2016.09.23
*/


#include "meta_object.h"


CMetaObject::CMetaObject()
{

}
CMetaObject::~CMetaObject()
{
	m_arrStaticProps.clear();
	m_arrDynamicProps.clear();
	m_arrSubObjects.clear();
}

/** @}*/
