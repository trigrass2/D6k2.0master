#ifndef SCADAAPI_GLOBAL_H
#define SCADAAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SCADAAPI_LIBRARY)
#  define SCADAAPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define SCADAAPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SCADAAPI_GLOBAL_H
