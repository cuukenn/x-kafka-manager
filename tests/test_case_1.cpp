#include <iostream>
#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>
// #include <zookeeper/zookeeper.h>
int main(int, char **)
{
    try
    {
        std::string err_str;
        auto conf = RdKafka::Conf::create(RdKafka::Conf::ConfType::CONF_GLOBAL);
        conf->set("bootstrap.servers", "127.0.0.1:9092", err_str);
        conf->set("group.id", "default", err_str);
        RdKafka::KafkaConsumer *m_consumer = RdKafka::KafkaConsumer::create(conf, err_str);
        if (!m_consumer)
        {
            std::cerr << "Connect To Kafka Fialed: " << err_str << std::endl;
            return -1;
        }
        RdKafka::Metadata *metadataMap = nullptr;
        auto code = m_consumer->metadata(true, nullptr, &metadataMap, -1);
        if (code == RdKafka::ErrorCode::ERR_NO_ERROR)
        {
            const RdKafka::Metadata::TopicMetadataVector tmv = *(metadataMap->topics());
            std::cout << "Find Topic Size: " << tmv.size() << std::endl;
            for (const RdKafka::TopicMetadata *metadata : tmv)
            {
                std::cout << "Topic Name: " << metadata->topic()
                          << "Partitions Size: "
                          << metadata->partitions()->size()
                          << std::endl;
            }
        }
        else
        {
            std::cout << "Get MetaData Failed: " << RdKafka::err2str(code) << std::endl;
        }
        m_consumer->close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}