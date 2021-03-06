// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace MitWMap
{

using global::System;
using global::FlatBuffers;

public struct WaferMap : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static WaferMap GetRootAsWaferMap(ByteBuffer _bb) { return GetRootAsWaferMap(_bb, new WaferMap()); }
  public static WaferMap GetRootAsWaferMap(ByteBuffer _bb, WaferMap obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public WaferMap __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int MaxRow { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int MaxCol { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public short Map(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.GetShort(__p.__vector(o) + j * 2) : (short)0; }
  public int MapLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetMapBytes() { return __p.__vector_as_span(8); }
#else
  public ArraySegment<byte>? GetMapBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public short[] GetMapArray() { return __p.__vector_as_array<short>(8); }
  public string WaferFab { get { int o = __p.__offset(10); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetWaferFabBytes() { return __p.__vector_as_span(10); }
#else
  public ArraySegment<byte>? GetWaferFabBytes() { return __p.__vector_as_arraysegment(10); }
#endif
  public byte[] GetWaferFabArray() { return __p.__vector_as_array<byte>(10); }
  public string FabCode { get { int o = __p.__offset(12); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetFabCodeBytes() { return __p.__vector_as_span(12); }
#else
  public ArraySegment<byte>? GetFabCodeBytes() { return __p.__vector_as_arraysegment(12); }
#endif
  public byte[] GetFabCodeArray() { return __p.__vector_as_array<byte>(12); }
  public string IntCode { get { int o = __p.__offset(14); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetIntCodeBytes() { return __p.__vector_as_span(14); }
#else
  public ArraySegment<byte>? GetIntCodeBytes() { return __p.__vector_as_arraysegment(14); }
#endif
  public byte[] GetIntCodeArray() { return __p.__vector_as_array<byte>(14); }
  public string LotNum { get { int o = __p.__offset(16); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetLotNumBytes() { return __p.__vector_as_span(16); }
#else
  public ArraySegment<byte>? GetLotNumBytes() { return __p.__vector_as_arraysegment(16); }
#endif
  public byte[] GetLotNumArray() { return __p.__vector_as_array<byte>(16); }
  public string Device { get { int o = __p.__offset(18); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetDeviceBytes() { return __p.__vector_as_span(18); }
#else
  public ArraySegment<byte>? GetDeviceBytes() { return __p.__vector_as_arraysegment(18); }
#endif
  public byte[] GetDeviceArray() { return __p.__vector_as_array<byte>(18); }
  public string DesignId { get { int o = __p.__offset(20); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetDesignIdBytes() { return __p.__vector_as_span(20); }
#else
  public ArraySegment<byte>? GetDesignIdBytes() { return __p.__vector_as_arraysegment(20); }
#endif
  public byte[] GetDesignIdArray() { return __p.__vector_as_array<byte>(20); }
  public string ScribId { get { int o = __p.__offset(22); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetScribIdBytes() { return __p.__vector_as_span(22); }
#else
  public ArraySegment<byte>? GetScribIdBytes() { return __p.__vector_as_arraysegment(22); }
#endif
  public byte[] GetScribIdArray() { return __p.__vector_as_array<byte>(22); }
  public string ScribLot { get { int o = __p.__offset(24); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetScribLotBytes() { return __p.__vector_as_span(24); }
#else
  public ArraySegment<byte>? GetScribLotBytes() { return __p.__vector_as_arraysegment(24); }
#endif
  public byte[] GetScribLotArray() { return __p.__vector_as_array<byte>(24); }
  public string WaferNum { get { int o = __p.__offset(26); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetWaferNumBytes() { return __p.__vector_as_span(26); }
#else
  public ArraySegment<byte>? GetWaferNumBytes() { return __p.__vector_as_arraysegment(26); }
#endif
  public byte[] GetWaferNumArray() { return __p.__vector_as_array<byte>(26); }
  public short MapId { get { int o = __p.__offset(28); return o != 0 ? __p.bb.GetShort(o + __p.bb_pos) : (short)0; } }
  public short NumRefDie { get { int o = __p.__offset(30); return o != 0 ? __p.bb.GetShort(o + __p.bb_pos) : (short)0; } }
  public stXY? RefDie(int j) { int o = __p.__offset(32); return o != 0 ? (stXY?)(new stXY()).__assign(__p.__vector(o) + j * 8, __p.bb) : null; }
  public int RefDieLength { get { int o = __p.__offset(32); return o != 0 ? __p.__vector_len(o) : 0; } }
  public short RefChipDir { get { int o = __p.__offset(34); return o != 0 ? __p.bb.GetShort(o + __p.bb_pos) : (short)0; } }
  public short RefNotch { get { int o = __p.__offset(36); return o != 0 ? __p.bb.GetShort(o + __p.bb_pos) : (short)0; } }
  public stXY? StartLoc { get { int o = __p.__offset(38); return o != 0 ? (stXY?)(new stXY()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public short NullBin { get { int o = __p.__offset(40); return o != 0 ? __p.bb.GetShort(o + __p.bb_pos) : (short)0; } }
  public float DieSizeX { get { int o = __p.__offset(42); return o != 0 ? __p.bb.GetFloat(o + __p.bb_pos) : (float)0.0f; } }
  public float DieSizeY { get { int o = __p.__offset(44); return o != 0 ? __p.bb.GetFloat(o + __p.bb_pos) : (float)0.0f; } }
  public short DegRotated { get { int o = __p.__offset(46); return o != 0 ? __p.bb.GetShort(o + __p.bb_pos) : (short)0; } }
  public format BincodeFormat { get { int o = __p.__offset(48); return o != 0 ? (format)__p.bb.GetSbyte(o + __p.bb_pos) : format.Ascii; } }

  public static void StartWaferMap(FlatBufferBuilder builder) { builder.StartObject(23); }
  public static void AddMaxRow(FlatBufferBuilder builder, int maxRow) { builder.AddInt(0, maxRow, 0); }
  public static void AddMaxCol(FlatBufferBuilder builder, int maxCol) { builder.AddInt(1, maxCol, 0); }
  public static void AddMap(FlatBufferBuilder builder, VectorOffset mapOffset) { builder.AddOffset(2, mapOffset.Value, 0); }
  public static VectorOffset CreateMapVector(FlatBufferBuilder builder, short[] data) { builder.StartVector(2, data.Length, 2); for (int i = data.Length - 1; i >= 0; i--) builder.AddShort(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateMapVectorBlock(FlatBufferBuilder builder, short[] data) { builder.StartVector(2, data.Length, 2); builder.Add(data); return builder.EndVector(); }
  public static void StartMapVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(2, numElems, 2); }
  public static void AddWaferFab(FlatBufferBuilder builder, StringOffset waferFabOffset) { builder.AddOffset(3, waferFabOffset.Value, 0); }
  public static void AddFabCode(FlatBufferBuilder builder, StringOffset fabCodeOffset) { builder.AddOffset(4, fabCodeOffset.Value, 0); }
  public static void AddIntCode(FlatBufferBuilder builder, StringOffset intCodeOffset) { builder.AddOffset(5, intCodeOffset.Value, 0); }
  public static void AddLotNum(FlatBufferBuilder builder, StringOffset lotNumOffset) { builder.AddOffset(6, lotNumOffset.Value, 0); }
  public static void AddDevice(FlatBufferBuilder builder, StringOffset deviceOffset) { builder.AddOffset(7, deviceOffset.Value, 0); }
  public static void AddDesignId(FlatBufferBuilder builder, StringOffset designIdOffset) { builder.AddOffset(8, designIdOffset.Value, 0); }
  public static void AddScribId(FlatBufferBuilder builder, StringOffset scribIdOffset) { builder.AddOffset(9, scribIdOffset.Value, 0); }
  public static void AddScribLot(FlatBufferBuilder builder, StringOffset scribLotOffset) { builder.AddOffset(10, scribLotOffset.Value, 0); }
  public static void AddWaferNum(FlatBufferBuilder builder, StringOffset waferNumOffset) { builder.AddOffset(11, waferNumOffset.Value, 0); }
  public static void AddMapId(FlatBufferBuilder builder, short mapId) { builder.AddShort(12, mapId, 0); }
  public static void AddNumRefDie(FlatBufferBuilder builder, short numRefDie) { builder.AddShort(13, numRefDie, 0); }
  public static void AddRefDie(FlatBufferBuilder builder, VectorOffset refDieOffset) { builder.AddOffset(14, refDieOffset.Value, 0); }
  public static void StartRefDieVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(8, numElems, 4); }
  public static void AddRefChipDir(FlatBufferBuilder builder, short refChipDir) { builder.AddShort(15, refChipDir, 0); }
  public static void AddRefNotch(FlatBufferBuilder builder, short refNotch) { builder.AddShort(16, refNotch, 0); }
  public static void AddStartLoc(FlatBufferBuilder builder, Offset<stXY> startLocOffset) { builder.AddStruct(17, startLocOffset.Value, 0); }
  public static void AddNullBin(FlatBufferBuilder builder, short nullBin) { builder.AddShort(18, nullBin, 0); }
  public static void AddDieSizeX(FlatBufferBuilder builder, float dieSizeX) { builder.AddFloat(19, dieSizeX, 0.0f); }
  public static void AddDieSizeY(FlatBufferBuilder builder, float dieSizeY) { builder.AddFloat(20, dieSizeY, 0.0f); }
  public static void AddDegRotated(FlatBufferBuilder builder, short degRotated) { builder.AddShort(21, degRotated, 0); }
  public static void AddBincodeFormat(FlatBufferBuilder builder, format bincodeFormat) { builder.AddSbyte(22, (sbyte)bincodeFormat, 1); }
  public static Offset<WaferMap> EndWaferMap(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<WaferMap>(o);
  }
  public static void FinishWaferMapBuffer(FlatBufferBuilder builder, Offset<WaferMap> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedWaferMapBuffer(FlatBufferBuilder builder, Offset<WaferMap> offset) { builder.FinishSizePrefixed(offset.Value); }
};


}
