// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: AgentCommandMsg.capnp

#ifndef CAPNP_INCLUDED_d6da624da6f5faee_
#define CAPNP_INCLUDED_d6da624da6f5faee_

#include <capnp/generated-header-support.h>

#if CAPNP_VERSION != 6001
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif

#include <capnzero/ID.capnp.h>

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(a1be158cb99fb677);
CAPNP_DECLARE_SCHEMA(da1644efbb3f711e);
CAPNP_DECLARE_SCHEMA(c71410885ec9a782);

}  // namespace schemas
}  // namespace capnp

namespace control {

struct AgentCommandMsg {
  AgentCommandMsg() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  static constexpr  ::uint8_t START = 0u;
  static constexpr  ::uint8_t STOP = 1u;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(a1be158cb99fb677, 1, 1)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class AgentCommandMsg::Reader {
public:
  typedef AgentCommandMsg Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline bool hasReceiverId() const;
  inline  ::capnzero::ID::Reader getReceiverId() const;

  inline  ::uint8_t getCmd() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class AgentCommandMsg::Builder {
public:
  typedef AgentCommandMsg Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool hasReceiverId();
  inline  ::capnzero::ID::Builder getReceiverId();
  inline void setReceiverId( ::capnzero::ID::Reader value);
  inline  ::capnzero::ID::Builder initReceiverId();
  inline void adoptReceiverId(::capnp::Orphan< ::capnzero::ID>&& value);
  inline ::capnp::Orphan< ::capnzero::ID> disownReceiverId();

  inline  ::uint8_t getCmd();
  inline void setCmd( ::uint8_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class AgentCommandMsg::Pipeline {
public:
  typedef AgentCommandMsg Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::capnzero::ID::Pipeline getReceiverId();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline bool AgentCommandMsg::Reader::hasReceiverId() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool AgentCommandMsg::Builder::hasReceiverId() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::capnzero::ID::Reader AgentCommandMsg::Reader::getReceiverId() const {
  return ::capnp::_::PointerHelpers< ::capnzero::ID>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::capnzero::ID::Builder AgentCommandMsg::Builder::getReceiverId() {
  return ::capnp::_::PointerHelpers< ::capnzero::ID>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::capnzero::ID::Pipeline AgentCommandMsg::Pipeline::getReceiverId() {
  return  ::capnzero::ID::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void AgentCommandMsg::Builder::setReceiverId( ::capnzero::ID::Reader value) {
  ::capnp::_::PointerHelpers< ::capnzero::ID>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::capnzero::ID::Builder AgentCommandMsg::Builder::initReceiverId() {
  return ::capnp::_::PointerHelpers< ::capnzero::ID>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void AgentCommandMsg::Builder::adoptReceiverId(
    ::capnp::Orphan< ::capnzero::ID>&& value) {
  ::capnp::_::PointerHelpers< ::capnzero::ID>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnzero::ID> AgentCommandMsg::Builder::disownReceiverId() {
  return ::capnp::_::PointerHelpers< ::capnzero::ID>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::uint8_t AgentCommandMsg::Reader::getCmd() const {
  return _reader.getDataField< ::uint8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint8_t AgentCommandMsg::Builder::getCmd() {
  return _builder.getDataField< ::uint8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void AgentCommandMsg::Builder::setCmd( ::uint8_t value) {
  _builder.setDataField< ::uint8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

}  // namespace

#endif  // CAPNP_INCLUDED_d6da624da6f5faee_