#ifndef __PROTOBUF_APP_CC__
#define __PROTOBUF_APP_CC__

#include "protobuf_app.h"

RxTx::RxTx()
{
}
RxTx::~RxTx()
{
}

int RxTx::transmit(int32_t channel) 
{
  unicloud::request_ req;

  req.clear_header();
  req.clear_data();
  fillToProtobuf(req);
  std::string toBeSent;
  toBeSent.clear();

  req.SerializeToString(&toBeSent);

  receive(toBeSent);
  return(0);
}

int RxTx::receive(std::string in)
{
  unicloud::request_ rsp;
  rsp.clear_header();
  rsp.clear_data();

  rsp.ParseFromString(in);
  fillFromProtobuf(rsp);
  return(0);
}

void RxTx::request(unicloud::request_ req)
{
  m_request = req;
}

unicloud::request_& RxTx::request()
{
  return(m_request);
}

void RxTx::fillToProtobuf(unicloud::request_& protoEnt)
{
  unicloud::header& hdr = *(protoEnt.mutable_header());
  /*! First part of Body */
  unicloud::payload& body = *(protoEnt.add_data());

  hdr.clear_sender();
  hdr.clear_receiver();
  hdr.clear_version();
  hdr.clear_payload_length();

  /*! populating the protobuf structure */
  hdr.set_version(1);
  hdr.mutable_sender()->set_task(1);
  hdr.mutable_sender()->set_node(1);
  hdr.mutable_sender()->set_proc(1);

  hdr.mutable_receiver()->set_task(2);
  hdr.mutable_receiver()->set_node(2);
  hdr.mutable_receiver()->set_proc(2);

  std::string dd("Hello World!");

  hdr.set_payload_length(dd.length());

  body.clear_data();
  body.set_length(dd.length());
  body.set_data(dd.c_str(), dd.length());
}

void RxTx::fillFromProtobuf(unicloud::request_& protoEnt)
{

    if(protoEnt.has_header()) {
      std::cout << "Header is filled" << std::endl;
    
        if(protoEnt.header().has_sender()) {
          std::cout << "Sender is filled ";
          std::cout << " Sender's task is " << protoEnt.header().sender().task();
          std::cout << " Sender's node is " << protoEnt.header().sender().node();
          std::cout << " Sender's proc is " << protoEnt.header().sender().proc() << std::endl;
        }

        if(protoEnt.header().has_receiver()) {
          std::cout << "Receiver is filled ";
          std::cout << " Receiver's task is " << protoEnt.header().receiver().task();
          std::cout << " Receiver's node is " << protoEnt.header().receiver().node();
          std::cout << " Receiver's proc is " << protoEnt.header().receiver().proc() << std::endl;
        }

        if(protoEnt.data_size()) {
	  for(int idx = 0; idx < protoEnt.data_size(); ++idx) {
            std::cout << "data_size is " << protoEnt.data_size() <<" filled " << std::endl;
	    std::cout << " The length is " << protoEnt.data(idx).length() << std::endl;
	    std::cout << " The data is " << protoEnt.data(idx).data() << std::endl;
	  }
        }
    }
}


int main(int argc, char* argv[])
{
  RxTx rx;
  rx.transmit(0);

  return(0);
}



#endif /* __PROTOBUF_APP_CC__ */
