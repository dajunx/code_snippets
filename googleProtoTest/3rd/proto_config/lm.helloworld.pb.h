// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: lm.helloworld.proto

#ifndef PROTOBUF_lm_2ehelloworld_2eproto__INCLUDED
#define PROTOBUF_lm_2ehelloworld_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace lm {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_lm_2ehelloworld_2eproto();
void protobuf_AssignDesc_lm_2ehelloworld_2eproto();
void protobuf_ShutdownFile_lm_2ehelloworld_2eproto();

class am_broadcast_raw_data_to_channel;
class am_dispatch_raw_datas;

// ===================================================================

class am_broadcast_raw_data_to_channel : public ::google::protobuf::Message {
 public:
  am_broadcast_raw_data_to_channel();
  virtual ~am_broadcast_raw_data_to_channel();
  
  am_broadcast_raw_data_to_channel(const am_broadcast_raw_data_to_channel& from);
  
  inline am_broadcast_raw_data_to_channel& operator=(const am_broadcast_raw_data_to_channel& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const am_broadcast_raw_data_to_channel& default_instance();
  
  void Swap(am_broadcast_raw_data_to_channel* other);
  
  // implements Message ----------------------------------------------
  
  am_broadcast_raw_data_to_channel* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const am_broadcast_raw_data_to_channel& from);
  void MergeFrom(const am_broadcast_raw_data_to_channel& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 msg_id = 1;
  inline bool has_msg_id() const;
  inline void clear_msg_id();
  static const int kMsgIdFieldNumber = 1;
  inline ::google::protobuf::uint32 msg_id() const;
  inline void set_msg_id(::google::protobuf::uint32 value);
  
  // required uint64 top_channel_id = 2;
  inline bool has_top_channel_id() const;
  inline void clear_top_channel_id();
  static const int kTopChannelIdFieldNumber = 2;
  inline ::google::protobuf::uint64 top_channel_id() const;
  inline void set_top_channel_id(::google::protobuf::uint64 value);
  
  // @@protoc_insertion_point(class_scope:lm.am_broadcast_raw_data_to_channel)
 private:
  inline void set_has_msg_id();
  inline void clear_has_msg_id();
  inline void set_has_top_channel_id();
  inline void clear_has_top_channel_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint64 top_channel_id_;
  ::google::protobuf::uint32 msg_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_lm_2ehelloworld_2eproto();
  friend void protobuf_AssignDesc_lm_2ehelloworld_2eproto();
  friend void protobuf_ShutdownFile_lm_2ehelloworld_2eproto();
  
  void InitAsDefaultInstance();
  static am_broadcast_raw_data_to_channel* default_instance_;
};
// -------------------------------------------------------------------

class am_dispatch_raw_datas : public ::google::protobuf::Message {
 public:
  am_dispatch_raw_datas();
  virtual ~am_dispatch_raw_datas();
  
  am_dispatch_raw_datas(const am_dispatch_raw_datas& from);
  
  inline am_dispatch_raw_datas& operator=(const am_dispatch_raw_datas& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const am_dispatch_raw_datas& default_instance();
  
  void Swap(am_dispatch_raw_datas* other);
  
  // implements Message ----------------------------------------------
  
  am_dispatch_raw_datas* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const am_dispatch_raw_datas& from);
  void MergeFrom(const am_dispatch_raw_datas& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional uint32 msg_id = 1;
  inline bool has_msg_id() const;
  inline void clear_msg_id();
  static const int kMsgIdFieldNumber = 1;
  inline ::google::protobuf::uint32 msg_id() const;
  inline void set_msg_id(::google::protobuf::uint32 value);
  
  // optional bytes datas = 2;
  inline bool has_datas() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 2;
  inline const ::std::string& datas() const;
  inline void set_datas(const ::std::string& value);
  inline void set_datas(const char* value);
  inline void set_datas(const void* value, size_t size);
  inline ::std::string* mutable_datas();
  inline ::std::string* release_datas();
  
  // @@protoc_insertion_point(class_scope:lm.am_dispatch_raw_datas)
 private:
  inline void set_has_msg_id();
  inline void clear_has_msg_id();
  inline void set_has_datas();
  inline void clear_has_datas();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* datas_;
  ::google::protobuf::uint32 msg_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_lm_2ehelloworld_2eproto();
  friend void protobuf_AssignDesc_lm_2ehelloworld_2eproto();
  friend void protobuf_ShutdownFile_lm_2ehelloworld_2eproto();
  
  void InitAsDefaultInstance();
  static am_dispatch_raw_datas* default_instance_;
};
// ===================================================================


// ===================================================================

// am_broadcast_raw_data_to_channel

// required uint32 msg_id = 1;
inline bool am_broadcast_raw_data_to_channel::has_msg_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void am_broadcast_raw_data_to_channel::set_has_msg_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void am_broadcast_raw_data_to_channel::clear_has_msg_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void am_broadcast_raw_data_to_channel::clear_msg_id() {
  msg_id_ = 0u;
  clear_has_msg_id();
}
inline ::google::protobuf::uint32 am_broadcast_raw_data_to_channel::msg_id() const {
  return msg_id_;
}
inline void am_broadcast_raw_data_to_channel::set_msg_id(::google::protobuf::uint32 value) {
  set_has_msg_id();
  msg_id_ = value;
}

// required uint64 top_channel_id = 2;
inline bool am_broadcast_raw_data_to_channel::has_top_channel_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void am_broadcast_raw_data_to_channel::set_has_top_channel_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void am_broadcast_raw_data_to_channel::clear_has_top_channel_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void am_broadcast_raw_data_to_channel::clear_top_channel_id() {
  top_channel_id_ = GOOGLE_ULONGLONG(0);
  clear_has_top_channel_id();
}
inline ::google::protobuf::uint64 am_broadcast_raw_data_to_channel::top_channel_id() const {
  return top_channel_id_;
}
inline void am_broadcast_raw_data_to_channel::set_top_channel_id(::google::protobuf::uint64 value) {
  set_has_top_channel_id();
  top_channel_id_ = value;
}

// -------------------------------------------------------------------

// am_dispatch_raw_datas

// optional uint32 msg_id = 1;
inline bool am_dispatch_raw_datas::has_msg_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void am_dispatch_raw_datas::set_has_msg_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void am_dispatch_raw_datas::clear_has_msg_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void am_dispatch_raw_datas::clear_msg_id() {
  msg_id_ = 0u;
  clear_has_msg_id();
}
inline ::google::protobuf::uint32 am_dispatch_raw_datas::msg_id() const {
  return msg_id_;
}
inline void am_dispatch_raw_datas::set_msg_id(::google::protobuf::uint32 value) {
  set_has_msg_id();
  msg_id_ = value;
}

// optional bytes datas = 2;
inline bool am_dispatch_raw_datas::has_datas() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void am_dispatch_raw_datas::set_has_datas() {
  _has_bits_[0] |= 0x00000002u;
}
inline void am_dispatch_raw_datas::clear_has_datas() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void am_dispatch_raw_datas::clear_datas() {
  if (datas_ != &::google::protobuf::internal::kEmptyString) {
    datas_->clear();
  }
  clear_has_datas();
}
inline const ::std::string& am_dispatch_raw_datas::datas() const {
  return *datas_;
}
inline void am_dispatch_raw_datas::set_datas(const ::std::string& value) {
  set_has_datas();
  if (datas_ == &::google::protobuf::internal::kEmptyString) {
    datas_ = new ::std::string;
  }
  datas_->assign(value);
}
inline void am_dispatch_raw_datas::set_datas(const char* value) {
  set_has_datas();
  if (datas_ == &::google::protobuf::internal::kEmptyString) {
    datas_ = new ::std::string;
  }
  datas_->assign(value);
}
inline void am_dispatch_raw_datas::set_datas(const void* value, size_t size) {
  set_has_datas();
  if (datas_ == &::google::protobuf::internal::kEmptyString) {
    datas_ = new ::std::string;
  }
  datas_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* am_dispatch_raw_datas::mutable_datas() {
  set_has_datas();
  if (datas_ == &::google::protobuf::internal::kEmptyString) {
    datas_ = new ::std::string;
  }
  return datas_;
}
inline ::std::string* am_dispatch_raw_datas::release_datas() {
  clear_has_datas();
  if (datas_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = datas_;
    datas_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace lm

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_lm_2ehelloworld_2eproto__INCLUDED