#include "context.h"
Context::Context(QObject *parent) : QObject{parent}
{
    this->m_text = "This is a Test";
}
Context::~Context()
{
}