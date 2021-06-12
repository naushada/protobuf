#ifndef __PROTOBUF_APP_H__
#define __PROTOBUF_APP_H__

#include "protobuf_test.pb.h"

class RxTx {
  public:
    RxTx();
    ~RxTx();

    int transmit(int32_t channel);
    int receive(std::string in);
    unicloud::request_& request();
    void request(unicloud::request_ arg);
    void fillToProtobuf(unicloud::request_& protoEnt);
    void fillFromProtobuf(unicloud::request_& protoEnt);

  private:
    unicloud::request_ m_request; 

};






















#endif /* __PROTOBUF_APP_H__ */
