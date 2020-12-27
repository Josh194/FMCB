package main.java.item;

import main.java.init.ModItems;
import net.minecraft.creativetab.CreativeTabs;
import net.minecraft.item.Item;

public class ItemGeneral extends Item {

    public ItemGeneral (String name){
        setUnlocalizedName(name);
        setRegistryName(name);
        
        setCreativeTab(CreativeTabs.FOOD);
        
		ModItems.items.add(this);
    }

}
