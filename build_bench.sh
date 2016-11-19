#!/bin/sh
g++ bench.cpp coprocess.a -o bench `pkg-config protobuf-lite --cflags --libs` -lbenchmark
