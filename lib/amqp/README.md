# offcenter_common_amqp

Simplifies connecting to and using an ActiveMQ server as well as processing ActiveMQ Messages.

## Examples

### [offcenter_amqp_example_process_message](https://github.com/CodeRancher/offcenter_common/blob/main/lib/amqp/example/src/process_amqp_message_example.cpp)
Illustrates how to create a ProcessAmqpMessageThread that will automatically process a received AMQP message. This is a stand-alone application that will create a thread that will listen for messages that are created on the main thread, then process the message.