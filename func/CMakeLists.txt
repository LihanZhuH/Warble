cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Proto file path
get_filename_component(func_proto "../protos/func.proto" ABSOLUTE)
get_filename_component(func_proto_path "${func_proto}" PATH)

# func
set(func_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/func.pb.cc")
set(func_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/func.pb.h")
set(func_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/func.grpc.pb.cc")
set(func_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/func.grpc.pb.h")
add_custom_command(
      OUTPUT "${func_proto_srcs}" "${func_proto_hdrs}" "${func_grpc_srcs}" "${func_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${func_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${func_proto}"
      DEPENDS "${func_proto}")

# Compiles event_handler as a library
add_library(event_handler STATIC event_handler.cc event_handler.h)

# Google test
add_executable(event_handler_test event_handler_test.cc)
target_link_libraries(event_handler_test event_handler ${GLOG_LIBRARIES} gtest gtest_main "pthread")

add_executable(func_server "func_server.cc"
  ${func_proto_srcs}
  ${func_grpc_srcs})
target_link_libraries(func_server
  ${_GRPC_GRPCPP_UNSECURE}
  ${_PROTOBUF_LIBPROTOBUF}
  event_handler
  ${GLOG_LIBRARIES})