package hdf5;

class Dataset
{
   public var name(default,null):String;
   public var shape(get,null):Array<Int>;
   public var type(get,null):Int;
   public var typename(get,null):String;

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

   function get_shape() : Array<Int>
   {
      var d:Dynamic = datasetGetShape(handle);
      return d;
   }

   function get_type() : Int
   {
      return datasetGetType(handle);
   }

   function get_typename() : String
   {
      return DataType.string(datasetGetType(handle));
   }


   static var datasetClose = Loader.load("datasetClose","ov");
   static var datasetGetShape = Loader.load("datasetGetShape","oo");
   static var datasetGetType = Loader.load("datasetGetType","oi");
}

