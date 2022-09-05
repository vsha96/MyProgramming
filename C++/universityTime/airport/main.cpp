#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//#include "airport.h"
#include "appengine.h"

//#include "testmodel.h"
#include "qairportmodel.h"
#include "qrequestsmodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

//    Airport model;
//    qmlRegisterType<Airport> ("Airport", 1, 0, "AirportModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    AppEngine appEngine(2);
//    appEngine.setNumberOfRunways(2);
    QAirportModel* runwaysListModel = appEngine.getAirportModel();
    QRequestsModel* requestsListModel = appEngine.getRequestsModel();
//    TestModel model(2);
//    appEngine.setTestModel(&model);

    engine.rootContext()->setContextProperty("app", &appEngine);
    engine.rootContext()->setContextProperty("runwaysListModel", runwaysListModel);
    engine.rootContext()->setContextProperty("requestsListModel", requestsListModel);

    engine.load(url);

    return app.exec();
}
