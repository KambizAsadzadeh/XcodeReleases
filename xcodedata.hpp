#ifndef XCODEDATA_HPP
#define XCODEDATA_HPP

#include <QAbstractItemModel>
#include <QCoreApplication>
#include <QQmlEngine>
#include <QAbstractListModel>
#include <QQmlContext>

#define API_URL "https://xcodereleases.com/data.json"

class XcodeData final
{
public:
    XcodeData(
        const QString& version,
        const QString& release,
        const QString& build,
        const QString& released,
        const QString& requiredOs,
        const QString& link);

    ~XcodeData();

    Q_INVOKABLE void setData();

    Q_INVOKABLE void getData();

    Q_INVOKABLE QList<QObject*> dataList;

    QString version() const;
    QString release() const;
    QString build() const;
    QString released() const;
    QString requiresOs() const;
    QString link() const;


    void setVersion(const QString& val);
    void setRelease(const QString& val);
    void setBuild(const QString& val);
    void setReleased(const QString& val);
    void setRequiredOs(const QString& val);
    void setLink(const QString& val);

private:
    QString m_version;
    QString m_release;
    QString m_build;
    QString m_released;
    QString m_requiresOs;
    QString m_link;
};

class RoleEntryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // Define the role names to be used
    enum RoleNames {
        VersionRole = Qt::UserRole,
        ReleaseRole = Qt::UserRole+2,
        BuildRole = Qt::UserRole+3,
        ReleasedRole = Qt::UserRole+4,
        RequiresRole = Qt::UserRole+5,
        LinkRole = Qt::UserRole+6
    };

    explicit RoleEntryModel(QObject *parent = 0);
    ~RoleEntryModel();

    // QAbstractItemModel interface
public:
    void addXcodeData(const XcodeData& xcodeData);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QList<XcodeData> m_xcodeData;
    QHash<int, QByteArray> m_roleNames;
};

static void registerForQtQuick() {
    qmlRegisterType<RoleEntryModel>("QtXcodeDataModel", 1, 0, "XcodeDataModel");
}

Q_COREAPP_STARTUP_FUNCTION(registerForQtQuick)


#endif // XCODEDATA_HPP
