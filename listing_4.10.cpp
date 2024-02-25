//Download by www.cctry.com
#include <future>
class connection_set  {};
void process_connections(connection_set& connections) {
    while(!done(connections)) {
        for(connection_iterator connection=connections.begin(),
          end=connections.end(); connection!=end; ++connection) {
            if(connection->has_incoming_data()) {
// For incoming packets, the data associated with the future is the payload of the data packet
                data_packet data=connection->incoming();
                std::promise<payload_type>& p = connection->get_promise(data.id);
                p.set_value(data.payload); // set value, receive success
            }
            if(connection->has_outgoing_data()) {
// the value associated with the future is a simple success/failure flag
                outgoing_packet data = connection->top_of_outgoing_queue();
                connection->send(data.payload);
                data.promise.set_value(true); // class of connection_set internal promise, send success
            }
        }
    }
}