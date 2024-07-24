#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QValidator>
#include <QDoubleValidator>
#include <QDebug>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

class Validator : public QValidator
{
    Q_OBJECT
public:
    explicit Validator(QObject *parent = 0);

signals:

public slots:
public:
    QValidator::State validate(QString & input, int & pos) const;

};

#endif // VALIDATOR_H
