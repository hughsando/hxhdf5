package hdf5;

import hdf5.ItemType;

class Item
{
   public var parent(default,null):Group;
   public var path(default,null):String;
   public var type(default,null):ItemType;

   public var attribs(get,null):Dynamic;

   public function new(inParent:Group, inPath:String, inType:ItemType)
   {
      parent = inParent;
      path = inPath;
      type = inType;
   }

   public function openDataset() : Dataset
   {
      if (type!=DatasetItem)
         throw "openDataset - type is not a dataset";
      return parent.openDataset(path);
   }

   //public function openGroup() : Group
   //{
   //   return parent.openGroup(path);
   //}

   function get_attribs():Dynamic
   {
      return parent.getAttributes(path);
   }

   public function toString() return '$type($path)';

}


