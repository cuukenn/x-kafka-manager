#pragma once
#include "kafka_client.h"
#include "context.h"
namespace XKafka
{
    class KafkaMonitor
    {
    private:
        KafkaClient kafka_client;

    public:
        KafkaMonitor(KafkaClient &kafka_client, Context &context);
        ~KafkaMonitor();
    };
}