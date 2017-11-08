package hdf5;

import hdf5.Item;

class Group
{
   var handle:Dynamic;

   public var itemCount(get,null):Int;

   function new(inHandle:Dynamic) handle = inHandle;

   public function getAttributes(path:String = "."):Dynamic
   {
      return groupGetAttributes(handle,path);
   }

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
      return switch(item.type)
      {
         case 0: GroupItem(item.name);
         case 1: DatasetItem(item.name);
         case 2: TypeItem(item.name);
         case 3: LinkItem(item.name);
         case 4: UserLinkItem(item.name);
         default:
            UnknownItem(item.name);
      }
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
}

