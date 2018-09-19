// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_LOTINFOARM_LOTINFO_ARM_H_
#define FLATBUFFERS_GENERATED_LOTINFOARM_LOTINFO_ARM_H_

#include "flatbuffers/flatbuffers.h"

namespace lotinfo_arm {

struct ARM_RECORD;

struct ARM;

struct ARM_RECORD FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_FIELDNAME = 4,
    VT_STATS = 6
  };
  const flatbuffers::String *fieldname() const {
    return GetPointer<const flatbuffers::String *>(VT_FIELDNAME);
  }
  const flatbuffers::Vector<flatbuffers::Offset<ARM>> *stats() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<ARM>> *>(VT_STATS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_FIELDNAME) &&
           verifier.VerifyString(fieldname()) &&
           VerifyOffset(verifier, VT_STATS) &&
           verifier.VerifyVector(stats()) &&
           verifier.VerifyVectorOfTables(stats()) &&
           verifier.EndTable();
  }
};

struct ARM_RECORDBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_fieldname(flatbuffers::Offset<flatbuffers::String> fieldname) {
    fbb_.AddOffset(ARM_RECORD::VT_FIELDNAME, fieldname);
  }
  void add_stats(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ARM>>> stats) {
    fbb_.AddOffset(ARM_RECORD::VT_STATS, stats);
  }
  explicit ARM_RECORDBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ARM_RECORDBuilder &operator=(const ARM_RECORDBuilder &);
  flatbuffers::Offset<ARM_RECORD> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ARM_RECORD>(end);
    return o;
  }
};

inline flatbuffers::Offset<ARM_RECORD> CreateARM_RECORD(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> fieldname = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<ARM>>> stats = 0) {
  ARM_RECORDBuilder builder_(_fbb);
  builder_.add_stats(stats);
  builder_.add_fieldname(fieldname);
  return builder_.Finish();
}

inline flatbuffers::Offset<ARM_RECORD> CreateARM_RECORDDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *fieldname = nullptr,
    const std::vector<flatbuffers::Offset<ARM>> *stats = nullptr) {
  return lotinfo_arm::CreateARM_RECORD(
      _fbb,
      fieldname ? _fbb.CreateString(fieldname) : 0,
      stats ? _fbb.CreateVector<flatbuffers::Offset<ARM>>(*stats) : 0);
}

struct ARM FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_PASS = 4,
    VT_FAIL = 6,
    VT_LOST = 8,
    VT_TOTAL = 10,
    VT_YIELD = 12
  };
  int64_t pass() const {
    return GetField<int64_t>(VT_PASS, 0);
  }
  int64_t fail() const {
    return GetField<int64_t>(VT_FAIL, 0);
  }
  int64_t lost() const {
    return GetField<int64_t>(VT_LOST, 0);
  }
  int64_t total() const {
    return GetField<int64_t>(VT_TOTAL, 0);
  }
  float yield() const {
    return GetField<float>(VT_YIELD, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int64_t>(verifier, VT_PASS) &&
           VerifyField<int64_t>(verifier, VT_FAIL) &&
           VerifyField<int64_t>(verifier, VT_LOST) &&
           VerifyField<int64_t>(verifier, VT_TOTAL) &&
           VerifyField<float>(verifier, VT_YIELD) &&
           verifier.EndTable();
  }
};

struct ARMBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pass(int64_t pass) {
    fbb_.AddElement<int64_t>(ARM::VT_PASS, pass, 0);
  }
  void add_fail(int64_t fail) {
    fbb_.AddElement<int64_t>(ARM::VT_FAIL, fail, 0);
  }
  void add_lost(int64_t lost) {
    fbb_.AddElement<int64_t>(ARM::VT_LOST, lost, 0);
  }
  void add_total(int64_t total) {
    fbb_.AddElement<int64_t>(ARM::VT_TOTAL, total, 0);
  }
  void add_yield(float yield) {
    fbb_.AddElement<float>(ARM::VT_YIELD, yield, 0.0f);
  }
  explicit ARMBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ARMBuilder &operator=(const ARMBuilder &);
  flatbuffers::Offset<ARM> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ARM>(end);
    return o;
  }
};

inline flatbuffers::Offset<ARM> CreateARM(
    flatbuffers::FlatBufferBuilder &_fbb,
    int64_t pass = 0,
    int64_t fail = 0,
    int64_t lost = 0,
    int64_t total = 0,
    float yield = 0.0f) {
  ARMBuilder builder_(_fbb);
  builder_.add_total(total);
  builder_.add_lost(lost);
  builder_.add_fail(fail);
  builder_.add_pass(pass);
  builder_.add_yield(yield);
  return builder_.Finish();
}

inline const lotinfo_arm::ARM_RECORD *GetARM_RECORD(const void *buf) {
  return flatbuffers::GetRoot<lotinfo_arm::ARM_RECORD>(buf);
}

inline const lotinfo_arm::ARM_RECORD *GetSizePrefixedARM_RECORD(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<lotinfo_arm::ARM_RECORD>(buf);
}

inline bool VerifyARM_RECORDBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<lotinfo_arm::ARM_RECORD>(nullptr);
}

inline bool VerifySizePrefixedARM_RECORDBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<lotinfo_arm::ARM_RECORD>(nullptr);
}

inline void FinishARM_RECORDBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<lotinfo_arm::ARM_RECORD> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedARM_RECORDBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<lotinfo_arm::ARM_RECORD> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace lotinfo_arm

#endif  // FLATBUFFERS_GENERATED_LOTINFOARM_LOTINFO_ARM_H_
