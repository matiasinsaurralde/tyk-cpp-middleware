#!/bin/sh
g++ -c tyk/coprocess_common.pb.cc tyk/coprocess_object.pb.cc tyk/coprocess_return_overrides.pb.cc tyk/coprocess_session_state.pb.cc tyk/coprocess_mini_request_object.pb.cc
ar rvs coprocess.a coprocess_*.o
rm coprocess_*.o
g++ -shared -fPIC middleware.cpp coprocess.a -o middleware.so `pkg-config protobuf --cflags --libs`
rm coprocess.a
