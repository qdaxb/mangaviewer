#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H
#include "common.h"
#include <QString>
#include <QList>
#include <QMap>
#include <QtXml/QDomDocument>
#include "viewercommand.h"
class QxtGlobalShortcut;
class QGraphicsManagaView;
class ShortcutManager:public QObject,public Singleton<ShortcutManager>
{
Q_OBJECT
public:
    void loadFromXmlFile(QString fileName);
    void saveToXmlFile(QString file);
    void updateShortcut(QString keySequence,QString command);
    ViewerCommand *getCommand(QString shortcut);
    void setViewer(QGraphicsManagaView *viewer){mViewer=viewer;}
    ShortcutManager();
private:
    QMap<QString,ViewerCommand*> mShortcuts;
    QMap<QxtGlobalShortcut*,ViewerCommand*> mGlobalShortcuts;
    QGraphicsManagaView *mViewer;
private slots:
    void globalShortcutActived(QxtGlobalShortcut* shortcut);
};

#endif // SHORTCUTMANAGER_H
