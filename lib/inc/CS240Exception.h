#ifndef CS240_EXCEPTION_H
#define CS240_EXCEPTION_H

#include <string>

using namespace std;

class CS240Exception {
 protected:
  std::string message;

 public:
  CS240Exception() : message("Unknown Error") {
    return;
  }
  CS240Exception(const string & msg) : message(msg) {
    return;
  }
  CS240Exception(const CS240Exception & e) : message(e.message) {
    return;
  }
  ~CS240Exception() {
    return;
  }
  const string & GetMessage() {
    return message;
  }
};


class InvalidArgumentException : public CS240Exception {
 public:
  InvalidArgumentException() : CS240Exception("Invalid Argument") {
    return;
  }
  InvalidArgumentException(const string & msg):	CS240Exception(string("Invalid Argument: ") +
															   msg) {
    return;
  }
  InvalidArgumentException(const InvalidArgumentException & e) : CS240Exception(e) {
    return;
  }
  ~InvalidArgumentException() {
    return;
  }
};


class InvalidURLException : public CS240Exception {
 public:
  InvalidURLException() : CS240Exception("Invalid URL") {
    return;
  }
  InvalidURLException(const string & msg) : CS240Exception(string("Invalid URL: ") + msg) {
    return;
  }
  InvalidURLException(const InvalidURLException & e) : CS240Exception(e) {
    return;
  }
  ~InvalidURLException() {
    return;
  }
};


class IllegalStateException : public CS240Exception {
 public:
  IllegalStateException() : CS240Exception("Illegal State") {
    return;
  }
  IllegalStateException(const string & msg) : CS240Exception(string("Illegal State: ") + msg) {
    return;
  }
  IllegalStateException(const IllegalStateException & e) : CS240Exception(e) {
    return;
  }
  ~IllegalStateException() {
    return;
  }
};


class IOException : public CS240Exception {
 public:
  IOException() : CS240Exception("I/O Error") {
    return;
  }
  IOException(const string & msg) : CS240Exception(string("I/O Error: ") + msg) {
    return;
  }
  IOException(const IOException & e) : CS240Exception(e) {
    return;
  }
  ~IOException() {
    return;
  }
};


class NetworkException : public CS240Exception {
 public:
  NetworkException() : CS240Exception("Network Error") {
    return;
  }
  NetworkException(const string & msg) : CS240Exception(string("Network Error: ") + msg) {
    return;
  }
  NetworkException(const NetworkException & e) : CS240Exception(e) {
    return;
  }
  ~NetworkException() {
    return;
  }
};


class FileException : public CS240Exception {
 public:
  FileException() : CS240Exception("File Error") {
    return;
  }
  FileException(const string & msg) : CS240Exception(string("File Error: ") + msg) {
    return;
  }
  FileException(const FileException & e) : CS240Exception(e) {
    return;
  }
  ~FileException() {
    return;
  }
};



#endif
