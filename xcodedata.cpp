#include "xcodedata.hpp"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

XcodeData::XcodeData(const QString& version,
                     const QString& release,
                     const QString& build,
                     const QString& released,
                     const QString& requiredOs,
                     const QString& link)
    : m_version(version)
    , m_release(release)
    , m_build(build)
    , m_released(released)
    , m_requiresOs(requiredOs)
    , m_link(link)
{

}

XcodeData::~XcodeData() {}


QString XcodeData::version() const
{
    return m_version;
}

QString XcodeData::release() const
{
    return m_release;
}

QString XcodeData::build() const
{
    return m_build;
}

QString XcodeData::released() const
{
    return m_released;
}

QString XcodeData::requiresOs() const
{
    return m_requiresOs;
}

QString XcodeData::link() const
{
    return m_link;
}

void XcodeData::setVersion(const QString& val)
{
    if (val != m_version) {
        m_version = val;
    }
}

void XcodeData::setRelease(const QString& var)
{
    if (var != m_release) {
        m_release = var;
    }
}

void XcodeData::setBuild(const QString& var)
{
    if (var != m_build) {
        m_build = var;
    }
}

void XcodeData::setReleased(const QString& var)
{
    if (var != m_released) {
        m_released = var;
    }
}

void XcodeData::setRequiredOs(const QString& var)
{
    if (var != m_requiresOs) {
        m_requiresOs = var;
    }
}

void XcodeData::setLink(const QString& var)
{
    if (var != m_link) {
        m_link = var;
    }
}

RoleEntryModel::RoleEntryModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames[VersionRole]   = "version";
    m_roleNames[ReleaseRole]   = "release";
    m_roleNames[BuildRole]     = "build";
    m_roleNames[ReleasedRole]  = "released";
    m_roleNames[RequiresRole]  = "requires";
    m_roleNames[LinkRole]      = "url";

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl(API_URL));
    QNetworkReply* reply = manager->get(request);


    connect(reply, &QNetworkReply::finished, [request, reply, this](){

        QString strReply = (QString)reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QString version;
        QString release;
        QString build;
        QString released;
        QString requiredOs;
        QString link;

        foreach (const QJsonValue& value, jsonResponse.array())
        {
            version     = value["version"]["number"].toString();
            release     = ""; //ToDo Fix...
            build       = value["version"]["build"].toString();
            released    = QString::number(value["date"]["year"].toInt()).append("/").append(QString::number(value["date"]["month"].toInt())).append("/").append(QString::number(value["date"]["day"].toInt()));
            requiredOs  = value["requires"].toString();

            for (const QJsonValue& l : value["links"]["download"].toObject())
            {
                link = l.toString("url");
            }
            addXcodeData(XcodeData(version, release, build, released, requiredOs, link));
        }
    });

}

RoleEntryModel::~RoleEntryModel()
{
}

void RoleEntryModel::addXcodeData(const XcodeData& xcodeData)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_xcodeData.append(xcodeData);
    endInsertRows();
}

int RoleEntryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_xcodeData.count();
}

QVariant RoleEntryModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_xcodeData.count()) {
        return QVariant();
    }    
    const XcodeData& xcodeData = m_xcodeData[index.row()];
    switch(role)
    {
    case VersionRole:   return xcodeData.version();
    case ReleaseRole:   return xcodeData.release();
    case BuildRole:     return xcodeData.build();
    case ReleasedRole:  return xcodeData.released();
    case RequiresRole:  return xcodeData.requiresOs();
    case LinkRole:      return xcodeData.link();
    }
    return QVariant();
}

QHash<int, QByteArray> RoleEntryModel::roleNames() const
{
    return m_roleNames;
}
