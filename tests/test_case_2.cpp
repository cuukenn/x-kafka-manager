#include <iostream>
#include "kafka_client.h"
int main(int, char **)
{
    try
    {
        XKafka::server_conf_t conf{
            "127.0.0.1:9092",
            "default"};
        XKafka::KafkaClient kafkaClient{conf};
        kafkaClient.connect();
        XKafka::overview_t overview;
        kafkaClient.overview(overview);
        std::cout << "Bootstraps: " << overview.bootstrap_servers << std::endl
                  << "Topic Total Size: " << overview.total_topic_size << std::endl
                  << "Topic Total Partitions: " << overview.total_partition_size << std::endl;
        std::vector<XKafka::topic_t> topics;
        kafkaClient.topics(topics);
        std::cout << "Topics: " << std::endl;
        for (const XKafka::topic_t topic : topics)
        {
            std::cout
                << "-"
                << "  Topic Name: " << topic.name
                << std::endl
                << "   Partitions Size: "
                << topic.partition_size
                << std::endl;
        }
        kafkaClient.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}