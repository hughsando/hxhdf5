package hdf5;

import hdf5.ItemType;

class Group
{
   var handle:Dynamic;

   public var itemCount(get,null):Int;
   public var attribs(get,null):Dynamic;


   function new(inHandle:Dynamic) handle = inHandle;

   public function getAttributes(path:String = "."):Dynamic
   {
      return groupGetAttributes(handle,path);
   }

   function get_attribs() return getAttributes();

   public function getItemsRecurse() : Array<Item>
   {
      var vals:Array<Dynamic> = groupGetAllChildren(handle);
      var result = new Array<Item>();
      for(item in vals)
         result.push(anonToItem(item));
      return result;
   }

   function anonToItem(item:Dynamic) : Item
   {
      var type = switch(item.type)
      {
         case 0: GroupItem;
         case 1: DatasetItem;
         case 2: TypeItem;
         case 3: LinkItem;
         case 4: UserLinkItem;
         default:
            UnknownItem;
      }
      return new Item(this, item.name, type);
   }

   public function openDataset(inPath:String) : Dataset
   {
      return new Dataset(inPath, groupOpenDataset(handle, inPath) );
   }

   public function getItem(i:Int) : Item
   {
      var item = groupGetItemAt(handle,i);
      return anonToItem(item);
   }

   function get_itemCount() : Int return groupGetItemCount(handle);


   static var groupGetItemAt = Loader.load("groupGetItemAt","oio");
   static var groupGetItemCount = Loader.load("groupGetItemCount","oi");
   static var groupGetAllChildren = Loader.load("groupGetAllChildren","oo");
   static var groupGetAttributes = Loader.load("groupGetAttributes","oso");
   static var groupOpenDataset = Loader.load("groupOpenDataset","oso");
}

