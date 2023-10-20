#pragma once
#include <vector>
#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>
namespace XKafka
{
    typedef struct
    {
        std::string bootstrap_servers;
        std::string group_id;
    } server_conf_t;
    typedef struct
    {
        std::string bootstrap_servers;
        size_t total_topic_size;
        size_t total_partition_size;
    } overview_t;
    typedef struct
    {
        std::string name;
        size_t partition_size;
    } topic_t;
    class KafkaClient
    {
    private:
        server_conf_t conf;
        RdKafka::KafkaConsumer *consumer;

    public:
        KafkaClient(server_conf_t &conf);
        ~KafkaClient();
        bool connect();
        void close();
        bool isClose();
        /* get basic info */
        void overview(overview_t &ov);
        void topics(std::vector<topic_t> &vt);
        /* topic op */
        void new_topic(char *topic_name, long partition_size);
        void delete_topic(rd_kafka_topic_t &topic_t);
    };
}
