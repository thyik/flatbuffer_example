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

            Console.WriteLine("LotId : " + readMap.LotNum);
            Console.WriteLine("BinFormat : " + readMap.BincodeFormat);

            for (int i = 0; i < readMap.MapLength; i++)
            {
                Console.WriteLine(readMap.Map(i).ToString());
            }


            filename = @"D:\Temp\csharp.dat";
            // deserialize from file
            stream = File.OpenRead(filename);
            Console.WriteLine("Deserializing buffer");
            byte[] loadbuf = (byte[])formatter.Deserialize(stream);
            stream.Close();

            var loadBytebuf = new ByteBuffer(loadbuf);
            var loadMap = WaferMap.GetRootAsWaferMap(loadBytebuf);

            Console.WriteLine("LotId : " + loadMap.LotNum);

            // binary reader
            //filename = @"D:\Temp\output.dat";
            //// deserialize from file
            //BinaryReader reader = new BinaryReader(File.Open(@"D:\Temp\output.dat", FileMode.Open));
      
            //int length = (int)reader.BaseStream.Length;

            //Console.WriteLine("binary read buffer");
            //byte[] loadbinbuf = reader.ReadBytes(length);
            //reader.Close();

            //var loadbinBytebuf = new ByteBuffer(loadbinbuf);
            //var loadbinMap = WaferMap.GetRootAsWaferMap(loadbinBytebuf);

            //Console.WriteLine("LotId : " + loadbinMap.LotNum);
            //for (int i = 0; i < loadbinMap.MapLength; i++)
            //{
            //    Console.WriteLine(loadbinMap.Map(i).ToString());
            //}

            var test = new CTestIni();

            test.fn();


            //
            const int INT_SIZE = 4;
            const int DBL_SIZE = sizeof(double);
            double[] dblArray = { 1.999, 2.899, 3.933 };
            int[] arr = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
            byte[] byteData = new byte[INT_SIZE * 10];
            byte[] byteDbl = new byte[DBL_SIZE * 3];

            Buffer.BlockCopy(dblArray, 0, byteDbl, 0, DBL_SIZE * 3);
            //Buffer.BlockCopy(arr, 0, byteData, 0, INT_SIZE * 10);
            foreach (byte value in byteDbl)
                Console.Write("{0}  ", value);

            Console.Write("\n");

            int[] outBuf = new int [10];
            double[] dblBuf = new double[3];
            //Buffer.BlockCopy(byteData, 0, outBuf, 0, INT_SIZE * 10);
            Buffer.BlockCopy(byteDbl, 0, dblBuf, 0, DBL_SIZE * 3);
            foreach (double value in dblBuf)
                Console.Write("{0}  ", value);


            var watch = System.Diagnostics.Stopwatch.StartNew();
            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;
            ////
            //watch.Restart();

        }
    }
}
