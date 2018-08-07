#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("D:/wxb/myxmlstream/InputChan.xml");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug()<<"Error:cannot open file";
        return 1;
    }
    QXmlStreamReader reader;
    reader.setDevice(&file);
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType type=reader.readNext();
        if(type==QXmlStreamReader::StartDocument)
            qDebug()<<reader.documentEncoding()<<reader.documentVersion();
        if(type==QXmlStreamReader::StartElement)
        {
            qDebug()<<"<"<<reader.name()<<">";
            if(reader.attributes().hasAttribute("id"))
                qDebug()<<reader.attributes().value("id");
        }
        if(type==QXmlStreamReader::EndElement)
            qDebug()<<"<"<<reader.name()<<">";
        if(type==QXmlStreamReader::Characters&&!reader.isWhitespace())
            qDebug()<<reader.text();
    }
    if(reader.hasError())
    {
        qDebug()<<"error:"<<reader.errorString();
    }
    file.close();

    return a.exec();
}
