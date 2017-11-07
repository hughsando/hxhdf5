package hdf5;

enum Item
{
   GroupItem(name:String);
   DatasetItem(name:String);
   TypeItem(name:String);
   LinkItem(name:String);
   UserLinkItem(name:String);
   UnknownItem(name:String);
}


