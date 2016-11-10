#include <iostream>
#include <fstream>
#include <string>
#include "tyk/coprocess_object.pb.h"
using namespace std;

struct CoProcessMessage {
  void* p_data;
  int length;
};

void ProcessRequest_(struct CoProcessMessage* cp_object, struct CoProcessMessage* cp_output_object) {
  coprocess::Object object;

  char* input_data = (char*)cp_object->p_data;
  std::string str(input_data);
  object.ParseFromString(str);

  std::cout << object.DebugString() << std::endl;

  coprocess::MiniRequestObject* object_request;
  object_request = object.mutable_request();

  google::protobuf::Map<std::string, std::string>* set_headers;
  set_headers = object_request->mutable_set_headers();

  std::string header_name("cppheader");
  std::string header_value("cppheadervalue");

  (*set_headers)[header_name] = header_value;

  /*
  std::cout << "Modified object" << std::endl;
  std::cout << object.DebugString() << std::endl;
  */

  std::string modified_object_data;
  object.SerializeToString(&modified_object_data);

  int length = modified_object_data.length();
  const char* modified_object_data_p = modified_object_data.c_str();

  cp_output_object->p_data = malloc(length);
  memmove(cp_output_object->p_data, modified_object_data_p, length);
  cp_output_object->length = length;

}

extern "C" {
  #include <stdio.h>
  void ProcessRequest(struct CoProcessMessage* cp_object, struct CoProcessMessage* cp_output_object) {
    ProcessRequest_(cp_object, cp_output_object);
  }
}
