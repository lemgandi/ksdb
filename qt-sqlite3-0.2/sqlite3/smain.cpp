/****************************************************************************
**
** Implementation of SQLite driver plugin
**
** Created : 031106
**
** Copyright (C) 1992-2003 Trolltech AS.  All rights reserved.
**
** This file is part of the sql module of the Qt GUI Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid Qt Enterprise Edition licenses may use this
** file in accordance with the Qt Commercial License Agreement provided
** with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#include <qsqldriverplugin.h>
#include "qsql_sqlite3.h"

class QSQLite3DriverPlugin : public QSqlDriverPlugin
{
public:
    QSQLite3DriverPlugin();

    QSqlDriver* create( const QString & );
    QStringList keys() const;
};

QSQLite3DriverPlugin::QSQLite3DriverPlugin()
    : QSqlDriverPlugin()
{
}

QSqlDriver* QSQLite3DriverPlugin::create( const QString &name )
{
    if ( name == "QSQLITE3" ) {
	QSQLite3Driver* driver = new QSQLite3Driver();
	return driver;
    }
    return 0;
}

QStringList QSQLite3DriverPlugin::keys() const
{
    QStringList l;
    l  << "QSQLITE3";
    return l;
}

Q_EXPORT_PLUGIN( QSQLite3DriverPlugin )
