// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonVariant.hpp"

namespace ArduinoJson {

inline JsonVariant::JsonVariant(bool value) {
  using namespace Internals;
  _type = JSON_BOOLEAN;
  _content.asInteger = static_cast<JsonInteger>(value);
}

inline JsonVariant::JsonVariant(const char *value) {
  _type = Internals::JSON_STRING;
  _content.asString = value;
}

inline JsonVariant::JsonVariant(Internals::Unparsed value) {
  _type = Internals::JSON_UNPARSED;
  _content.asString = value;
}

inline JsonVariant::JsonVariant(double value, uint8_t decimals) {
  using namespace Internals;
  _type = static_cast<JsonVariantType>(JSON_FLOAT_0_DECIMALS + decimals);
  _content.asFloat = static_cast<JsonFloat>(value);
}

inline JsonVariant::JsonVariant(float value, uint8_t decimals) {
  using namespace Internals;
  _type = static_cast<JsonVariantType>(JSON_FLOAT_0_DECIMALS + decimals);
  _content.asFloat = static_cast<JsonFloat>(value);
}

inline JsonVariant::JsonVariant(JsonArray &array) {
  _type = Internals::JSON_ARRAY;
  _content.asArray = &array;
}

inline JsonVariant::JsonVariant(JsonObject &object) {
  _type = Internals::JSON_OBJECT;
  _content.asObject = &object;
}

template <typename T>
inline T JsonVariant::invalid() {
  return T();
}

template <typename T>
inline bool JsonVariant::is() const {
  return false;
}

template <>  // in .cpp
bool JsonVariant::is<signed long>() const;

template <>  // in .cpp
bool JsonVariant::is<double>() const;

template <>
inline bool JsonVariant::is<bool>() const {
  return _type == Internals::JSON_BOOLEAN;
}

template <>
inline bool JsonVariant::is<char const *>() const {
  return _type == Internals::JSON_STRING;
}

template <>
inline bool JsonVariant::is<float>() const {
  return is<double>();
}

template <>
inline bool JsonVariant::is<JsonArray &>() const {
  return _type == Internals::JSON_ARRAY;
}

template <>
inline bool JsonVariant::is<JsonArray const &>() const {
  return _type == Internals::JSON_ARRAY;
}

template <>
inline bool JsonVariant::is<JsonObject &>() const {
  return _type == Internals::JSON_OBJECT;
}

template <>
inline bool JsonVariant::is<JsonObject const &>() const {
  return _type == Internals::JSON_OBJECT;
}

template <>
inline bool JsonVariant::is<signed char>() const {
  return is<signed long>();
}

template <>
inline bool JsonVariant::is<signed int>() const {
  return is<signed long>();
}

template <>
inline bool JsonVariant::is<signed short>() const {
  return is<signed long>();
}

template <>
inline bool JsonVariant::is<unsigned char>() const {
  return is<signed long>();
}

template <>
inline bool JsonVariant::is<unsigned int>() const {
  return is<signed long>();
}

template <>
inline bool JsonVariant::is<unsigned long>() const {
  return is<signed long>();
}

template <>
inline bool JsonVariant::is<unsigned short>() const {
  return is<signed long>();
}

#ifdef ARDUINOJSON_ENABLE_STD_STREAM
inline std::ostream &operator<<(std::ostream &os, const JsonVariant &source) {
  return source.printTo(os);
}
#endif

}  // namespace ArduinoJson
