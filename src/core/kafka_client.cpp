#include "kafka_client.h"
#include <iostream>
namespace XKafka
{
    KafkaClient::KafkaClient(server_conf_t &conf)
    {
        this->conf = conf;
        this->consumer = nullptr;
    }
    KafkaClient::~KafkaClient()
    {
    }
    bool KafkaClient::connect()
    {
        if (!this->isClose())
        {
            return true;
        }
        std::string err_str;
        auto conf = RdKafka::Conf::create(RdKafka::Conf::ConfType::CONF_GLOBAL);
        conf->set("bootstrap.servers", this->conf.bootstrap_servers, err_str);
        conf->set("group.id", this->conf.group_id, err_str);
        this->consumer = RdKafka::KafkaConsumer::create(conf, err_str);
        if (!this->consumer)
        {
            std::cerr << "Connect To Kafka Fialed: " << err_str << std::endl;
            return false;
        }
        return true;
    }
    bool KafkaClient::isClose()
    {
        return this->consumer == nullptr || this->consumer->closed();
    }
    void KafkaClient::close()
    {
        if (this->consumer != nullptr && !this->consumer->closed())
        {
            this->consumer->close();
        }
    }
    void KafkaClient::overview(overview_t &overview)
    {
        if (this->isClose())
        {
            return;
        }
        std::vector<topic_t> topics;
        this->topics(topics);
        size_t total_topic = topics.size();
        size_t total_partition = 0;
        for (topic_t t : topics)
        {
            total_partition += t.partition_size;
        }
        overview.total_topic_size = total_topic;
        overview.total_partition_size = total_partition;
    }
    void KafkaClient::topics(std::vector<topic_t> &topics)
    {
        if (this->isClose())
        {
            return;
        }
        RdKafka::Metadata *metadataMap = nullptr;
        auto code = this->consumer->metadata(true, nullptr, &metadataMap, -1);
        if (code != RdKafka::ErrorCode::ERR_NO_ERROR)
        {
            std::cerr << "Get MetaData Failed: " << RdKafka::err2str(code) << std::endl;
            return;
        }
        const RdKafka::Metadata::TopicMetadataVector tmv = *(metadataMap->topics());
        for (const RdKafka::TopicMetadata *metadata : tmv)
        {
            topics.push_back({metadata->topic(),
                              metadata->partitions()->size()});
        }
    }
    void KafkaClient::new_topic(char *topic_name, long partition_size)
    {
        rd_kafka_topic_new(this->consumer->c_ptr(), topic_name, nullptr);
    }
    void KafkaClient::delete_topic(rd_kafka_topic_t &topic_t)
    {
        rd_kafka_topic_destroy(&topic_t);
    }
}