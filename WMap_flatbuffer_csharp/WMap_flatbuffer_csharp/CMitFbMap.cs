using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;

using FlatBuffers;
using MitWMap;

namespace WMap_flatbuffer_csharp
{
    class CMitFbMap
    {
        public CMitFbMap()
        {

        }

        public bool Write(string filename, short [] data)
        {
            var builder = new FlatBufferBuilder(1);

            var waferid = builder.CreateString("TestWafer");
            var wnum = (short)1;
            var lotid = builder.CreateString("LotWafer");
            var binFormat = format.Hex;

            var mapdata = WaferMap.CreateMapVector(builder, data);

            WaferMap.StartWaferMap(builder);
            WaferMap.AddMap(builder, mapdata);
            WaferMap.AddMaxCol(builder, 5);
            WaferMap.AddMaxRow(builder, 2);

            WaferMap.AddLotNum(builder, lotid);
            WaferMap.AddBincodeFormat(builder, binFormat);
            
            var mitMap = WaferMap.EndWaferMap(builder);

            builder.Finish(mitMap.Value);

            /// serialize to file
            /// 
            BinaryWriter writer = new BinaryWriter(File.Open(filename, FileMode.CreateNew | FileMode.Truncate));

            byte[] savebuf = builder.SizedByteArray();
            writer.Write(savebuf);

            writer.Close();

            return true;
        }

        public bool Read(string filename)
        {

            // binary reader
            //// deserialize from file
            BinaryReader reader = new BinaryReader(File.Open(filename, FileMode.Open));

            int length = (int)reader.BaseStream.Length;

            //Console.WriteLine("binary read buffer");
            byte[] loadbinbuf = reader.ReadBytes(length);
            reader.Close();

            var loadbinBytebuf = new ByteBuffer(loadbinbuf);
            var loadbinMap = WaferMap.GetRootAsWaferMap(loadbinBytebuf);

            Console.WriteLine("LotId : " + loadbinMap.LotNum);
            for (int i = 0; i < loadbinMap.MapLength; i++)
            {
                Console.WriteLine(loadbinMap.Map(i).ToString());
            }

            return true;
        }
    }
}
