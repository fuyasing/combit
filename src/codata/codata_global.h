#ifndef CODATA_GLOBAL_H
#define CODATA_GLOBAL_H

#include <QtCore/qglobal.h>
#include "version_codata.h"

#if defined(CODATA_LIBRARY)
#  define CODATA_EXPORT Q_DECL_EXPORT
#else
#  define CODATA_EXPORT Q_DECL_IMPORT
#endif

#endif // CODATA_GLOBAL_H
