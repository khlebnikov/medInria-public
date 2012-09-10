// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "%1.h"
#include "%1Plugin.h"
#include "%1ToolBox.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// %1PluginPrivate
// /////////////////////////////////////////////////////////////////

class %1PluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * %1PluginPrivate::s_Name = "%1";

// /////////////////////////////////////////////////////////////////
// %1Plugin
// /////////////////////////////////////////////////////////////////

%1Plugin::%1Plugin(QObject *parent) : dtkPlugin(parent), d(new %1PluginPrivate)
{
    
}

%1Plugin::~%1Plugin(void)
{
    delete d;
    
    d = NULL;
}

bool %1Plugin::initialize(void)
{
    if(!%1::registered())
        dtkWarn() << "Unable to register %1 type";
    
    if ( !%1ToolBox::registered() )
        dtkWarn() << "Unable to register %1 toolbox";
    
    return true;
}

bool %1Plugin::uninitialize(void)
{
    return true;
}

QString %1Plugin::name(void) const
{
    return "%1Plugin";
}

QString %1Plugin::description(void) const
{
    return tr("%3");
}

QString %1Plugin::version(void) const
{
    return %2PLUGIN_VERSION;
}

QString %1Plugin::contact(void) const
{
    return "";
}

QStringList %1Plugin::authors(void) const
{
    QStringList list;
    return list;
}

QStringList %1Plugin::contributors(void) const
{
    QStringList list;
    return list;
}

QString %1Plugin::identifier(void) const
{
    return %1PluginPrivate::s_Name;
}


QStringList %1Plugin::tags(void) const
{
    return QStringList();
}

QStringList %1Plugin::types(void) const
{
    return QStringList() << "%1";
}
QStringList %1Plugin::dependencies(void) const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(%1Plugin, %1Plugin)
