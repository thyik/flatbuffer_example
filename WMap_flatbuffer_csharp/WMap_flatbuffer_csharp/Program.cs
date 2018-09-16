using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// for file serialize
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

using FlatBuffers;
using MitWMap;

namespace WMap_flatbuffer_csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            var builder = new FlatBufferBuilder(1);

            var waferid = builder.CreateString("TestWafer");
            var wnum = (short)1;
            var lotid = builder.CreateString("LotWafer");
            var binFormat = format.Hex;
            var data = new short[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            var map_info = WaferMap.CreateMapVector(builder, data);

            var mitMap = WaferMap.CreateWaferMap(builder, waferid, wnum, lotid, binFormat, map_info);

            builder.Finish(mitMap.Value);
            /// serialize to file
            /// 
            var filename = "D:\\Temp\\csharp.dat";
            FileStream stream = File.Create(filename);
            var formatter = new BinaryFormatter();
            Console.WriteLine("Serializing buffer");
            byte[] savebuf = builder.SizedByteArray();
            formatter.Serialize(stream, savebuf);
            stream.Close();

            // access read buffer
            var buf = builder.DataBuffer;

            // Get access to the root:
            var readMap = WaferMap.GetRootAsWaferMap(buf);

            Console.WriteLine("LotId : " + readMap.Lotid);
            Console.WriteLine("BinFormat : " + readMap.BinFormat);

            for (int i = 0; i < readMap.MapLength; i++)
            {
                Console.WriteLine(readMap.Map(i).ToString());
            }


            filename = "D:\\Temp\\csharp.dat";
            // deserialize from file
            stream = File.OpenRead(filename);
            Console.WriteLine("Deserializing buffer");
            byte[] loadbuf = (byte[])formatter.Deserialize(stream);
            stream.Close();

            var loadBytebuf = new ByteBuffer(loadbuf);
            var loadMap = WaferMap.GetRootAsWaferMap(loadBytebuf);

            Console.WriteLine("LotId : " + loadMap.Lotid);

            // binary reader
            filename = "D:\\Temp\\output.dat";
            // deserialize from file
            BinaryReader reader = new BinaryReader(File.Open(@"D:\\Temp\\output.dat", FileMode.Open));
      
            int length = (int)reader.BaseStream.Length;

            Console.WriteLine("binary read buffer");
            byte[] loadbinbuf = reader.ReadBytes(length);
            reader.Close();

            var loadbinBytebuf = new ByteBuffer(loadbinbuf);
            var loadbinMap = WaferMap.GetRootAsWaferMap(loadbinBytebuf);

            Console.WriteLine("LotId : " + loadbinMap.Lotid);
            for (int i = 0; i < loadbinMap.MapLength; i++)
            {
                Console.WriteLine(loadbinMap.Map(i).ToString());
            }

        }
    }
}
