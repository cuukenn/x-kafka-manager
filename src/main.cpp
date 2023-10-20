#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include "context.h"

int main(int argc, char *argv[])
{
	try
	{
		QGuiApplication app(argc, argv);
		QQmlApplicationEngine engine;
		const QUrl url("qrc:/qml/main.qml");
		QObject::connect(
			&engine, &QQmlApplicationEngine::objectCreated,
			&app, [url](QObject *obj, const QUrl &objUrl)
			{
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1); },
			Qt::QueuedConnection);
		engine.rootContext()->setContextProperty("context", new Context);
		engine.load(url);

		return app.exec();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
}
