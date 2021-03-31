package fmcb.item;

import fmcb.init.ModItems;
import net.minecraft.creativetab.CreativeTabs;
import net.minecraft.item.Item;

public class ItemGeneral extends Item {

    public ItemGeneral (String name){
    	super();
    	
        setUnlocalizedName(name);
        setRegistryName(name);
        
        setCreativeTab(CreativeTabs.FOOD);
        
		ModItems.items.add(this);
    }

}
