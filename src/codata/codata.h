#ifndef CODATA_H
#define CODATA_H

#include "codata_global.h"

#include <QObject>

class CODATA_EXPORT CoData : public QObject
{
  Q_OBJECT
  
  public:
    CoData();
    ~CoData();
};

#endif // CODATA_H
