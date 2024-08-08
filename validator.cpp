#include "validator.h"

Validator::Validator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State Validator::validate(QString &input, int &pos) const
{
    qDebug() << input<< pos;
    QRegularExpressionValidator reg(QRegularExpression("(([0-9]+)([\+|\\-|\*|\/]|[\.]))+"));
    input.remove(" ");
    if(input.contains(",,") || input.startsWith(","))
        return QValidator::Invalid;

    // QStringList list = input.split(",");
    // qDebug()<< list;

    bool isOk = true;

        int i = 0;
        if(reg.validate(input,i) == QValidator::Invalid)
            return QValidator::Invalid;
        if(reg.validate(input,i) == QValidator::Intermediate)
            isOk = false;
    if(isOk)
        return QValidator::Acceptable;
    else
        return QValidator::Intermediate;
}
