using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;

using FlatBuffers;
using MitMAP;

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

            var mapdata = MAP.CreateMapVector(builder, data);

            MAP.StartTargetDieVector(builder, 2);
            stXY.CreatestXY(builder, 22, 25);
            stXY.CreatestXY(builder, 23, 25);
            var vecTargetDie = builder.EndVector();

            MAP.StartRefDieVector(builder, 2);
            stXY.CreatestXY(builder, 1, 5);
            stXY.CreatestXY(builder, 2, 5);
            var vecRefDie = builder.EndVector();

            //var vecRefDie = builder.CreateVectors(refDieOffset);
      
            MAP.StartMAP(builder);
            MAP.AddMaxCol(builder, 5);
            MAP.AddMaxRow(builder, 2);
            MAP.AddMap(builder, mapdata);

            MAP.AddTargetDie(builder, vecTargetDie);

            MAP.AddRefDie(builder, vecRefDie);

            MAP.AddLotNum(builder, lotid);
            MAP.AddBincodeFormat(builder, binFormat);

            var mitMap = MAP.EndMAP(builder);

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
            var loadbinMap = MAP.GetRootAsMAP(loadbinBytebuf);

            short [] MapData = loadbinMap.GetMapArray();
            Console.WriteLine("LotId : " + loadbinMap.LotNum);

            Console.WriteLine("RefDie0 : " + loadbinMap.RefDie(0).Value.X.ToString() + "," + loadbinMap.RefDie(0).Value.Y.ToString());
            Console.WriteLine("RefDie1 : " + loadbinMap.RefDie(1).Value.X.ToString() + "," + loadbinMap.RefDie(1).Value.Y.ToString());

            Console.WriteLine("TargetDie0 : " + loadbinMap.TargetDie(0).Value.X.ToString() + "," + loadbinMap.TargetDie(0).Value.Y.ToString());
            Console.WriteLine("TargetDie1 : " + loadbinMap.TargetDie(1).Value.X.ToString() + "," + loadbinMap.TargetDie(1).Value.Y.ToString());

            for (int i = 0; i < loadbinMap.MapLength; i++)
            {
                Console.WriteLine(loadbinMap.Map(i).ToString());
            }

            return true;
        }
    }
}
