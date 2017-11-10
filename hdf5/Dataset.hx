package hdf5;

import haxe.io.Bytes;

class Dataset
{
   public var name(default,null):String;
   public var shape(get,null):Array<Int>;
   public var elementCount(get,null):Int;
   public var type(get,null):Int;
   public var typename(get,null):String;
   public var elementSize(get,null):Int;

   var handle:Dynamic;

   public function new(inName:String, inHandle:Dynamic)
   {
      name = inName;
      handle = inHandle;
   }

   public function close()
   {
      if (handle!=null)
      {
         datasetClose(handle);
         handle = null;
      }
   }

   public function readData(inDataType:Int) : Bytes
   {
      var elemSize = DataType.size(inDataType);
      if (elemSize<=0)
         throw "Can't readData of type " + DataType.string(inDataType);
      var byteCount = elementCount * elemSize;
      var result = Bytes.alloc(byteCount);
      datasetReadData(handle,inDataType, result);
      return result;
   }

   public function fillData(buffer:Dynamic, inDataType:Int):Void
   {
      datasetReadData(handle,inDataType, buffer);
   }


   function get_shape() : Array<Int>
   {
      var d:Dynamic = datasetGetShape(handle);
      return d;
   }

   function get_type() : Int
   {
      return datasetGetType(handle);
   }

   function get_elementSize() : Int
   {
      return DataType.size( datasetGetType(handle) );
   }

   function get_size() : Int  return datasetGetSize(handle);
   function get_elementCount() : Int  return datasetGetSize(handle);


   function get_typename() : String
   {
      return DataType.string(datasetGetType(handle));
   }


   static var datasetClose = Loader.load("datasetClose","ov");
   static var datasetGetShape = Loader.load("datasetGetShape","oo");
   static var datasetGetSize = Loader.load("datasetGetSize","oi");
   static var datasetGetType = Loader.load("datasetGetType","oi");
   static var datasetReadData = Loader.load("datasetReadData","oiov");
}

